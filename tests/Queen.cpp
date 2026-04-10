#include "checkersMate/pieces/Queen.h"

#include <gtest/gtest.h>

#include "checkersMate/Board.h"
#include "checkersMate/pieces/Pawn.h"

TEST(MethodChecking, possibleMovesDifferentColourQueen) {

    Board theBoard {};
    Queen* whiteQueen {dynamic_cast<Queen *>(theBoard.piecePtrAtCoordinates(Coordinates (3, 0)))};

    Pawn* blackPawn1 {dynamic_cast<Pawn*>(theBoard.piecePtrAtCoordinates(Coordinates(0,6)))};
    Pawn* blackPawn2 {dynamic_cast<Pawn*>(theBoard.piecePtrAtCoordinates(Coordinates(1,6)))};
    Pawn* blackPawn3 {dynamic_cast<Pawn*>(theBoard.piecePtrAtCoordinates(Coordinates(2,6)))};
    Pawn* blackPawn4 {dynamic_cast<Pawn*>(theBoard.piecePtrAtCoordinates(Coordinates(3,6)))};
    Pawn* blackPawn5 {dynamic_cast<Pawn*>(theBoard.piecePtrAtCoordinates(Coordinates(4,6)))};
    Pawn* blackPawn6 {dynamic_cast<Pawn*>(theBoard.piecePtrAtCoordinates(Coordinates(5,6)))};
    Pawn* blackPawn7 {dynamic_cast<Pawn*>(theBoard.piecePtrAtCoordinates(Coordinates(6,6)))};
    Pawn* blackPawn8 {dynamic_cast<Pawn*>(theBoard.piecePtrAtCoordinates(Coordinates(7,6)))};

    std::set<Piece*> piecesToKeep {whiteQueen, blackPawn1, blackPawn2, blackPawn3, blackPawn4, blackPawn5, blackPawn6, blackPawn7, blackPawn8};
    theBoard.emptyTheBoard(piecesToKeep);

    Coordinates central  (4,4);
    whiteQueen->setCoordinates(central);
    std::set<Coordinates> expectedMoves {};


    for (int i = 1; i < 8; ++i) {
        // Horizontal and Vertical

        if (central.getX() + i < 8) {
            Coordinates expectedMove {central.getX() + i, central.getY()};
            expectedMoves.insert(expectedMove);
            blackPawn1->setCoordinates(expectedMove);
        }
        if (central.getX() - i >= 0) {
            Coordinates expectedMove {central.getX() - i, central.getY()};
            expectedMoves.insert(expectedMove);
            blackPawn2->setCoordinates(expectedMove);
        }
        if (central.getY() + i < 8) {
            Coordinates expectedMove {central.getX(), central.getY() + i};
            expectedMoves.insert(expectedMove);
            blackPawn3->setCoordinates(expectedMove);
        }
        if (central.getY() - i >= 0) {
            Coordinates expectedMove {central.getX(), central.getY() - i};
            expectedMoves.insert(expectedMove);
            blackPawn4->setCoordinates(expectedMove);
        }
        // Diagonally

        if (central.getX() - i >= 0 && central.getY() + i < 8) {
            Coordinates expectedMove {central.getX() - i, central.getY() + i};
            expectedMoves.insert(expectedMove);
            blackPawn5->setCoordinates(expectedMove);
        }
        if (central.getX() + i < 8 && central.getY() + i < 8) {
            Coordinates expectedMove {central.getX() + i, central.getY() + i};
            expectedMoves.insert(expectedMove);
            blackPawn6->setCoordinates(expectedMove);
        }
        if (central.getX() + i < 8 && central.getY() - i >= 0) {
            Coordinates expectedMove {central.getX() + i, central.getY() - i};
            expectedMoves.insert(expectedMove);
            blackPawn7->setCoordinates(expectedMove);
        }
        if (central.getX() - i >= 0 && central.getY() - i >= 0) {
            Coordinates expectedMove {central.getX() - i, central.getY() - i};
            expectedMoves.insert(expectedMove);
            blackPawn8->setCoordinates(expectedMove);
        }

        auto moves = whiteQueen->possibleMoves();
        for (auto move: moves) {
            EXPECT_TRUE(expectedMoves.find(move) != expectedMoves.end());
        }
        EXPECT_EQ(expectedMoves.size(), moves.size());
        //std::cout << "The i is " << i << " and the number of times the pawns have moved is " << expectedMoves.size() << " and the number of legal tower moves is " << moves.size() << '\n';

    }
}

