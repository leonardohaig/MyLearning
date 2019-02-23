cmake_minimum_required(VERSION 3.10)
project(MyLearning)

set(CMAKE_CXX_STANDARD 11)
#set(CMAKE_VERBOSE_MAKEFILE ON)

IF(NOT CMAKE_BUILD_TYPE)
    SET(CMAKE_BUILD_TYPE Release)
ENDIF()

MESSAGE("=============Build type: " ${CMAKE_BUILD_TYPE} "=======================")
if( ${CMAKE_BUILD_TYPE} STREQUAL Release )
    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS}  -Wall  -O3 -march=native ")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall   -O3 -march=native")
    message("===============程序将进行O3优化==========================")
else()
    message("==============程序未采用O3优化=========================")
endif()

MESSAGE(STATUS "operation system is ${CMAKE_SYSTEM}")
message("===========CMAKE_CXX_COMPILER:${CMAKE_CXX_COMPILER}")
message("===========CMAKE_CURRENT_LIST_DIR:${CMAKE_CURRENT_LIST_DIR}")




if (CMAKE_C_COMPILER MATCHES "aarch64")
    message(STATUS "build for arm-aarch64")
elseif(CMAKE_C_COMPILER MATCHES "gnueabi-gcc")
    message(STATUS "build for arm-gnueabi")
elseif(CMAKE_C_COMPILER MATCHES "gnueabihf")
    message(STATUS "build for arm-gnueabihf")
elseif(CMAKE_C_COMPILER MATCHES "x86_64")
    message(STATUS "build for x86_64")
else()
    message(STATUS "build for current host")
endif()


set(LCM_INCLUDE_DIRS /usr/local/include/lcm)
list(APPEND LCM_LIBRARIES  /usr/local/lib/liblcm.so)

# Check C++11 support
include(CheckCXXCompilerFlag)
CHECK_CXX_COMPILER_FLAG("-std=c++11" COMPILER_SUPPORTS_CXX11)
if(COMPILER_SUPPORTS_CXX11)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
    add_definitions(-DCOMPILEDWITHC11)
    message(STATUS "Using flag -std=c++11.")
else()
    message(FATAL_ERROR "The compiler ${CMAKE_CXX_COMPILER} has no C++11 support. Please use a different C++ compiler.")
endif()

#set(OpenCV_DIR /home/liheng/CLionProjects/opencv-2.4.13.6/share/OpenCV)
set(OpenCV_DIR /usr/local/opencv4.0.0)
#set(OpenCV_DIR /usr/share/OpenCV)
find_package(OpenCV REQUIRED)
include_directories(${OpenCV_INCLUDE_DIRS})


message("==============OpenCV library status:==================")
message("====version: ${OpenCV_VERSION}")
message("====libraries: ${OpenCV_LIBS}")
message("====include path: ${OpenCV_INCLUDE_DIRS}")
message("======================================================")



FIND_PACKAGE( OpenMP REQUIRED)
if(OPENMP_FOUND)
    message("OPENMP FOUND")
    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} ${OpenMP_C_FLAGS}")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${OpenMP_CXX_FLAGS}")
    set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} ${OpenMP_EXE_LINKER_FLAGS}")
endif()

add_executable(persectivetransform persectivetransform.cpp)
target_link_libraries(persectivetransform ${OpenCV_LIBS})

add_executable(morphologicalOperations morphologicalOperations.cpp)
target_link_libraries(morphologicalOperations ${OpenCV_LIBS})

add_executable(morphologicalOperations2 morphologicalOperations2.cpp)
target_link_libraries(morphologicalOperations2 ${OpenCV_LIBS})