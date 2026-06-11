#ifndef DOMAIN_VALUE_OBJECTS_BOUNDING_BOX_H
#define DOMAIN_VALUE_OBJECTS_BOUNDING_BOX_H

#include <optional>

class BoundingBox {
   public:
    // Default constructor
    BoundingBox();

    // Factory method
    static std::optional<BoundingBox> create(const float& xtl,
                                             const float& ytl,
                                             const float& width,
                                             const float& height);

    // Copy constructor và destructor
    BoundingBox(const BoundingBox&);
    ~BoundingBox() = default;

    // Getters
    float getXtl() const;
    float getYtl() const;
    float getWidth() const;
    float getHeight() const;
    float getXCenter() const;
    float getYCenter() const;

    // Operators
    BoundingBox& operator=(const BoundingBox&);
    bool operator==(const BoundingBox&);
    bool operator!=(const BoundingBox&);

   private:
    // Private constructor
    BoundingBox(const float& xtl,
                const float& ytl,
                const float& width,
                const float& height);

    float xtl;  // x top-left
    float ytl;  // y top-left
    float width;
    float height;
};

#endif  // DOMAIN_VALUE_OBJECTS_BOUNDING_BOX_H
