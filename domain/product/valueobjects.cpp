#include "valueobjects.h"

/* Product struct declaration */
Product::Product(const QString& _className, const Tag& _tag)
    : tag(_tag), className(_className) {}

Product::Product(const Product& _other)
    : tag(_other.tag), className(_other.className) {}

Product& Product::operator=(const Product& _other) {
    if (this == &_other)
        return *this;
    this->tag = _other.tag;
    this->className = _other.className;
    return *this;
}


Product::Tag Product::getTag() {
    return this->tag;
}

QString Product::getClassName() {
    return this->className;
}