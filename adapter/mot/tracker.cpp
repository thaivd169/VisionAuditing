#include "tracker.h"

#include "ByteTrack/Object.h"
#include "ByteTrack/Rect.h"

Tracker::Tracker() : tracker_(nullptr) {}

Tracker::~Tracker() {}

bool Tracker::init() {
    tracker_ = std::make_unique<byte_track::BYTETracker>(25, 30, 0.5f, 0.6f, 0.8f);
    return true;
}

std::vector<TrackDto> Tracker::update(const std::vector<DetectionDto>& detections) {
    std::vector<byte_track::Object> objects;
    objects.reserve(detections.size());
    for (const auto& d : detections) {
        objects.emplace_back(
            byte_track::Rect<float>(d.getBBox().getXtl(),
                                    d.getBBox().getYtl(),
                                    d.getBBox().getWidth(),
                                    d.getBBox().getHeight()),
            0,
            d.getConfidenceScore());
    }

    std::vector<TrackDto> results;
    if (!tracker_)
        return results;

    auto tracks = tracker_->update(objects);
    results.reserve(tracks.size());
    for (const auto& t : tracks) {
        const auto& r = t->getRect();
        results.emplace_back(
            t->getTrackId(),
            BBox(r.x(), r.y(), r.width(), r.height()),
            t->getScore());
    }
    return results;
}

bool Tracker::stop() {
    tracker_.reset();
    return true;
}
