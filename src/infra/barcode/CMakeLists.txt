FILE(GLOB_RECURSE sources "*.cpp")
add_library(infra_barcode STATIC ${sources})

target_include_directories(infra_barcode 
    PUBLIC
    ${CMAKE_SOURCE_DIR}/src
    ${CMAKE_SOURCE_DIR}/lib/yolos_cpp/include
    ${OpenCV_INCLUDE_DIRS}
)
target_link_libraries(infra_barcode 
    PUBLIC
    ZXing::ZXing
    ${OpenCV_LIBS}
)