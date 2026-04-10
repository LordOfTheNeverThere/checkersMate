#include "checkersMate/pieces/Pawn.h"

#include <gtest/gtest.h>

#include "checkersMate/Board.h"
#include "checkersMate/pieces/Bishop.h"

TEST(MethodChecking, possibleMovesWhite) {
    Board theBoard {};

    // normal first time moving
    Pawn* pawn {dynamic_cast<Pawn*>(theBoard.piecePtrAtCoordinates(Coordinates(3,1)))};
    EXPECT_TRUE(pawn); // Conversion to Pawn should be successful, since that Piece is in fact of the Pawn Subclass so the dynamic cast ought to work
    Piece* lastPieceMoved {theBoard.piecePtrAtCoordinates(Coordinates(3,6))};
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
    moves = pawn->possibleMoves(blackPawn);
    EXPECT_EQ(moves.size(), 2);
    EXPECT_EQ(moves.at(0), Coordinates(3,2));
    EXPECT_EQ(moves.at(1), Coordinates(2,2));

    // Normal Capture right
    blackPawn->setCoordinates(Coordinates(4, 2));
    moves = pawn->possibleMoves(blackPawn);
    EXPECT_EQ(moves.size(), 2);
    EXPECT_EQ(moves.at(0), Coordinates(3,2));
    EXPECT_EQ(moves.at(1), Coordinates(4,2));

    //Blocking movement
    blackPawn->setCoordinates(Coordinates(3, 2));
    moves = pawn->possibleMoves(blackPawn);
    EXPECT_EQ(moves.size(), 0);
}

TEST(MethodChecking, possibleMovesWhiteEnPassant) {
    Board theBoard {};
    // En passant left
    Pawn* pawn {dynamic_cast<Pawn*>(theBoard.piecePtrAtCoordinates(Coordinates(3,1)))};
    EXPECT_TRUE(pawn); // Conversion to Pawn should be successful, since that Piece is in fact of the Pawn Subclass so the dynamic cast ought to work
    Pawn* fleeingPawn {dynamic_cast<Pawn*>(theBoard.piecePtrAtCoordinates(Coordinates(2,6)))};
    pawn->setCoordinates(Coordinates(3,4));
    fleeingPawn->setCoordinates(Coordinates(2,4));
    auto moves = pawn->possibleMoves(fleeingPawn);
     EXPECT_EQ(moves.size(), 2);
     EXPECT_EQ(moves.at(0), Coordinates(3,5));
     EXPECT_EQ(moves.at(1), Coordinates(2,5));

    // En Passant Right
    Pawn* anotherFleeingPawn {dynamic_cast<Pawn*>(theBoard.piecePtrAtCoordinates(Coordinates(4,6)))};
    anotherFleeingPawn->setCoordinates(4,4);
    moves = pawn->possibleMoves(anotherFleeingPawn);
    EXPECT_EQ(moves.size(), 2);
    EXPECT_EQ(moves.at(0), Coordinates(3,5));
    EXPECT_EQ(moves.at(1), Coordinates(4,5));

    // Fail, not double move forward
    fleeingPawn->setCoordinates(Coordinates(2,4));// Increments counter
    moves = pawn->possibleMoves(fleeingPawn);
    EXPECT_EQ(moves.size(), 1);
    EXPECT_EQ(moves.at(0), Coordinates(3,5));
    anotherFleeingPawn->setCoordinates(4,4);
    moves = pawn->possibleMoves(anotherFleeingPawn);
    EXPECT_EQ(moves.size(), 1);
    EXPECT_EQ(moves.at(0), Coordinates(3,5));
}

TEST(MethodChecking, possibleMovesWhiteEnPassantWrongRow) {

    Board theBoard {};
    Pawn* pawn {dynamic_cast<Pawn*>(theBoard.piecePtrAtCoordinates(Coordinates(3,1)))};
    EXPECT_TRUE(pawn); // Conversion to Pawn should be successful, since that Piece is in fact of the Pawn Subclass so the dynamic cast ought to work
    Pawn* fleeingPawn {dynamic_cast<Pawn*>(theBoard.piecePtrAtCoordinates(Coordinates(2,6)))};
    pawn->setCoordinates(Coordinates(3,5));
    fleeingPawn->setCoordinates(Coordinates(2,5));
    auto moves = pawn->possibleMoves(fleeingPawn);
    EXPECT_EQ(moves.size(), 1);
    EXPECT_EQ(moves.at(0), Coordinates(4,6));
    Pawn* anotherFleeingPawn {dynamic_cast<Pawn*>(theBoard.piecePtrAtCoordinates(Coordinates(4,6)))};
    anotherFleeingPawn->setCoordinates(4,5);
    moves = pawn->possibleMoves(anotherFleeingPawn);
    EXPECT_EQ(moves.size(), 0);
}

