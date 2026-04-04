#ifndef CHECKERSMATE_QUEEN_H
#define CHECKERSMATE_QUEEN_H
#include "Piece.h"

class Queen : public Piece {
public:
    Queen(Int x, Int y, const std::array<std::weak_ptr<Piece>, 32> &otherPieces, PieceType type);
};
#endif //CHECKERSMATE_QUEEN_H