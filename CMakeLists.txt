cmake_minimum_required(VERSION 3.16)
project(OpenGLProject CXX C)

# Set C++ Standard
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Generate compile_commands.json for clangd/Zed LSP support
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Find required packages
find_package(OpenGL REQUIRED)
find_package(glfw3 REQUIRED)
find_package(Threads REQUIRED)

# 1. Collect all header files in include/ to extract their parent directories
file(GLOB_RECURSE ALL_INCLUDE_FILES
    CONFIGURE_DEPENDS
    "${CMAKE_CURRENT_SOURCE_DIR}/include/*.h"
    "${CMAKE_CURRENT_SOURCE_DIR}/include/*.hpp"
)

# 2. Extract unique directories from the found headers
set(INCLUDE_DIRS "${CMAKE_CURRENT_SOURCE_DIR}/include")
foreach(HEADER_FILE ${ALL_INCLUDE_FILES})
    get_filename_component(DIR_PATH ${HEADER_FILE} DIRECTORY)
    list(APPEND INCLUDE_DIRS ${DIR_PATH})
endforeach()
list(REMOVE_DUPLICATES INCLUDE_DIRS)

# 3. Collect project source files
file(GLOB_RECURSE SOURCES
    CONFIGURE_DEPENDS
    "src/*.cpp"
    "src/*.c"
    "include/*.c"
    "include/*.cpp"
)

# Exclude tools, c_api, and all backend implementations from the globbed list
list(FILTER SOURCES EXCLUDE REGEX ".*/(tools|c_api|backend)/.*")

# Explicitly re-add only the miniaudio backend file
file(GLOB_RECURSE MINIAUDIO_SRC
    CONFIGURE_DEPENDS
   "${CMAKE_CURRENT_SOURCE_DIR}/include/*soloud_miniaudio.cpp"
   "${CMAKE_CURRENT_SOURCE_DIR}/src/*soloud_miniaudio.cpp"
)
list(APPEND SOURCES ${MINIAUDIO_SRC})
list(REMOVE_DUPLICATES SOURCES)

# Define target executable
add_executable(main ${SOURCES})

# Compile definitions for SoLoud backend
target_compile_definitions(main PRIVATE WITH_MINIAUDIO)

# Add all collected include subdirectories to the target
target_include_directories(main PRIVATE ${INCLUDE_DIRS})

# Automatically copy the 'res' directory to the build folder
add_custom_command(
    TARGET main POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
            ${CMAKE_CURRENT_SOURCE_DIR}/res
            ${CMAKE_CURRENT_BINARY_DIR}/res
    COMMENT "Copying resource files to binary directory..."
)

# Link libraries to main executable
target_link_libraries(main PRIVATE
    glfw
    OpenGL::GL
    ${CMAKE_DL_LIBS}
    Threads::Threads
    m
)
