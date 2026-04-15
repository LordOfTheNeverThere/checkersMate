#include "checkersMate/pieces/King.h"
#include <gtest/gtest.h>

#include "checkersMate/Board.h"

TEST(MethodChecking, checkSafePossibleMovesStart) {
    Board theBoard {};
    King* theKing {dynamic_cast<King*>(theBoard.piecePtrAtCoordinates(4,0))};
    EXPECT_FALSE(theKing->validKingsideCastling());
    EXPECT_FALSE(theKing->validQueensideCastling());
    auto moves {theKing->possibleMoves()};
    EXPECT_EQ(moves.size(), 0);
}

TEST(MethodChecking, checkSafePossibleMovesCastling) {
    Board theBoard {};
    King* theKing {dynamic_cast<King*>(theBoard.piecePtrAtCoordinates(4,7))};
    Piece* queenTower {theBoard.piecePtrAtCoordinates(0,7)};
    Piece* kingTower {theBoard.piecePtrAtCoordinates(7,7)};
    theBoard.emptyTheBoard({theKing, queenTower,kingTower});
    EXPECT_TRUE(theKing->validKingsideCastling());
    EXPECT_TRUE(theKing->validQueensideCastling());
    auto moves {theKing->possibleMoves()};
    EXPECT_EQ(moves.size(), 7);
}

TEST(MethodChecking, legalQueenCastling) {
    Board theBoard {};
    King* theKing {dynamic_cast<King*>(theBoard.piecePtrAtCoordinates(4,7))};
    Piece* queen {theBoard.piecePtrAtCoordinates(3,7)};
    Piece* bishop {theBoard.piecePtrAtCoordinates(2,7)};
    Piece* horse {theBoard.piecePtrAtCoordinates(1,7)};

    queen->setCoordinates(3,5);
    bishop->setCoordinates(2,5);
    horse->setCoordinates(1,5);
    EXPECT_FALSE(theKing->validKingsideCastling());
    EXPECT_TRUE(theKing->validQueensideCastling());
    auto moves {theKing->possibleMoves()};
    EXPECT_EQ(moves.size(), 2);
}

TEST(MethodChecking, legalKingCastling) {
    Board theBoard {};
    King* theKing {dynamic_cast<King*>(theBoard.piecePtrAtCoordinates(4,7))};
    Piece* bishop {theBoard.piecePtrAtCoordinates(5,7)};
    Piece* horse {theBoard.piecePtrAtCoordinates(6,7)};

    bishop->setCoordinates(5,5);
    horse->setCoordinates(6,5);
    EXPECT_TRUE(theKing->validKingsideCastling());
    EXPECT_FALSE(theKing->validQueensideCastling());
    auto moves {theKing->possibleMoves()};
    EXPECT_EQ(moves.size(), 2);
}


TEST(MethodChecking, ilegalQueenCastling) {
    Board theBoard {};
    King* theKing {dynamic_cast<King*>(theBoard.piecePtrAtCoordinates(4,7))};
    Piece* queenTower {theBoard.piecePtrAtCoordinates(0,7)};
    Piece* kingTower {theBoard.piecePtrAtCoordinates(7,7)};
    Piece* enemyTower {theBoard.piecePtrAtCoordinates(0,0)};
    theBoard.emptyTheBoard({theKing, queenTower, kingTower, enemyTower});

    for (int i = 0; i < 4; ++i) {
        enemyTower->setCoordinates(theKing->getCoordinates().getX() - i, enemyTower->getCoordinates().getY());
        if (i!=0) EXPECT_TRUE(theKing->validKingsideCastling());
        if (i<=2) {
            EXPECT_FALSE(theKing->validQueensideCastling());
        } else {
            EXPECT_TRUE(theKing->validQueensideCastling());
        }
    }
}

TEST(MethodChecking, ilegalKingCastling) {
    Board theBoard {};
    King* theKing {dynamic_cast<King*>(theBoard.piecePtrAtCoordinates(4,7))};
    Piece* kingTower {theBoard.piecePtrAtCoordinates(7,7)};
    Piece* queenTower {theBoard.piecePtrAtCoordinates(0,7)};
    Piece* enemyTower {theBoard.piecePtrAtCoordinates(0,0)};
    theBoard.emptyTheBoard({theKing,kingTower,queenTower, enemyTower});

    for (int i = 0; i < 3; ++i) {
        enemyTower->setCoordinates(theKing->getCoordinates().getX() + i, enemyTower->getCoordinates().getY());
        if (i!=0) EXPECT_TRUE(theKing->validQueensideCastling());
        EXPECT_FALSE(theKing->validKingsideCastling());
    }
}
