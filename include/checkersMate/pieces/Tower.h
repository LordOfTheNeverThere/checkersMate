#ifndef CHECKERSMATE_TOWER_H
#define CHECKERSMATE_TOWER_H
#include "Piece.h"

class Tower : public Piece {
public:
    Tower(const Int x, const Int y,Board* currentBoard, PieceColour colour);
    void print(std::ostream& os) const {
        unsigned char charName {'T'};
        if (getColour() == PieceColour::black) {
            charName = std::tolower(charName);
        }
        os << charName;
    }
};
#endif //CHECKERSMATE_TOWER_H