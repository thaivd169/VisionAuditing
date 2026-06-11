#include "yolor.h"

#include "domain/value_objects/bounding_box.h"
#include "lib/yolos_cpp/include/yolos/tasks/detection.hpp"

Yolor::Yolor()
    : infer_(std::make_unique<yolos::det::YOLODetector>(
          "/home/thaivd/TDIC/VisionAuditing/assets/detection/yolo11n.onnx",
          "/home/thaivd/TDIC/VisionAuditing/assets/detection/coco.names",
          false)) {
}

Yolor::~Yolor() {
    infer_.reset();
}

std::optional<std::vector<DetectionBox>> Yolor::process(const cv::Mat& frame) {
    if (!infer_)
        return std::nullopt;

    std::vector<yolos::det::Detection> detections = infer_->detect(frame);
    std::vector<DetectionBox> results;
    results.reserve(detections.size());

    for (const auto& item : detections) {
        auto maybeBox = BoundingBox::create(item.box.x,
                                            item.box.y,
                                            item.box.width,
                                            item.box.height);
        if (!maybeBox)
            continue;

        auto maybeDet = DetectionBox::create(maybeBox.value(), item.conf,
                                             infer_->getClassNames().at(item.classId));
        if (!maybeDet)
            continue;

        results.push_back(maybeDet.value());
    }

    return results;
}
