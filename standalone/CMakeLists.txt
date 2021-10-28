cmake_minimum_required(VERSION 3.14 FATAL_ERROR)

project({#PROJECT_TITLE#}Standalone LANGUAGES CXX)

# --- Import tools ----

include(../cmake/tools.cmake)

# ---- Dependencies ----

include(../cmake/CPM.cmake)

CPMAddPackage(
  GITHUB_REPOSITORY jarro2783/cxxopts
  VERSION 2.2.1
  OPTIONS "CXXOPTS_BUILD_EXAMPLES NO" "CXXOPTS_BUILD_TESTS NO" "CXXOPTS_ENABLE_INSTALL YES"
)

CPMAddPackage(NAME {#PROJECT_TITLE#} SOURCE_DIR ${CMAKE_CURRENT_LIST_DIR}/..)

# ---- Create standalone executable ----

file(GLOB sources CONFIGURE_DEPENDS ${CMAKE_CURRENT_SOURCE_DIR}/source/*.cpp)

add_executable({#PROJECT_TITLE#}Standalone ${sources})

set_target_properties({#PROJECT_TITLE#}Standalone PROPERTIES CXX_STANDARD 17 OUTPUT_NAME "{#PROJECT_TITLE#}")

target_link_libraries({#PROJECT_TITLE#}Standalone {#PROJECT_TITLE#}::{#PROJECT_TITLE#} cxxopts)
