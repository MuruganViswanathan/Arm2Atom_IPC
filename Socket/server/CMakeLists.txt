#
#   Author: Murugan Viswanathan
#   date: 09/08/2017
#

set(PROJ_SOCKSERVER sockserver)
file(GLOB SOURCES "*.c")

add_executable(sockserver ${SOURCES})
#add_library(${PROJ_SOCKSERVER} STATIC ${HEADERS} ${SOURCES})
#add_library(${PROJ_SOCKSERVER}.shared SHARED ${HEADERS} ${SOURCES})
#set_target_properties(${PROJ_SOCKSERVER}.shared PROPERTIES OUTPUT_NAME ${PROJ_SOCKSERVER})
#set_property(TARGET ${PROJ_SOCKSERVER} PROPERTY C_STANDARD 99)
#set_property(TARGET ${PROJ_SOCKSERVER}.shared PROPERTY C_STANDARD 99)


target_link_libraries (${PROJ_SOCKSERVER}
    ${CMAKE_THREAD_LIBS_INIT}
    -lm
    -lpthread
    -lrt
    )

install (TARGETS ${PROJ_SOCKSERVER} DESTINATION bin)

