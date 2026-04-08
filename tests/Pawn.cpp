#include "checkersMate/pieces/Pawn.h"

#include <gtest/gtest.h>

#include "checkersMate/Board.h"

TEST(MethodChecking, possibleMovesWhite) {
    Board theBoard {};

    // normal first time moving
    Pawn* pawn {dynamic_cast<Pawn*>(theBoard.piecePtrAtCoordinates(Coordinates(3,1)))};
    EXPECT_TRUE(pawn); // Conversion to Pawn should be successful, since that Piece is in fact of the Pawn Subclass so the dynamic cast ought to work
    Piece lastPieceMoved {theBoard.pieceAtCoordinates(Coordinates(3,6))};
    auto moves = pawn->possibleMoves(lastPieceMoved);
    EXPECT_EQ(moves.at(0), Coordinates(3,2));
    EXPECT_EQ(moves.at(1), Coordinates(3,3));

    // normal after second time moving
    pawn->m_NumOfMoves = 1;
    moves = pawn->possibleMoves(lastPieceMoved);
    EXPECT_EQ(moves.size(), 1);
    EXPECT_EQ(moves.at(0), Coordinates(3,2));


    // Normal Capture left
    Pawn* blackPawn {dynamic_cast<Pawn*>(theBoard.piecePtrAtCoordinates(Coordinates(2,6)))};
    blackPawn->setCoordinates(Coordinates(2, 2));
    moves = pawn->possibleMoves(*blackPawn);
    EXPECT_EQ(moves.size(), 2);
    EXPECT_EQ(moves.at(0), Coordinates(3,2));
    EXPECT_EQ(moves.at(1), Coordinates(2,2));

    //Blocking movement
    blackPawn->setCoordinates(Coordinates(3, 2));
    moves = pawn->possibleMoves(*blackPawn);
    EXPECT_EQ(moves.size(), 0);

    //TODO : Normal capture right
    // En passant left
    // En passant right
    // En passant left (failed due to not being in the correct row)
    // En passant right (failed due to not being in the correct row)
    // En passant left (failed due to not being the correct piece)
    // En passant right (failed due to not being the correct piece)
    // En passant left (failed due to not being the correct colour)
    // En passant right (failed due to not being the correct colour)

}

TEST(MethodChecking, possibleMovesBlack) {
    Board theBoard {};

    // normal first time moving
    Pawn* pawn {dynamic_cast<Pawn*>(theBoard.piecePtrAtCoordinates(Coordinates(3,6)))};
    EXPECT_TRUE(pawn); // Conversion to Pawn should be successful, since that Piece is in fact of the Pawn Subclass so the dynamic cast ought to work
    Piece lastPieceMoved {theBoard.pieceAtCoordinates(Coordinates(3,1))};
    auto moves = pawn->possibleMoves(lastPieceMoved);
    EXPECT_EQ(moves.at(0), Coordinates(3,5));
    EXPECT_EQ(moves.at(1),  Coordinates(3,4));

    // normal after second time moving
    pawn->m_NumOfMoves = 1;
    moves = pawn->possibleMoves(lastPieceMoved);
    EXPECT_EQ(moves.size(), 1);
    EXPECT_EQ(moves.at(0), Coordinates(3,5));
}