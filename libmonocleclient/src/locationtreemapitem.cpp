// locationtreemapitem.cpp
//

///// Includes /////

#include "monocleclient/locationtreemapitem.h"

#include "monocleclient/devicetreeitem.h"
#include "monocleclient/locationtree.h"
#include "monocleclient/locationtreeitem.h"
#include "monocleclient/locationtreerecordingitem.h"
#include "monocleclient/mainwindow.h"
#include "monocleclient/map.h"
#include "monocleclient/recording.h"

///// Namespaces /////

namespace client
{

///// Methods /////

LocationTreeMapItem::LocationTreeMapItem(LocationTree* parent, const boost::shared_ptr<Device>& device, const QSharedPointer<Map>& map, const QIcon& mapicon) :
  QTreeWidgetItem(parent, QStringList(std::initializer_list<QString>({ map->GetName() })), DEVICE_TREE_ITEM_TYPE::DEVICE_MAP),
  device_(device),
  map_(map)
{
  setIcon(0, mapicon);

}

LocationTreeMapItem::LocationTreeMapItem(LocationTreeItem* parent, const boost::shared_ptr<Device>& device, const QSharedPointer<Map>& map, const QIcon& mapicon) :
  QTreeWidgetItem(parent, QStringList(std::initializer_list<QString>({ map->GetName() })), DEVICE_TREE_ITEM_TYPE::DEVICE_MAP),
  device_(device),
  map_(map)
{
  setIcon(0, mapicon);

}

LocationTreeMapItem::~LocationTreeMapItem()
{

}

void LocationTreeMapItem::ContextMenuEvent(const QPoint& pos)
{

}

void LocationTreeMapItem::Expanded()
{

}

void LocationTreeMapItem::Collapsed()
{

}

void LocationTreeMapItem::DoubleClicked()
{
  MainWindow::Instance()->GetVideoWidgetsMgr().CreateMapView(device_, map_);

}

void LocationTreeMapItem::SetFilter(const QString& filter)
{
  if (filter.isEmpty())
  {
    setHidden(false);

  }
  else
  {
    if ((map_->GetName().indexOf(filter, 0, Qt::CaseInsensitive) == -1) && (map_->GetLocation().indexOf(filter, 0, Qt::CaseInsensitive) == -1))
    {
      setHidden(true);

    }
    else
    {
      setHidden(false);

    }
  }
}

uint64_t LocationTreeMapItem::GetToken() const
{
  return map_->GetToken();
}

void LocationTreeMapItem::Clear()
{
  for (int i = (childCount()-1); i >= 0; --i)
  {
    removeChild(child(i));

  }
}

bool LocationTreeMapItem::operator<(const QTreeWidgetItem& rhs) const
{
  uint64_t guiorder = 0;
  if (rhs.type() == DEVICE_TREE_ITEM_TYPE::DEVICE_RECORDING)
  {
    const LocationTreeRecordingItem* recordingitem = static_cast<const LocationTreeRecordingItem*>(&rhs);
    guiorder = recordingitem->GetRecording()->GetGuiOrder();
  }
  else if (rhs.type() == DEVICE_TREE_ITEM_TYPE::DEVICE_MAP)
  {
    const LocationTreeMapItem* mapitem = static_cast<const LocationTreeMapItem*>(&rhs);
    guiorder = mapitem->GetMap()->GetGuiOrder();
  }
  return (map_->GetGuiOrder() < guiorder);
}

}
