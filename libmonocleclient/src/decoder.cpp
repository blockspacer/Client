// decoder.cpp
//

///// Includes /////

#include "monocleclient/decoder.h"

extern "C"
{
  #include <libavutil/hwcontext.h>
}

#include "monocleclient/mainwindow.h"

///// Namespaces /////

namespace client
{

///// Functions /////

QString ToString(DECODERERROR decodererror)
{
  switch (decodererror)
  {
    case DECODERERROR_SUCCESS:
    {

      return QObject::tr("Success");
    }
    case DECODERERROR_INITCODEC:
    {

      return QObject::tr("Error creating codec");
    }
    case DECODERERROR_INITCONTEXT:
    {

      return QObject::tr("Error allocating codec context");
    }
    case DECODERERROR_RESETCODEC:
    {

      return QObject::tr("Error retrieving codec settings");
    }
    case DECODERERROR_INVALIDRTPMAPS:
    {

      return QObject::tr("No valid rtpmap");
    }
    case DECODERERROR_INVALIDFMTP:
    {

      return QObject::tr("No valid fmtp");
    }
    case DECODERERROR_INVALIDPACKETIZATIONMODE:
    {

      return QObject::tr("Unsupported packetization mode");
    }
    case DECODERERROR_INVALIDPROFILELEVELID:
    {

      return QObject::tr("Unsupported profile-level-id");
    }
    case DECODERERROR_INVALIDSPROPPARAMETERSETS:
    {

      return QObject::tr("Unsupported sprop-parameter-sets");
    }
    case DECODERERROR_INVALIDCONFIG:
    {

      return QObject::tr("Invalid config");
    }
    case DECODERERROR_OPENCODEC:
    {

      return QObject::tr("Error opening codec");
    }
    default:
    {

      return QString();
    }
  }
}

int32_t FrameDifference(uint16_t frame1, uint16_t frame2)
{
  return std::min(std::abs((static_cast<int32_t>(std::numeric_limits<uint16_t>::max()) - static_cast<int32_t>(frame1)) + static_cast<int32_t>(frame2) + 1), std::abs(static_cast<int32_t>(frame1) - static_cast<int32_t>(frame2)));
}


AVPixelFormat ToFormat(const IMAGEBUFFERTYPE type)
{
  switch (type)
  {
    case IMAGEBUFFERTYPE_INVALID:
    {

      return AV_PIX_FMT_NONE;
    }

    case IMAGEBUFFERTYPE_TEXT:
    {

      return AV_PIX_FMT_RGBA;
    }
    case IMAGEBUFFERTYPE_RGBA:
    {

      return AV_PIX_FMT_RGBA;
    }
    case IMAGEBUFFERTYPE_YUV:
    {

      return AV_PIX_FMT_YUV420P;
    }
    default:
    {

      return AV_PIX_FMT_NONE;
    }
  }
}

///// Methods /////

ImageBuffer::ImageBuffer() :
  playrequestindex_(0),
  type_(IMAGEBUFFERTYPE_INVALID),
  data_({ nullptr, nullptr, nullptr }),
  buffer_(nullptr),
  widths_({ 0, 0, 0 }),
  heights_({ 0, 0, 0 }),
  strides_({ 0, 0, 0 }),
  originalsize_(0),
  time_(0),
  sequencenum_(0),
  marker_(true)
{

}

ImageBuffer::ImageBuffer(const ImageBuffer& imagebuffer) :
  playrequestindex_(imagebuffer.playrequestindex_),
  codec_(imagebuffer.codec_),
  type_(imagebuffer.type_),
  data_(imagebuffer.data_),
  buffer_(imagebuffer.buffer_),
  widths_(imagebuffer.widths_),
  heights_(imagebuffer.heights_),
  strides_(imagebuffer.strides_),
  originalsize_(imagebuffer.originalsize_),
  time_(imagebuffer.time_),
  sequencenum_(imagebuffer.sequencenum_),
  digitallysigned_(imagebuffer.digitallysigned_),
  marker_(imagebuffer.marker_)
{

}

void ImageBuffer::Destroy()
{
  type_ = IMAGEBUFFERTYPE_INVALID;
  data_.fill(nullptr);
  widths_.fill(0);
  heights_.fill(0);
  strides_.fill(0);
  originalsize_ = 0;
  if (buffer_)
  {
    delete [] buffer_;
    buffer_ = nullptr;
  }
}

FreeImageBuffers::FreeImageBuffers()
{

}

FreeImageBuffers::~FreeImageBuffers()
{

}

SPSCFreeFrameBuffers::SPSCFreeFrameBuffers()
{

}

SPSCFreeFrameBuffers::~SPSCFreeFrameBuffers()
{
  queue_.consume_all([this](const ImageBuffer& imagebuffer) { const_cast<ImageBuffer&>(imagebuffer).Destroy(); });

}

ImageBuffer SPSCFreeFrameBuffers::GetFreeImage()
{
  ImageBuffer imagebuffer;
  if (queue_.pop(imagebuffer))
  {

    return imagebuffer;
  }
  else
  {

    return imagebuffer;
  }
}

void SPSCFreeFrameBuffers::AddFreeImage(ImageBuffer& imagebuffer)
{
  if (!queue_.write_available())
  {
    imagebuffer.Destroy();

  }
  else
  {
    queue_.push(imagebuffer);

  }
}

VectorFreeFrameBuffer::VectorFreeFrameBuffer()
{

}

VectorFreeFrameBuffer::~VectorFreeFrameBuffer()
{
  for (ImageBuffer& imagebuffer : queue_)
  {
    imagebuffer.Destroy();

  }
}

ImageBuffer VectorFreeFrameBuffer::GetFreeImage()
{
  if (queue_.empty())
  {
    
    return ImageBuffer();
  }
  else
  {
    ImageBuffer imagebuffer = queue_.back();
    queue_.pop_back();
    return imagebuffer;
  }
}

void VectorFreeFrameBuffer::AddFreeImage(ImageBuffer& imagebuffer)
{
  if (queue_.size() > 5) // No need for the queue to get any bigger than this
  {
    imagebuffer.Destroy();
    
  }
  else
  {
    queue_.push_back(imagebuffer);

  }
}

Decoder::Decoder(const uint64_t id, const utility::PublicKey& publickey) :
  id_(id),
  publickey_(publickey),
  codec_(nullptr),
  context_(nullptr),
  hwdevice_(nullptr),
  frame_(av_frame_alloc()),
  swsframe_(av_frame_alloc()),
  swscontext_(nullptr)
{
  av_init_packet(&packet_);
  packet_.dts = AV_NOPTS_VALUE;
  packet_.pts = AV_NOPTS_VALUE;
}

Decoder::~Decoder()
{
  Destroy();

  if (packet_.buf)
  {
    av_free_packet(&packet_);
    packet_.buf = nullptr;
  }

  if (frame_)
  {
    if (frame_->hw_frames_ctx)
    {
      av_buffer_unref(&frame_->hw_frames_ctx);
      frame_->hw_frames_ctx = nullptr;
    }

    av_frame_free(&frame_);
    frame_ = nullptr;
  }

  if (swsframe_)
  {
    av_frame_free(&swsframe_);
    swsframe_ = nullptr;
  }
}

void Decoder::Destroy()
{
  // FFMPEG stuff
  if (context_)
  {
    context_->extradata_size = 0;
    if (context_->extradata)
    {
      delete[] context_->extradata;
      context_->extradata = nullptr;
    }

    if (context_->hw_device_ctx)
    {
      av_buffer_unref(&context_->hw_device_ctx);
      context_->hw_device_ctx = nullptr;
    }

    avcodec_free_context(&context_);
    context_ = nullptr;
  }

  if (hwdevice_)
  {
    av_buffer_unref(&hwdevice_);
    hwdevice_ = nullptr;
  }

  if (codec_)
  {
    codec_ = nullptr;

  }

  if (swscontext_)
  {
    sws_freeContext(swscontext_);
    swscontext_ = nullptr;
  }
}

ImageBuffer Decoder::Decode(const uint64_t playrequestindex, const bool marker, const uint64_t time, const int64_t sequencenum, const uint8_t* signature, const size_t signaturesize, const char* signaturedata, const size_t signaturedatasize, const uint8_t* data, const int size, FreeImageBuffers* freeimagebuffers)
{
  if (context_ == nullptr)
  {
    // Shouldn't happen..?
    return ImageBuffer();
  }

  packet_.data = const_cast<uint8_t*>(data); // Promise not to change the data...
  packet_.size = size;

  int framefinished = 0;
  const int result = avcodec_decode_video2(context_, frame_, &framefinished, &packet_);
  if (result < 0)
  {

    return ImageBuffer();
  }
  else if (framefinished > 0)
  {
    ImageBuffer imagebuffer = freeimagebuffers->GetFreeImage();
    if (context_->pix_fmt == AV_PIX_FMT_CUDA)
    {
      imagebuffer.type_ = IMAGEBUFFERTYPE_NV12;

      if (frame_->hw_frames_ctx == nullptr)
      {
        frame_->hw_frames_ctx = av_buffer_ref(context_->hw_frames_ctx);

      }

      swsframe_->format = AV_PIX_FMT_NV12;
      auto ret = av_hwframe_transfer_data(swsframe_, frame_, 0);
      if (ret)
      {
        // Not sure what to do here, SetMessage and log messages could spam, lets just ignore it for the moment...
        return ImageBuffer();
      }

      const std::array<int, 3> widths =
      {
        swsframe_->width,
        swsframe_->width / 2,
        0
      };
      const std::array<int, 3> heights =
      {
        swsframe_->height,
        swsframe_->height / 2,
        0
      };
      const std::array<int, 3> strides =
      {
        swsframe_->linesize[0],
        swsframe_->linesize[1],
        0
      };
      const int ysize = strides[0] * heights[0];
      const int usize = strides[1] * heights[1];
      if (widths != imagebuffer.widths_ || (heights != imagebuffer.heights_) || strides != imagebuffer.strides_)
      {
        imagebuffer.widths_ = widths;
        imagebuffer.heights_ = heights;
        imagebuffer.strides_ = strides;
        if (imagebuffer.buffer_)
        {
          delete imagebuffer.buffer_;

        }
        imagebuffer.buffer_ = new uint8_t[ysize + usize + 512];
      }
      imagebuffer.data_[0] = imagebuffer.buffer_;
      imagebuffer.data_[1] = imagebuffer.buffer_ + ysize + 64;
      memcpy(imagebuffer.data_[0], swsframe_->data[0], ysize);
      memcpy(imagebuffer.data_[1], swsframe_->data[1], usize);
    }
    else if (context_->pix_fmt == AV_PIX_FMT_QSV)
    {
      int i = 0;//TODO QuickSync HW acceleration through QSV, data[3] contains a pointer to the mfxFrameSurface1 structure. could just av_hwframe_transfer_data... or maybe pass directly to the ImageBuffer->gpu if possible?

    }
    else if ((context_->pix_fmt == AV_PIX_FMT_YUV420P) || (context_->pix_fmt == AV_PIX_FMT_YUVJ420P)) // This format is converted on the GPU, so we pass 3 planes in
    {
      imagebuffer.type_ = IMAGEBUFFERTYPE_YUV;
      const std::array<int, 3> widths =
      {
        frame_->width,
        frame_->width / 2,
        frame_->width / 2
      };
      const std::array<int, 3> heights =
      {
        frame_->height,
        frame_->height / 2,
        frame_->height / 2
      };
      const std::array<int, 3> strides =
      {
        frame_->linesize[0],
        frame_->linesize[1],
        frame_->linesize[2]
      };
      const int ysize = strides[0] * heights[0];
      const int usize = strides[1] * heights[1];
      const int vsize = strides[2] * heights[2];
      if (widths != imagebuffer.widths_ || (heights != imagebuffer.heights_) || strides != imagebuffer.strides_)
      {
        imagebuffer.widths_ = widths;
        imagebuffer.heights_ = heights;
        imagebuffer.strides_ = strides;
        if (imagebuffer.buffer_)
        {
          delete imagebuffer.buffer_;

        }
        imagebuffer.buffer_ = new uint8_t[ysize + usize + vsize + 512];
      }
      imagebuffer.data_[0] = imagebuffer.buffer_;
      imagebuffer.data_[1] = imagebuffer.buffer_ + ysize + 64;
      imagebuffer.data_[2] = imagebuffer.buffer_ + ysize + usize + 128;
      memcpy(imagebuffer.data_[0], frame_->data[0], ysize);
      memcpy(imagebuffer.data_[1], frame_->data[1], usize);
      memcpy(imagebuffer.data_[2], frame_->data[2], vsize);
    }
    else // Convert it to RGB
    {
      if (swscontext_ == nullptr)
      {
        swscontext_ = sws_getContext(frame_->width, frame_->height, context_->pix_fmt, frame_->width, frame_->height, AVPIXELFORMAT, 0, nullptr, nullptr, nullptr);
        if (swscontext_ == nullptr)
        {
          imagebuffer.Destroy();
          return ImageBuffer();
        }
      }

      if ((imagebuffer.widths_[0] != frame_->width) || (imagebuffer.heights_[0] != frame_->height)) // Realloc AVFrame if not the same size
      {
        const int size = av_image_get_buffer_size(AVPIXELFORMAT, frame_->width, frame_->height, AVALIGNMENT);
        swsframe_->width = frame_->width;
        swsframe_->height = frame_->height;
        swsframe_->format = AVPIXELFORMAT;
        av_image_fill_arrays(swsframe_->data, swsframe_->linesize, (uint8_t*)av_malloc(size * sizeof(uint8_t)), AVPIXELFORMAT, frame_->width, frame_->height, AVALIGNMENT);
        imagebuffer.widths_[0] = frame_->width;
        imagebuffer.heights_[0] = frame_->height;
      }
      
      if (sws_scale(swscontext_, frame_->data, frame_->linesize, 0, frame_->height, swsframe_->data, swsframe_->linesize) < 0)
      {
        imagebuffer.Destroy();
        return ImageBuffer();
      }
      imagebuffer.type_ = IMAGEBUFFERTYPE_RGBA;
      if ((imagebuffer.widths_[0] != frame_->width) || (imagebuffer.heights_[0] != frame_->height))
      {
        imagebuffer.widths_[0] = frame_->width;
        imagebuffer.heights_[0] = frame_->height;
        const size_t size = frame_->width * frame_->height * 4;
        if (imagebuffer.buffer_)
        {
          delete imagebuffer.buffer_;

        }
        imagebuffer.buffer_ = new uint8_t[size];
      }

      imagebuffer.data_[0] = imagebuffer.buffer_;
      memcpy(imagebuffer.data_[0], frame_->data[0], size);
    }

    boost::optional<bool> digitallysigned;
    if (publickey_.GetKey() && signature && signaturedata)
    {
      if (signaturesize == 256)
      {
        digitallysigned = publickey_.Verify(reinterpret_cast<const unsigned char*>(signaturedata), signaturedatasize, signature);

      }
      else
      {
        digitallysigned = false;

      }
    }
    
    imagebuffer.codec_ = GetCodec();
    imagebuffer.originalsize_ = size;
    imagebuffer.playrequestindex_ = playrequestindex;
    imagebuffer.time_ = time;
    imagebuffer.sequencenum_ = sequencenum;
    imagebuffer.digitallysigned_ = digitallysigned;
    imagebuffer.marker_ = marker;
    return imagebuffer;
  }
  else
  {

    return ImageBuffer();
  }
}

}