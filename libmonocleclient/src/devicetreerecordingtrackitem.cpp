// devicetreerecordingtrackitem.cpp
//

///// Includes /////

#include "monocleclient/devicetreerecordingtrackitem.h"

#include <network/uri.hpp>
#include <QMenu>
#include <QMessageBox>

#include "monocleclient/mainwindow.h"
#include "monocleclient/manageonvifwindow.h"
#include "monocleclient/managetrackwindow.h"
#include "monocleclient/receiver.h"
#include "monocleclient/recording.h"
#include "monocleclient/recordingjobsource.h"
#include "monocleclient/recordinglogwindow.h"
#include "monocleclient/recordingtrack.h"

///// Namespaces /////

namespace client
{

///// Methods /////

DeviceTreeRecordingTrackItem::DeviceTreeRecordingTrackItem(DeviceTreeItem* parent, const boost::shared_ptr<Device>& device, const QSharedPointer<client::Recording>& recording, const QSharedPointer<client::RecordingJob>& recordingjob, const QSharedPointer<client::RecordingJobSource>& recordingjobsource, const QSharedPointer<client::RecordingJobSourceTrack>& recordingjobsourcetrack, const QSharedPointer<client::RecordingTrack>& track, const QIcon& cameraicon) :
  DeviceTreeItem(parent, GetName(track), DEVICE_TREE_ITEM_TYPE::DEVICE_RECORDING_TRACK),
  device_(device),
  recording_(recording),
  recordingjob_(recordingjob),
  recordingjobsource_(recordingjobsource),
  recordingjobsourcetrack_(recordingjobsourcetrack),
  track_(track),
  edit_(new QAction("Edit", this)),
  remove_(new QAction("Remove", this)),
  managedevice_(new QAction("Manage Device", this)),
  viewlog_(new QAction("View Log", this))
{
  connect(edit_, &QAction::triggered, this, &DeviceTreeRecordingTrackItem::Edit);
  connect(remove_, &QAction::triggered, this, &DeviceTreeRecordingTrackItem::Remove);
  connect(managedevice_, &QAction::triggered, this, &DeviceTreeRecordingTrackItem::ManageDevice);
  connect(viewlog_, &QAction::triggered, this, &DeviceTreeRecordingTrackItem::ViewLog);
  connect(recording.get(), &Recording::TrackChanged, this, &DeviceTreeRecordingTrackItem::TrackChanged);
  connect(track.get(), &RecordingTrack::DataRate, this, &DeviceTreeRecordingTrackItem::DataRate);

  setIcon(0, cameraicon);
}

DeviceTreeRecordingTrackItem::~DeviceTreeRecordingTrackItem()
{
  removetrackconnection_.Close();

}

void DeviceTreeRecordingTrackItem::ContextMenuEvent(const QPoint& pos)
{
  const QSharedPointer<Receiver> receiver = device_->GetReceiver(recordingjobsource_->GetReceiverToken());
  if (!receiver)
  {
    QMessageBox(QMessageBox::Warning, tr("Error"), tr("Unable to find receiver: ") + QString::number(recordingjobsource_->GetReceiverToken()), QMessageBox::Ok, nullptr, Qt::MSWindowsFixedSizeDialogHint).exec();
    return;
  }

  QMenu* menu = new QMenu(treeWidget());
  menu->addAction(edit_);
  menu->addAction(remove_);
  if (IsONVIF(receiver->GetMediaUri().toStdString()))
  {
    menu->addAction(managedevice_);

  }
  menu->addAction(viewlog_);
  menu->exec(pos);
}

void DeviceTreeRecordingTrackItem::Expanded()
{

}

void DeviceTreeRecordingTrackItem::Collapsed()
{

}

void DeviceTreeRecordingTrackItem::DoubleClicked()
{
  if (track_->GetTrackType() != monocle::TrackType::Video)
  {

    return;
  }
  MainWindow::Instance()->GetVideoWidgetsMgr().CreateVideoView(device_, recording_, track_);
}

QString DeviceTreeRecordingTrackItem::GetName(const QSharedPointer<client::RecordingTrack>& track) const
{
  if (track->GetDescription().isEmpty())
  {

    return monocle::EnumNameTrackType(track->GetTrackType());
  }
  else
  {

    return track->GetDescription();
  }
}

bool DeviceTreeRecordingTrackItem::IsONVIF(const std::string& mediauri) const
{
  try
  {
    const network::uri uri(mediauri);
    if (uri.has_scheme() && ((uri.scheme().compare("http") == 0) || (uri.scheme().compare("https") == 0)) && uri.has_path() && (uri.path().compare("/onvif/device_service") == 0))
    {

      return true;
    }
    else
    {

      return false;
    }
  }
  catch (...)
  {

    return false;
  }
}

void DeviceTreeRecordingTrackItem::Edit(bool)
{
  boost::make_shared<ManageTrackWindow>(treeWidget(), device_, recording_, recordingjob_, recordingjobsource_, recordingjobsourcetrack_, track_, QString())->exec();

}

void DeviceTreeRecordingTrackItem::Remove(bool)
{
  if (QMessageBox::question(treeWidget(), tr("Remove"), tr("Are you sure?"), QMessageBox::Yes | QMessageBox::No) == QMessageBox::Yes)
  {
    std::vector<uint32_t> removetracks = { track_->GetId() };
    for (const QSharedPointer<RecordingTrack>& track : recording_->GetObjectDetectorTracks())
    {
      if (track->GetToken() == QString::number(track_->GetId()))
      {
        removetracks.push_back(track->GetId());

      }
    }

    removetrackconnection_ = device_->RemoveTracks(recording_->GetToken(), removetracks, [](const std::chrono::steady_clock::duration latency, const monocle::client::REMOVETRACKSRESPONSE& removetracksresponse)
    {
      if (removetracksresponse.GetErrorCode() != monocle::ErrorCode::Success)
      {
        QMessageBox(QMessageBox::Warning, tr("Error"), tr("Remove failed: ") + QString::fromStdString(removetracksresponse.GetErrorText()), QMessageBox::Ok, nullptr, Qt::MSWindowsFixedSizeDialogHint).exec();
        return;
      }
    });
  }
}

void DeviceTreeRecordingTrackItem::ManageDevice(bool)
{
  const QSharedPointer<Receiver> receiver = device_->GetReceiver(recordingjobsource_->GetReceiverToken());
  if (!receiver)
  {
    QMessageBox(QMessageBox::Warning, tr("Error"), tr("Unable to find receiver: ") + QString::number(recordingjobsource_->GetReceiverToken()), QMessageBox::Ok, nullptr, Qt::MSWindowsFixedSizeDialogHint).exec();
    return;
  }

  if (!IsONVIF(receiver->GetMediaUri().toStdString()))
  {

    return;
  }
  
  ManageONVIFWindow(treeWidget(), sock::ProxyParams(sock::PROXYTYPE_HTTP, device_->GetAddress().toStdString(), device_->GetPort(), true, device_->GetUsername().toStdString(), device_->GetPassword().toStdString()), receiver->GetMediaUri(), receiver->GetUsername(), receiver->GetPassword()).exec();
}

void DeviceTreeRecordingTrackItem::ViewLog(bool)
{
  RecordingLogWindow(treeWidget(), device_, { recording_ }, { track_ }, std::vector< QSharedPointer<client::RecordingJob> >(), std::vector< QSharedPointer<client::RecordingJobSourceTrack> >()).exec();

}

void DeviceTreeRecordingTrackItem::TrackChanged(const QSharedPointer<client::RecordingTrack>& track)
{
  if (track_ != track)
  {

    return;
  }
  setText(0, GetName(track));
}

void DeviceTreeRecordingTrackItem::DataRate(const uint64_t datarate)
{
  setToolTip(0, QString::number(datarate / 1024) + "kB/s");

}

}
