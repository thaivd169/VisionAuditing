#include "bounding_box.h"

#include <algorithm>
#include <cmath>
#include <limits>
#include <string>

BoundingBox::BoundingBox()
    : xtl(0.0f),
      ytl(0.0f),
      width(0.0f),
      height(0.0f) {
}

std::optional<BoundingBox> BoundingBox::create(const float& xtl,
                                               const float& ytl,
                                               const float& width,
                                               const float& height) {
    if (xtl < 0.0f || ytl < 0.0f || width < 0.0f || height < 0.0f) {
        return std::nullopt;
    }
    return BoundingBox(xtl, ytl, width, height);
}

BoundingBox::BoundingBox(const float& _xtl,
                         const float& _ytl,
                         const float& _width,
                         const float& _height)
    : xtl(_xtl), ytl(_ytl), width(_width), height(_height) {
}

float BoundingBox::getXtl() const {
    return xtl;
}

float BoundingBox::getYtl() const {
    return ytl;
}

float BoundingBox::getWidth() const {
    return width;
}

float BoundingBox::getHeight() const {
    return height;
}

float BoundingBox::getXCenter() const {
    return (xtl + width / 2.0f);
}

float BoundingBox::getYCenter() const {
    return (ytl + height / 2.0f);
}

BoundingBox::BoundingBox(const BoundingBox& _other)
    : xtl(_other.xtl), ytl(_other.ytl), width(_other.width), height(_other.height) {
}

BoundingBox& BoundingBox::operator=(const BoundingBox& _other) {
    if (this == &_other)
        return *this;
    xtl = _other.xtl;
    ytl = _other.ytl;
    width = _other.width;
    height = _other.height;
    return *this;
}

bool BoundingBox::operator==(const BoundingBox& _other) {
    return !(*this != _other);
}

static inline bool isEqualWith2Doubles(double firstNum, double secondNum) {
    double maxNum = std::max({1.0, std::fabs(firstNum), std::fabs(secondNum)});
    return std::fabs(firstNum - secondNum) <= std::numeric_limits<double>::epsilon() * maxNum;
}

bool BoundingBox::operator!=(const BoundingBox& _other) {
    return !isEqualWith2Doubles(static_cast<double>(xtl), static_cast<double>(_other.xtl)) ||
           !isEqualWith2Doubles(static_cast<double>(ytl), static_cast<double>(_other.ytl)) ||
           !isEqualWith2Doubles(static_cast<double>(width), static_cast<double>(_other.width)) ||
           !isEqualWith2Doubles(static_cast<double>(height), static_cast<double>(_other.height));
}
