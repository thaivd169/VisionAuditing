add_subdirectory(detector)
add_subdirectory(mot)
add_library(infra 
    PUBLIC
    infra_mot
    infra_detector
)