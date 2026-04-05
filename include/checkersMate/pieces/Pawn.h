#ifndef CHECKERSMATE_PAWN_H
#define CHECKERSMATE_PAWN_H
#include "Piece.h"

class Pawn : public Piece {
public:
    Pawn(const Int x, const Int y,Board* currentBoard, PieceColour colour);
};
#endif //CHECKERSMATE_PAWN_H