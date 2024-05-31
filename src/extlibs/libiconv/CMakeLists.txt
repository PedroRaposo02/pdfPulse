cmake_minimum_required(VERSION 3.29)

# Set the project name
project(libiconv)

set(CMAKE_CXX_STANDARD 14)

set(SOURCES
    source/iconv.c
    source/localcharset.c
    source/localcharset.h
    source/relocatable.c
    source/relocatable.h    
)

# Add library
add_library(libiconv STATIC ${SOURCES})

# Add include directories
target_include_directories(libiconv 
    PUBLIC 
        include
)