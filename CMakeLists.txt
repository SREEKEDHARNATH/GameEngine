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

# 1. Collect all files and subdirectories under include/ and src/ for flat includes
file(GLOB_RECURSE ALL_PROJECT_FILES
    CONFIGURE_DEPENDS
    "${CMAKE_CURRENT_SOURCE_DIR}/include/*"
    "${CMAKE_CURRENT_SOURCE_DIR}/src/*"
)

set(INCLUDE_DIRS
    "${CMAKE_CURRENT_SOURCE_DIR}/include"
    "${CMAKE_CURRENT_SOURCE_DIR}/src"
)

foreach(ITEM ${ALL_PROJECT_FILES})
    if(IS_DIRECTORY "${ITEM}")
        list(APPEND INCLUDE_DIRS "${ITEM}")
    else()
        get_filename_component(PARENT_DIR "${ITEM}" DIRECTORY)
        list(APPEND INCLUDE_DIRS "${PARENT_DIR}")
    endif()
endforeach()
list(REMOVE_DUPLICATES INCLUDE_DIRS)

# 2. Collect project source files
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
    ${CMAKE_CURRENT_SOURCE_DIR}/libs/libbox2d.a
    ${CMAKE_CURRENT_SOURCE_DIR}/libs/libimgui.a
    ${CMAKE_CURRENT_SOURCE_DIR}/libs/libsoloud.a

)
