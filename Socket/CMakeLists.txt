#
#   Author: Murugan Viswanathan
#   date: 09/08/2017
#

cmake_minimum_required(VERSION 2.8.7)

project(Arm2AtomIPC)
include(ExternalProject)
include(CTest)

#add_definitions(-std=c99)
add_definitions(-std=gnu99)
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -std=c99 -g -Werror -Wall")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c99 -g -Werror -Wall")

set(INSTALL_DIR ${CMAKE_CURRENT_BINARY_DIR}/_install)
set(PREFIX_DIR ${CMAKE_CURRENT_BINARY_DIR}/_prefix)
set(INCLUDE_DIR ${INSTALL_DIR}/include)
set(LIBRARY_DIR ${INSTALL_DIR}/lib)
set(LIBRARY_DIR64 ${INSTALL_DIR}/lib64)
include_directories(${INCLUDE_DIR})
include_directories (SYSTEM /usr/include)

#enable_testing()

if (NOT BUILD_YOCTO)
endif ()

link_directories ( ${LIBRARY_DIR} ${LIBRARY_DIR64} )

add_subdirectory(server)
add_subdirectory(client)


