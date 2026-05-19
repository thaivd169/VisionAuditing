#include "barcode.h"

Barcode::Barcode(const std::string& format,
                 const std::string& data)
    : format(format), data(data) {
}

std::string Barcode::getFormat() const {
    return format;
}

std::string Barcode::getData() const {
    return data;
}

std::optional<Barcode> Barcode::create(const std::string& format,
                                       const std::string& data) {
    if (format.empty() || data.empty()) {
        return std::nullopt;
    }
    return Barcode(format, data);
}