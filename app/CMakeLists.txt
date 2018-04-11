# For more information about using CMake with Android Studio, read the
# documentation: https://d.android.com/studio/projects/add-native-code.html

# Sets the minimum version of CMake required to build the native library.

cmake_minimum_required(VERSION 3.4.1)

# Creates and names a library, sets it as either STATIC
# or SHARED, and provides the relative paths to its source code.
# You can define multiple libraries, and CMake builds them for you.
# Gradle automatically packages shared libraries with your APK.
#定义常量
set(my_lib_path ${CMAKE_SOURCE_DIR}/libs)
include_directories(${CMAKE_SOURCE_DIR}/src/main/cpp/inc)

add_library(fmod SHARED IMPORTED)
set_target_properties(
        fmod
        PROPERTIES IMPORTED_LOCATION
        ${my_lib_path}/${ANDROID_ABI}/libfmod.so
)
add_library(fmodL SHARED IMPORTED)
set_target_properties(
        fmodL
        PROPERTIES
        IMPORTED_LOCATION
        ${my_lib_path}/${ANDROID_ABI}/libfmodL.so
)
add_library(
        GaofVoiceJni
        SHARED
        src/main/cpp/GaofVoiceJni.cpp)


find_library(
        log-lib
        log)

target_link_libraries(
        GaofVoiceJni
        fmod fmodL
        ${log-lib})