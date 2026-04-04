#ifndef CHECKERSMATE_KNIGHT_H
#define CHECKERSMATE_KNIGHT_H
#include "Piece.h"

class Horse : public Piece {
public:
    Horse(Int x, Int y, const std::array<std::weak_ptr<Piece>, 32> &otherPieces, PieceType type);
};
#endif //CHECKERSMATE_KNIGHT_H