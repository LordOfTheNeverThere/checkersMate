#ifndef CHECKERSMATE_TOWER_H
#define CHECKERSMATE_TOWER_H
#include "Piece.h"

class Tower : public Piece {
public:
    Tower(Int x, Int y, const std::array<std::weak_ptr<Piece>, 32> &otherPieces, PieceType type);
};
#endif //CHECKERSMATE_TOWER_H