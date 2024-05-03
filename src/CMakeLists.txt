cmake_minimum_required(VERSION 3.22)

include(FetchContent)

set(CMAKE_POLICY_DEFAULT_CMP0077 NEW)
set(SKIP_INSTALL_EXPORT TRUE)
set(FETCHCONTENT_QUIET FALSE)
set(CMAKE_VERBOSE_MAKEFILE ON)
set(CMAKE_POSITION_INDEPENDENT_CODE ON)

set(CMAKE_CXX_STANDARD 14)

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
  GIT_REPOSITORY https://github.com/DreamyCecil/ZipLib.git
  GIT_TAG        689a2570a15bf17a98f8729936abb5097193e6a6
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

  set(ZIPLIB_INCLUDE_DIR ${ziplib_SOURCE_DIR}/Source/ZipLib)
  set(ZIPLIB_LIBRARY ziplib)

  cmake_policy(SET CMP0077 NEW)

  add_subdirectory(${ziplib_SOURCE_DIR} ${ziplib_BINARY_DIR})
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
  add_subdirectory(${libharu_SOURCE_DIR} ${libharu_BINARY_DIR} EXCLUDE_FROM_ALL)
endif()

include_directories(
  ${libharu_SOURCE_DIR}/include 
  ${libharu_BINARY_DIR}/include
  ${ZIPLIB_INCLUDE_DIR}
  ${PROJECT_BINARY_DIR}/extlibs/rapidxml
  ${PROJECT_BINARY_DIR}/include
)

link_directories(
  ${libharu_BINARY_DIR}/src
  ${ZIPLIB_BINARY_DIR}/Source/ZipLib
)

set(sources_library
    zip_extractor.cpp
    xml_parser.cpp
    pdf_builder.cpp
)

set(headers_library
    zip_extractor.hpp
    xml_parser.hpp
    pdf_builder.hpp
)

set(sources_executable
    main.cpp
)

set(headers_executable
)

# add_library(pdf_pulse STATIC ${sources_library} ${headers_library})

# target_link_libraries(pdf_pulse
#     PUBLIC
#         ${HPDF_LIBRARY}
#         ${ZIPLIB_LIBRARY}
# )

add_executable(pdf_pulse_exe ${sources_executable} ${headers_executable})

# target_link_libraries(pdf_pulse_exe
#     PRIVATE
#         pdf_pulse
# )