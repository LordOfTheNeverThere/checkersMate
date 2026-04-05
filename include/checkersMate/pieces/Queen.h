#ifndef CHECKERSMATE_QUEEN_H
#define CHECKERSMATE_QUEEN_H
#include "Piece.h"

class Queen : public Piece {
public:
    Queen(const Int x, const Int y,Board* currentBoard, PieceColour colour);
};
#endif //CHECKERSMATE_QUEEN_H