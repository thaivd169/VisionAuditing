#ifndef ADAPTER_MOT_TRACKER_H
#define ADAPTER_MOT_TRACKER_H

#include <memory>
#include <vector>

#include "ByteTrack/BYTETracker.h"
#include "domain/detection/dto.h"
#include "domain/mot/dto.h"

class Tracker {
   public:
    Tracker();
    Tracker(const Tracker&) = delete;
    Tracker& operator=(const Tracker&) = delete;

    ~Tracker();

    bool init();
    std::vector<TrackDto> update(const std::vector<DetectionDto>& detections);
    bool stop();

   private:
    std::unique_ptr<byte_track::BYTETracker> tracker_;
};

#endif  // ADAPTER_MOT_TRACKER_H
