#ifndef CHECKERSMATE_KING_H
#define CHECKERSMATE_KING_H
#include "Piece.h"

class King : public Piece{
public:
    King(Int x, Int y, const std::array<std::weak_ptr<Piece>, 32> &otherPieces, PieceType type);
};

#endif //CHECKERSMATE_KING_H