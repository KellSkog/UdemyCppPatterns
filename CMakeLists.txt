#[[
    When CMake processes a project source tree, the entry point is a source file called CMakeLists.txt 
    in the top-level source directory. This file may contain the entire build specification or 
    use the add_subdirectory() command to add subdirectories to the build. 
    Each subdirectory added by the command must also contain a CMakeLists.txt file as the entry point to that directory. 
    For each source directory whose CMakeLists.txt file is processed CMake generates 
    a corresponding directory in the build tree to act as the default working and output directory.]]
cmake_minimum_required(VERSION 3.10)
project(CppPatterns)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

add_executable(prima src/main.cc)
#[[
    target_include_directories(<target> [SYSTEM] [BEFORE]
  <INTERFACE|PUBLIC|PRIVATE> [items1...]
  [<INTERFACE|PUBLIC|PRIVATE> [items2...] ...])
  If BEFORE is specified, the content will be prepended to the property instead of being appended.
]]
target_include_directories(prima PRIVATE inc)

#Arguments to target_compile_definitions may use “generator expressions” with the syntax $<...>.
#target_compile_definitions(prima)
#target_compile_options(prima)

#Arguments to target_compile_features may use “generator expressions” with the syntax $<...>.
#target_compile_features(prima)
