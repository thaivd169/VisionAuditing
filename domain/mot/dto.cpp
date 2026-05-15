#include "dto.h"

TrackDto::TrackDto(const size_t& id, const BBox& bbox, const float& confidenceScore)
    : Id(id), bbox(bbox), confidenceScore(confidenceScore) {}

TrackDto::~TrackDto() {}

size_t TrackDto::getId() const {
    return Id;
}

BBox TrackDto::getBBox() const {
    return bbox;
}

float TrackDto::getConfidenceScore() const {
    return confidenceScore;
}
