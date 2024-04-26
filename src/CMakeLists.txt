# Add the executable target
add_executable(PdfPulse main.cpp)

# Include directories for external libraries
add_subdirectory(extLibs)

# Link against any libraries if needed
# target_link_libraries(PdfPulse SomeOtherLibrary)

# Link against the ZipLib library
target_link_libraries(PdfPulse ZipLib)