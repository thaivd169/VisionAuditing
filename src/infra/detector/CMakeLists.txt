FILE(GLOB_RECURSE sources "*.cpp")
add_library(infra_detector STATIC ${sources})

target_include_directories(infra_detector 
    PUBLIC
    ${ONNXRUNTIME_INCLUDE_DIR}
    ${CMAKE_SOURCE_DIR}
    ${CMAKE_SOURCE_DIR}/src
    ${CMAKE_SOURCE_DIR}/lib/yolos_cpp/include
)
target_link_libraries(infra_detector 
    PUBLIC
    opencv_core
    ${ONNXRUNTIME_LIBRARY}
)