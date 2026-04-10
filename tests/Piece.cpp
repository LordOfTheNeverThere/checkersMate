#include "checkersMate/pieces/Piece.h"

#include <gtest/gtest.h>

#include "checkersMate/Board.h"


TEST(MethodChecking, emptyConstructor) {
    Piece* somePiece {};
    EXPECT_EQ(somePiece, nullptr);
}


TEST(MethodChecking, isFriendlyFire) {
    Board theBoard {};
    Piece* blackTower {theBoard.piecePtrAtCoordinates(Coordinates(7,7))};

    for (Int row = 6; row < 8; row++) {
        for (int col = 0; col < 8; col++) {
            EXPECT_TRUE(blackTower->isFriendlyFire(Coordinates(col, row)));
        }
    }

    for (Int row = 0; row < 2; row++) {
        for (int col = 0; col < 8; col++) {
            EXPECT_FALSE(blackTower->isFriendlyFire(Coordinates(col, row)));
        }
    }
}
