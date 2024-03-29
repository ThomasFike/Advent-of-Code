cmake_minimum_required(VERSION 3.25)

project(Advent-Of-Code)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)
set(CMAKE_CXX_EXTENSIONS OFF)

set(ENABLE_DEVELOPER_MODE
    TRUE
    CACHE BOOL "Enable 'developer mode'")

set(OPT_WARNINGS_AS_ERRORS_DEVELOPER_DEFAULT TRUE)

include(FetchContent)
FetchContent_Declare(_project_options URL https://github.com/aminya/project_options/archive/refs/tags/v0.20.0.zip)
FetchContent_MakeAvailable(_project_options)
include(${_project_options_SOURCE_DIR}/Index.cmake)

set(GIT_SHA
    "Unknown"
    CACHE STRING "SHA this build was generated from")
string(
  SUBSTRING "${GIT_SHA}"
            0
            8
            GIT_SHORT_SHA)


include(${_project_options_SOURCE_DIR}/src/DynamicProjectOptions.cmake)


dynamic_project_options(
  # Note: PCH is disabled by default in developer mode because these headers become
  # globally included and they can mask other errors
  PCH_HEADERS
  <vector>
  <string> # This is a list of headers to pre-compile, here are some common ones
  ENABLE_CONAN
  # CONAN_OPTIONS    # Extra options to pass to conan
  # MSVC_WARNINGS    # Override the defaults for the MSVC warnings
  # CLANG_WARNINGS   # Override the defaults for the CLANG warnings
  # GCC_WARNINGS     # Override the defaults for the GCC warnings
  CPPCHECK_OPTIONS
  --enable=style,performance,warning,portability
  --inline-suppr
  # We cannot act on a bug/missing feature of cppcheck
  --suppress=cppcheckError
  --suppress=internalAstError
  # if a file does not have an internalAstError, we get an unmatchedSuppression error
  --suppress=unmatchedSuppression
  --suppress=passedByValue
  --suppress=syntaxError
  --inconclusive
)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

find_package(fmt CONFIG)

add_subdirectory(common)

add_subdirectory(Day1)
add_subdirectory(Day2)
add_subdirectory(Day3)
add_subdirectory(Day4)
add_subdirectory(Day5)
add_subdirectory(Day6)
add_subdirectory(Day7)
add_subdirectory(Day8)
add_subdirectory(Day9)
add_subdirectory(Day10)
add_subdirectory(Day11)