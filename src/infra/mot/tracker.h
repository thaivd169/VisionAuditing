#ifndef INFRA_MOT_TRACKER_H
#define INFRA_MOT_TRACKER_H

#include <memory>
#include <vector>

#include "domain/services/itracker.h"

namespace byte_track {
class BYTETracker;
}

class Tracker : public ITracker {
   public:
    Tracker();
    Tracker(const Tracker&) = delete;
    Tracker& operator=(const Tracker&) = delete;
    ~Tracker();

    std::optional<std::vector<Track>> update(const std::vector<DetectionBox>& detections) override;

   private:
    std::unique_ptr<byte_track::BYTETracker> tracker_;
};

#endif  // INFRA_MOT_TRACKER_H
