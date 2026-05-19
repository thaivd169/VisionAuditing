#include "barcoder.h"

#include <BarcodeFormat.h>
#include <ReadBarcode.h>

#include <opencv2/imgproc.hpp>

namespace {
ZXing::ImageView imageViewFromMat(const cv::Mat& image) {
    using ZXing::ImageFormat;

    if (image.empty() || image.depth() != CV_8U) {
        return {nullptr, 0, 0, ImageFormat::None};
    }

    auto format = ImageFormat::None;
    switch (image.channels()) {
        case 1:
            format = ImageFormat::Lum;
            break;
        case 2:
            format = ImageFormat::LumA;
            break;
        case 3:
            format = ImageFormat::BGR;
            break;
        case 4:
            format = ImageFormat::BGRA;
            break;
        default:
            return {nullptr, 0, 0, ImageFormat::None};
    }

    return {image.data, image.cols, image.rows, format};
}
}  // namespace

Barcoder::Barcoder() = default;

Barcoder::~Barcoder() = default;

std::optional<std::vector<Barcode>> Barcoder::decode(const cv::Mat& frame) {
    if (frame.empty()) {
        return std::nullopt;
    }

    auto view = imageViewFromMat(frame);
    if (view.format() == ZXing::ImageFormat::None) {
        return std::nullopt;
    }

    ZXing::ReaderOptions options;
    options.setFormats(
        ZXing::BarcodeFormat::Code128 |
        ZXing::BarcodeFormat::QRCode |
        ZXing::BarcodeFormat::EAN13);
    options.setTryHarder(true);

    auto results = ZXing::ReadBarcodes(view, options);
    if (results.empty()) {
        return std::nullopt;
    }

    std::vector<Barcode> decoded;
    decoded.reserve(results.size());

    for (const auto& result : results) {
        // if (!result.isValid()) {
        //     continue;
        // }

        const std::string format = ZXing::ToString(result.format());
        const std::string data = result.text();

        auto maybeBarcode = Barcode::create(format, data);
        if (maybeBarcode) {
            decoded.emplace_back(*maybeBarcode);
        }
    }

    if (decoded.empty()) {
        return std::nullopt;
    }

    return decoded;
}
