#ifndef DOMAIN_VALUEOBJECTS_H
#define DOMAIN_VALUEOBJECTS_H

#ifndef __cplusplus
#error valueobjects.hpp header must be compiled as C++
#endif

#include <opencv2/core/types.hpp>
#include <QString>


class Product {
   public:
    enum class Tag : unsigned char {
        NONE,
        COSMETIC,
    };

    Product(const QString& className, const Tag& tag = Tag::NONE);
    Product(const Product&);
    Product& operator=(const Product&);

    Tag getTag();
    QString getClassName();

   private:
    Tag tag;
    QString className;
};

#endif  // VALUEOBJECTS_H