TEST(MethodChecking, possibleMovesWhiteEnPassantWrongPiece) {

    Board theBoard {};
    Pawn* pawn {dynamic_cast<Pawn*>(theBoard.piecePtrAtCoordinates(Coordinates(3,1)))};
    EXPECT_TRUE(pawn); // Conversion to Pawn should be successful, since that Piece is in fact of the Pawn Subclass so the dynamic cast ought to work
    Bishop* aBishop {dynamic_cast<Bishop*>(theBoard.piecePtrAtCoordinates(Coordinates(2,7)))};
    pawn->setCoordinates(Coordinates(3,4));
    aBishop->setCoordinates(Coordinates(2,4));
    auto moves = pawn->possibleMoves(aBishop);
    EXPECT_EQ(moves.size(), 1);
    EXPECT_EQ(moves.at(0), Coordinates(3,5));
    Bishop* anotherBishop {dynamic_cast<Bishop*>(theBoard.piecePtrAtCoordinates(Coordinates(5,7)))};
    anotherBishop->setCoordinates(4,4);
    moves = pawn->possibleMoves(anotherBishop);
    EXPECT_EQ(moves.size(), 1);
    EXPECT_EQ(moves.at(0), Coordinates(3,5));
}

TEST(MethodChecking, possibleMovesWhiteEnPassantWrongColour) {

    Board theBoard {};
    Pawn* pawn {dynamic_cast<Pawn*>(theBoard.piecePtrAtCoordinates(Coordinates(3,1)))};
    EXPECT_TRUE(pawn); // Conversion to Pawn should be successful, since that Piece is in fact of the Pawn Subclass so the dynamic cast ought to work
    Pawn* friendlyPawn {dynamic_cast<Pawn*>(theBoard.piecePtrAtCoordinates(Coordinates(2,1)))};
    pawn->setCoordinates(Coordinates(3,4));
    friendlyPawn->setCoordinates(Coordinates(2,4));
    auto moves = pawn->possibleMoves(friendlyPawn);
    EXPECT_EQ(moves.size(), 1);
    EXPECT_EQ(moves.at(0), Coordinates(3,5));
    Pawn* anotherFriendlyPawn {dynamic_cast<Pawn*>(theBoard.piecePtrAtCoordinates(Coordinates(4,1)))};
    anotherFriendlyPawn->setCoordinates(4,4);
    moves = pawn->possibleMoves(anotherFriendlyPawn);
    EXPECT_EQ(moves.size(), 1);
    EXPECT_EQ(moves.at(0), Coordinates(3,5));
}


TEST(MethodChecking, possibleMovesBlack) {
    Board theBoard {};

    // normal first time moving
    Pawn* pawn {dynamic_cast<Pawn*>(theBoard.piecePtrAtCoordinates(Coordinates(3,6)))};
    EXPECT_TRUE(pawn); // Conversion to Pawn should be successful, since that Piece is in fact of the Pawn Subclass so the dynamic cast ought to work
    Piece* lastPieceMoved {theBoard.piecePtrAtCoordinates(Coordinates(3,1))};
    auto moves = pawn->possibleMoves(lastPieceMoved);
    EXPECT_EQ(moves.at(0), Coordinates(3,5));
    EXPECT_EQ(moves.at(1),  Coordinates(3,4));

    // normal after second time moving
    pawn->m_NumOfMoves = 1;
    moves = pawn->possibleMoves(lastPieceMoved);
    EXPECT_EQ(moves.size(), 1);
    EXPECT_EQ(moves.at(0), Coordinates(3,5));

    // Normal Capture left
    Pawn* whitePawn {dynamic_cast<Pawn*>(theBoard.piecePtrAtCoordinates(Coordinates(2,1)))};
    whitePawn->setCoordinates(Coordinates(2, 5));
    moves = pawn->possibleMoves(whitePawn);
    EXPECT_EQ(moves.size(), 2);
    EXPECT_EQ(moves.at(0), Coordinates(3,5));
    EXPECT_EQ(moves.at(1), Coordinates(2,5));

    // Normal Capture right
    whitePawn->setCoordinates(Coordinates(4, 5));
    moves = pawn->possibleMoves(whitePawn);
    EXPECT_EQ(moves.size(), 2);
    EXPECT_EQ(moves.at(0), Coordinates(3,5));
    EXPECT_EQ(moves.at(1), Coordinates(4,5));

    //Blocking movement
    whitePawn->setCoordinates(Coordinates(3, 5));
    moves = pawn->possibleMoves(whitePawn);
    EXPECT_EQ(moves.size(), 0);
}


