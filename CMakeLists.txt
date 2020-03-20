cmake_minimum_required(VERSION 3.10)
project(CameraPrototype)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

### Wenn mit Windows compiliert wird dann, Pfad der OpenCV Dll
set(OpenCV_DIR "C:\\opencv\\build2\\install\\x64\\vc16\\lib")
include_directories("C:\\opencv\\build2\\install\\x64\\vc16\\bin")
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake-modules/")

find_package(OpenCV REQUIRED)
#include_directories(${CMAKE_CUDA_TOOLKIT_INCLUDE_DIRECTORIES})
#add_executable(Camera examples/videocapture_basic.cpp)

add_executable(CameraPrototype prototype.cpp)
set(OpenCV_LIBS opencv_core opencv_imgproc opencv_video opencv_highgui opencv_imgcodecs)
#        opencv_cudaimgproc opencv_cudev opencv_cudacodec opencv_xfeatures2d opencv_dnn)
#        opencv_cudaarithm opencv_superres opencv_videoio opencv_aruco
#        opencv_bgsegm opencv_bioinspired opencv_calib3d opencv_ccalib
#        opencv_cudabgsegm opencv_cudafeatures2d opencv_cudafilters
#        opencv_cudalegacy opencv_cudaobjdetect opencv_cudaoptflow
#        opencv_cudastereo opencv_cudawarping opencv_datasets opencv_dnn_objdetect
#        opencv_dnn_superres opencv_dnn opencv_dpm opencv_face opencv_features2d
#        opencv_flann opencv_fuzzy opencv_gapi opencv_hfs opencv_img_hash
#        opencv_line_descriptor opencv_ml opencv_objdetect opencv_optflow
#        opencv_phase_unwrapping opencv_photo opencv_plot opencv_quality
#        opencv_rapid opencv_reg opencv_rgbd opencv_saliency opencv_shape
#        opencv_stereo opencv_stitching opencv_structured_light
#        opencv_surface_matching opencv_text opencv_tracking opencv_videostab
##        opencv_xfeatures2d opencv_ximgproc opencv_xobjdetect opencv_xphoto)
#target_link_libraries(CameraPrototype opencv_core opencv_highgui opencv_imgcodecs)


#ocv_install_example_src(gpu *.cpp *.hpp CMakeLists.txt)

#set(OPENCV_CUDA_SAMPLES_REQUIRED_DEPS
#        opencv_core
#        opencv_flann
#        opencv_imgproc
#        opencv_imgcodecs
#        opencv_videoio
#        opencv_highgui
#        opencv_ml
#        opencv_video
#        opencv_objdetect
#        opencv_features2d
#        opencv_calib3d
#        opencv_superres
#        opencv_cudaarithm
#        opencv_cudafilters
#        opencv_cudawarping
#        opencv_cudaimgproc
#        opencv_cudafeatures2d
#        opencv_cudaoptflow
#        opencv_cudabgsegm
#        opencv_cudastereo
#        opencv_cudaobjdetect)
#ocv_check_dependencies(${OPENCV_CUDA_SAMPLES_REQUIRED_DEPS})
#
#if(NOT BUILD_EXAMPLES OR NOT OCV_DEPENDENCIES_FOUND)
#    return()
#endif()
#
#project(gpu_samples)
#if(HAVE_CUDA OR CUDA_FOUND)
#    add_definitions(-DHAVE_CUDA=1)
#endif()
#if(COMMAND ocv_warnings_disable)
#    ocv_warnings_disable(CMAKE_CXX_FLAGS -Wsuggest-override -Winconsistent-missing-override)
#endif()
#ocv_include_modules_recurse(${OPENCV_CUDA_SAMPLES_REQUIRED_DEPS})
#if(HAVE_opencv_xfeatures2d)
#    ocv_include_modules_recurse(opencv_xfeatures2d)
#endif()
#if(HAVE_opencv_cudacodec)
#    ocv_include_modules_recurse(opencv_cudacodec)
#endif()
#if(HAVE_CUDA)
#    ocv_include_directories(${CUDA_INCLUDE_DIRS})
#endif()
#if((CV_GCC OR CV_CLANG) AND NOT ENABLE_NOISY_WARNINGS)
#    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wno-unused-function")
#endif()
#file(GLOB all_samples RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} *.cpp)
#foreach(sample_filename ${all_samples})
#    ocv_define_sample(tgt ${sample_filename} gpu)
#    ocv_target_link_libraries(${tgt} PRIVATE ${OPENCV_LINKER_LIBS} ${OPENCV_CUDA_SAMPLES_REQUIRED_DEPS})
#    if(HAVE_opencv_xfeatures2d)
#        ocv_target_link_libraries(${tgt} PRIVATE opencv_xfeatures2d)
#    endif()
#    if(HAVE_opencv_cudacodec)
#        ocv_target_link_libraries(${tgt} PRIVATE opencv_cudacodec)
#    endif()
#endforeach()

target_link_libraries(CameraPrototype ${OpenCV_LIBS})
