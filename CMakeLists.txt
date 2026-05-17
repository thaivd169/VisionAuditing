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
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(TD_3RDPARTY_PATH "${CMAKE_SOURCE_DIR}/../3rdparty")
add_compile_definitions(VISION_AUDITING_VERSION_STRING="${VISION_AUDITING_VERSION}-${GIT_COMMIT_HASH}")

# Setup Qt framework
list(APPEND CMAKE_PREFIX_PATH "$ENV{HOME}/Qt/6.11.0/gcc_64/lib/cmake/Qt6")
find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Widgets)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets)

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


add_subdirectory(lib/bytetrack)
add_subdirectory(src/infra)
add_subdirectory(src/app)
add_subdirectory(src/domain)
add_subdirectory(src/adapter)



# Qt for iOS sets MACOSX_BUNDLE_GUI_IDENTIFIER automatically since Qt 6.1.
# If you are developing for iOS or macOS you should consider setting an
# explicit, fixed bundle identifier manually though.
# if(${QT_VERSION} VERSION_LESS 6.1.0)
#   set(BUNDLE_ID_OPTION MACOSX_BUNDLE_GUI_IDENTIFIER com.example.${CMAKE_PROJECT_NAME})
# endif()
# set_target_properties(${CMAKE_PROJECT_NAME} PROPERTIES
#     ${BUNDLE_ID_OPTION}
#     MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
#     MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
#     MACOSX_BUNDLE TRUE
#     WIN32_EXECUTABLE TRUE
# )

# include(GNUInstallDirs)
# install(TARGETS ${CMAKE_PROJECT_NAME}
#     BUNDLE DESTINATION .
#     LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
#     RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
# )

# if(QT_VERSION_MAJOR EQUAL 6)
#     qt_finalize_executable(${CMAKE_PROJECT_NAME})
# endif()
