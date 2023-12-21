cmake_minimum_required(VERSION 3.5)

project(programming-person-exercise LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(programming-person-exercise main.cpp
    person.cpp
    person.h
    table.h)

include(GNUInstallDirs)
install(TARGETS programming-person-exercise
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
