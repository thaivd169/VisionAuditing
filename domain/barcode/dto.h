#ifndef DOMAIN_BARCODE_DTO_H
#define DOMAIN_BARCODE_DTO_H

#include <QList>
#include <QMetaType>
#include <cstddef>
#include <string>

#include "domain/detection/dto.h"

class BarcodeDto {
   public:
    BarcodeDto(const size_t& id, const std::string& text, const std::string& type, const BBox& bbox);
    ~BarcodeDto();

    size_t getId() const;
    std::string getText() const;
    std::string getType() const;
    BBox getBBox() const;

   private:
    size_t id;
    std::string text;
    std::string type;
    BBox bbox;
};

Q_DECLARE_METATYPE(BarcodeDto)
Q_DECLARE_METATYPE(QList<BarcodeDto>)

#endif  // DOMAIN_BARCODE_DTO_H
