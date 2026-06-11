#ifndef DOMAIN_SERVICES_ITRACKER_H
#define DOMAIN_SERVICES_ITRACKER_H

#include <optional>
#include <vector>

#include "domain/value_objects/detection_box.h"
#include "domain/value_objects/track.h"

class ITracker {
   public:
    virtual ~ITracker() = default;
    virtual std::optional<std::vector<Track>> update(const std::vector<DetectionBox>& detections) = 0;
};

#endif  // DOMAIN_SERVICES_ITRACKER_H