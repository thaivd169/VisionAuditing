file(GLOB sources "*.cpp")
add_library(ui_splash STATIC ${sources})
target_link_libraries(ui_splash PRIVATE Qt${QT_VERSION_MAJOR}::Widgets)