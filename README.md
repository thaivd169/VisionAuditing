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
    - [Install OnnxRuntime library](#install-onnxruntime-library)
    - [Download AI models and export to ONNX format](#download-ai-models-and-export-to-onnx-format)


# Todo list
- [x] Install OpenCV
- [x] Integrate Object Detection (use YOLOs-CPP)
- [x] Integrate MOT (use ByteTracker)

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
# Prepare dependencies
sudo apt -y install libeigen3-dev libfreetype-dev libharfbuzz-dev cmake libboost-all-dev libx264-dev
# Export Qt6 dir before
export Qt6_DIR=$HOME/Qt/6.11.0/gcc_64/lib/cmake
# Build and install opencv
cd opencv
rm -rf build/
mkdir build
cd build
cmake \
    -D CMAKE_INSTALL_PREFIX=$HOME/TDIC/3rdparty/opencv \
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
### Install OnnxRuntime library
```
cd ~/Downloads
wget https://github.com/microsoft/onnxruntime/releases/download/v1.26.0/onnxruntime-linux-x64-1.26.0.tgz
sha256sum onnxruntime-linux-x64-1.26.0.tgz
tar -xvf ./onnxruntime-linux-x64-1.26.0.tgz -C $HOME/TDIC/3rdparty
mv ~/TDIC/3rdparty/onnxruntime-linux-x64-1.26.0 ~/TDIC/3rdparty/onnxruntime
```

### Download AI models and export to ONNX format
```
-> create folder assets/models
cd ~/Music
mkdir yolo11 && cd yolo11
python3 -m venv .venv
source .venv/bin/activate
pip install ultralytics onnx onnxslim onnxruntime
# download `yolo11n.pt` from https://docs.ultralytics.com/models/yolo11 to 
yolo export \
  model=yolo11n.pt \
  format=onnx \
  imgsz=640 \
  dynamic=False \
  simplify=True 
```
