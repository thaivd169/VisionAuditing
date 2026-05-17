add_subdirectory(video_capturer)
add_subdirectory(image_worker)
add_subdirectory(ui)

add_library(adapter 
    STATIC
    adapter_videocapturer
    adapter_image_worker
    adapter_ui
)