cmake_minimum_required(VERSION 3.16)

project(visionAuditing VERSION 0.1 LANGUAGES CXX)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(TD_3RDPARTY_PATH "${CMAKE_SOURCE_DIR}/../3rdparty")
# Setup Opencv library
list(APPEND CMAKE_PREFIX_PATH "${TD_3RDPARTY_PATH}/opencv/lib/cmake/opencv4")
find_package(OpenCV REQUIRED)
message ("[${CMAKE_PROJECT_NAME}] [OpenCV] version   :   ${OpenCV_VERSION}")
message ("[${CMAKE_PROJECT_NAME}] [OpenCV] include   :   ${OpenCV_INCLUDE_DIRS}")
message ("[${CMAKE_PROJECT_NAME}] [OpenCV] libraries :   ${OpenCV_LIBRARIES}")

# Setup Onnxruntime library
set(ONNXRUNTIME_ROOT "${TD_3RDPARTY_PATH}/onnxruntime")
find_path(ONNXRUNTIME_INCLUDE_DIR onnxruntime_cxx_api.h
    PATHS ${ONNXRUNTIME_ROOT}/include
)
find_library(ONNXRUNTIME_LIBRARY onnxruntime
    PATHS ${ONNXRUNTIME_ROOT}/lib
)

add_subdirectory(lib/bytetrack)

list(APPEND CMAKE_PREFIX_PATH "$ENV{HOME}/Qt/6.11.0/gcc_64/lib/cmake/Qt6")
find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Widgets)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets)

set(PROJECT_SOURCES
        main.cpp
        mainwindow.cpp
        mainwindow.h
        mainwindow.ui
)

if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    qt_add_executable(${CMAKE_PROJECT_NAME}
        MANUAL_FINALIZATION
        ${PROJECT_SOURCES}
        adapter/videocapturer/videocapturer.h adapter/videocapturer/videocapturer.cpp
        adapter/detection/objectdetector.h adapter/detection/objectdetector.cpp
        domain/product/valueobjects.h domain/product/valueobjects.cpp
        adapter/imageworker/imageworker.h adapter/imageworker/imageworker.cpp
        domain/detection/dto.h domain/detection/dto.cpp
        domain/mot/dto.h domain/mot/dto.cpp
        adapter/mot/tracker.h adapter/mot/tracker.cpp
        domain/barcode/dto.h domain/barcode/dto.cpp
    )
# Define target properties for Android with Qt 6 as:
#    set_property(TARGET ${CMAKE_PROJECT_NAME} APPEND PROPERTY QT_ANDROID_PACKAGE_SOURCE_DIR
#                 ${CMAKE_CURRENT_SOURCE_DIR}/android)
# For more information, see https://doc.qt.io/qt-6/qt-add-executable.html#target-creation
else()
    if(ANDROID)
        add_library(${CMAKE_PROJECT_NAME} SHARED
            ${PROJECT_SOURCES}
        )
# Define properties for Android with Qt 5 after find_package() calls as:
#    set(ANDROID_PACKAGE_SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/android")
    else()
        add_executable(${CMAKE_PROJECT_NAME}
            ${PROJECT_SOURCES}
        )
    endif()
endif()

target_include_directories(
    ${CMAKE_PROJECT_NAME} PUBLIC 
    ${CMAKE_SOURCE_DIR} 
    ${CMAKE_SOURCE_DIR}/lib/yolos_cpp/include 
    ${ONNXRUNTIME_INCLUDE_DIR} 
    ${CMAKE_SOURCE_DIR}/lib/bytetrack/include)

target_link_libraries(
    ${CMAKE_PROJECT_NAME} PRIVATE 
    Qt${QT_VERSION_MAJOR}::Widgets 
    opencv_core opencv_videoio opencv_objdetect
    ${ONNXRUNTIME_LIBRARY} 
    bytetrack)

# Qt for iOS sets MACOSX_BUNDLE_GUI_IDENTIFIER automatically since Qt 6.1.
# If you are developing for iOS or macOS you should consider setting an
# explicit, fixed bundle identifier manually though.
if(${QT_VERSION} VERSION_LESS 6.1.0)
  set(BUNDLE_ID_OPTION MACOSX_BUNDLE_GUI_IDENTIFIER com.example.${CMAKE_PROJECT_NAME})
endif()
set_target_properties(${CMAKE_PROJECT_NAME} PROPERTIES
    ${BUNDLE_ID_OPTION}
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

include(GNUInstallDirs)
install(TARGETS ${CMAKE_PROJECT_NAME}
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)

if(QT_VERSION_MAJOR EQUAL 6)
    qt_finalize_executable(${CMAKE_PROJECT_NAME})
endif()
