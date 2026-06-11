#ifndef DOMAIN_SERVICES_IDETECTOR_H
#define DOMAIN_SERVICES_IDETECTOR_H

#include <opencv2/core/mat.hpp>
#include <optional>
#include <vector>

#include "domain/value_objects/detection_box.h"
#include "domain/value_objects/track.h"

class IDetector {
   public:
    virtual ~IDetector() = default;
    virtual std::optional<std::vector<DetectionBox>> process(const cv::Mat& frame) = 0;
};

#endif  // DOMAIN_SERVICES_IDETECTOR_H