TEST(MethodChecking, possibleMovesSameColourQueen) {

    Board theBoard {};
    Queen* blackQueen {dynamic_cast<Queen *>(theBoard.piecePtrAtCoordinates(Coordinates (3, 7)))};

    Pawn* blackPawn1 {dynamic_cast<Pawn*>(theBoard.piecePtrAtCoordinates(Coordinates(0,6)))};
    Pawn* blackPawn2 {dynamic_cast<Pawn*>(theBoard.piecePtrAtCoordinates(Coordinates(1,6)))};
    Pawn* blackPawn3 {dynamic_cast<Pawn*>(theBoard.piecePtrAtCoordinates(Coordinates(2,6)))};
    Pawn* blackPawn4 {dynamic_cast<Pawn*>(theBoard.piecePtrAtCoordinates(Coordinates(3,6)))};
    Pawn* blackPawn5 {dynamic_cast<Pawn*>(theBoard.piecePtrAtCoordinates(Coordinates(4,6)))};
    Pawn* blackPawn6 {dynamic_cast<Pawn*>(theBoard.piecePtrAtCoordinates(Coordinates(5,6)))};
    Pawn* blackPawn7 {dynamic_cast<Pawn*>(theBoard.piecePtrAtCoordinates(Coordinates(6,6)))};
    Pawn* blackPawn8 {dynamic_cast<Pawn*>(theBoard.piecePtrAtCoordinates(Coordinates(7,6)))};

    std::set<Piece*> piecesToKeep {blackQueen, blackPawn1, blackPawn2, blackPawn3, blackPawn4, blackPawn5, blackPawn6, blackPawn7, blackPawn8};
    theBoard.emptyTheBoard(piecesToKeep);

    Coordinates central  (4,4);
    blackQueen->setCoordinates(central);
    std::set<Coordinates> expectedMoves {};


    for (int i = 2; i < 8; ++i) {
        // Horizontal and Vertical

        if (central.getX() + i < 8) {
            Coordinates friendlyPieceCoord {central.getX() + i, central.getY()};
            Coordinates expectedMove {central.getX() + i -1, central.getY()};
            expectedMoves.insert(expectedMove);
            blackPawn1->setCoordinates(friendlyPieceCoord);
        }
        if (central.getX() - i >= 0) {
            Coordinates friendlyPieceCoord {central.getX() - i, central.getY()};
            Coordinates expectedMove {central.getX() - i + 1, central.getY()};
            expectedMoves.insert(expectedMove);
            blackPawn2->setCoordinates(friendlyPieceCoord);
        }
        if (central.getY() + i < 8) {
            Coordinates friendlyPieceCoord {central.getX(), central.getY() + i};
            Coordinates expectedMove {central.getX(), central.getY() + i - 1};
            expectedMoves.insert(expectedMove);
            blackPawn3->setCoordinates(friendlyPieceCoord);
        }
        if (central.getY() - i >= 0) {
            Coordinates friendlyPieceCoord {central.getX(), central.getY() - i};
            Coordinates expectedMove {central.getX(), central.getY() - i + 1};
            expectedMoves.insert(expectedMove);
            blackPawn4->setCoordinates(friendlyPieceCoord);
        }
        // Diagonally

        if (central.getX() - i >= 0 && central.getY() + i < 8) {
            Coordinates friendlyPieceCoord {central.getX() - i, central.getY() + i};
            Coordinates expectedMove {central.getX() - i + 1, central.getY() + i - 1};
            expectedMoves.insert(expectedMove);
            blackPawn5->setCoordinates(friendlyPieceCoord);
        }
        if (central.getX() + i < 8 && central.getY() + i < 8) {
            Coordinates friendlyPieceCoord {central.getX() + i, central.getY() + i};
            Coordinates expectedMove {central.getX() + i - 1, central.getY() + i - 1};
            expectedMoves.insert(expectedMove);
            blackPawn6->setCoordinates(friendlyPieceCoord);
        }
        if (central.getX() + i < 8 && central.getY() - i >= 0) {
            Coordinates friendlyPieceCoord {central.getX() + i, central.getY() - i};
            Coordinates expectedMove {central.getX() + i - 1, central.getY() - i + 1};
            expectedMoves.insert(expectedMove);
            blackPawn7->setCoordinates(friendlyPieceCoord);
        }
        if (central.getX() - i >= 0 && central.getY() - i >= 0) {
            Coordinates friendlyPieceCoord {central.getX() - i, central.getY() - i};
            Coordinates expectedMove {central.getX() - i + 1, central.getY() - i + 1};
            expectedMoves.insert(expectedMove);
            blackPawn8->setCoordinates(friendlyPieceCoord);
        }

        auto moves = blackQueen->possibleMoves();
        for (auto move: moves) {
            EXPECT_TRUE(expectedMoves.find(move) != expectedMoves.end());
        }
        EXPECT_EQ(expectedMoves.size(), moves.size());
        //std::cout << "The i is " << i << " and the number of times the pawns have moved is " << expectedMoves.size() << " and the number of legal tower moves is " << moves.size() << '\n';

    }
}
