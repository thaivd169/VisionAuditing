file(GLOB sources *.cpp)
add_library(domain_value_objects STATIC
    ${sources}
)