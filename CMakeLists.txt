# CMakeList.txt : Top-level CMake project file, do global configuration
# and include sub-projects here.
#
cmake_minimum_required (VERSION 3.8)

project ("GuiFramework")

add_executable(Gui 
	src/GuiFramework.hpp
    src/main.cpp
    src/webview.h
    src/comp.cpp
)

if (WIN32)
    FetchContent_Declare(
        webview_native
        URL https://www.nuget.org/api/v2/package/Microsoft.Web.WebView2
        DOWNLOAD_EXTRACT_TIMESTAMP TRUE
    )

    FetchContent_MakeAvailable(webview_native)
    message("--- fetch windows webview2 completed")
    target_compile_definitions(Gui WEBVIEW_EDGE)
    target_include_directories(Gui ${webview_native_SOURCE_DIR}/build/native/include)

    # See: https://github.com/webview/webview/blob/master/script/build.bat
    target_link_libraries(Gui "-mwindows -ladvapi32 -lole32 -lshell32 -lshlwapi -luser32 -lversion")

    target_compile_options(Gui PUBLIC /std:c++20)
else()

    EXECUTE_PROCESS(COMMAND pkg-config --cflags gtk+-3.0 webkit2gtk-4.0
        TIMEOUT 5
        OUTPUT_VARIABLE WEB_FLAGS
        OUTPUT_STRIP_TRAILING_WHITESPACE
    )

    EXECUTE_PROCESS(COMMAND pkg-config --libs gtk+-3.0 webkit2gtk-4.0
        TIMEOUT 5
        OUTPUT_VARIABLE WEB_LIBS
        OUTPUT_STRIP_TRAILING_WHITESPACE
    )

    if(CMAKE_BUILD_TYPE STREQUAL "Release") 
        target_compile_options(Gui PUBLIC -Wall -Wextra -Wpedantic -Wunused -Wconversion -O3 -std=c++20)
        target_link_options(Gui PUBLIC -fuse-ld=lld)
    else()
        target_compile_options(Gui PUBLIC -g -fsanitize=address -Wall -Wextra -Wpedantic -Wunused -Wconversion -O3 -std=c++20)
        target_link_options(Gui PUBLIC -fuse-ld=lld -fsanitize=address)
    endif()

    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${WEB_FLAGS}")
    target_link_libraries(Gui ${WEB_LIBS})
endif()

