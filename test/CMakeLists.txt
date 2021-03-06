cmake_minimum_required(VERSION 3.14 FATAL_ERROR)

project({#PROJECT_TITLE#}Tests LANGUAGES CXX)

# ---- Options ----

option(ENABLE_TEST_COVERAGE "Enable test coverage" OFF)
option(TEST_INSTALLED_VERSION "Test the version found by find_package" OFF)

# --- Import tools ----

include(../cmake/tools.cmake)

# ---- Dependencies ----

include(../cmake/CPM.cmake)

CPMAddPackage("gh:onqtam/doctest#2.4.5")
CPMAddPackage("gh:TheLartians/Format.cmake@1.7.0")

if(TEST_INSTALLED_VERSION)
  find_package({#PROJECT_TITLE#} REQUIRED)
else()
  CPMAddPackage(NAME {#PROJECT_TITLE#} SOURCE_DIR ${CMAKE_CURRENT_LIST_DIR}/..)
endif()

# ---- Create binary ----

file(GLOB sources CONFIGURE_DEPENDS ${CMAKE_CURRENT_SOURCE_DIR}/source/*.cpp)
add_executable({#PROJECT_TITLE#}Tests ${sources})
target_link_libraries({#PROJECT_TITLE#}Tests doctest::doctest {#PROJECT_TITLE#}::{#PROJECT_TITLE#})
set_target_properties({#PROJECT_TITLE#}Tests PROPERTIES CXX_STANDARD 17)

# enable compiler warnings
if(NOT TEST_INSTALLED_VERSION)
  if(CMAKE_CXX_COMPILER_ID MATCHES "Clang" OR CMAKE_CXX_COMPILER_ID MATCHES "GNU")
    target_compile_options({#PROJECT_TITLE#} PUBLIC -Wall -Wpedantic -Wextra -Werror)
  elseif(MSVC)
    target_compile_options({#PROJECT_TITLE#} PUBLIC /W4 /WX)
    target_compile_definitions({#PROJECT_TITLE#}Tests PUBLIC DOCTEST_CONFIG_USE_STD_HEADERS)
  endif()
endif()

# ---- Add {#PROJECT_TITLE#}Tests ----

enable_testing()

# Note: doctest and similar testing frameworks can automatically configure CMake tests. For other
# testing frameworks add the tests target instead: add_test(NAME {#PROJECT_TITLE#}Tests COMMAND {#PROJECT_TITLE#}Tests)

include(${doctest_SOURCE_DIR}/scripts/cmake/doctest.cmake)
doctest_discover_tests({#PROJECT_TITLE#}Tests)

# ---- code coverage ----

if(ENABLE_TEST_COVERAGE)
  target_compile_options({#PROJECT_TITLE#} PUBLIC -O0 -g -fprofile-arcs -ftest-coverage)
  target_link_options({#PROJECT_TITLE#} PUBLIC -fprofile-arcs -ftest-coverage)
endif()
