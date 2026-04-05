#ifndef CHECKERSMATE_KNIGHT_H
#define CHECKERSMATE_KNIGHT_H
#include "Piece.h"

class Horse : public Piece {
public:
    Horse(const Int x, const Int y,Board* currentBoard, PieceColour colour);
};
#endif //CHECKERSMATE_KNIGHT_H