#ifndef DOMAIN_VALUE_OBJECTS_DETECTION_BOX_H
#define DOMAIN_VALUE_OBJECTS_DETECTION_BOX_H

#include <optional>
#include <string>

#include "bounding_box.h"

class DetectionBox {
   public:
    // Default constructor
    DetectionBox();
    // Factory method
    static std::optional<DetectionBox> create(const BoundingBox& bbox,
                                              const float& confScore,
                                              const std::string& className);

    // Destructor
    ~DetectionBox() = default;

    // Getters
    BoundingBox getBoundingBox() const;
    float getConfidenceScore() const;
    std::string getClassName() const;

    // Copy constructor và assignment
    DetectionBox(const DetectionBox&);
    DetectionBox& operator=(const DetectionBox&);

   private:
    // Private constructor
    DetectionBox(const BoundingBox& bbox,
                 const float& confScore,
                 const std::string& className);

    BoundingBox bbox;
    float confScore;
    std::string className;
};

#endif  // DOMAIN_VALUE_OBJECTS_DETECTION_BOX_H