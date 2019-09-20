cmake_minimum_required (VERSION 3.1)
include(ExternalProject)

project(kcollections-example)

set(CMAKE_CURRENT_SOURCE_DIR src)

set(SOURCE
  ${CMAKE_CURRENT_SOURCE_DIR}/TestSetLoad.cxx)

ExternalProject_Add(project_kcollections
  GIT_REPOSITORY "git@github.com:masakistan/kcollections.git"
  GIT_TAG "origin/cmake"
  INSTALL_COMMAND ""
  UPDATE_COMMAND "")
ExternalProject_Get_Property(project_kcollections install_dir)
add_library(Kset SHARED IMPORTED)
set(KCOLLECTIONS_DIR "${install_dir}/src/project_kcollections")
set_property(TARGET Kset PROPERTY IMPORTED_LOCATION ${KCOLLECTIONS_DIR}-build/libKset${CMAKE_SHARED_LIBRARY_SUFFIX})
include_directories(test "${KCOLLECTIONS_DIR}/inc")
include_directories(test "${KCOLLECTIONS_DIR}/libs/uint256_t")

set(CMAKE_CXX_STANDARD 14)

add_executable(test ${SOURCE})
set_target_properties(test PROPERTIES COMPILE_DEFINITIONS "KSET")
add_dependencies(test project_kcollections)
target_link_libraries(test Kset)
