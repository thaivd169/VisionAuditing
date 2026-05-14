#ifndef DOMAIN_VALUEOBJECTS_H
#define DOMAIN_VALUEOBJECTS_H

#ifndef __cplusplus
#error valueobjects.hpp header must be compiled as C++
#endif

#include <opencv2/core/types.hpp>
#include <ostream>
#include <QString>

class BBox {
   public:
    BBox();
    BBox(const float& xtl, const float& ytl, const float& width, const float& height);
    BBox(const cv::Rect2d&);
    BBox(const BBox&);

    // Member methods
    float getXCenter();
    float getYCenter();
    cv::Rect2d cvtCvRect2d();

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

class Product {
   public:
    enum class Tag : unsigned char {
        NONE,
        COSMETIC,
    };

    Product(const BBox& bbox, const QString& className, const Tag& tag = Tag::NONE);
    Product(const Product&);
    Product& operator=(const Product&);

    BBox getBBox();
    Tag getTag();
    QString getClassName();

   private:
    BBox bbox;
    Tag tag;
    QString className;
};

#endif  // VALUEOBJECTS_H
