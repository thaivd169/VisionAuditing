#ifndef ADAPTER_VIDEO_IMAGEWORKER_H
#define ADAPTER_VIDEO_IMAGEWORKER_H

#include <QList>
#include <QObject>
#include <QPointer>

#include "domain/entities/entity.h"
#include "domain/services/ibarcoder.h"
#include "domain/services/idetector.h"
#include "domain/services/itracker.h"
#include "domain/value_objects/barcode.h"
#include "domain/value_objects/track.h"

class ImageWorker : public QObject {
    Q_OBJECT
   public:
    explicit ImageWorker(std::unique_ptr<IDetector> detector,
                         std::unique_ptr<ITracker> tracker,
                         std::unique_ptr<IBarcoder> barcoder,
                         QObject* parent = nullptr);
    ImageWorker(const ImageWorker& imageWorkder) = delete;
    ImageWorker& operator=(const ImageWorker&) = delete;

    ~ImageWorker();

   signals:
    void done(const QList<Track>& tracks);

   public slots:
    void updateIsOcrProcessing(const bool& status);
    void fetch(const cv::Mat& frame);

   private:
    bool isOcrProcessing;
    QList<Track> tracks_;
    std::unique_ptr<IBarcoder> barcoder_;
    std::unique_ptr<IDetector> detector_;
    std::unique_ptr<ITracker> tracker_;
};

#endif  // ADAPTER_VIDEO_IMAGEWORKER_H
