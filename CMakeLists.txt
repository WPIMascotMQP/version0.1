cmake_minimum_required(VERSION 3.5)

project(Goatbot C CXX)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)

FIND_PACKAGE ( OpenCV REQUIRED )
FIND_PACKAGE ( Threads REQUIRED )

set(OpenCV_LIBS opencv_core opencv_imgproc opencv_calib3d opencv_video opencv_features2d opencv_ml opencv_highgui opencv_objdetect opencv_contrib opencv_legacy opencv_gpu)

add_executable(Goatbot MasterControlLoop.cpp)

target_include_directories(Goatbot PUBLIC
  "${PROJECT_BINARY_DIR}")

TARGET_LINK_LIBRARIES ( Goatbot ${CMAKE_THREAD_LIBS_INIT} )
TARGET_LINK_LIBRARIES ( Goatbot ${OpenCV_LIBS} )