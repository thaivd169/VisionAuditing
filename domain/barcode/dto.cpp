#include "dto.h"

BarcodeDto::BarcodeDto(const size_t& id, const std::string& text, const std::string& type, const BBox& bbox)
    : id(id), text(text), type(type), bbox(bbox) {}

BarcodeDto::~BarcodeDto() {}

size_t BarcodeDto::getId() const {
    return id;
}

std::string BarcodeDto::getText() const {
    return text;
}

std::string BarcodeDto::getType() const {
    return type;
}

BBox BarcodeDto::getBBox() const {
    return bbox;
}
