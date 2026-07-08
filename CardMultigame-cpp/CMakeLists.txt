cmake_minimum_required(VERSION 3.22)
project(CardMultigame CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# --- Core library: every src/**/*.cpp except the REPL entry point ---
# GLOB with CONFIGURE_DEPENDS re-globs on build, so new class files are picked up
# without a manual re-configure (the tree grows slice by slice).
file(GLOB_RECURSE CM_LIB_SOURCES CONFIGURE_DEPENDS ${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp)
list(REMOVE_ITEM CM_LIB_SOURCES ${CMAKE_CURRENT_SOURCE_DIR}/src/main.cpp)

if(CM_LIB_SOURCES)
    add_library(cardmultigame_core STATIC ${CM_LIB_SOURCES})
    target_include_directories(cardmultigame_core PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/src)
else()
    # Slice 0: no classes yet — header-only placeholder so the graph links.
    add_library(cardmultigame_core INTERFACE)
    target_include_directories(cardmultigame_core INTERFACE ${CMAKE_CURRENT_SOURCE_DIR}/src)
endif()

# --- REPL executable ---
add_executable(cardmultigame src/main.cpp)
target_link_libraries(cardmultigame PRIVATE cardmultigame_core)

# --- Tests (doctest, vendored) ---
enable_testing()
file(GLOB CM_TEST_SOURCES CONFIGURE_DEPENDS ${CMAKE_CURRENT_SOURCE_DIR}/tests/*.cpp)
add_executable(cardmultigame_tests ${CM_TEST_SOURCES})
target_include_directories(cardmultigame_tests PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/tests)
target_link_libraries(cardmultigame_tests PRIVATE cardmultigame_core)
add_test(NAME cardmultigame_tests COMMAND cardmultigame_tests)
