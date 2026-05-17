FILE(GLOB sources "*.cpp")
add_library(infra_mot STATIC ${sources})

target_include_directories(infra_mot PUBLIC
    ${CMAKE_SOURCE_DIR}
    ${CMAKE_SOURCE_DIR}/lib/bytetrack/include
)
target_link_libraries(infra_mot PUBLIC
    bytetrack
)