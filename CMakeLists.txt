############## BASE & VERSIONING ###############
######## This should work on any system ########

cmake_minimum_required (VERSION 3.0)
project (indieStudio)
set(CMAKE_CXX_STANDARD 11)
set (Tutorial_VERSION_MAJOR 1)
set (Tutorial_VERSION_MINOR 0)
enable_language(CXX)

################### MACROS ####################

MACRO(HEADER_DIRECTORIES return_list)
    FILE(GLOB_RECURSE new_list *.hpp)
    SET(dir_list "")
    FOREACH(file_path ${new_list})
        GET_FILENAME_COMPONENT(dir_path ${file_path} PATH)
        SET(dir_list ${dir_list} ${dir_path})
    ENDFOREACH()
    LIST(REMOVE_DUPLICATES dir_list)
ENDMACRO()

################# VARIABLES #################

set(BASE_PATH ${CMAKE_CURRENT_SOURCE_DIR})
set(LIBS_PATH ${CMAKE_CURRENT_SOURCE_DIR}/libs)
set(SRC_PATH ${BASE_PATH}/src)
set(INC_PATH ${BASE_PATH}/include)
set(X11_DIR ${LIBS_PATH}/X11)
set(XXF86VM_DIR ${LIBS_PATH}/Xxf86vm)
set(GL_DIR ${LIBS_PATH}/GL)
set(IRRLICH_DIR ${LIBS_PATH}/irrlicht-1.8.4)
set(IRRLICH_BIN_DIR ${IRRLICH_DIR}/bin)
set(EXECUTABLE_OUTPUT_PATH "../dist")

message(STATUS ${BASE_PATH})

file(GLOB_RECURSE HDR_FILES ${BASE_PATH}/include/*.hpp)
file(GLOB_RECURSE SRC_FILES ${BASE_PATH}/src/*.cpp)

HEADER_DIRECTORIES(${BASE_PATH}/include)

############# PLATFORM HANDLING #############

if (MSVC)
    message(STATUS Compiling for Windows MSVC)
    set(LIBRARIES ${IRRLICH_DIR}/lib/Win32-visualstudio/Irrlicht.lib)
    set(LIBRARIES_RUNTIME ${IRRLICH_DIR}/bin/Win32-VisualStudio/Irrlicht.dll)
    install(FILES ${LIBRARIES_RUNTIME} DESTINATION ${BASE_PATH}/dist)
    include_directories(${IRRLICH_DIR}/include/
   	                ${dir_list})
endif(MSVC)

if (UNIX AND NOT APPLE)
    message(STATUS "Compiling for UNIX")
    find_package(OpenGL REQUIRED)

    set(LIBRARIES ${LIBRARIES} ${IRRLICH_DIR}/lib/Linux/libIrrlicht.a)
    set(LIBRARIES ${LIBRARIES} ${X11_DIR}/libX11.so.6.3.0)
    set(LIBRARIES ${LIBRARIES} ${XXF86VM_DIR}/libXxf86vm.so.1)
    set(LIBRARIES ${LIBRARIES} ${GL_DIR}/libGL.so)
    set(LIBRARIES ${LIBRARIES} pthread)



    set_property(DIRECTORY APPEND PROPERTY ADDITIONAL_MAKE_CLEAN_FILES
            "${BASE_PATH}/dist/Irrlicht.dll"
            "${BASE_PATH}/dist/indieStudio.ilk"
            "${BASE_PATH}/dist/indieStudio")
    include_directories(${IRRLICH_DIR}/include/
    		                ${dir_list})
endif(UNIX AND NOT APPLE)

if (APPLE AND UNIX)
    message(STATUS "Compiling for UNIX")
    set(LIBRARIES ${LIBRARIES} ${IRRLICH_DIR}/lib/MacOSX/libIrrlicht.a)

    set_property(DIRECTORY APPEND PROPERTY ADDITIONAL_MAKE_CLEAN_FILES
            "${BASE_PATH}/dist/Irrlicht.dll"
            "${BASE_PATH}/dist/indieStudio.ilk"
            "${BASE_PATH}/dist/indieStudio")
    include_directories(${IRRLICH_DIR}/include/
    		                ${dir_list})
endif()

################# COMPILATION #################

add_executable(indieStudio ${HDR_FILES} ${SRC_FILES} include/Components/PhysicalBody.hpp include/Systems/MovementSystem.hpp src/Systems/MovementSystem.cpp include/Components/WallCollision.hpp include/Components/PlayerCollision.hpp include/Systems/CollisionSystem.hpp src/Systems/CollisionSystem.cpp)
target_link_libraries(indieStudio ${LIBRARIES})


################ CRITERION ####################

set (CRITERION "False" CACHE STRING "Enable/Disable criterion [True | False]")
