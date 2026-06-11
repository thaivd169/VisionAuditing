file(GLOB_RECURSE sources *.cpp)
qt_add_library(adapter_ui STATIC ${sources})
target_link_libraries(adapter_ui 
    PUBLIC 
    Qt${QT_VERSION_MAJOR}::Widgets
    opencv_core
)
target_include_directories(adapter_ui
    PUBLIC
    ${CMAKE_SOURCE_DIR}/src
)
