#ifndef CHECKERSMATE_PAWN_H
#define CHECKERSMATE_PAWN_H
#include "Piece.h"

class Pawn : public Piece {
public:
    Pawn(const Int x, const Int y,Board* currentBoard, PieceColour colour);
    void print(std::ostream& os) const {
        unsigned char charName {'P'};
        if (getColour() == PieceColour::black) {
            charName = std::tolower(charName);
        }
        os << charName;
    }
};
#endif //CHECKERSMATE_PAWN_H