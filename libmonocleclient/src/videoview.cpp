// videoview.cpp
//

///// Includes /////

#include "monocleclient/videoview.h"

#include <boost/algorithm/string.hpp>
#include <boost/algorithm/string/predicate.hpp>
#include <boost/asio/ip/address.hpp>
#include <boost/bind.hpp>
#include <onvifclient/deviceclient.hpp>
#include <onvifclient/eventclient.hpp>
#include <onvifclient/mediaclient.hpp>
#include <onvifclient/ptzclient.hpp>
#include <network/uri.hpp>
#include <QFileDialog>
#include <QMessageBox>
#include <QPainter>
#include <QResource>
#include <QStandardPaths>
#include <QUrl>
#include <utility/utility.hpp>

#include "monocleclient/device.h"
#include "monocleclient/h265decoder.h"
#include "monocleclient/h264decoder.h"
#include "monocleclient/mainwindow.h"
#include "monocleclient/mjpegdecoder.h"
#include "monocleclient/mpeg4decoder.h"
#include "monocleclient/receiver.h"
#include "monocleclient/recording.h"
#include "monocleclient/recordingjob.h"
#include "monocleclient/videowidget.h"
#include "monocleclient/videoviewpropertieswindow.h"
#include "monocleclient/view.h"

///// Namespaces /////

