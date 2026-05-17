#ifndef DOMAIN_VALUE_OBJECTS_TRACK_H
#define DOMAIN_VALUE_OBJECTS_TRACK_H

#include <cstddef>
#include <optional>

#include "domain/value_objects/bounding_box.h"

class Track {
   public:
    // Factory method
    static std::optional<Track> create(const size_t& id,
                                       const BoundingBox& bbox,
                                       const float& confScore);

    ~Track() = default;

    size_t getId() const;
    BoundingBox getBoundingBox() const;
    float getConfidenceScore() const;

   private:
    Track(const size_t& id,
          const BoundingBox& bbox,
          const float& confScore);

    size_t id;
    BoundingBox bbox;
    float confScore;
};

#endif  // DOMAIN_VALUE_OBJECTS_TRACK_H
