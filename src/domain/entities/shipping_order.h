#ifndef DOMAIN_ENTITIES_ORDER_H
#define DOMAIN_ENTITIES_ORDER_H

#include <chrono>
#include <cstdint>
#include <optional>

#include "domain/value_objects/barcode.h"
#include "domain/value_objects/track.h"
#include "entity.h"

using namespace std::chrono;

class ShippingOrder : public Entity {
   public:
    // Factory method
    static std::optional<ShippingOrder> create(const std::string& uuid,
                                               const Track& track,
                                               const Barcode& barcode,
                                               const system_clock::time_point& startTime);

    ~ShippingOrder() = default;

    system_clock::time_point getStartTime() const;
    Barcode getBarcode() const;
    Track getTrack() const;
    void setTrack(const Track& track);

   private:
    ShippingOrder(const std::string& uuid,
                  const Track& track,
                  const Barcode& barcode,
                  const system_clock::time_point& startTime);

    Track track;
    system_clock::time_point startTime;
    Barcode barcode;
};

#endif  // DOMAIN_ENTITIES_ORDER_H