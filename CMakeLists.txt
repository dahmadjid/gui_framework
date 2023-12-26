# CMakeList.txt : Top-level CMake project file, do global configuration
# and include sub-projects here.
#
cmake_minimum_required (VERSION 3.8)

project ("GuiFramework")


add_subdirectory(lib/webview)

add_executable(Gui 
	src/GuiFramework.hpp
    src/main.cpp
)

if (WIN32)
    target_compile_options(Gui PUBLIC /std:c++20)
else()
    if(CMAKE_BUILD_TYPE STREQUAL "Release") 
        target_compile_options(Gui PUBLIC -Wall -Wextra -Wpedantic -Wunused -Wconversion -O3 -std=c++20 -fno-exceptions -ffast-math)
        target_link_options(Gui PUBLIC -fuse-ld=lld)
    else()
        target_compile_options(Gui PUBLIC -g -fsanitize=address -Wall -Wextra -Wpedantic -Wunused -Wconversion -O3 -std=c++20 -fno-exceptions)
        target_link_options(Gui PUBLIC -fuse-ld=lld -fsanitize=address)
    endif()
endif()
target_link_libraries(Gui webview)
