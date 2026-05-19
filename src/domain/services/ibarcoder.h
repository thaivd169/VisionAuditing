#ifndef DOMAIN_SERVICES_IBARCODER_H
#define DOMAIN_SERVICES_IBARCODER_H
#include <opencv2/core/mat.hpp>
#include <optional>
#include <vector>

#include "domain/value_objects/barcode.h"

class IBarcoder {
   public:
    virtual ~IBarcoder() = default;
    virtual std::optional<std::vector<Barcode>> decode(const cv::Mat& frame) = 0;
};

#endif  // DOMAIN_SERVICES_IBARCODER_H