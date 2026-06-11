#include "detection_box.h"

DetectionBox::DetectionBox()
    : confScore(0.0f) {
}

std::optional<DetectionBox> DetectionBox::create(const BoundingBox& bbox,
                                                 const float& confScore,
                                                 const std::string& className) {
    if (confScore < 0.0f || confScore > 1.0f) {
        return std::nullopt;
    }
    if (className.empty()) {
        return std::nullopt;
    }

    return DetectionBox(bbox, confScore, className);
}

DetectionBox::DetectionBox(const BoundingBox& _bbox,
                           const float& _confScore,
                           const std::string& _className)
    : bbox(_bbox),
      confScore(_confScore),
      className(_className) {
}

BoundingBox DetectionBox::getBoundingBox() const {
    return bbox;
}

float DetectionBox::getConfidenceScore() const {
    return confScore;
}

std::string DetectionBox::getClassName() const {
    return className;
}

DetectionBox::DetectionBox(const DetectionBox& _other)
    : bbox(_other.bbox),
      confScore(_other.confScore),
      className(_other.className) {
}

DetectionBox& DetectionBox::operator=(const DetectionBox& _other) {
    if (this == &_other)
        return *this;
    bbox = _other.bbox;
    confScore = _other.confScore;
    className = _other.className;
    return *this;
}