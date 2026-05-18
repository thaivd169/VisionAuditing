#ifndef ADAPTER_VIDEO_IMAGEWORKER_H
#define ADAPTER_VIDEO_IMAGEWORKER_H

#include <QList>
#include <QObject>
#include <QPointer>

#include "domain/services/idetector.h"
#include "domain/services/itracker.h"
#include "domain/value_objects/track.h"

class ImageWorker : public QObject {
    Q_OBJECT
   public:
    explicit ImageWorker(std::unique_ptr<IDetector> detector,
                         std::unique_ptr<ITracker> tracker,
                         QObject* parent = nullptr);
    ImageWorker(const ImageWorker& imageWorkder) = delete;
    ImageWorker& operator=(const ImageWorker&) = delete;

    ~ImageWorker();

   signals:
    void done(const QList<Track>& tracks);

   public slots:
    void fetch(const cv::Mat& frame);

   private:
    QList<Track> tracks_;
    std::unique_ptr<IDetector> detector_;
    std::unique_ptr<ITracker> tracker_;
};

#endif  // ADAPTER_VIDEO_IMAGEWORKER_H
