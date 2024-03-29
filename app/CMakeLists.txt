# For more information about using CMake with Android Studio, read the
# documentation: https://d.android.com/studio/projects/add-native-code.html

# Sets the minimum version of CMake required to build the native library.

cmake_minimum_required(VERSION 3.4.1)


# 设置生成的so动态库最后输出的路径，
# set后面两个参数， 前面一个是命令，后面是路径。
#set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/../jniLibs/${ANDROID_ABI})
#set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/src/main/jniLibs/${ANDROID_ABI})
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/jniLibs/${ANDROID_ABI})


#设置生成so库的名称，并为源文件提供一个相对路径
#设置统配符
# 将.cpp文件配置在CMakeLists.txt中，如果是在子目录下，
file(GLOB native_srcs "${CMAKE_SOURCE_DIR}/src/main/cpp/video/*.cpp")

# Creates and names a library, sets it as either STATIC
# or SHARED, and provides the relative paths to its source code.
# You can define multiple libraries, and CMake builds them for you.
# Gradle automatically packages shared libraries with your APK.

add_library( # Sets the name of the library.
        native-lib

        # Sets the library as a shared library.
        SHARED

        # Provides a relative path to your source file(s).
        ${native_srcs})

# CMAKE_SOURCE_DIR CMAKE_SOURCE_DIR 表示CMakeLists.txt所在文件的根目录，如当前的根目录是app文件夹；
#设置头文件目录
include_directories(${CMAKE_SOURCE_DIR}/src/main/cpp/include)

# ffmpeg so库
add_library(avcodec SHARED IMPORTED)
set_target_properties(avcodec
        PROPERTIES
        IMPORTED_LOCATION
        ${CMAKE_SOURCE_DIR}/src/main/cpp/armeabi-v7a/libavcodec.so)

add_library(avformat SHARED IMPORTED)
set_target_properties(
        avformat
        PROPERTIES
        IMPORTED_LOCATION
        ${CMAKE_SOURCE_DIR}/src/main/cpp/armeabi-v7a/libavformat.so)

add_library(avfilter SHARED IMPORTED)
set_target_properties(
        avfilter
        PROPERTIES
        IMPORTED_LOCATION
        ${CMAKE_SOURCE_DIR}/src/main/cpp/armeabi-v7a/libavfilter.so)

add_library(avutil SHARED IMPORTED)
set_target_properties(
        avutil
        PROPERTIES
        IMPORTED_LOCATION
        ${CMAKE_SOURCE_DIR}/src/main/cpp/armeabi-v7a/libavutil.so)

add_library(swresample SHARED IMPORTED)
set_target_properties(
        swresample
        PROPERTIES
        IMPORTED_LOCATION
        ${CMAKE_SOURCE_DIR}/src/main/cpp/armeabi-v7a/libswresample.so)

add_library(swscale SHARED IMPORTED)
set_target_properties(
        swscale
        PROPERTIES
        IMPORTED_LOCATION
        ${CMAKE_SOURCE_DIR}/src/main/cpp/armeabi-v7a/libswscale.so)


# ffmpeg  end

# Searches for a specified prebuilt library and stores the path as a
# variable. Because CMake includes system libraries in the search path by
# default, you only need to specify the name of the public NDK library
# you want to add. CMake verifies that the library exists before
# completing its build.

find_library( # Sets the name of the path variable.
        log-lib

        # Specifies the name of the NDK library that
        # you want CMake to locate.
        log)

# Specifies libraries CMake should link to your target library. You
# can link multiple libraries, such as libraries you define in this
# build script, prebuilt third-party libraries, or system libraries.

target_link_libraries( # Specifies the target library.
        native-lib

        # Links the target library to the log library
        # included in the NDK.
        #目标库需要链接的库
        avcodec
        avformat
        avfilter
        avutil
        swresample
        swscale

        # shader渲染视频
        EGL
        GLESv2
        OpenSLES

        android
        ${log-lib})