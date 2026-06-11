file(GLOB sources *.cpp)
add_library(domain_entities STATIC
    ${sources}
)
target_include_directories(domain_entities
    PUBLIC
    ${CMAKE_SOURCE_DIR}/src
)