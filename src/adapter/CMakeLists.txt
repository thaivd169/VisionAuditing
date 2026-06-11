add_subdirectory(ui)
add_subdirectory(video)

add_library(adapter STATIC)
target_link_libraries(adapter PUBLIC adapter_ui adapter_video)