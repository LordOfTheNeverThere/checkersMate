
add_executable(checkersMateTests
Board.cpp
        Horse.cpp
        Piece.cpp
        Coordinates.cpp
        Pawn.cpp
        Tower.cpp
        Bishop.cpp
        Queen.cpp
)

target_link_libraries(checkersMateTests
        PRIVATE
        checkersMateLib
        socks
        GTest::gtest_main
)

target_compile_definitions(checkersMateTests PRIVATE
        SOCKS_RESOURCES="${socks_BINARY_DIR}/resources/"
)

include(GoogleTest)
gtest_discover_tests(checkersMateTests)