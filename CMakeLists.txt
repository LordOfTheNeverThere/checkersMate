cmake_minimum_required(VERSION 3.28)
project(checkersMate VERSION 1.0.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)


# --- FETCH DEPENDENCIES ---

include(FetchContent)
# Fetch socks library
FetchContent_Declare(
        socks
        GIT_REPOSITORY https://github.com/LordOfTheNeverThere/socks.git
        GIT_TAG        master
)
FetchContent_MakeAvailable(socks)

# Fetch GoogleTest
FetchContent_Declare(
        googletest
        URL https://github.com/google/googletest/archive/refs/heads/main.zip
)
FetchContent_MakeAvailable(googletest)

add_library(checkersMateLib STATIC
        include/checkersMate/Board.h
        src/Board.cpp
)

# Link against the fetched socks library
target_link_libraries(checkersMateLib PUBLIC socks)

target_include_directories(checkersMateLib
        PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
        $<INSTALL_INTERFACE:include>
        $<BUILD_INTERFACE:${socks_BINARY_DIR}/generated>
        PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/src  # Allows /src/*.cpp files to find local headers easily
)

# Main Application Executable
add_executable(checkersMate src/main.cpp)
target_link_libraries(checkersMate PUBLIC checkersMateLib)

# --- INSTALLATION LOGIC ---

# Install the app binary
install(TARGETS checkersMate RUNTIME DESTINATION bin)

# GTEST
enable_testing()
add_subdirectory(tests)
