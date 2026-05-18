file(GLOB sources *.cpp)
add_library(domain_value_objects STATIC
    ${sources}
)

target_include_directories(domain_value_objects PUBLIC
    ${CMAKE_SOURCE_DIR}/src
)