#ifndef INFRA_BARCODE_BARCODER_H
#define INFRA_BARCODE_BARCODER_H

#include "domain/services/ibarcoder.h"

class Barcoder : public IBarcoder {
   public:
    Barcoder();
    Barcoder(const Barcoder&) = delete;
    Barcoder& operator=(const Barcoder&) = delete;
    ~Barcoder();

   private:
    std::optional<std::vector<Barcode>> decode(const cv::Mat& frame) override;
};

#endif  // INFRA_BARCODE_BARCODER_H