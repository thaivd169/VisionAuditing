#ifndef IMAGEWORKER_H
#define IMAGEWORKER_H

#include <QObject>
#include <QPointer>
#include <QThreadPool>

#include "adapter/detection/objectdetector.h"
#include "adapter/mot/tracker.h"
#include "domain/barcode/dto.h"
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
    void barcodeDetected(const QList<BarcodeDto>& barcodes);

   public slots:
    void startSession();
    void fetchSession(const cv::Mat& frame);
    void stopSession();

   private slots:
    void updateBarcodeResults(const QList<BarcodeDto>& results);

   private:
    QList<TrackDto> tracks;
    ObjectDetector* detector;
    Tracker* tracker;
    int _frameCount = 0;
    QList<BarcodeDto> _barcodeResults;
};

#endif  // IMAGEWORKER_H
