############## BASE & VERSIONING ###############
######## This should work on any system ########

cmake_minimum_required (VERSION 3.0)
project (indieStudio)
set (Tutorial_VERSION_MAJOR 1)
set (Tutorial_VERSION_MINOR 0)

set(SRC_FILES
      ../src/test.cpp)

set(HDR_FILES
      ../include/test.hpp)

set(EXECUTABLE_OUTPUT_PATH "../dist")
set(IRRLICHT_REPOSITORY "../libs/irrlicht-1.8.4/")
add_executable(indieStudio ${SRC_FILES} ${HDR_FILES})

############## PLATFORM HANDLING ###############

if (UNIX)
    install(TARGETS indieStudio DESTINATION "bin")
elseif (WIN32 or WIN64)
    message(WARNING "Use the installer in the dist directory")
endif()

