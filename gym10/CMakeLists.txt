cmake_minimum_required(VERSION 3.28)

project(gym10 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
add_compile_options(-Wall -Wextra)

include_directories(include)

add_executable(main src/main.cc)

file(GLOB_RECURSE SOURCES "src/*.cc")

target_sources(main PRIVATE ${SOURCES})

find_program(CLANG_FORMAT_EXE NAMES clang-format)

if(CLANG_FORMAT_EXE)
  file(GLOB_RECURSE FILES src/*.cc include/*.hpp)
  list(FILTER FILES EXCLUDE REGEX ".*/json.hpp$")
  add_custom_target(
    format
    COMMAND ${CLANG_FORMAT_EXE} -i ${FILES}
    COMMENT "Running clang-format on source files"
  )
  add_dependencies(main format)
endif()

