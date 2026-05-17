#ifndef INFRA_DETECTOR_YOLOR_H
#define INFRA_DETECTOR_YOLOR_H

#include <memory>

#include "domain/services/idetector.h"

namespace yolos {
namespace det {
class YOLODetector;
}
}  // namespace yolos

class Yolor : public IDetector {
   public:
    Yolor();
    Yolor(const Yolor&) = delete;
    Yolor& operator=(const Yolor&) = delete;
    ~Yolor();

    std::optional<std::vector<DetectionBox>> process(const cv::Mat& frame) override;

   private:
    std::unique_ptr<yolos::det::YOLODetector> infer_;
};

#endif  // INFRA_DETECTOR_YOLOR_H
