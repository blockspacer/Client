// videochartview.h
// 

#ifndef IDNUONLE5ZXCZZXCKLZJCKZXCXDSDS3TFS
#define IDNUONLE5ZXCZZXCKLZJCKZXCXDSDS3TFS

///// Includes /////

#include <array>
#include <boost/asio.hpp>
#include <memory>
#include <monocleprotocol/client/connection.hpp>
#include <QGridLayout>
#include <QtCharts>
#include <QWidget>
#include <vector>

#include "view.h"

///// Namespaces /////

namespace client
{

///// Declarations /////

class Device;
class Recording;

///// Classes /////

class VideoChartView : public View
{
 Q_OBJECT

 public:

  VideoChartView(VideoWidget* videowidget, CUcontext cudacontext, const QColor& selectedcolour, const unsigned int x, const unsigned int y, const unsigned int width, const unsigned int height, const boost::shared_ptr<client::Device>& device, const QSharedPointer<client::Recording>& recording, const std::vector< QSharedPointer<client::RecordingTrack> >& tracks, const QResource* arial);
  ~VideoChartView();

  virtual VIEWTYPE GetViewType() const override { return VIEWTYPE_MONOCLECHART; }

  virtual void GetMenu(QMenu& parent) override;

  virtual double GetAspectRatio() const override;

  virtual bool GetImage(ImageBuffer& imagebuffer) override;

  virtual int64_t GetTimeOffset() const override { return 0; }

  virtual void FrameStep(const bool forwards) override;
  virtual void Play(const uint64_t time, const boost::optional<uint64_t>& numframes) override;
  virtual void Pause(const boost::optional<uint64_t>& time) override;
  virtual void Stop() override;
  virtual void Scrub(const uint64_t time) override;

  inline const boost::shared_ptr<Device>& GetDevice() const { return device_; }
  inline const QSharedPointer<Recording>& GetRecording() const { return recording_; }

  virtual void wheelEvent(QWheelEvent* event) override;
  virtual void SetPosition(VideoWidget* videowidget, const unsigned int x, const unsigned int y, const unsigned int width, const unsigned int height, const ROTATION rotation, const bool mirror, const bool stretch, const bool makecurrent) override;

 private:

  void SendImage();
  void CloseConnections();
  bool AllZero(const QLineSeries* series) const;

  boost::shared_ptr<client::Device> device_;
  QSharedPointer<Recording> recording_;
  std::vector< QSharedPointer<RecordingTrack> > tracks_;

  QWidget* widget_;
  QGridLayout* layout_;
  QChartView chart_;
  std::vector< std::pair<monocle::ObjectClass, QLineSeries*> > series_;
  QDateTimeAxis* xaxis_;
  QValueAxis* yaxis_;

  std::vector<monocle::client::Connection> streamsconnections_;

 private slots:

};

}

#endif
