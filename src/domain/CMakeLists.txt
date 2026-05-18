add_subdirectory(entities)
add_subdirectory(value_objects)

add_library(domain STATIC)
target_link_libraries(domain 
    PUBLIC 
    domain_entities 
    domain_value_objects
)