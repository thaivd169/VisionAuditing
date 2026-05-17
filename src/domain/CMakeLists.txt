add_subdirectory(entities)
add_subdirectory(value_objects)
add_library(domain
    PUBLIC
    domain_entities
    domain_value_objects
)