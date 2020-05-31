cmake_minimum_required(VERSION 3.8)
project(LibrarySystem)

set(CMAKE_C_STANDARD 99)

set(SOURCE_FILES main.c Book.h MeM.h Book.c MeM.c main.h Admin.c Admin.h)
add_executable(LibrarySystem ${SOURCE_FILES})