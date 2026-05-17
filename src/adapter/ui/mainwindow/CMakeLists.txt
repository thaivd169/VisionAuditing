file(GLOB_RECURSE sources "*.cpp")
add_library(ui_mainwindow STATIC ${sources})
target_link_libraries(ui_mainwindow PRIVATE Qt${QT_VERSION_MAJOR}::Widgets)