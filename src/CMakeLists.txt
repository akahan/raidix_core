
set (RDCORE_SRC_FILES
    ../lib/ipc.cpp
    ../lib/daemon.cpp
    ../lib/object.cpp
    ../lib/raid.cpp
    ../lib/lun.cpp
)

set (RDCMD_SRC_FILES
    rdcmd/main.cpp
    rdcmd/rdcmd.cpp
)

add_library(rdcore SHARED ${RDCORE_SRC_FILES})
target_include_directories(rdcore PUBLIC
    $<BUILD_INTERFACE:${CMAKE_SOURCE_DIR}/include>
)

add_executable(rdcmd  ${RDCMD_SRC_FILES})
target_include_directories(rdcmd PUBLIC
    $<BUILD_INTERFACE:${CMAKE_SOURCE_DIR}/include>
)
target_link_libraries( rdcmd rdcore ${Boost_LIBRARIES} ${CMAKE_THREAD_LIBS_INIT} )

add_executable(rdscan rdscan/client.cpp)
target_link_libraries( rdscan ${Boost_LIBRARIES} ${CMAKE_THREAD_LIBS_INIT} )

install(TARGETS rdcmd rdscan RUNTIME DESTINATION bin)


