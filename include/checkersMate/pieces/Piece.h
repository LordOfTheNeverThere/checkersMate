#ifndef CHECKERSMATE_PIECE_H
#define CHECKERSMATE_PIECE_H
#include "PieceColour.h"
#include "PieceType.h"
#include "../Coordinates.h"

#include "gtest/gtest.h"
#include <iostream>
#include <vector>

class Board; // Forward Declaration

class Piece {
    FRIEND_TEST(MethodChecking, BoardConstructor);
    FRIEND_TEST(MethodChecking, emptyConstructor);
    FRIEND_TEST(MethodChecking, isFriendlyFire);

protected:
    Board* m_currentBoard {};
    Coordinates m_coordinates {0,0};
    PieceColour m_colour {};
    PieceType m_type {};
    uint64_t m_NumOfMoves{};

    bool isFriendlyFire(const Coordinates& newCoords) const;
public:
    Piece();
    Piece(const Int x, const Int y,Board* currentBoard, PieceColour colour);

    virtual std::set<Coordinates> possibleMoves(const Piece* lastPlayedPiece = nullptr) = 0;

    Board* getCurrentBoard() const {
        return m_currentBoard;
    }

    Coordinates getCoordinates() const {
        return m_coordinates;
    }

    Coordinates *getCoordinatesPtr() {
        return &m_coordinates;
    }

    void setCoordinates(const Int x, const Int y) {
        m_coordinates.setX(x);
        m_coordinates.setY(y);
        m_NumOfMoves++;
    }

    void setCoordinates(const Coordinates coordinates) {
        m_coordinates = coordinates;
        m_NumOfMoves++;
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
    uint64_t getNumOfMoves() const {
        return m_NumOfMoves;
    }

    virtual void print(std::ostream& os) const {}
    friend inline bool operator==(const Piece& lhs, const Piece& rhs);
};

inline std::ostream& operator<<(std::ostream& os, const Piece& piece) {
    piece.print(os);
    return os;
}

inline bool operator==(const Piece& lhs, const Piece& rhs) {
    return (lhs.getCurrentBoard() == rhs.getCurrentBoard()
    && lhs.getCoordinates() == rhs.getCoordinates()
    && lhs.getColour() == rhs.getColour()
    && lhs.getType() == rhs.getType()
    && lhs.m_NumOfMoves == rhs.m_NumOfMoves);
}

inline bool operator!=(const Piece& lhs, const Piece& rhs) {
    return !operator==(lhs,rhs);
}

#endif //CHECKERSMATE_PIECE_H