#----------------------------------------------------------------------------------
# THE ROOT CMAKE FILE FOR CORE_IPS APPLICATION
#----------------------------------------------------------------------------------
if(" ${CMAKE_SOURCE_DIR}" STREQUAL " ${CMAKE_BINARY_DIR}")
  message(FATAL_ERROR "FATAL: In-source builds are not allowed. You should create a separate directory for build files.")
endif()

cmake_minimum_required(VERSION 3.16)

# Setup CMake properties
execute_process(
  COMMAND cat ./VERSION
  WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
  OUTPUT_VARIABLE VISION_AUDITING_VERSION
  OUTPUT_STRIP_TRAILING_WHITESPACE
  ERROR_QUIET
)
execute_process(
  COMMAND git rev-parse --short HEAD
  WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
  OUTPUT_VARIABLE GIT_COMMIT_HASH
  OUTPUT_STRIP_TRAILING_WHITESPACE
  ERROR_QUIET
)
project(visionAuditing
        VERSION ${VISION_AUDITING_VERSION}
        LANGUAGES CXX
        DESCRIPTION "A backend service applying computer vision \
                    for auditing purposes to warehouse management."
)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(TD_3RDPARTY_PATH "${CMAKE_SOURCE_DIR}/../3rdparty")
add_compile_definitions(VISION_AUDITING_VERSION_STRING="${VISION_AUDITING_VERSION}-${GIT_COMMIT_HASH}")

# Setup Qt framework
list(APPEND CMAKE_PREFIX_PATH "$ENV{HOME}/Qt/6.11.0/gcc_64/lib/cmake/Qt6")
find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Core)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Core Widgets Network Concurrent)
message ("[${CMAKE_PROJECT_NAME}] [Qt] version   :   ${QT_VERSION_MAJOR}.${QT_VERSION_MINOR}.${QT_VERSION_PATCH}")
message ("[${CMAKE_PROJECT_NAME}] [Qt] include   :   TODO")
message ("[${CMAKE_PROJECT_NAME}] [Qt] libraries :   TODO")
qt_standard_project_setup()


# Setup OpenCV library
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

# Setup ZXing library for decoding barcodes
list(APPEND CMAKE_PREFIX_PATH "${TD_3RDPARTY_PATH}/zxing_cpp/lib/cmake/ZXing")
find_package(ZXing REQUIRED)
message ("[${CMAKE_PROJECT_NAME}] [ZXing] version   :   ${ZXing_VERSION}")
message ("[${CMAKE_PROJECT_NAME}] [ZXing] include   :   ${ZXing_INCLUDE_DIRS}")
message ("[${CMAKE_PROJECT_NAME}] [ZXing] libraries :   ${ZXing_LIBRARIES}")


add_subdirectory(lib/bytetrack)
add_subdirectory(src/infra)
add_subdirectory(src/app)
add_subdirectory(src/domain)
add_subdirectory(src/adapter)