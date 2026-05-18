add_subdirectory(detector)
add_subdirectory(mot)

add_library(infra STATIC)
target_link_libraries(infra PUBLIC infra_mot infra_detector)