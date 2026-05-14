#ifndef ADAPTER_OBJECTDETECTOR_H
#define ADAPTER_OBJECTDETECTOR_H

#ifndef __cplusplus
#error objectdetector.hpp header must be compiled as C++
#endif

#include <QList>
#include <QPointer>
#include <opencv2/core/types.hpp>
#include "domain/product/valueobjects.h"


class IDetector {
public:
    virtual ~IDetector() = default;

public:
    virtual bool init() = 0;
    virtual bool process(const cv::Mat& frame, QList<Product>& products) = 0;
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
    bool process(const cv::Mat& frame, QList<Product>& products);
    bool stop();

private:
    QPointer<IDetector> iDetector;
};

#endif // ADAPTER_OBJECTDETECTOR_H
