#include "checkersMate/pieces/Tower.h"

#include <gtest/gtest.h>

#include "checkersMate/Board.h"
#include "checkersMate/pieces/Pawn.h"

TEST(MethodChecking, possibleMovesDifferentColour) {
    Board theBoard {};
    Tower* whiteTower {dynamic_cast<Tower*>(theBoard.piecePtrAtCoordinates(Coordinates(0,0)))};
    Pawn* blackPawn1 {dynamic_cast<Pawn*>(theBoard.piecePtrAtCoordinates(Coordinates(0,6)))};
    Pawn* blackPawn2 {dynamic_cast<Pawn*>(theBoard.piecePtrAtCoordinates(Coordinates(1,6)))};
    Pawn* blackPawn3 {dynamic_cast<Pawn*>(theBoard.piecePtrAtCoordinates(Coordinates(2,6)))};
    Pawn* blackPawn4 {dynamic_cast<Pawn*>(theBoard.piecePtrAtCoordinates(Coordinates(3,6)))};

    std::set<Piece*> piecesToKeep {whiteTower, blackPawn1, blackPawn2, blackPawn3, blackPawn4};
    theBoard.emptyTheBoard(piecesToKeep);

    Coordinates centralTower  (3,3);
    whiteTower->setCoordinates(centralTower);
    std::set<Coordinates> expectedMoves {};
    for (int i = 1; i < 8; ++i) {
        if (centralTower.getX() + i < 8) {
            Coordinates expectedMove {centralTower.getX() + i, centralTower.getY()};
            expectedMoves.insert(expectedMove);
            blackPawn1->setCoordinates(expectedMove);
        }
        if (centralTower.getX() - i >= 0) {
            Coordinates expectedMove {centralTower.getX() - i, centralTower.getY()};
            expectedMoves.insert(expectedMove);
            blackPawn2->setCoordinates(expectedMove);
        }
        if (centralTower.getY() + i < 8) {
            Coordinates expectedMove {centralTower.getX(), centralTower.getY() + i};
            expectedMoves.insert(expectedMove);
            blackPawn3->setCoordinates(expectedMove);
        }
        if (centralTower.getY() - i >= 0) {
            Coordinates expectedMove {centralTower.getX(), centralTower.getY() - i};
            expectedMoves.insert(expectedMove);
            blackPawn4->setCoordinates(expectedMove);
        }
        auto moves = whiteTower->possibleMoves();
        for (auto move: moves) {
            EXPECT_TRUE(expectedMoves.find(move) != expectedMoves.end());
        }
        //std::cout << "The i is " << i << " and the number of times the pawns have moved is " << expectedMoves.size() << " and the number of legal tower moves is " << moves.size() << '\n';
    }
}

TEST(MethodChecking, possibleMovesSameColour) {
    Board theBoard {};
    Tower* blackTower {dynamic_cast<Tower*>(theBoard.piecePtrAtCoordinates(Coordinates(0,7)))};
    Pawn* blackPawn1 {dynamic_cast<Pawn*>(theBoard.piecePtrAtCoordinates(Coordinates(0,6)))};
    Pawn* blackPawn2 {dynamic_cast<Pawn*>(theBoard.piecePtrAtCoordinates(Coordinates(1,6)))};
    Pawn* blackPawn3 {dynamic_cast<Pawn*>(theBoard.piecePtrAtCoordinates(Coordinates(2,6)))};
    Pawn* blackPawn4 {dynamic_cast<Pawn*>(theBoard.piecePtrAtCoordinates(Coordinates(3,6)))};

    std::set<Piece*> piecesToKeep {blackTower, blackPawn1, blackPawn2, blackPawn3, blackPawn4};
    theBoard.emptyTheBoard(piecesToKeep);

    Coordinates centralTower  (3,3);
    blackTower->setCoordinates(centralTower);
    std::set<Coordinates> expectedMoves {};
    for (int i = 2; i < 8; ++i) {
        if (centralTower.getX() + i < 8) {
            Coordinates friendlyPieceCoord {centralTower.getX() + i, centralTower.getY()};
            Coordinates expectedMove {centralTower.getX() + i -1, centralTower.getY()};
            expectedMoves.insert(expectedMove);
            blackPawn1->setCoordinates(friendlyPieceCoord);
        }
        if (centralTower.getX() - i >= 0) {
            Coordinates friendlyPieceCoord {centralTower.getX() - i, centralTower.getY()};
            Coordinates expectedMove {centralTower.getX() - i + 1, centralTower.getY()};
            expectedMoves.insert(expectedMove);
            blackPawn2->setCoordinates(friendlyPieceCoord);
        }
        if (centralTower.getY() + i < 8) {
            Coordinates friendlyPieceCoord {centralTower.getX(), centralTower.getY() + i};
            Coordinates expectedMove {centralTower.getX(), centralTower.getY() + i - 1};
            expectedMoves.insert(expectedMove);
            blackPawn3->setCoordinates(friendlyPieceCoord);
        }
        if (centralTower.getY() - i >= 0) {
            Coordinates friendlyPieceCoord {centralTower.getX(), centralTower.getY() - i};
            Coordinates expectedMove {centralTower.getX(), centralTower.getY() - i + 1};
            expectedMoves.insert(expectedMove);
            blackPawn4->setCoordinates(friendlyPieceCoord);
        }
        auto moves = blackTower->possibleMoves();
        for (auto move: moves) {
            EXPECT_TRUE(expectedMoves.find(move) != expectedMoves.end());
        }
        //std::cout << "The i is " << i << " and the number of times the pawns have moved is " << expectedMoves.size() << " and the number of legal tower moves is " << moves.size() << '\n';
    }

}
