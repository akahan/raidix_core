
add_library(rdcore SHARED ../lib/object.cpp ../lib/raid.cpp)
target_include_directories(rdcore PUBLIC 
    $<BUILD_INTERFACE:${CMAKE_SOURCE_DIR}/include>
)

add_executable(rdcmd  rdcmd/main.cpp ../lib/ipc.cpp)
target_include_directories(rdcmd PUBLIC 
    $<BUILD_INTERFACE:${CMAKE_SOURCE_DIR}/include>
)
target_link_libraries( rdcmd ${Boost_LIBRARIES} ${CMAKE_THREAD_LIBS_INIT} )

add_executable(rdscan rdscan/client.cpp)
target_link_libraries( rdscan ${Boost_LIBRARIES} ${CMAKE_THREAD_LIBS_INIT} )

install(TARGETS rdcmd rdscan RUNTIME DESTINATION bin)


