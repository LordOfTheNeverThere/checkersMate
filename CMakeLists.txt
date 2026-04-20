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
        include/checkersMate/pieces/Piece.h
        include/checkersMate/Exceptions.h
        include/checkersMate/Coordinates.h
        src/pieces/Piece.cpp
        include/checkersMate/pieces/Pawn.h
        include/checkersMate/pieces/Bishop.h
        include/checkersMate/pieces/Horse.h
        include/checkersMate/pieces/Tower.h
        include/checkersMate/pieces/Queen.h
        include/checkersMate/pieces/King.h
        include/checkersMate/pieces/PieceColour.h
        src/pieces/Pawn.cpp
        src/pieces/Bishop.cpp
        src/pieces/Tower.cpp
        src/pieces/Horse.cpp
        src/pieces/Queen.cpp
        src/pieces/King.cpp
        include/checkersMate/pieces/PieceType.h
        include/checkersMate/ChessTools.h
        src/Coordinates.cpp
        include/checkersMate/networking/HostEngine.h
        src/networking/HostEngine.cpp
        include/checkersMate/networking/GuestEngine.h
        include/checkersMate/networking/Engine.h
        src/networking/GuestEngine.cpp
        include/checkersMate/networking/ChessBoardHeader.h
        include/checkersMate/networking/ChessPieceHeader.h
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
