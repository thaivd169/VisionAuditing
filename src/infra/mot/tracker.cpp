#include "tracker.h"

#include "ByteTrack/BYTETracker.h"
#include "ByteTrack/Object.h"
#include "ByteTrack/Rect.h"
#include "domain/value_objects/bounding_box.h"
#include "domain/value_objects/detection_box.h"
#include "domain/value_objects/track.h"

Tracker::Tracker()
    : tracker_(std::make_unique<byte_track::BYTETracker>(25, 30, 0.5f, 0.6f, 0.8f)) {
}

Tracker::~Tracker() {
    tracker_.reset();
}

std::optional<std::vector<Track>> Tracker::update(const std::vector<DetectionBox>& detections) {
    if (!tracker_)
        return std::nullopt;

    std::vector<byte_track::Object> objects;
    objects.reserve(detections.size());
    for (const auto& d : detections) {
        const auto& bb = d.getBoundingBox();
        objects.emplace_back(
            byte_track::Rect<float>(bb.getXtl(), bb.getYtl(), bb.getWidth(), bb.getHeight()),
            0,
            d.getConfidenceScore());
    }

    auto tracks_ptrs = tracker_->update(objects);
    std::vector<Track> results;
    results.reserve(tracks_ptrs.size());
    for (const auto& t : tracks_ptrs) {
        const auto& r = t->getRect();
        auto maybeBox = BoundingBox::create(r.x(), r.y(), r.width(), r.height());
        if (!maybeBox)
            continue;
        auto maybeTrack = Track::create(t->getTrackId(), maybeBox.value(), t->getScore());
        if (maybeTrack)
            results.push_back(maybeTrack.value());
    }

    return results;
}
