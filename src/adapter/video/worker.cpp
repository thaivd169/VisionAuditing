#include "worker.h"

ImageWorker::ImageWorker(std::unique_ptr<IDetector> detector,
                         std::unique_ptr<ITracker> tracker,
                         QObject* parent)
    : detector_(std::move(detector)),
      tracker_(std::move(tracker)) {
}

ImageWorker::~ImageWorker() {
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
}
