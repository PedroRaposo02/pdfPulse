# Add the executable target
add_executable(PdfPulse main.cpp)

# Include directories for external libraries
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/../extLibs/RapidXml)

# Link against any libraries if needed
# target_link_libraries(MyExecutable SomeOtherLibrary)