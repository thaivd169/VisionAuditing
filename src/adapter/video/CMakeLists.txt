file(GLOB sources *.cpp)
qt_add_library(adapter_video STATIC ${sources})
target_include_directories(adapter_video 
    PUBLIC
    ${CMAKE_SOURCE_DIR}/src
)
target_link_libraries(adapter_video PUBLIC
    opencv_core
    opencv_imgproc
    opencv_videoio
    Qt6::Core
)