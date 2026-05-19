#include "worker.h"

#include <QDebug>
#include <QPointer>
#include <QRunnable>
#include <QThreadPool>
#include <QUuid>

ImageWorker::ImageWorker(std::unique_ptr<IDetector> detector,
                         std::unique_ptr<ITracker> tracker,
                         std::unique_ptr<IBarcoder> barcoder,
                         QObject* parent)
    : isOcrProcessing(false),
      detector_(std::move(detector)),
      tracker_(std::move(tracker)),
      barcoder_(std::move(barcoder)) {
}

ImageWorker::~ImageWorker() {
}

void ImageWorker::updateIsOcrProcessing(const bool& status) {
    isOcrProcessing = status;
}

void ImageWorker::fetch(const cv::Mat& frame) {
    auto maybeDects = detector_->process(frame);
    if (!maybeDects) {
        return;
    }
    auto maybeTracks = tracker_->update(maybeDects.value());
    if (!maybeTracks) {
        return;
    }
    QList<Track> output(maybeTracks.value().begin(), maybeTracks.value().end());
    emit done(output);

    if (isOcrProcessing) {
        return;
    }

    cv::Mat frameCopy = frame.clone();
    QList<Track> trackedCopy = output;
    QPointer<ImageWorker> self = this;

    QThreadPool::globalInstance()->start(QRunnable::create([frameCopy, trackedCopy, self]() {
        if (self) {
            QMetaObject::invokeMethod(self, "updateIsOcrProcessing",
                                      Qt::QueuedConnection,
                                      Q_ARG(bool, true));
        }

        QList<Entity> results;
        // qDebug() << "+== start with size " << trackedCopy.size();

        for (const Track& track : trackedCopy) {
            qDebug() << "-== Start with object ID " << track.getId();
            const auto& b = track.getBoundingBox();
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

            auto maybeBarcodes = self->barcoder_->decode(trackROI);
            if (!maybeBarcodes) {
                continue;
            }
            for (const auto& barcode : maybeBarcodes.value()) {
                qDebug() << "Decoded Id:" << track.getId() << " - " << barcode.getFormat() << " - " << barcode.getData();
                // results.append(BarcodeDto(track.getId(),
                //                           barcode.getData(),
                //                           barcode.getFormat(),
                //                           track.getBBox()));
            }
        }

        if (self) {
            // QMetaObject::invokeMethod(self, "updateBarcodeResults",
            //                           Qt::QueuedConnection,
            //                           Q_ARG(QList<Barcode>, results));
            QMetaObject::invokeMethod(self, "updateIsOcrProcessing",
                                      Qt::QueuedConnection,
                                      Q_ARG(bool, false));
            qDebug() << "+== Run complented";
        }
    }));
}
