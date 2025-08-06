cmake_minimum_required(VERSION 3.10)

project(design_patterns LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_BUILD_TYPE Release)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
add_compile_options(-Wall -Wextra)

find_program(CLANG_FORMAT NAMES clang-format)
if(CLANG_FORMAT)
  file(GLOB_RECURSE SOURCES *.hpp *.cc)
  add_custom_target(format
    COMMAND ${CLANG_FORMAT} -i ${SOURCES}
    COMMENT "Formatting source files with clang-format"
    WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
  )
else()
  message(WARNING "clang-format not found, 'format' target will not be available.")
endif()

find_program(CLANG_TIDY NAMES clang-tidy)
if(CLANG_TIDY)
  message(STATUS "clang-tidy found: ${CLANG_TIDY}")
  # set(CMAKE_CXX_CLANG_TIDY "${CLANG_TIDY}")
else()
  message(WARNING "clang-tidy not found! Static analysis skipped.")
endif()

foreach(GYM_NUMBER RANGE 15 15)
  if(GYM_NUMBER LESS 10)
    set(GYM_DIR "gym0${GYM_NUMBER}")
  else()
    set(GYM_DIR "gym${GYM_NUMBER}")
  endif()
  
  if(EXISTS "${CMAKE_CURRENT_SOURCE_DIR}/${GYM_DIR}")
    message(STATUS "Configuring ${GYM_DIR}")
    file(GLOB_RECURSE ${GYM_DIR}_SOURCES "${GYM_DIR}/src/*.cc")
    add_executable(${GYM_DIR})
    target_sources(${GYM_DIR} PRIVATE ${${GYM_DIR}_SOURCES})
    target_include_directories(${GYM_DIR} PRIVATE ${GYM_DIR}/include)
  endif()
endforeach()
