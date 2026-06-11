#include "entity.h"

Entity::Entity(const std::string& uuid)
    : uuid(uuid) {
}

std::string Entity::getUuid() const {
    return uuid;
}