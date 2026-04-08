#include "checkersMate/pieces/Piece.h"

#include <gtest/gtest.h>

#include "checkersMate/Board.h"


TEST(MethodChecking, emptyConstructor) {
    Piece somePiece {};
    EXPECT_EQ(somePiece.getCoordinates(), Coordinates(0,0));
    EXPECT_EQ(somePiece.getCurrentBoard(), nullptr);
    EXPECT_EQ(somePiece.getColour(), PieceColour::empty);
    EXPECT_EQ(somePiece.getType(), PieceType::empty);
    EXPECT_EQ(somePiece.m_NumOfMoves, 0);
}

TEST(MethodChecking, equalOperator) {
    Piece somePiece {};
    Piece someOtherPiece {};
    EXPECT_EQ(someOtherPiece, somePiece);
    someOtherPiece.setColour(PieceColour::white);
    EXPECT_NE(somePiece, someOtherPiece);
}

TEST(MethodChecking, isFriendlyFire) {
    Board theBoard {};
    Piece blackTower {theBoard.pieceAtCoordinates(Coordinates(7,7))};

    for (Int row = 6; row < 8; row++) {
        for (int col = 0; col < 8; col++) {
            EXPECT_TRUE(blackTower.isFriendlyFire(Coordinates(col, row)));
        }
    }

    for (Int row = 0; row < 2; row++) {
        for (int col = 0; col < 8; col++) {
            EXPECT_FALSE(blackTower.isFriendlyFire(Coordinates(col, row)));
        }
    }
}
