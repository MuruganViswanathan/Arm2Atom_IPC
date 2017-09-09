#
#   Author: Murugan Viswanathan
#   date: 09/08/2017
#

set(PROJ_SOCKCLIENT sockclient)
file(GLOB SOURCES "*.c")

add_executable(sockclient ${SOURCES})
#add_library(${PROJ_SOCKCLIENT} STATIC ${HEADERS} ${SOURCES})
#add_library(${PROJ_SOCKCLIENT}.shared SHARED ${HEADERS} ${SOURCES})
#set_target_properties(${PROJ_SOCKCLIENT}.shared PROPERTIES OUTPUT_NAME ${PROJ_SOCKCLIENT})
#set_property(TARGET ${PROJ_SOCKCLIENT} PROPERTY C_STANDARD 99)
#set_property(TARGET ${PROJ_SOCKCLIENT}.shared PROPERTY C_STANDARD 99)


target_link_libraries (${PROJ_SOCKCLIENT}
    ${CMAKE_THREAD_LIBS_INIT}
    -lm
    -lpthread
    -lrt
    )

install (TARGETS ${PROJ_SOCKCLIENT} DESTINATION bin)

