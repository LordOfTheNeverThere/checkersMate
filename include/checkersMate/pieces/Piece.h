#ifndef CHECKERSMATE_PIECE_H
#define CHECKERSMATE_PIECE_H
#include "PieceColour.h"
#include "PieceType.h"
#include "../Coordinates.h"

#include <iostream>

class Board; // Forward Declaration

class Piece {
    Board* m_currentBoard {};
    Coordinates m_coordinates {0,0};
    PieceColour m_colour {};
    PieceType m_type {};
    uint64_t m_NumOfMoves{};
public:
    Piece();
    Piece(const Int x, const Int y,Board* currentBoard, PieceColour colour);

    Board* getCurrentBoard() {
        return m_currentBoard;
    }

    Coordinates getCoordinates() const {
        return m_coordinates;
    }

    void setCoordinates(const Int x, const Int y) {
        m_coordinates.setX(x);
        m_coordinates.setY(y);
    }

    PieceType getType() const {
        return m_type;
    }

    void setType(const PieceType type) {
        m_type = type;
    }

    PieceColour getColour() const {
        return m_colour;
    }

    void setColour(const PieceColour colour) {
        m_colour = colour;
    }

    virtual void print(std::ostream& os) const {}
};

inline std::ostream& operator<<(std::ostream& os, const Piece& piece) {
    piece.print(os);
    return os;
}

#endif //CHECKERSMATE_PIECE_H