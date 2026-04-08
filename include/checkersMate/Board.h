#ifndef CHECKERSMATE_BOARD_H
#define CHECKERSMATE_BOARD_H
#include <array>
#include <iomanip>
#include <memory>

#include "gtest/gtest.h"
#include "pieces/Piece.h"

class Board{
    friend class Piece;
    FRIEND_TEST(MethodChecking, BoardConstructor);
    FRIEND_TEST(MethodChecking, possibleMovesStartingPosition);
    FRIEND_TEST(MethodChecking, possibleMovesOnEnemyPieces);

    std::array<std::unique_ptr<Piece>, 32> m_pieces {};
public:
    Board();
    bool isSquareFree(const Coordinates newCoords) const;
    Piece pieceAtCoordinates(const Coordinates newCoords) const;
    Piece* piecePtrAtCoordinates(const Coordinates newCoords) const;
    void printBoardView(PieceColour& viewFromColour) const; // Create a function which prints the board from 0,0 for white and 7,7 for black
    // friend std::ostream& operator<<(std::ostream& os, const Board& board) {
    //     for (int i = 0 ; i < board.m_pieces.size(); i++) {
    //         if (i % 8 == 0) {
    //             os << '\n';
    //         }
    //         os << std::setw(3) << *board.m_pieces.at(i);
    //     }
    //     return os;
    // }
};



#endif //CHECKERSMATE_BOARD_H