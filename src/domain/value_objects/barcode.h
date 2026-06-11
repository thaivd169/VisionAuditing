#ifndef DOMAIN_VALUE_OBJECTS_BARCODE_H
#define DOMAIN_VALUE_OBJECTS_BARCODE_H

#include <cstddef>
#include <optional>
#include <string>

class Barcode {
   public:
    // Factory method
    static std::optional<Barcode> create(const std::string& format,
                                         const std::string& data);

    std::string getFormat() const;
    std::string getData() const;

    ~Barcode() = default;

   private:
    Barcode(const std::string& format,
            const std::string& data);

    std::string format;
    std::string data;
};

#endif  // DOMAIN_VALUE_OBJECTS_BARCODE_H
