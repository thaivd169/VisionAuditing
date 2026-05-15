#ifndef DOMAIN_MOT_DTO_H
#define DOMAIN_MOT_DTO_H

#include <cstddef>

#include "domain/detection/dto.h"

class TrackDto {
   public:
    TrackDto(const size_t& id, const BBox& bbox, const float& confidenceScore);
    ~TrackDto();

    size_t getId() const;
    BBox getBBox() const;
    float getConfidenceScore() const;

   private:
    size_t Id;
    BBox bbox;
    float confidenceScore;
};

#endif  // DOMAIN_MOT_DTO_H
