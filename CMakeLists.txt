# CMakeList.txt : CMake project for space-invaders, include source and define
# project specific logic here.
#
cmake_minimum_required (VERSION 3.8)

# Enable Hot Reload for MSVC compilers if supported.
if (POLICY CMP0141)
  cmake_policy(SET CMP0141 NEW)
  set(CMAKE_MSVC_DEBUG_INFORMATION_FORMAT "$<IF:$<AND:$<C_COMPILER_ID:MSVC>,$<CXX_COMPILER_ID:MSVC>>,$<$<CONFIG:Debug,RelWithDebInfo>:EditAndContinue>,$<$<CONFIG:Debug,RelWithDebInfo>:ProgramDatabase>>")
endif()

project (space-invaders LANGUAGES C CXX)

# add source files
file(GLOB SOURCES "src/*.cpp")
add_executable (space-invaders ${SOURCES})

# add raylib include headers and link
if(MSVC)
target_include_directories(space-invaders PRIVATE deps/raylib/include)
# Link raylib library (Windows)
target_link_libraries(space-invaders PRIVATE ${CMAKE_SOURCE_DIR}/deps/raylib/lib/raylib.lib)

    set_target_properties(space-invaders PROPERTIES LINK_FLAGS "/NODEFAULTLIB:\"msvcrt.lib\"")
    target_link_libraries(space-invaders PRIVATE winmm)
endif()
