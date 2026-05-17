add_subdirectory(mainwindow)
add_subdirectory(splash)

add_library(ui INTERFACE)
target_link_libraries(ui INTERFACE ui_mainwindow ui_splash)