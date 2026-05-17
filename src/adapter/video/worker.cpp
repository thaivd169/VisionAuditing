#include "imageworker.h"

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
}

void ImageWorker::stopSession() {
    detector->stop();
    tracker->stop();
    delete tracker;
    tracker = nullptr;
}
