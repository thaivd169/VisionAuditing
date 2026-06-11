#include "track.h"

std::optional<Track> Track::create(const size_t& id,
                                   const BoundingBox& bbox,
                                   const float& confScore) {
    if (confScore < 0.0f || confScore > 1.0f) {
        return std::nullopt;
    }
    return Track(id, bbox, confScore);
}

Track::Track(const size_t& _id, const BoundingBox& _bbox, const float& _confScore)
    : id(_id), bbox(_bbox), confScore(_confScore) {}

size_t Track::getId() const { return id; }

BoundingBox Track::getBoundingBox() const { return bbox; }

float Track::getConfidenceScore() const { return confScore; }
