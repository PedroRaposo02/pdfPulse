cmake_minimum_required(VERSION 3.22)

include(FetchContent)

set(CMAKE_CXX_STANDARD 14)

set(CMAKE_POLICY_DEFAULT_CMP0077 NEW)
set(SKIP_INSTALL_EXPORT TRUE)
set(FETCHCONTENT_QUIET FALSE)
set(CMAKE_VERBOSE_MAKEFILE ON)
set(CMAKE_POSITION_INDEPENDENT_CODE ON)


if (UNIX AND NOT APPLE)
  find_package(PkgConfig REQUIRED)
  pkg_check_modules(GTK REQUIRED gtk+-3.0)
  include_directories(${GTK_INCLUDE_DIRS})  
endif (UNIX AND NOT APPLE)

FetchContent_Declare(libpng
  GIT_REPOSITORY  https://github.com/glennrp/libpng.git
  GIT_TAG         v1.6.39
  GIT_SHALLOW     TRUE
  GIT_PROGRESS    TRUE
)

FetchContent_Declare(zlib
  GIT_REPOSITORY  https://github.com/madler/zlib.git
  GIT_TAG         v1.2.13
  GIT_SHALLOW     TRUE
  GIT_PROGRESS    TRUE
)

FetchContent_Declare(ziplib
  GIT_REPOSITORY https://github.com/PedroRaposo02/ZipLib.git
  GIT_TAG        master
  GIT_SHALLOW    TRUE
  GIT_PROGRESS   TRUE
  OVERRIDE_FIND_PACKAGE
)

FetchContent_Declare(libharu
  GIT_REPOSITORY  https://github.com/libharu/libharu.git
  GIT_TAG         8dbcfe470581edc4bc52c3ef132d410e66cadc20
  GIT_SHALLOW     TRUE
  GIT_PROGRESS    TRUE
  OVERRIDE_FIND_PACKAGE
)

# FETCHContent_Declare(libiconv
#   GIT_REPOSITORY https://github.com/PedroRaposo02/libiconv.git
#   GIT_TAG        master
#   GIT_SHALLOW    TRUE
#   GIT_PROGRESS   TRUE
#   OVERRIDE_FIND_PACKAGE
# )

FetchContent_GetProperties(zlib)
if(NOT zlib_POPULATED)
  FetchContent_Populate(zlib)
  execute_process(
    COMMAND           ${GIT_EXECUTABLE} apply ${CMAKE_CURRENT_LIST_DIR}/cmake/zlib.patch
    WORKING_DIRECTORY ${zlib_SOURCE_DIR}
    #OUTPUT_QUIET
    #ERROR_QUIET
  )
  set(ZLIB_INCLUDE_DIR ${zlib_SOURCE_DIR} ${zlib_BINARY_DIR})
  set(ZLIB_LIBRARY zlibstatic)
  set(CMAKE_PROJECT_INCLUDE_BEFORE "${CMAKE_CURRENT_SOURCE_DIR}/cmake/enable_cmp0048.cmake")
  add_subdirectory(${zlib_SOURCE_DIR} ${zlib_BINARY_DIR} EXCLUDE_FROM_ALL)
  unset(CMAKE_PROJECT_INCLUDE_BEFORE)
endif()

if(NOT libpng_POPULATED)
  FetchContent_Populate(libpng)

  set(PNG_PNG_INCLUDE_DIR ${libpng_SOURCE_DIR} ${libpng_BINARY_DIR})
  set(PNG_INCLUDE_DIR ${PNG_PNG_INCLUDE_DIR})
  set(PNG_LIBRARY png_static)

  cmake_policy(SET CMP0077 NEW)
  set(PNG_SHARED OFF)
  set(CMAKE_PROJECT_INCLUDE_BEFORE "${CMAKE_CURRENT_SOURCE_DIR}/cmake/enable_cmp0048.cmake")
  add_subdirectory(${libpng_SOURCE_DIR} ${libpng_BINARY_DIR} EXCLUDE_FROM_ALL)
  unset(CMAKE_PROJECT_INCLUDE_BEFORE)

