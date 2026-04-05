#ifndef CHECKERSMATE_TOWER_H
#define CHECKERSMATE_TOWER_H
#include "Piece.h"

class Tower : public Piece {
public:
    Tower(const Int x, const Int y,Board* currentBoard, PieceColour colour);
};
#endif //CHECKERSMATE_TOWER_H