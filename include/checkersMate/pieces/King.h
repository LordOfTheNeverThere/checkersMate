#ifndef CHECKERSMATE_KING_H
#define CHECKERSMATE_KING_H
#include "Piece.h"

class King : public Piece{
public:
    King(const Int x, const Int y,Board* currentBoard, PieceColour colour);
};

#endif //CHECKERSMATE_KING_H