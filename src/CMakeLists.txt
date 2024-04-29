add_subdirectory(extlibs)

set(sources
    main.cpp
    zip_extractor.cpp
    zip_extractor.hpp
    xml_parser.cpp
    xml_parser.hpp
)

set(CMAKE_CXX_STANDARD 11)
add_executable(PdfPulse ${sources})

target_include_directories(PdfPulse
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/extlibs/rapidxml-1.13
)

target_link_libraries(PdfPulse
    PRIVATE
        ZipLib
        hpdf
)