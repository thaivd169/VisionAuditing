#ifndef DOMAIN_ENTITIES_ENTITY_H
#define DOMAIN_ENTITIES_ENTITY_H

#include <string>
class Entity {
   public:
    Entity(const std::string& uuid);
    virtual ~Entity() = default;
    std::string getUuid() const;

   private:
    std::string uuid;
};

#endif  // DOMAIN_ENTITIES_ENTITY_H