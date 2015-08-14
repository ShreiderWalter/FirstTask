cmake_minimum_required (VERSION 2.6)

project (FirstTask)

set_property(GLOBAL PROPERTY ON)

message ("cxx Flags: " ${CMAKE_CXX_FLAGS})

add_subdirectory(Client)
add_subdirectory(CommonLib)
add_subdirectory(Server)