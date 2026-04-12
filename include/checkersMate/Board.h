#ifndef CHECKERSMATE_BOARD_H
#define CHECKERSMATE_BOARD_H
#include <array>
#include <memory>

#include "gtest/gtest.h"
#include "pieces/Piece.h"

class Board{
    friend class Piece;
    FRIEND_TEST(MethodChecking, checkIfBoardConstructorMapWorksWithCoordinatesPtr);
    FRIEND_TEST(MethodChecking, BoardConstructorV2);
    FRIEND_TEST(MethodChecking, possibleMovesStartingPosition);
    FRIEND_TEST(MethodChecking, possibleMovesOnEnemyPieces);

    std::array<std::unique_ptr<Piece>, 32> m_pieces {}; //TODO: Changes this to a map of map of a map, where the first sorts by colour and then the other by piece type and the last has a pointer to the coordinates of the piece (the val)
    std::map<PieceColour, std::map<PieceType, std::map<Coordinates*, std::unique_ptr<Piece>>>> m_piecesV2;
public:
    Board();

    std::set<Piece *> generalFilter(const PieceType &type = PieceType::empty, const PieceColour &colour = PieceColour::empty, const Coordinates *coords = nullptr);

    bool isSquareFree(const Coordinates newCoords) const;

    bool isKingChecked(const PieceColour &colour);

    std::vector<Coordinates> checkChecker(std::vector<Coordinates>& moves, Piece* piecePtr);

    // Piece pieceAtCoordinates(const Coordinates newCoords) const;
    Piece* piecePtrAtCoordinates(const Coordinates newCoords) const;

    void emptyTheBoard(std::set<Piece *> piecesToKeep);

    std::set<Piece *> queryPieces(const PieceType &type = PieceType::empty, const PieceColour &colour = PieceColour::empty);

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