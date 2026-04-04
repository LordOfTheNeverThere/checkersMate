#ifndef CHECKERSMATE_BISHOP_H
#define CHECKERSMATE_BISHOP_H
#include "Piece.h"

class Bishop : public Piece {
public:
    Bishop(Int x, Int y, const std::array<std::weak_ptr<Piece>, 32> &otherPieces, PieceType type);
};
#endif //CHECKERSMATE_BISHOP_H