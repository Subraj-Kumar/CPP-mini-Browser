cmake_minimum_required(VERSION 3.16)
project(cpp_mini_browser)

# --- 1. C++ Standard ---
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# --- 2. Find SFML ---
# This looks for the graphics, window, and system modules in MSYS2
find_package(SFML 2.5 COMPONENTS graphics window system REQUIRED)

# --- 3. Executable & Source Files ---
# List every .cpp file we created across all days
add_executable(browser
    src/main.cpp
    src/file_loader/FileLoader.cpp
    src/tokenizer/Tokenizer.cpp
    src/dom/DOMBuilder.cpp
    src/renderer/Renderer.cpp
)

# --- 4. Include Directories ---
# This allows us to use #include "dom/Node.hpp" without long relative paths
target_include_directories(browser PRIVATE include)

# --- 5. Link Libraries ---
target_link_libraries(browser sfml-graphics sfml-window sfml-system)

# --- 6. Asset Automation (CRITICAL) ---
# This command copies your 'assets' folder into the 'build' folder 
# every time you compile, so the relative paths always work.
add_custom_command(TARGET browser POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
    "${CMAKE_SOURCE_DIR}/assets"
    "$<TARGET_FILE_DIR:browser>/assets"
)

# --- 7. Windows Specific DLL Copy ---
# In MSYS2/MinGW, this helps copy necessary SFML DLLs to the build folder
if(WIN32)
    add_custom_command(TARGET browser POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_directory
        "${SFML_DIR}/../../../bin"
        "$<TARGET_FILE_DIR:browser>"
    )
endif()