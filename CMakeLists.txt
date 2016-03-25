# this is for emacs file handling -*- mode: cmake; indent-tabs-mode: nil -*-
CMAKE_MINIMUM_REQUIRED(VERSION 3.1)

set(PROJECT_NAME_STR ogre_minimal)
project(${PROJECT_NAME_STR} CXX)

if(UNIX)
    if(EXISTS "/usr/share/OGRE/cmake/modules")
        set(CMAKE_MODULE_PATH "/usr/share/OGRE/cmake/modules;${CMAKE_MODULE_PATH}")
                
    else ()
        message(SEND_ERROR "Failed to find module path.")
    endif(EXISTS "/usr/share/OGRE/cmake/modules")
endif(UNIX)

find_package(OGRE REQUIRED)
find_package(OIS REQUIRED)
# BOOST
set(OGRE_BOOST_COMPONENTS thread date_time)
find_package(Boost COMPONENTS ${OGRE_BOOST_COMPONENTS} REQUIRED)
add_definitions(-DBOOST_ALL_NO_LIB)
set(OGRE_LIBRARIES ${OGRE_LIBRARIES} ${Boost_LIBRARIES})

#-------------------
# set common include folder for module
#-------------------
set(COMMON_INCLUDES ${PROJECT_SOURCE_DIR}/src)

#-------------------
# Build location
#-------------------
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/build)

#-------------------
# Executable
#-------------------
add_executable(${PROJECT_NAME_STR}
        src/main.cpp
        src/ObjectManager.cpp
        src/SimpleFrameListener.cpp
        src/SimpleKeyListener.cpp
        src/SimpleMouseListener.cpp
        )
target_link_libraries(${PROJECT_NAME_STR} ${OGRE_LIBRARIES} ${OIS_LIBRARIES})

# Enable C++11 support in GNU-Compiler
set_property(TARGET ${PROJECT_NAME_STR} PROPERTY CXX_STANDARD 11)
