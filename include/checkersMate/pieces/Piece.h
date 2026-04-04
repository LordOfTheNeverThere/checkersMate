#ifndef CHECKERSMATE_PIECE_H
#define CHECKERSMATE_PIECE_H
#include <memory>
#include <array>
#include "PieceType.h"
#include "../Coordinates.h"


class Piece {
    std::array<std::weak_ptr<Piece>, 32> m_otherPieces {};
    Coordinates m_coordinates {0,0};
    PieceType m_type {};
public:
    Piece(Int x, Int y, const std::array<std::weak_ptr<Piece>, 32> &otherPieces, PieceType type);

    std::array<std::weak_ptr<Piece>, 32> getOtherPieces() {
        return m_otherPieces;
    }
    void setOtherPieces(std::array<std::weak_ptr<Piece>, 32> otherPieces) {
        m_otherPieces = std::move(otherPieces);
    }

    Coordinates getCoordinates() const {
        return m_coordinates;
    }
    void setCoordinates(Int x, Int y) {
        m_coordinates.setX(x);
        m_coordinates.setY(y);
    }

    PieceType getType() const {
        return m_type;
    }

    void setType(const PieceType type) {
        m_type = type;
    }
};

#endif //CHECKERSMATE_PIECE_H