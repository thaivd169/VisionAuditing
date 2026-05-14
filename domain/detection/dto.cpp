#include "dto.h"

#include <string>

/* DetectionDto struct declaration */
DetectionDto::DetectionDto(const BBox& bbox, const float& confScore, const std::string& className)
    : bbox(bbox), confidenceScore(confScore), className(className) {}

DetectionDto::~DetectionDto() {}

BBox DetectionDto::getBBox() const {
    return this->bbox;
}

float DetectionDto::getConfidenceScore() const {
    return this->confidenceScore;
}

std::string DetectionDto::getClassName() const {
    return this->className;
}

/* BBox struct declaration */
BBox::BBox() {
    this->xtl = 0.0;
    this->ytl = 0.0;
    this->width = 0.0;
    this->height = 0.0;
}
BBox::BBox(const float& _xtl, const float& _ytl, const float& _width, const float& _height) {
    this->xtl = _xtl;
    this->ytl = _ytl;
    this->width = _width;
    this->height = _height;
}

BBox::BBox(const cv::Rect2d& _tmpRect) {
    this->xtl = static_cast<float>(_tmpRect.x);
    this->ytl = static_cast<float>(_tmpRect.y);
    this->width = static_cast<float>(_tmpRect.width);
    this->height = static_cast<float>(_tmpRect.height);
}

float BBox::getXtl() const {
    return this->xtl;
}

float BBox::getYtl() const {
    return this->ytl;
}

float BBox::getWidth() const {
    return this->width;
}

float BBox::getHeight() const {
    return this->height;
}

float BBox::getXCenter() const {
    return (this->xtl + this->width / 2.0f);
}

float BBox::getYCenter() const {
    return (this->ytl + this->height / 2.0f);
}

cv::Rect2d BBox::cvtCvRect2d() const {
    return cv::Rect2d(this->xtl, this->ytl, this->width, this->height);
}

BBox::BBox(const BBox& _other) {
    this->xtl = _other.xtl;
    this->ytl = _other.ytl;
    this->width = _other.width;
    this->height = _other.height;
}

BBox& BBox::operator=(const BBox& _other) {
    if (this == &_other)
        return *this;
    this->xtl = _other.xtl;
    this->ytl = _other.ytl;
    this->width = _other.width;
    this->height = _other.height;
    return *this;
}

bool BBox::operator==(const BBox& _other) {
    if (*this != _other)
        return false;
    return true;
}

static inline bool isEqualWith2Doubles(double firstNum, double secondNum) {
    double maxNum = std::max({1.0, std::fabs(firstNum), std::fabs(secondNum)});
    bool result = std::fabs(firstNum - secondNum) <= std::numeric_limits<double>::epsilon() * maxNum;
    return result;
}

bool BBox::operator!=(const BBox& _other) {
    if (!isEqualWith2Doubles(static_cast<double>(this->xtl), static_cast<double>(_other.xtl)) ||
        !isEqualWith2Doubles(static_cast<double>(this->ytl), static_cast<double>(_other.ytl)) ||
        !isEqualWith2Doubles(static_cast<double>(this->width), static_cast<double>(_other.width)) ||
        !isEqualWith2Doubles(static_cast<double>(this->height), static_cast<double>(_other.height)))
        return true;
    return false;
}
