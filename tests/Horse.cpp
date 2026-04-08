#include "checkersMate/pieces/Horse.h"
#include "checkersMate/Board.h"
#include "gtest/gtest.h"

TEST(MethodChecking, possibleMovesStartingPosition) {
    Board theBoard {};

    for (const auto& piece: theBoard.m_pieces) {
        if (piece.get()->getType() == PieceType::horse && piece.get()->getColour() == PieceColour::white) {
            if (piece.get()->getCoordinates().getX() == 1 && piece.get()->getCoordinates().getY() == 0) {
                auto result = piece->possibleMoves();
                EXPECT_EQ(result.at(0), Coordinates(0,2));
                EXPECT_EQ(result.at(1), Coordinates(2,2));
            } else if (piece.get()->getCoordinates().getX() == 6 && piece.get()->getCoordinates().getY() == 0) {
                auto result = piece->possibleMoves();
                EXPECT_EQ(result.at(0), Coordinates(5,2));
                EXPECT_EQ(result.at(1), Coordinates(7,2));
            }
        }
    }
}

TEST(MethodChecking, possibleMovesOnEnemyPieces) {

    Board theBoard {};
    Int pawnsMoved {};
    for (const auto& piece: theBoard.m_pieces) {
        if (piece.get()->getType() == PieceType::pawn && piece.get()->getColour() == PieceColour::black && pawnsMoved == 0) {
            piece->setCoordinates(Coordinates(0,2));
            pawnsMoved++;
        } else if (piece.get()->getType() == PieceType::pawn && piece.get()->getColour() == PieceColour::black && pawnsMoved == 1) {
            piece->setCoordinates(Coordinates(2,2));
            pawnsMoved++;
        } else if (piece.get()->getType() == PieceType::pawn && piece.get()->getColour() == PieceColour::black && pawnsMoved == 2) {
            piece->setCoordinates(Coordinates(5,2));
            pawnsMoved++;
        } else if (piece.get()->getType() == PieceType::pawn && piece.get()->getColour() == PieceColour::black && pawnsMoved == 3) {
            piece->setCoordinates(Coordinates(7,2));
            pawnsMoved++;
        }
    }

    for (const auto& piece: theBoard.m_pieces) {
        if (piece.get()->getType() == PieceType::horse && piece.get()->getColour() == PieceColour::white) {
            if (piece.get()->getCoordinates().getX() == 1 && piece.get()->getCoordinates().getY() == 0) {
                auto result = piece->possibleMoves();
                EXPECT_EQ(result.at(0), Coordinates(0,2));
                EXPECT_EQ(result.at(1), Coordinates(2,2));
            } else if (piece.get()->getCoordinates().getX() == 6 && piece.get()->getCoordinates().getY() == 0) {
                auto result = piece->possibleMoves();
                EXPECT_EQ(result.at(0), Coordinates(5,2));
                EXPECT_EQ(result.at(1), Coordinates(7,2));
            }
        }
    }
}