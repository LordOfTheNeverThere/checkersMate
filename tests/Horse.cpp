#include "checkersMate/pieces/Horse.h"
#include "checkersMate/Board.h"
#include "gtest/gtest.h"

TEST(MethodChecking, possibleMovesStartingPosition) {
    Board theBoard {};
    std::set<Piece*> whiteHorsesSet {theBoard.generalFilter(PieceType::horse, PieceColour::white)};
    for (auto piece: whiteHorsesSet) {
        if (piece->getCoordinates().getX() == 1 && piece->getCoordinates().getY() == 0) {
            auto result = piece->possibleMoves();
            EXPECT_EQ(result.at(0), Coordinates(0,2));
            EXPECT_EQ(result.at(1), Coordinates(2,2));
        } else if (piece->getCoordinates().getX() == 6 && piece->getCoordinates().getY() == 0) {
            auto result = piece->possibleMoves();
            EXPECT_EQ(result.at(0), Coordinates(5,2));
            EXPECT_EQ(result.at(1), Coordinates(7,2));
        }
    }
}

TEST(MethodChecking, possibleMovesOnEnemyPieces) {

    Board theBoard {};
    std::set<Piece*> enemyPawns {theBoard.generalFilter(PieceType::pawn, PieceColour::black)};
    std::set<Piece*> whiteHorsesSet {theBoard.generalFilter(PieceType::horse, PieceColour::white)};
    Int pawnsMoved {};
    for (auto piece: enemyPawns) {
        if (pawnsMoved == 0) {
            piece->setCoordinates(Coordinates(0,2));
            pawnsMoved++;
        } else if (pawnsMoved == 1) {
            piece->setCoordinates(Coordinates(2,2));
            pawnsMoved++;
        } else if (pawnsMoved == 2) {
            piece->setCoordinates(Coordinates(5,2));
            pawnsMoved++;
        } else if (pawnsMoved == 3) {
            piece->setCoordinates(Coordinates(7,2));
            pawnsMoved++;
        }
    }

    for (const auto& piece: whiteHorsesSet) {
        if (piece->getCoordinates().getX() == 1 && piece->getCoordinates().getY() == 0) {
            auto result = piece->possibleMoves();
            EXPECT_EQ(result.at(0), Coordinates(0,2));
            EXPECT_EQ(result.at(1), Coordinates(2,2));
        } else if (piece->getCoordinates().getX() == 6 && piece->getCoordinates().getY() == 0) {
            auto result = piece->possibleMoves();
            EXPECT_EQ(result.at(0), Coordinates(5,2));
            EXPECT_EQ(result.at(1), Coordinates(7,2));
        }
    }
}