endif()

if(NOT ziplib_POPULATED)
  FetchContent_Populate(ziplib)

  set(ZIPLIB_LIBRARY ziplib)

  set(ZIPLIB_INCLUDE_DIRS
    ${ziplib_SOURCE_DIR}
    ${ziplib_BINARY_DIR}
  )

  cmake_policy(SET CMP0077 NEW)

  add_subdirectory(${ziplib_SOURCE_DIR} ${ziplib_BINARY_DIR} EXCLUDE_FROM_ALL)
endif()

if (WIN32 OR APPLE)
  find_package(PNG REQUIRED)
endif ()

FetchContent_GetProperties(libharu)
if(NOT libharu_POPULATED)
  FetchContent_Populate(libharu)
  set(LIBHPDF_STATIC ON)
  set(BUILD_SHARED_LIBS OFF)
  set(HPDF_LIBRARY hpdf)
  set(LIBHARU_INCLUDE_DIRS
    ${libharu_BINARY_DIR}/include
    ${libharu_SOURCE_DIR}/include
  )
  add_subdirectory(${libharu_SOURCE_DIR} ${libharu_BINARY_DIR} EXCLUDE_FROM_ALL)
endif()

# FetchContent_GetProperties(libiconv)
# if(NOT libiconv_POPULATED)
#   FetchContent_Populate(libiconv)
#   set(LIBICONV_INCLUDE_DIRS 
#     ${libiconv_BINARY_DIR}/include
#     ${libiconv_BINARY_DIR}/source
#   )
#   set(LIBICONV_LIBRARY libiconv)
#   add_subdirectory(${libiconv_SOURCE_DIR} ${libiconv_BINARY_DIR} EXCLUDE_FROM_ALL)
# endif()

set(sources_library
    pdf_pulse.cpp
    pdf_builder.cpp
    zip_extractor.cpp
    xml_parser.cpp
    utils.cpp
)

set(headers_library
    pdf_pulse.hpp
    pdf_builder.hpp
    zip_extractor.hpp
    xml_parser.hpp
    globals.hpp
    printer.hpp
    utils.hpp
)

set(SRCS_EXECUTABLE
    test/main.cpp
)

set(RAPIDXML_HPP
    extlibs/rapidxml/rapidxml.hpp
    extlibs/rapidxml/rapidxml_print.hpp
    extlibs/rapidxml/rapidxml_utils.hpp
    extlibs/rapidxml/rapidxml_iterators.hpp
)

set(RAPIDXML_INCLUDE_DIRS
    extlibs/rapidxml
)

add_subdirectory(extlibs/libiconv)
set(LIBICONV_INCLUDE_DIRS 
    ${libiconv_BINARY_DIR}/include
    ${libiconv_BINARY_DIR}/source
)

set(LIBICONV_LIBRARY libiconv)

add_library(pdf_pulse STATIC ${sources_library} ${RAPIDXML_HPP})

target_include_directories(pdf_pulse
    PUBLIC
        include
        ${LIBHARU_INCLUDE_DIRS}
        ${ZIPLIB_INCLUDE_DIRS}
        ${RAPIDXML_INCLUDE_DIRS}
        # ${LIBICONV_INCLUDE_DIRS}
)
target_link_libraries(pdf_pulse
    PUBLIC
        ${HPDF_LIBRARY}
        ${ZIPLIB_LIBRARY}
        # ${LIBICONV_LIBRARY}
)


add_executable(pdf_pulse_main ${SRCS_EXECUTABLE})

target_link_libraries(pdf_pulse_main
    PUBLIC
        pdf_pulse
)

target_include_directories(pdf_pulse_main
    PUBLIC
        pdf_pulse
)