cmake_minimum_required(VERSION 3.6)
project(irrlitchtest)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES
        main.cpp)

set(IRRLICHT_INCLUDE_DIR /usr/include/Irrlitch)

include_directories(${IRRLICHT_INCLUDE_DIR} ${CMAKE_SOURCE_DIR}/includes)
link_libraries(-lIrrlicht)

add_executable(irrlitchtest ${SOURCE_FILES})