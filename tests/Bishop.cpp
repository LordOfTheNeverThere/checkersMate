#include "checkersMate/pieces/Bishop.h"

#include <gtest/gtest.h>

#include "checkersMate/Board.h"
#include "checkersMate/pieces/Pawn.h"

TEST(MethodChecking, possibleMovesDifferentColourBishop) {
    Board theBoard {};
    Bishop* whiteBishop {dynamic_cast<Bishop*>(theBoard.piecePtrAtCoordinates(Coordinates(2,0)))};
    Pawn* blackPawn1 {dynamic_cast<Pawn*>(theBoard.piecePtrAtCoordinates(Coordinates(0,6)))};
    Pawn* blackPawn2 {dynamic_cast<Pawn*>(theBoard.piecePtrAtCoordinates(Coordinates(1,6)))};
    Pawn* blackPawn3 {dynamic_cast<Pawn*>(theBoard.piecePtrAtCoordinates(Coordinates(2,6)))};
    Pawn* blackPawn4 {dynamic_cast<Pawn*>(theBoard.piecePtrAtCoordinates(Coordinates(3,6)))};

    std::set<Piece*> piecesToKeep {whiteBishop, blackPawn1, blackPawn2, blackPawn3, blackPawn4};
    theBoard.emptyTheBoard(piecesToKeep);

    Coordinates central  (4,4);
    whiteBishop->setCoordinates(central);
    std::set<Coordinates> expectedMoves {};

    for (int i = 1; i < 8; ++i) {
        if (central.getX() - i >= 0 && central.getY() + i < 8) {
            Coordinates expectedMove {central.getX() - i, central.getY() + i};
            expectedMoves.insert(expectedMove);
            blackPawn1->setCoordinates(expectedMove);
        }
        if (central.getX() + i < 8 && central.getY() + i < 8) {
            Coordinates expectedMove {central.getX() + i, central.getY() + i};
            expectedMoves.insert(expectedMove);
            blackPawn2->setCoordinates(expectedMove);
        }
        if (central.getX() + i < 8 && central.getY() - i >= 0) {
            Coordinates expectedMove {central.getX() + i, central.getY() - i};
            expectedMoves.insert(expectedMove);
            blackPawn3->setCoordinates(expectedMove);
        }
        if (central.getX() - i >= 0 && central.getY() - i >= 0) {
            Coordinates expectedMove {central.getX() - i, central.getY() - i};
            expectedMoves.insert(expectedMove);
            blackPawn4->setCoordinates(expectedMove);
        }
        auto moves = whiteBishop->possibleMoves();
        for (auto move: moves) {
            EXPECT_TRUE(expectedMoves.find(move) != expectedMoves.end());
        }
        //std::cout << "The i is " << i << " and the number of times the pawns have moved is " << expectedMoves.size() << " and the number of legal tower moves is " << moves.size() << '\n';
    }
}

TEST(MethodChecking, possibleMovesSameColourBishop) {
    Board theBoard {};
    Bishop* blackBishop {dynamic_cast<Bishop*>(theBoard.piecePtrAtCoordinates(Coordinates(2,7)))};
    Pawn* blackPawn1 {dynamic_cast<Pawn*>(theBoard.piecePtrAtCoordinates(Coordinates(0,6)))};
    Pawn* blackPawn2 {dynamic_cast<Pawn*>(theBoard.piecePtrAtCoordinates(Coordinates(1,6)))};
    Pawn* blackPawn3 {dynamic_cast<Pawn*>(theBoard.piecePtrAtCoordinates(Coordinates(2,6)))};
    Pawn* blackPawn4 {dynamic_cast<Pawn*>(theBoard.piecePtrAtCoordinates(Coordinates(3,6)))};

    std::set<Piece*> piecesToKeep {blackBishop, blackPawn1, blackPawn2, blackPawn3, blackPawn4};
    theBoard.emptyTheBoard(piecesToKeep);

    Coordinates central  (4,4);
    blackBishop->setCoordinates(central);
    std::set<Coordinates> expectedMoves {};

    for (int i = 2; i < 8; ++i) {
        if (central.getX() - i >= 0 && central.getY() + i < 8) {
            Coordinates friendlyPieceCoord {central.getX() - i, central.getY() + i};
            Coordinates expectedMove {central.getX() - i + 1, central.getY() + i - 1};
            expectedMoves.insert(expectedMove);
            blackPawn1->setCoordinates(friendlyPieceCoord);
        }
        if (central.getX() + i < 8 && central.getY() + i < 8) {
            Coordinates friendlyPieceCoord {central.getX() + i, central.getY() + i};
            Coordinates expectedMove {central.getX() + i - 1, central.getY() + i - 1};
            expectedMoves.insert(expectedMove);
            blackPawn2->setCoordinates(friendlyPieceCoord);
        }
        if (central.getX() + i < 8 && central.getY() - i >= 0) {
            Coordinates friendlyPieceCoord {central.getX() + i, central.getY() - i};
            Coordinates expectedMove {central.getX() + i - 1, central.getY() - i + 1};
            expectedMoves.insert(expectedMove);
            blackPawn3->setCoordinates(friendlyPieceCoord);
        }
        if (central.getX() - i >= 0 && central.getY() - i >= 0) {
            Coordinates friendlyPieceCoord {central.getX() - i, central.getY() - i};
            Coordinates expectedMove {central.getX() - i + 1, central.getY() - i + 1};
            expectedMoves.insert(expectedMove);
            blackPawn4->setCoordinates(friendlyPieceCoord);
        }
        auto moves = blackBishop->possibleMoves();
        for (auto move: moves) {
            EXPECT_TRUE(expectedMoves.find(move) != expectedMoves.end());
        }
        //std::cout << "The i is " << i << " and the number of times the pawns have moved is " << expectedMoves.size() << " and the number of legal tower moves is " << moves.size() << '\n';
    }
}