TEST(MethodChecking, possibleMovesBlackEnPassant) {
    Board theBoard {};
    // En passant left
    Pawn* pawn {dynamic_cast<Pawn*>(theBoard.piecePtrAtCoordinates(Coordinates(3,6)))};
    EXPECT_TRUE(pawn); // Conversion to Pawn should be successful, since that Piece is in fact of the Pawn Subclass so the dynamic cast ought to work
    Pawn* fleeingPawn {dynamic_cast<Pawn*>(theBoard.piecePtrAtCoordinates(Coordinates(2,1)))};
    pawn->setCoordinates(Coordinates(3,3));
    fleeingPawn->setCoordinates(Coordinates(2,3));
    auto moves = pawn->possibleMoves(fleeingPawn);
    EXPECT_EQ(moves.size(), 2);
    EXPECT_EQ(moves.at(0), Coordinates(3,2));
    EXPECT_EQ(moves.at(1), Coordinates(2,2));

    // En Passant Right
    Pawn* anotherFleeingPawn {dynamic_cast<Pawn*>(theBoard.piecePtrAtCoordinates(Coordinates(4,1)))};
    anotherFleeingPawn->setCoordinates(4,3);
    moves = pawn->possibleMoves(anotherFleeingPawn);
    EXPECT_EQ(moves.size(), 2);
    EXPECT_EQ(moves.at(0), Coordinates(3,2));
    EXPECT_EQ(moves.at(1), Coordinates(4,2));

    // // Fail, not double move forward
    fleeingPawn->setCoordinates(Coordinates(2,3));// Increments counter
    moves = pawn->possibleMoves(fleeingPawn);
    EXPECT_EQ(moves.size(), 1);
    EXPECT_EQ(moves.at(0), Coordinates(3,2));
    anotherFleeingPawn->setCoordinates(4,3);
    moves = pawn->possibleMoves(anotherFleeingPawn);
    EXPECT_EQ(moves.size(), 1);
    EXPECT_EQ(moves.at(0), Coordinates(3,2));
}

TEST(MethodChecking, possibleMovesBlackEnPassantWrongRow) {

    Board theBoard {};
    Pawn* pawn {dynamic_cast<Pawn*>(theBoard.piecePtrAtCoordinates(Coordinates(3,6)))};
    EXPECT_TRUE(pawn); // Conversion to Pawn should be successful, since that Piece is in fact of the Pawn Subclass so the dynamic cast ought to work
    Pawn* fleeingPawn {dynamic_cast<Pawn*>(theBoard.piecePtrAtCoordinates(Coordinates(2,1)))};
    pawn->setCoordinates(Coordinates(3,4));
    fleeingPawn->setCoordinates(Coordinates(2,4));
    auto moves = pawn->possibleMoves(fleeingPawn);
    EXPECT_EQ(moves.size(), 1);
    EXPECT_EQ(moves.at(0), Coordinates(3,3));
    Pawn* anotherFleeingPawn {dynamic_cast<Pawn*>(theBoard.piecePtrAtCoordinates(Coordinates(4,1)))};
    anotherFleeingPawn->setCoordinates(4,4);
    moves = pawn->possibleMoves(anotherFleeingPawn);
    EXPECT_EQ(moves.size(), 1);
    EXPECT_EQ(moves.at(0), Coordinates(3,3));
}

TEST(MethodChecking, possibleMovesBlackEnPassantWrongPiece) {

    Board theBoard {};
    Pawn* pawn {dynamic_cast<Pawn*>(theBoard.piecePtrAtCoordinates(Coordinates(3,6)))};
    EXPECT_TRUE(pawn); // Conversion to Pawn should be successful, since that Piece is in fact of the Pawn Subclass so the dynamic cast ought to work
    Bishop* aBishop {dynamic_cast<Bishop*>(theBoard.piecePtrAtCoordinates(Coordinates(2,0)))};
    pawn->setCoordinates(Coordinates(3,3));
    aBishop->setCoordinates(Coordinates(2,3));
    auto moves = pawn->possibleMoves(aBishop);
    EXPECT_EQ(moves.size(), 1);
    EXPECT_EQ(moves.at(0), Coordinates(3,2));
    Bishop* anotherBishop {dynamic_cast<Bishop*>(theBoard.piecePtrAtCoordinates(Coordinates(5,0)))};
    anotherBishop->setCoordinates(4,3);
    moves = pawn->possibleMoves(anotherBishop);
    EXPECT_EQ(moves.size(), 1);
    EXPECT_EQ(moves.at(0), Coordinates(3,2));
}

TEST(MethodChecking, possibleMovesBlackEnPassantWrongColour) {

    Board theBoard {};
    Pawn* pawn {dynamic_cast<Pawn*>(theBoard.piecePtrAtCoordinates(Coordinates(3,6)))};
    EXPECT_TRUE(pawn); // Conversion to Pawn should be successful, since that Piece is in fact of the Pawn Subclass so the dynamic cast ought to work
    Pawn* friendlyPawn {dynamic_cast<Pawn*>(theBoard.piecePtrAtCoordinates(Coordinates(2,6)))};
    pawn->setCoordinates(Coordinates(3,3));
    friendlyPawn->setCoordinates(Coordinates(2,3));
    auto moves = pawn->possibleMoves(friendlyPawn);
    EXPECT_EQ(moves.size(), 1);
    EXPECT_EQ(moves.at(0), Coordinates(3,2));
    Pawn* anotherFriendlyPawn {dynamic_cast<Pawn*>(theBoard.piecePtrAtCoordinates(Coordinates(4,6)))};
    anotherFriendlyPawn->setCoordinates(4,3);
    moves = pawn->possibleMoves(anotherFriendlyPawn);
    EXPECT_EQ(moves.size(), 1);
    EXPECT_EQ(moves.at(0), Coordinates(3,2));
}