#include "objectdetector.h"
#include "lib/yolos_cpp/include/yolos/tasks/detection.hpp"
#include <string>


class Yolo11Concrete : public IDetector {
public:
    Yolo11Concrete() : dec(nullptr) {};
    ~Yolo11Concrete() {
        if(!dec) {
            dec.release();
        }
    };

    bool init() override {
        if (!dec) {
            const auto modelPath = "/home/thaivd/TDIC/testVisionAudit/assets/detection/yolo11n.onnx";
            const auto labelsPath = "/home/thaivd/TDIC/testVisionAudit/assets/detection/coco.names";
            const bool isGPU = true;
            dec = std::make_unique<yolos::det::YOLODetector>(modelPath, labelsPath, isGPU);
        }
        return true;
    };
    bool process(const cv::Mat& frame, std::vector<DetectionDto>& results) override {
        if (!dec)
            return false;
        std::vector<yolos::det::Detection> output = dec->detect(frame);
        if (!results.empty()) {
            results.clear();
        }
        for (const auto& itemIn : output) {
            DetectionDto itemOut(
                BBox(itemIn.box.x,
                    itemIn.box.y,
                    itemIn.box.width,
                    itemIn.box.height),
                    itemIn.conf,
                    dec->getClassNames().at(itemIn.classId));
            results.push_back(itemOut);
        }
        return true;
    };
    bool stop() override {
        return true;
    };
private:
    std::unique_ptr<yolos::det::YOLODetector> dec;
};


ObjectDetector::ObjectDetector()
    : iDec(nullptr) {
}

ObjectDetector::~ObjectDetector(){
    if (!iDec) {
        iDec.release();
    }
}

bool ObjectDetector::init() {
    if (!iDec) {
        iDec = std::make_unique<Yolo11Concrete>();
    }
    iDec->init();
    return true;
}

bool ObjectDetector::process(const cv::Mat& frame, std::vector<DetectionDto>& results) {
    if (!iDec) {
        return false;
    }
    return iDec->process(frame, results);
}

bool ObjectDetector::stop() {
    if (!iDec) {
        return false;
    }
    return iDec->stop();
}
