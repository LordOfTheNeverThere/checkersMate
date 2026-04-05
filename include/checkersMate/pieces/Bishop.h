#ifndef CHECKERSMATE_BISHOP_H
#define CHECKERSMATE_BISHOP_H
#include "Piece.h"

class Bishop : public Piece {
public:
    Bishop(const Int x, const Int y,Board* currentBoard, PieceColour colour);
};
#endif //CHECKERSMATE_BISHOP_H