namespace client
{

///// Methods /////

VideoView::VideoView(VideoWidget* videowidget, const QColor& selectedcolour, const unsigned int x, const unsigned int y, const unsigned int width, const unsigned int height, const ROTATION rotation, const bool mirror, const bool stretch, const bool info, boost::shared_ptr<client::Device> device, QSharedPointer<client::Recording> recording, QSharedPointer<client::RecordingTrack> track, const QResource* arial) :
  View(videowidget, selectedcolour, x, y, width, height, rotation, mirror, stretch, info, arial, true, true, true),
  device_(device),
  recording_(recording),
  track_(track),
  actionreconnect_(new QAction(tr("Reconnect"), this)),
  actionproperties_(new QAction(tr("Properties"), this)),
  connection_(boost::make_shared<Connection>(MainWindow::Instance()->GetIOServicePool().GetIoService(), device_->GetProxyParams(), device_->GetAddress(), device_->GetPort())),
  streamtoken_(0)
{
  connect(actionreconnect_, &QAction::triggered, this, static_cast<void (VideoView::*)(bool)>(&VideoView::Reconnect));
  connect(actionproperties_, &QAction::triggered, this, static_cast<void (VideoView::*)(bool)>(&VideoView::Properties));
  connect(device_.get(), &Device::SignalStateChanged, this, &VideoView::DeviceStateChanged);
  connect(recording_.get(), &Recording::TrackAdded, this, &VideoView::TrackAdded);
  connect(recording_.get(), &Recording::TrackRemoved, this, &VideoView::TrackRemoved);
  connect(recording_.get(), &Recording::ActiveJobChanged, this, &VideoView::ActiveJobChanged);

  rotation_ = GetRotation();
  SetPosition(videowidget_, rect_.x(), rect_.y(), rect_.width(), rect_.height(), rotation_, mirror_, stretch_, true);

  startTimer(std::chrono::milliseconds(200));

  Connect();
}

VideoView::~VideoView()
{
  Disconnect();

}

void VideoView::Connect()
{
  Disconnect();

  if (track_ == nullptr)
  {
    SetMessage(GetNextPlayRequestIndex(true), false, "Invalid track");
    return;
  }

  const std::vector< QSharedPointer<client::Receiver> > receivers = recording_->GetActiveReceivers(track_);
  if (receivers.size() > 1)
  {
    LOG_GUI_WARNING_SOURCE(device_, "Multiple active receivers");

  }

  if (receivers.size() >= 1)
  {
    const QUrl url(receivers[0]->GetMediaUri());
    if ((url.scheme() == "http") && (url.path() == "/onvif/device_service")) // If it looks like an ONVIF url, lets try connecting through the servers http proxy
    {
      ConnectONVIF(receivers[0]);

    }
  }

  SetPaused(false);
  SetMessage(GetNextPlayRequestIndex(true), false, "Connecting");
  const std::string username = device_->GetUsername().toStdString();
  const std::string password = device_->GetPassword().toStdString();
  connect_ = connection_->Connect([this, username, password](const boost::system::error_code& err)
  {
    std::lock_guard<std::mutex> lock(mutex_);
    if (err)
    {
      SetMessage(GetNextPlayRequestIndex(true), true, "Unable to connect");
      return;
    }

    SetMessage(GetPlayRequestIndex(), false, "Authenticating");
    getauthenticatenonce_ = connection_->GetAuthenticationNonce([this, username, password](const std::chrono::steady_clock::duration latency, const monocle::client::GETAUTHENTICATIONNONCERESPONSE& getauthenticationnonceresponse)
    {
      std::lock_guard<std::mutex> lock(mutex_);
      if (getauthenticationnonceresponse.GetErrorCode() != monocle::ErrorCode::Success)
      {
        SetMessage(GetNextPlayRequestIndex(true), true, "Unable to authenticate");
        return;
      }

      const std::string clientnonce = utility::GenerateRandomString(32);
      authenticate_ = connection_->Authenticate(username, clientnonce, monocle::AuthenticateDigest(username, password, getauthenticationnonceresponse.authenticatenonce_, clientnonce), [this](const std::chrono::steady_clock::duration latency, const monocle::client::AUTHENTICATERESPONSE& authenticateresponse)
      {
        std::lock_guard<std::mutex> lock(mutex_);
        if (authenticateresponse.GetErrorCode() != monocle::ErrorCode::Success)
        {
          SetMessage(GetNextPlayRequestIndex(true), true, "Unable to authenticate");
          return;
        }

        SetMessage(GetPlayRequestIndex(), false, "Creating Stream");
        createstream_ = connection_->CreateStream(recording_->GetToken(), track_->GetId(), [this](const std::chrono::steady_clock::duration latency, const monocle::client::CREATESTREAMRESPONSE& createstreamresponse)
        {
          std::lock_guard<std::mutex> lock(mutex_);
          if (createstreamresponse.GetErrorCode() != monocle::ErrorCode::Success)
          {
            SetMessage(GetNextPlayRequestIndex(true), true, "Unable to create stream: " + QString::fromStdString(createstreamresponse.GetErrorText()));
            return;
          }

          DestroyDecoders();
          for (const monocle::CODECINDEX& codecindex : createstreamresponse.codecindices_)
          {
            AddCodecIndex(codecindex);

          }

          SetMessage(GetPlayRequestIndex(), false, "Requesting Live");
          streamtoken_ = createstreamresponse.token_;

          controlstream_ = connection_->ControlStreamLive(streamtoken_, GetPlayRequestIndex(), [this](const std::chrono::steady_clock::duration latency, const monocle::client::CONTROLSTREAMRESPONSE& controlstreamresponse)
          {
            std::lock_guard<std::mutex> lock(mutex_);
            if (controlstreamresponse.GetErrorCode() != monocle::ErrorCode::Success)
            {
              SetMessage(GetNextPlayRequestIndex(true), true, "Unable to control stream");
              return;
            }
		        Keepalive();
          });
        }, VideoView::ControlStreamEnd, VideoView::H265Callback, VideoView::H264Callback, VideoView::MetadataCallback, VideoView::JPEGCallback, VideoView::MPEG4Callback, VideoView::NewCodecIndexCallback, this);
      });
    });
  });
}

void VideoView::Disconnect()
{
  {
    std::lock_guard<std::mutex> lock(mutex_);
    DestroyDecoders();
  }

  connect_.Close();
  getauthenticatenonce_.Close();
  authenticate_.Close();
  createstream_.Close();
  controlstream_.Close();
  keepalive_.Close();

  connection_->Destroy();

  if (onvifptz_)
  {
    onvifptz_->Destroy();
    onvifptz_.reset();
  }

  if (onvifmedia_)
  {
    onvifmedia_->Destroy();
    onvifmedia_.reset();
  }

  if (onvifevent_)
  {
    onvifevent_->Destroy();
    onvifevent_.reset();
  }

  if (onvifdevice_)
  {
    onvifdevice_->Destroy();
    onvifdevice_.reset();
  }

  ptzxmin_.reset();
  ptzxmax_.reset();
  ptzymin_.reset();
  ptzymax_.reset();
}

void VideoView::GetMenu(QMenu& parent)
{
  parent.addAction(actionreconnect_);
  parent.addAction(actionproperties_);

  // Tracks
  QMenu* tracks = new QMenu("Tracks", &parent);
  for (const QSharedPointer<client::RecordingTrack>& track : recording_->GetVideoTracks())
  {
    const QString description = track->GetDescription().isEmpty() ? track->GetToken() : QString("(" + track->GetDescription() + ")");
    QAction* action = tracks->addAction(description, [this, recordingtoken = recording_->GetToken(), trackid = track->GetId()]()
    {
      QSharedPointer<client::Recording> recording = device_->GetRecording(recordingtoken); // We do it like this, because the recording might have died
      if (recording == nullptr)
      {
        LOG_GUI_THREAD_WARNING_SOURCE(device_, QString("Unable to retrieve recording: ") + QString::number(recordingtoken));
        return;
      }

      QSharedPointer<client::RecordingTrack> track = recording->GetTrack(trackid);
      if (!track)
      {
        LOG_GUI_THREAD_WARNING_SOURCE(device_, QString("Unable to retrieve track: ") + QString::number(trackid));
        return;
      }
      track_ = track;
      Connect();
    });
    action->setCheckable(true);
    action->setChecked(track == track_);
  }
  parent.addMenu(tracks);

  View::GetMenu(parent);
}

double VideoView::GetAspectRatio() const
{
  if (imagewidth_ && imageheight_)
  {

    return (static_cast<double>(imagewidth_) / static_cast<double>(imageheight_));
  }
  else
  {

    return 0.0;
  }
}

bool VideoView::GetImage(ImageBuffer& imagebuffer)
{
  bool hasimage = false;
  ImageBuffer previmagebuffer;
  while (true)
  {
    if (imagequeue_.pop(imagebuffer))
    {
      bandwidthsizes_.push_back(std::make_pair(std::chrono::steady_clock::now(), imagebuffer.originalsize_));

      // If we have skipped frames, we should place them back into the temporary list, or destroy them if there is no room
      if (previmagebuffer.buffer_)
      {
        if (paused_)
        {
          cache_.push_back(previmagebuffer);

        }
        else
        {
          freeimagequeue_.AddFreeImage(previmagebuffer);

        }
      }
      previmagebuffer = imagebuffer;
      hasimage = true;
    }
    else
    {

      return hasimage;
    }
  }
}

int64_t VideoView::GetTimeOffset() const
{
  return device_->GetTimeOffset();
}

void VideoView::Play()
{
  SetPaused(false);
  if (time_ == 0) // If we haven't got anywhere to continue from, just play live
  {
    connection_->ControlStreamLive(streamtoken_, GetNextPlayRequestIndex(true));

  }
  else
  {
    connection_->ControlStream(streamtoken_, GetNextPlayRequestIndex(true), false, true, true, time_, boost::none, boost::none);

  }
}

void VideoView::FrameStep(const bool forwards)
{
  paused_ = true;
  std::vector<ImageBuffer>::iterator imagebuffer = cache_.end();
  for (std::vector<ImageBuffer>::iterator i = cache_.begin(); i != cache_.end(); ++i)
  {
    if (i->playrequestindex_ != GetPlayRequestIndex())
    {

      continue;
    }

    if (forwards)
    {
      if ((i->sequencenum_ > sequencenum_) && ((imagebuffer == cache_.end()) || ((imagebuffer != cache_.end()) && (i->sequencenum_ < imagebuffer->sequencenum_))))
      {
        imagebuffer = i;

      }
    }
    else
    {
      if ((i->sequencenum_ < sequencenum_) && ((imagebuffer == cache_.end()) || ((imagebuffer != cache_.end()) && (i->sequencenum_ > imagebuffer->sequencenum_))))
      {
        imagebuffer = i;

      }
    }
  }

  if (imagebuffer == cache_.end())
  {
    {
      std::lock_guard<std::mutex> lock(mutex_);
      ResetDecoders();
    }

    controlstreamendcallback_ = [this, forwards](const uint64_t playrequestindex, const monocle::ErrorCode error)
    {
      if (GetPlayRequestIndex() != playrequestindex)
      {

        return;
      }

      if (error != monocle::ErrorCode::Success)
      {
        LOG_GUI_THREAD_WARNING_SOURCE(device_, "ControlStream Play failed");
        return;
      }

      imagequeue_.consume_all([this](const ImageBuffer& imagebuffer){ cache_.push_back(imagebuffer); });

      // Find the previous/next frame to go to
      std::vector<ImageBuffer>::const_iterator imagebuffer = cache_.end();
      for (std::vector<ImageBuffer>::const_iterator i = cache_.begin(); i != cache_.end(); ++i)
      {
        if (i->playrequestindex_ != playrequestindex)
        {

          continue;
        }

        // Ignore all frames after or before in the opposite direction to what we are looking for
        if (forwards)
        {
          if (i->sequencenum_ <= sequencenum_)
          {

            continue;
          }
        }
        else
        {
          if (i->sequencenum_ >= sequencenum_)
          {

            continue;
          }
        }

        if (imagebuffer == cache_.end())
        {
          imagebuffer = i;

        }
        else
        {
          if (forwards)
          {
            if (i->sequencenum_ < imagebuffer->sequencenum_)
            {
              imagebuffer = i;

            }
          }
          else
          {
            if (i->sequencenum_ > imagebuffer->sequencenum_)
            {
              imagebuffer = i;

            }
          }
        }
      }

      if (imagebuffer == cache_.end())
      {
        LOG_GUI_THREAD_WARNING_SOURCE(device_, "ControlStream Unable to find frame");
        return;
      }

      WriteFrame(*imagebuffer);
    };

    connection_->ControlStreamFrameStep(streamtoken_, GetNextPlayRequestIndex(true), forwards, sequencenum_);
  }
  else
  {
    WriteFrame(*imagebuffer);
    
  }
}

void VideoView::Play(const uint64_t time, const boost::optional<uint64_t>& numframes)
{
  {
    std::lock_guard<std::mutex> lock(mutex_);
    ResetDecoders();
  }

  connection_->ControlStream(streamtoken_, GetNextPlayRequestIndex(true), true, !numframes.is_initialized(), true, time + GetTimeOffset(), boost::none, numframes);
  if (numframes.is_initialized() && ((*numframes == 0) || (*numframes == 1))) // Is this an effectively pause request...
  {
    controlstreamendcallback_ = [this](const uint64_t playrequestindex, const monocle::ErrorCode err)
    {
      if (GetPlayRequestIndex() != playrequestindex)
      {

        return;
      }

      if (err != monocle::ErrorCode::Success)
      {
        LOG_GUI_THREAD_WARNING_SOURCE(device_, "ControlStream Play failed");
        return;
      }

      imagequeue_.consume_all([this](const ImageBuffer& imagebuffer) { cache_.push_back(imagebuffer); });

      std::vector<ImageBuffer>::const_iterator imagebuffer = cache_.end();
      for (std::vector<ImageBuffer>::const_iterator i = cache_.begin(); i != cache_.end(); ++i)
      {
        if (i->playrequestindex_ != playrequestindex)
        {

          continue;
        }

        if (imagebuffer == cache_.end())
        {
          imagebuffer = i;

        }
        else
        {
          if (i->sequencenum_ > imagebuffer->sequencenum_)
          {
            imagebuffer = i;

          }
        }
      }

      if (imagebuffer == cache_.end())
      {
        LOG_GUI_THREAD_WARNING_SOURCE(device_, "ControlStream Unable to find frame");
        return;
      }

      WriteFrame(*imagebuffer);
    };
    paused_ = true;
  }
  else
  {
    paused_ = false;

  }
}

void VideoView::Pause(const boost::optional<uint64_t>& time)
{
  SetPaused(true);
  connection_->ControlStreamPause(streamtoken_, time);
}

void VideoView::Stop()
{
  SetPaused(false);
  connection_->ControlStreamLive(streamtoken_, GetNextPlayRequestIndex(true));
}

void VideoView::Scrub(const uint64_t time)
{
  {
    std::lock_guard<std::mutex> lock(mutex_);
    ResetDecoders();
  }

  connection_->ControlStream(streamtoken_, GetNextPlayRequestIndex(false), true, true, true, time + GetTimeOffset(), boost::none, 1);
  controlstreamendcallback_ = [this](const uint64_t playrequestindex, const monocle::ErrorCode err)
  {
    if (err != monocle::ErrorCode::Success)
    {
      LOG_GUI_THREAD_WARNING_SOURCE(device_, "Scrub failed");
      return;
    }

    imagequeue_.consume_all([this](const ImageBuffer& imagebuffer) { cache_.push_back(imagebuffer); });

    if (cache_.empty())
    {
      LOG_GUI_THREAD_WARNING_SOURCE(device_, "Scrub failed to find frames");
      return;
    }

    std::sort(cache_.begin(), cache_.end(), [](const ImageBuffer& lhs, const ImageBuffer& rhs)
    {
      if (lhs.playrequestindex_ == rhs.playrequestindex_)
      {

        return (lhs.time_ < rhs.time_);
      }
      else
      {

        return (lhs.playrequestindex_ < rhs.playrequestindex_);
      }
    });

    WriteFrame(cache_.back());
    std::for_each(cache_.begin(), cache_.end(), [](ImageBuffer& imagebuffer) { imagebuffer.Destroy(); });
    cache_.clear();
  };
  paused_ = true;
}

std::vector<int> VideoView::GetCUDADevices() const
{
  std::vector<int> cudadevices;
  for (const std::unique_ptr<H264Decoder>& h264decoder : h264decoders_)
  {
    if (h264decoder->GetHardwareDevice().is_initialized())
    {
      if (utility::Contains(cudadevices, *h264decoder->GetHardwareDevice()))
      {

        continue;
      }
      cudadevices.push_back(*h264decoder->GetHardwareDevice());
    }
  }
  return cudadevices;
}

std::vector<QString> VideoView::GetProfileTokens() const
{
  return recording_->GetActiveProfileTokens(track_);
}

void VideoView::timerEvent(QTimerEvent* event)
{
  if (onvifdevice_ && onvifdevice_->IsInitialised())
  {
    onvifdevice_->Update();

  }

  if (onvifevent_ && onvifevent_->IsInitialised())
  {
    onvifevent_->Update();

  }

  if (onvifmedia_ && onvifmedia_->IsInitialised())
  {
    onvifmedia_->Update();

  }

  if (onvifptz_ && onvifptz_->IsInitialised())
  {
    onvifptz_->Update();

  }

  View::timerEvent(event);
}

void VideoView::ControlStreamEnd(const uint64_t streamtoken, const uint64_t playrequestindex, const monocle::ErrorCode error, void* callbackdata)
{
  VideoView* videoview = reinterpret_cast<VideoView*>(callbackdata);
  if (videoview->GetPlayRequestIndex() != playrequestindex)
  {

    return;
  }

  QMetaObject::invokeMethod(videoview, [videoview, playrequestindex, error]()
  {
    if (videoview->controlstreamendcallback_)
    {
      videoview->controlstreamendcallback_(playrequestindex, error);

    }
  }, Qt::QueuedConnection);
}

void VideoView::H265Callback(const uint64_t streamtoken, const uint64_t playrequestindex, const uint64_t codecindex, const bool marker, const uint64_t timestamp, const int64_t sequencenum, const float progress, const uint8_t* signature, const size_t signaturesize, const char* signaturedata, const size_t signaturedatasize, const bool donlfield, const uint32_t* offsets, const size_t numoffsets, const char* framedata, const size_t size, void* callbackdata) // This gets called by the Connection thread
{
  VideoView* videoview = reinterpret_cast<VideoView*>(callbackdata);
  std::lock_guard<std::mutex> lock(videoview->mutex_);
  if (videoview->GetPlayRequestIndex() != playrequestindex)
  {

    return;
  }

  std::vector< std::unique_ptr<H265Decoder> >::iterator h265decoder = std::find_if(videoview->h265decoders_.begin(), videoview->h265decoders_.end(), [codecindex](std::unique_ptr<H265Decoder>& h265decoder) { return (h265decoder->GetId() == codecindex); });
  if (h265decoder == videoview->h265decoders_.end())
  {

    return;
  }

  ImageBuffer imagebuffer = (*h265decoder)->Decode(playrequestindex, marker, timestamp, sequencenum, signature, signaturesize, signaturedata, signaturedatasize, reinterpret_cast<const uint8_t*>(framedata), static_cast<unsigned int>(size), &videoview->freeimagequeue_);
  if (imagebuffer.buffer_)
  {
    if (videoview->imagequeue_.write_available())
    {
      videoview->imagequeue_.push(imagebuffer);

    }
    else
    {
      imagebuffer.Destroy();

    }
  }
}

void VideoView::H264Callback(const uint64_t streamtoken, const uint64_t playrequestindex, const uint64_t codecindex, const bool marker, const uint64_t timestamp, const int64_t sequencenum, const float progress, const uint8_t* signature, const size_t signaturesize, const char* signaturedata, const size_t signaturedatasize, const uint32_t* offsets, const size_t numoffsets, const char* framedata, const size_t size, void* callbackdata) // This gets called by the Connection thread
{
  VideoView* videoview = reinterpret_cast<VideoView*>(callbackdata);
  std::lock_guard<std::mutex> lock(videoview->mutex_);
  if (videoview->GetPlayRequestIndex() != playrequestindex)
  {

    return;
  }

  std::vector< std::unique_ptr<H264Decoder> >::iterator h264decoder = std::find_if(videoview->h264decoders_.begin(), videoview->h264decoders_.end(), [codecindex](std::unique_ptr<H264Decoder>& h264decoder) { return (h264decoder->GetId() == codecindex); });
  if (h264decoder == videoview->h264decoders_.end())
  {

    return;
  }

  ImageBuffer imagebuffer = (*h264decoder)->Decode(playrequestindex, marker, timestamp, sequencenum, signature, signaturesize, signaturedata, signaturedatasize, reinterpret_cast<const uint8_t*>(framedata), static_cast<unsigned int>(size), &videoview->freeimagequeue_);
  if (imagebuffer.buffer_)
  {
    if (videoview->imagequeue_.write_available())
    {
      videoview->imagequeue_.push(imagebuffer);

    }
    else
    {
      imagebuffer.Destroy();

    }
  }
}

void VideoView::MetadataCallback(const uint64_t streamtoken, const uint64_t playrequestindex, const uint64_t codecindex, const uint64_t timestamp, const int64_t sequencenum, const float progress, const uint8_t* signature, const size_t signaturesize, const char* signaturedata, const size_t signaturedatasize, const char* framedata, const size_t size, void* callbackdata)
{
  VideoView* videoview = reinterpret_cast<VideoView*>(callbackdata);
  std::lock_guard<std::mutex> lock(videoview->mutex_);
}

void VideoView::JPEGCallback(const uint64_t streamtoken, const uint64_t playrequestindex, const uint64_t codecindex, const uint64_t timestamp, const int64_t sequencenum, const float progress, const uint8_t* signature, const size_t signaturesize, const char* signaturedata, const size_t signaturedatasize, const uint16_t restartinterval, const uint32_t typespecificfragmentoffset, const uint8_t type, const uint8_t q, const uint8_t width, const uint8_t height, const uint8_t* lqt, const uint8_t* cqt, const char* framedata, const size_t size, void* callbackdata) // This gets called by the Connection thread
{
  VideoView* videoview = reinterpret_cast<VideoView*>(callbackdata);
  std::lock_guard<std::mutex> lock(videoview->mutex_);
  if (videoview->GetPlayRequestIndex() != playrequestindex)
  {

    return;
  }

  if (!videoview->mjpegdecoder_)
  {
    videoview->mjpegdecoder_ = std::make_unique<MJpegDecoder>(0, videoview->device_->GetPublicKey()); // Id doesn't matter because we always ignore it from this point onwards
    const client::DECODERERROR error = videoview->mjpegdecoder_->Init();
    if (error)
    {
      videoview->mjpegdecoder_.reset();
      LOG_GUI_THREAD_WARNING_SOURCE(videoview->device_, "MJPEGDecoder failed to initialise");
      return;
    }
  }

  ImageBuffer imagebuffer = videoview->mjpegdecoder_->Decode(playrequestindex, timestamp, sequencenum, signature, signaturesize, signaturedata, signaturedatasize, reinterpret_cast<const uint8_t*>(framedata), static_cast<unsigned int>(size), &videoview->freeimagequeue_);
  if (imagebuffer.buffer_)
  {
    if (videoview->imagequeue_.write_available())
    {
      videoview->imagequeue_.push(imagebuffer);

    }
    else
    {
      imagebuffer.Destroy();

    }
  }
}

void VideoView::MPEG4Callback(const uint64_t streamtoken, const uint64_t playrequestindex, const uint64_t codecindex, const bool marker, const uint64_t timestamp, const int64_t sequencenum, const float progress, const uint8_t* signature, const size_t signaturesize, const char* signaturedata, const size_t signaturedatasize, const char* framedata, const size_t size, void* callbackdata) // This gets called by the Connection thread
{
  VideoView* videoview = reinterpret_cast<VideoView*>(callbackdata);
  std::lock_guard<std::mutex> lock(videoview->mutex_);
  if (videoview->GetPlayRequestIndex() != playrequestindex)
  {

    return;
  }

  std::vector< std::unique_ptr<MPEG4Decoder> >::iterator mpeg4decoder = std::find_if(videoview->mpeg4decoders_.begin(), videoview->mpeg4decoders_.end(), [codecindex](std::unique_ptr<MPEG4Decoder>& mpeg4decoder) { return (mpeg4decoder->GetId() == codecindex); });
  if (mpeg4decoder == videoview->mpeg4decoders_.end())
  {

    return;
  }

  ImageBuffer imagebuffer = (*mpeg4decoder)->Decode(playrequestindex, timestamp, sequencenum, signature, signaturesize, signaturedata, signaturedatasize, reinterpret_cast<const uint8_t*>(framedata), static_cast<unsigned int>(size), &videoview->freeimagequeue_);
  if (imagebuffer.buffer_)
  {
    if (videoview->imagequeue_.write_available())
    {
      videoview->imagequeue_.push(imagebuffer);

    }
    else
    {
      imagebuffer.Destroy();

    }
  }
}

void VideoView::NewCodecIndexCallback(const uint64_t streamtoken, const uint64_t id, const monocle::Codec codec, const std::string& parameters, const uint64_t timestamp, void* callbackdata)
{
  VideoView* videoview = reinterpret_cast<VideoView*>(callbackdata);
  std::lock_guard<std::mutex> lock(videoview->mutex_);
  videoview->AddCodecIndex(monocle::CODECINDEX(id, codec, parameters, timestamp));
}

void VideoView::ConnectONVIF(const QSharedPointer<client::Receiver>& receiver)
{
  const std::vector<QString> profiletokens = recording_->GetActiveProfileTokens(track_);
  if (profiletokens.empty())
  {
    LOG_GUI_WARNING_SOURCE(device_, "No active profile tokens available to connect via ONVIF");
    return;
  }

  const std::string profile = profiletokens[0].toStdString();

  onvifdevice_ = boost::make_shared<onvif::device::DeviceClient>();
  onvifevent_ = boost::make_shared<onvif::event::EventClient>();
  onvifmedia_ = boost::make_shared<onvif::media::MediaClient>();
  onvifptz_ = boost::make_shared<onvif::ptz::PTZClient>();
  const std::string receiverusername = receiver->GetUsername().toStdString();
  const std::string receiverpassword = receiver->GetPassword().toStdString();

  if (onvifdevice_->Init(sock::ProxyParams(sock::PROXYTYPE_HTTP, device_->GetAddress().toStdString(), device_->GetPort(), true, device_->GetUsername().toStdString(), device_->GetPassword().toStdString()), receiver->GetMediaUri().toStdString(), receiverusername, receiverpassword, 1, false, true))
  {
    LOG_GUI_WARNING_SOURCE(device_, "ONVIF device service initialisation failed");
    return;
  }

  onvifconnection_ = onvifdevice_->GetSystemDateAndTimeCallback([this, profile, receiverusername, receiverpassword](const onvif::device::GetSystemDateAndTimeResponse& getsystemdateandtimeresponse)
  {
    if (!getsystemdateandtimeresponse.Error())
    {
      if (!getsystemdateandtimeresponse.systemdatetime_.is_initialized())
      {
        LOG_GUI_WARNING_SOURCE(device_, "Failed to retrieve system date and time");

      }
      else
      {
        onvifdevice_->SetTimeOffset(getsystemdateandtimeresponse.systemdatetime_->GetUtcOffset());
        onvifevent_->SetTimeOffset(getsystemdateandtimeresponse.systemdatetime_->GetUtcOffset());
        onvifmedia_->SetTimeOffset(getsystemdateandtimeresponse.systemdatetime_->GetUtcOffset());
        onvifptz_->SetTimeOffset(getsystemdateandtimeresponse.systemdatetime_->GetUtcOffset());
      }
    }

    onvifconnection_ = onvifdevice_->GetCapabilitiesCallback(onvif::CAPABILITYCATEGORY_ALL, [this, profile, receiverusername, receiverpassword](const onvif::device::GetCapabilitiesResponse& getcapabilitiesresponse)
    {
      if (getcapabilitiesresponse.Error())
      {
        LOG_GUI_WARNING_SOURCE(device_, "Failed to get capabilities");
        return;
      }

      if (!getcapabilitiesresponse.capabilities_.is_initialized())
      {
        LOG_GUI_WARNING_SOURCE(device_, "Invalid capabilities");
        return;
      }

      if (getcapabilitiesresponse.capabilities_->events_.is_initialized())
      {
        if (!getcapabilitiesresponse.capabilities_->events_->xaddr_.is_initialized())
        {
          LOG_GUI_WARNING_SOURCE(device_, "Invalid event xaddr");
          return;
        }

        if (onvifevent_->Init(sock::ProxyParams(sock::PROXYTYPE_HTTP, device_->GetAddress().toStdString(), device_->GetPort(), true, device_->GetUsername().toStdString(), device_->GetPassword().toStdString()), *getcapabilitiesresponse.capabilities_->events_->xaddr_, receiverusername, receiverpassword, 1, false, true))
        {
          LOG_GUI_WARNING_SOURCE(device_, "ONVIF event service initialisation failed");

        }
      }

      if (getcapabilitiesresponse.capabilities_->media_.is_initialized())
      {
        if (!getcapabilitiesresponse.capabilities_->media_->xaddr_.is_initialized())
        {
          LOG_GUI_WARNING_SOURCE(device_, "Invalid media xaddr");
          return;
        }

        if (onvifmedia_->Init(sock::ProxyParams(sock::PROXYTYPE_HTTP, device_->GetAddress().toStdString(), device_->GetPort(), true, device_->GetUsername().toStdString(), device_->GetPassword().toStdString()), *getcapabilitiesresponse.capabilities_->media_->xaddr_, receiverusername, receiverpassword, 1, false, true))
        {
          LOG_GUI_WARNING_SOURCE(device_, "ONVIF media service initialisation failed");

        }
      }

      if (getcapabilitiesresponse.capabilities_->ptz_.is_initialized())
      {
        if (!getcapabilitiesresponse.capabilities_->ptz_->xaddr_.is_initialized())
        {
          LOG_GUI_WARNING_SOURCE(device_, "Invalid PTZ xaddr");
          return;
        }

        if (onvifptz_->Init(sock::ProxyParams(sock::PROXYTYPE_HTTP, device_->GetAddress().toStdString(), device_->GetPort(), true, device_->GetUsername().toStdString(), device_->GetPassword().toStdString()), *getcapabilitiesresponse.capabilities_->ptz_->xaddr_, receiverusername, receiverpassword, 1, false, true))
        {
          LOG_GUI_WARNING_SOURCE(device_, "ONVIF PTZ service initialisation failed");

        }
      }

      if (onvifmedia_->IsInitialised())
      {
        onvifconnection_ = onvifmedia_->GetProfileCallback(profile, [this, profile](const onvif::media::GetProfileResponse& getprofileresponse)
        {
          if (getprofileresponse.Error())
          {
            LOG_GUI_WARNING_SOURCE(device_, QString("Failed to get profile: ") + QString::fromStdString(profile));
            return;
          }

          if (!getprofileresponse.profile_.is_initialized())
          {
            LOG_GUI_WARNING_SOURCE(device_, "Invalid profile");
            return;
          }

          if (onvifptz_->IsInitialised() && getprofileresponse.profile_->ptzconfiguration_.is_initialized() && getprofileresponse.profile_->ptzconfiguration_->defaultcontinuouspantiltvelocityspace_.is_initialized() && getprofileresponse.profile_->ptzconfiguration_->token_.is_initialized())
          {
            const std::string continuousvelocityspaceuri = *getprofileresponse.profile_->ptzconfiguration_->defaultcontinuouspantiltvelocityspace_;

            onvifconnection_ = onvifptz_->GetConfigurationOptionsCallback(*getprofileresponse.profile_->ptzconfiguration_->token_, [this, continuousvelocityspaceuri](const onvif::ptz::GetConfigurationOptionsResponse& getconfigurationoptionsresponse)
            {
              if (getconfigurationoptionsresponse.Error())
              {
                LOG_GUI_WARNING_SOURCE(device_, "Failed to retrieve PTZ configuration options");
                return;
              }

              if (getconfigurationoptionsresponse.ptzconfigurationoptions_.is_initialized() && getconfigurationoptionsresponse.ptzconfigurationoptions_->spaces_.is_initialized())
              {
                auto pantiltcontinuousvelocityspace = std::find_if(getconfigurationoptionsresponse.ptzconfigurationoptions_->spaces_->continuouspantiltvelocityspace_.cbegin(), getconfigurationoptionsresponse.ptzconfigurationoptions_->spaces_->continuouspantiltvelocityspace_.cend(), [continuousvelocityspaceuri](const onvif::Space2dDescription& continuouspantiltvelocityspace)
                {
                  return (continuouspantiltvelocityspace.uri_.is_initialized() &&
                          continuouspantiltvelocityspace.xrange_.is_initialized() &&
                          continuouspantiltvelocityspace.xrange_->min_.is_initialized() &&
                          continuouspantiltvelocityspace.xrange_->max_.is_initialized() &&
                          continuouspantiltvelocityspace.yrange_.is_initialized() &&
                          continuouspantiltvelocityspace.yrange_->min_.is_initialized() &&
                          continuouspantiltvelocityspace.yrange_->max_.is_initialized() &&
                          (*continuouspantiltvelocityspace.uri_ == continuousvelocityspaceuri));
                });
                if (pantiltcontinuousvelocityspace != getconfigurationoptionsresponse.ptzconfigurationoptions_->spaces_->continuouspantiltvelocityspace_.cend())
                {
                  ptzxmin_ = *pantiltcontinuousvelocityspace->xrange_->min_;
                  ptzxmax_ = *pantiltcontinuousvelocityspace->xrange_->max_;
                  ptzymin_ = *pantiltcontinuousvelocityspace->yrange_->min_;
                  ptzymax_ = *pantiltcontinuousvelocityspace->yrange_->max_;
                }

                auto zoomcontinuousvelocityspace = std::find_if(getconfigurationoptionsresponse.ptzconfigurationoptions_->spaces_->continuouszoomvelocityspace_.cbegin(), getconfigurationoptionsresponse.ptzconfigurationoptions_->spaces_->continuouszoomvelocityspace_.cend(), [continuousvelocityspaceuri](const onvif::Space1dDescription& continuouszoomvelocityspace)
                {
                  return (continuouszoomvelocityspace.uri_.is_initialized() &&
                          continuouszoomvelocityspace.xrange_.is_initialized() &&
                          continuouszoomvelocityspace.xrange_->min_.is_initialized() &&
                          continuouszoomvelocityspace.xrange_->max_.is_initialized() &&
                          (*continuouszoomvelocityspace.uri_ == continuousvelocityspaceuri));
                });
                if (zoomcontinuousvelocityspace != getconfigurationoptionsresponse.ptzconfigurationoptions_->spaces_->continuouszoomvelocityspace_.cend())
                {
                  zoommin_ = *zoomcontinuousvelocityspace->xrange_->min_;
                  zoommax_ = *zoomcontinuousvelocityspace->xrange_->max_;
                }
              }
            });
          }
        });
      }
    });
  });
}

void VideoView::AddCodecIndex(const monocle::CODECINDEX& codecindex)
{
  std::vector<std::string> parameterssplit;
  boost::split(parameterssplit, codecindex.parameters_, boost::is_any_of(";"), boost::algorithm::token_compress_on);

  if (codecindex.codec_ == monocle::Codec::MJPEG) // MJPEG sorts itself out
  {

    return;
  }
  else if (codecindex.codec_ == monocle::Codec::H265)
  {
    std::unique_ptr<H265Decoder> h265decoder = std::make_unique<H265Decoder>(codecindex.id_, device_->GetPublicKey());
    const DECODERERROR error = h265decoder->Init(parameterssplit);
    if (error)
    {
      LOG_GUI_THREAD_WARNING_SOURCE(device_, "H265Decoder failed to initialise");
      return;
    }
    h265decoders_.emplace_back(std::move(h265decoder));
  }
  else if (codecindex.codec_ == monocle::Codec::H264)
  {
    std::unique_ptr<H264Decoder> h264decoder = std::make_unique<H264Decoder>(codecindex.id_, device_->GetPublicKey());
    const DECODERERROR error = h264decoder->Init(parameterssplit);
    if (error)
    {
      LOG_GUI_THREAD_WARNING_SOURCE(device_, "H264Decoder failed to initialise");
      return;
    }
    h264decoders_.emplace_back(std::move(h264decoder));
  }
  else if (codecindex.codec_ == monocle::Codec::MPEG4)
  {
    std::unique_ptr<MPEG4Decoder> mpeg4decoder = std::make_unique<MPEG4Decoder>(codecindex.id_, device_->GetPublicKey());
    const DECODERERROR error = mpeg4decoder->Init(parameterssplit);
    if (error)
    {
      LOG_GUI_THREAD_WARNING_SOURCE(device_, "MPEG4Decoder failed to initialise");
      return;
    }
    mpeg4decoders_.emplace_back(std::move(mpeg4decoder));
  }
}

void VideoView::DestroyDecoders()
{
  if (mjpegdecoder_)
  {
    mjpegdecoder_->Destroy();
    mjpegdecoder_.reset();
  }

  for (std::unique_ptr<H265Decoder>& h265decoder : h265decoders_)
  {
    h265decoder->Destroy();

  }
  h264decoders_.clear();

  for (std::unique_ptr<H264Decoder>& h264decoder : h264decoders_)
  {
    h264decoder->Destroy();

  }
  h264decoders_.clear();

  for (std::unique_ptr<MPEG4Decoder>& mpeg4decoder : mpeg4decoders_)
  {
    mpeg4decoder->Destroy();

  }
  mpeg4decoders_.clear();
}

void VideoView::Keepalive()
{
  std::shared_ptr<boost::asio::deadline_timer> timer = std::make_shared<boost::asio::deadline_timer>(MainWindow::Instance()->GetGUIIOService());
  timer->expires_from_now(boost::posix_time::seconds(15));
  QWeakPointer<VideoView> ptr = sharedFromThis().staticCast<VideoView>();
  timer->async_wait([ptr, timer](const boost::system::error_code& err)
  {
    QSharedPointer<VideoView> p = ptr.lock();
    if (p == nullptr)
    {

      return;
    }

    if (err)
    {

      return;
    }

    p->keepalive_ = p->connection_->Keepalive([ptr](const std::chrono::steady_clock::duration latency, const monocle::client::KEEPALIVERESPONSE& keepaliveresponse)
    {
      QSharedPointer<VideoView> p = ptr.lock();
      if (p == nullptr)
      {

        return;
      }

      if (keepaliveresponse.GetErrorCode() != monocle::ErrorCode::Success)
      {

        return;
      }

      p->Keepalive();
    });
  });
}

ROTATION VideoView::GetRotation() const
{
  const std::vector<ROTATION> rotations = recording_->GetActiveRotations(track_);
  if (rotations.empty())
  {

    return ROTATION::_0;
  }
  return rotations.front();
}

void VideoView::ResetDecoders()
{
  for (std::unique_ptr<H264Decoder>& h264decoder : h264decoders_)
  {
    h264decoder->Reset();

  }

  for (std::unique_ptr<H265Decoder>& h265decoder : h265decoders_)
  {
    h265decoder->Reset();

  }

  for (std::unique_ptr<MPEG4Decoder>& mpeg4decoder : mpeg4decoders_)
  {
    mpeg4decoder->Reset();

  }
}

void VideoView::DeviceStateChanged(const DEVICESTATE state, const QString&)
{
  if (state == DEVICESTATE::SUBSCRIBED)
  {
    Reconnect(false);

  }
}

void VideoView::Reconnect(bool)
{
  Connect();

}

void VideoView::Properties(bool)
{
  VideoViewPropertiesWindow(videowidget_, sharedFromThis().staticCast<VideoView>()).exec();

}

void VideoView::TrackAdded(const QSharedPointer<client::RecordingTrack>& track)
{
  if (track_ == nullptr)
  {
    if (track->GetTrackType() == monocle::TrackType::Video)
    {
      track_ = track;
      Connect();
    }
  }
}

void VideoView::TrackRemoved(const uint32_t token)
{
  if (track_->GetToken() == token)
  {
    if (recording_->GetVideoTracks().size())
    {
      // Switch to another video track if one is available
      track_ = recording_->GetVideoTracks().front();
    }
    else
    {
      // Just live without a video track
      track_.reset();
    }
    Connect();
  }
}

void VideoView::ActiveJobChanged(const QSharedPointer<client::RecordingJob>& activejob)
{
  rotation_ = GetRotation();
  SetPosition(videowidget_, rect_.x(), rect_.y(), rect_.width(), rect_.height(), rotation_, mirror_, stretch_, true);
  Connect();
}

}