cmake_minimum_required(VERSION 3.18.0)
project(RapidXml)

set(sources
    rapidxml_iterators.hpp
    rapidxml_print.hpp
    rapidxml_utils.hpp
    rapidxml.hpp
)

# Library
add_library(RapidXml SHARED ${sources})

target_include_directories(RapidXml PRIVATE .)

# Properties
target_compile_features(RapidXml PUBLIC cxx_std_11)
set_target_properties(RapidXml PROPERTIES LINKER_LANGUAGE CXX)

# Set output name for the library file
set_target_properties(RapidXml PROPERTIES OUTPUT_NAME RapidXml)

set_target_properties(RapidXml PROPERTIES FOLDER "External")

# Specify output directory for the library file
set(LIBRARY_OUTPUT_PATH ${CMAKE_BINARY_DIR}/lib)  # Change this to your desired output directory

# Specify installation directory for the library file
install(TARGETS RapidXml
        ARCHIVE DESTINATION lib  # Change this to your desired installation directory
        )