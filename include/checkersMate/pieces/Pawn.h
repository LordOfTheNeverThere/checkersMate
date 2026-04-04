#ifndef CHECKERSMATE_PAWN_H
#define CHECKERSMATE_PAWN_H
#include "Piece.h"

class Pawn : public Piece {
public:
    Pawn(Int x, Int y, const std::array<std::weak_ptr<Piece>, 32> &otherPieces, PieceType type);
};
#endif //CHECKERSMATE_PAWN_H