cmake_minimum_required(VERSION 3.16)
project(cpp_mini_browser)

# Ensure we use modern C++
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# 1. Find the SFML library on your system (MSYS2)
find_package(SFML 2.5 COMPONENTS graphics window system REQUIRED)

# 2. Tell CMake where ALL your .cpp files are
# Note: As we add more files (Tokenizer, etc.), we will add them here.
add_executable(browser
    src/main.cpp
    src/file_loader/FileLoader.cpp
    src/tokenizer/Tokenizer.cpp
    src/dom/DOMBuilder.cpp
    src/renderer/Renderer.cpp
)

# 3. Tell CMake where your header (.hpp) files are located
# This allows you to write #include "file_loader/FileLoader.hpp" 
# instead of #include "../../include/file_loader/FileLoader.hpp"
target_include_directories(browser PRIVATE include)

# 4. Link the SFML libraries to your executable
target_link_libraries(browser sfml-graphics sfml-window sfml-system)

# 5. [Optional] Copy DLLs on Windows
# This is a 'pro' move. It helps find the .dll files automatically.
if(WIN32)
    add_custom_command(TARGET browser POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_directory
        "${SFML_DIR}/../../../bin"
        "$<TARGET_FILE_DIR:browser>"
    )
endif()