#include "imageworker.h"

ImageWorker::ImageWorker(QObject* parent)
    : detector(nullptr) {
}

ImageWorker::~ImageWorker() {
    if (detector) {
        delete detector;
        detector = nullptr;
    }
}

void ImageWorker::startSession() {
    detector = new ObjectDetector();
    detector->init();
}

void ImageWorker::fetchSession(const cv::Mat& frame) {
    std::vector<DetectionDto> results;
    detector->process(frame, results);
    QList<DetectionDto> output;
    for (const auto& result : results) {
        output.append(result);
    }
    emit done(output);
}

void ImageWorker::stopSession() {
    detector->stop();
}
