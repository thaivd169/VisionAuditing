#ifndef ADAPTER_OBJECTDETECTOR_H
#define ADAPTER_OBJECTDETECTOR_H

#ifndef __cplusplus
#error objectdetector.hpp header must be compiled as C++
#endif

#include <QList>
#include <memory>
#include <opencv2/core/types.hpp>
#include "domain/detection/dto.h"


class IDetector {
public:
    virtual ~IDetector() = default;

public:
    virtual bool init() = 0;
    virtual bool process(const cv::Mat& frame, std::vector<DetectionDto>& results) = 0;
    virtual bool stop() = 0;
};

class ObjectDetector
{
public:
    ObjectDetector();
    ObjectDetector(const ObjectDetector&) = delete;
    ObjectDetector& operator=(const ObjectDetector&) = delete;

    ~ObjectDetector();

    bool init();
    bool process(const cv::Mat& frame, std::vector<DetectionDto>& results);
    bool stop();

private:
    std::unique_ptr<IDetector> iDec;
};

#endif // ADAPTER_OBJECTDETECTOR_H
