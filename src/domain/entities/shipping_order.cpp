#include "shipping_order.h"

std::optional<ShippingOrder> ShippingOrder::create(
    const std::string& uuid,
    const Track& track,
    const Barcode& barcode,
    const system_clock::time_point& startTime) {
    if (uuid.empty()) {
        return std::nullopt;
    }
    return ShippingOrder(uuid, track, barcode, startTime);
}

ShippingOrder::ShippingOrder(const std::string& uuid,
                             const Track& track,
                             const Barcode& barcode,
                             const system_clock::time_point& startTime)
    : Entity(uuid), track(track), startTime(startTime), barcode(barcode) {}

system_clock::time_point ShippingOrder::getStartTime() const {
    return startTime;
}

Barcode ShippingOrder::getBarcode() const {
    return barcode;
}

Track ShippingOrder::getTrack() const {
    return track;
}

void ShippingOrder::setTrack(const Track& track) {
    this->track = track;
}
