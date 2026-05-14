#ifndef DOMAIN_DETECTION_DTO_H
#define DOMAIN_DETECTION_DTO_H

#include <opencv2/core/types.hpp>
#include <ostream>

class BBox {
   public:
    BBox();
    BBox(const float& xtl, const float& ytl, const float& width, const float& height);
    BBox(const cv::Rect2d&);
    BBox(const BBox&);

    float getXtl() const;
    float getYtl() const;
    float getWidth() const;
    float getHeight() const;
    float getXCenter() const;
    float getYCenter() const;
    cv::Rect2d cvtCvRect2d() const;

    // Overloading operators
    BBox& operator=(const BBox&);
    bool operator==(const BBox&);
    bool operator!=(const BBox&);
    friend std::ostream& operator<<(std::ostream& os, const BBox& bbox) {
        os << "[BBox] (x, y, w, h): " << bbox.xtl << ", "
           << bbox.ytl << ", "
           << bbox.width << ", "
           << bbox.height;
        return os;
    }

   private:
    float xtl;  // x top-left
    float ytl;  // y top-left
    float width;
    float height;
};

class DetectionDto {
   public:
    DetectionDto(const BBox& bbox, const float& confScore, const std::string& className);
    ~DetectionDto();

    BBox getBBox() const;
    float getConfidenceScore() const;
    std::string getClassName() const;

   private:
    BBox bbox;
    float confidenceScore;
    std::string className;
};

#endif  // DTO_H
