FILE(GLOB_RECURSE sources "*.cpp")
add_library(infra_barcode STATIC ${sources})

target_include_directories(infra_barcode 
    PRIVATE
    ${CMAKE_SOURCE_DIR}/src
    ${TD_3RDPARTY_PATH}/zxing_cpp/include
    ${OpenCV_INCLUDE_DIRS}
)
target_link_libraries(infra_barcode 
    PRIVATE 
    ZXing::ZXing
    ${OpenCV_LIBS}
)