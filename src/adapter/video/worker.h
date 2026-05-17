#ifndef ADAPTER_IMAGEWORKER_H
#define ADAPTER_IMAGEWORKER_H

#include <QObject>
#include <QPointer>

#include "adapter/detection/objectdetector.h"
#include "adapter/mot/tracker.h"
#include "domain/detection/dto.h"
#include "domain/mot/dto.h"

class ImageWorker : public QObject {
    Q_OBJECT
   public:
    explicit ImageWorker(QObject* parent = nullptr);
    ImageWorker(const ImageWorker& imageWorkder) = delete;
    ImageWorker& operator=(const ImageWorker&) = delete;

    ~ImageWorker();

   signals:
    void done(const QList<TrackDto>& tracks);

   public slots:
    void startSession();
    void fetchSession(const cv::Mat& frame);
    void stopSession();

   private:
    QList<TrackDto> tracks;
    ObjectDetector* detector;
    Tracker* tracker;
};

#endif  // ADAPTER_IMAGEWORKER_H
