<font size= "5"> **Table Of Contents** </font>
- [Todo list](#todo-list)
- [Introduction](#introduction)
- [Folder structure](#folder-structure)
- [Environment for development](#environment-for-development)
  - [At the first time](#at-the-first-time)
    - [System](#system)
    - [Preparation](#preparation)
    - [Qt6](#qt6)
    - [Build and release OpenCV library](#build-and-release-opencv-library)
    - [Build and release gRPC library](#build-and-release-grpc-library)
    - [Build and release spdlog library](#build-and-release-spdlog-library)
    - [Discard write permission for all release folders](#discard-write-permission-for-all-release-folders)
  - [At the second times](#at-the-second-times)
    - [Preparation](#preparation-1)
    - [Arrangement](#arrangement)
- [Contributors](#contributors)


# Todo list
- [x] Install OpenCV
- [ ] Integrate Object Detection (use YOLOs-CPP)
- [ ] Integrate MOT (use ByteTracker)

# Introduction
- A Back-end service for audit processing by Camera AI System
# Folder structure

# Environment for development
## At the first time
### System
- Reference to [My Jetson Orin AGX](./docs/jetson_system_information.md)
### Preparation
```
sudo apt update
sudo apt -y install libeigen3-dev libfreetype-dev libharfbuzz-dev cmake libboost-all-dev libx264-dev libsystemd-dev
```

### Qt6
- Crawl Qt framwork corresponding to the machine architecture at <global_path> (following pattern [Folder structure](#folder-structure)).
### Build and release OpenCV library
- Check out *opencv* and *opencv_contrib* repos to *4.13.0* tag
```
# Export Qt6 dir before
export Qt6_DIR=/home/thaivd/Qt/6.11.0/gcc_64/lib/cmake
# Build and install opencv
cd opencv
rm -rf build/
mkdir build
cd build
cmake \
    -D CMAKE_INSTALL_PREFIX=/home/thaivd/TDIC/3rdparty/opencv \
    -D CMAKE_BUILD_TYPE=RELEASE \
    -D BUILD_JAVA=OFF \
    -D BUILD_FAT_JAVA_LIB=OFF \
    -D WITH_WIN32UI=OFF 	\
    -D WITH_QT=ON \
    -D WITH_TBB=ON \
    -D WITH_FFMPEG=ON \
    -D WITH_GSTREAMER=ON \
    -D OPENCV_EXTRA_MODULES_PATH=../../opencv_contrib/modules \
    -D OPENCV_ENABLE_NONFREE=ON \
    ..

make install -j$(nproc)
ldconfig
```
### Build and release gRPC library


### Build and release spdlog library


### Discard write permission for all release folders


## At the second times
### Preparation

### Arrangement

# Contributors


