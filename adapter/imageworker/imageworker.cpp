#include "imageworker.h"

#include <QMetaObject>
#include <QRunnable>
#include <algorithm>
#include <opencv2/objdetect/barcode.hpp>

ImageWorker::ImageWorker(QObject* parent)
    : detector(nullptr), tracker(nullptr) {
}

ImageWorker::~ImageWorker() {
    if (detector) {
        delete detector;
        detector = nullptr;
    }
    if (tracker) {
        delete tracker;
        tracker = nullptr;
    }
}

void ImageWorker::startSession() {
    detector = new ObjectDetector();
    detector->init();
    tracker = new Tracker();
    tracker->init();
}

void ImageWorker::fetchSession(const cv::Mat& frame) {
    std::vector<DetectionDto> detResults;
    detector->process(frame, detResults);
    std::vector<TrackDto> tracked = tracker->update(detResults);
    QList<TrackDto> output(tracked.begin(), tracked.end());
    emit done(output);

    if (++_frameCount % 20 != 0)
        return;

    cv::Mat frameCopy = frame.clone();
    QList<TrackDto> trackedCopy = output;
    QPointer<ImageWorker> self = this;

    QThreadPool::globalInstance()->start(QRunnable::create([frameCopy, trackedCopy, self]() {
        cv::barcode::BarcodeDetector barcodeDetector;
        QList<BarcodeDto> results;

        for (const TrackDto& track : trackedCopy) {
            const BBox& b = track.getBBox();
            int x = static_cast<int>(b.getXtl());
            int y = static_cast<int>(b.getYtl());
            int w = static_cast<int>(b.getWidth());
            int h = static_cast<int>(b.getHeight());

            // Clamp ROI to frame bounds
            x = std::max(0, x);
            y = std::max(0, y);
            w = std::min(w, frameCopy.cols - x);
            h = std::min(h, frameCopy.rows - y);

            if (w <= 0 || h <= 0)
                continue;

            cv::Mat trackROI = frameCopy(cv::Rect(x, y, w, h));

            std::vector<std::string> decodedInfo;
            std::vector<std::string> decodedType;

            bool ok = barcodeDetector.detectAndDecodeWithType(trackROI, decodedInfo, decodedType);
            if (!ok || decodedInfo.empty() || decodedInfo[0].empty())
                continue;

            results.append(BarcodeDto(track.getId(),
                                      decodedInfo[0],
                                      decodedType.empty() ? "UNKNOWN" : decodedType[0],
                                      track.getBBox()));
        }

        if (self) {
            QMetaObject::invokeMethod(self, "updateBarcodeResults",
                                      Qt::QueuedConnection,
                                      Q_ARG(QList<BarcodeDto>, results));
        }
    }));
}

void ImageWorker::updateBarcodeResults(const QList<BarcodeDto>& results) {
    _barcodeResults = results;
    emit barcodeDetected(_barcodeResults);
}

void ImageWorker::stopSession() {
    detector->stop();
    tracker->stop();
    delete tracker;
    tracker = nullptr;
}
