#ifndef CHECKERSMATE_BISHOP_H
#define CHECKERSMATE_BISHOP_H
#include "Piece.h"

class Bishop : public Piece {
public:
    Bishop(const Int x, const Int y,Board* currentBoard, PieceColour colour);
    void print(std::ostream& os) const {
        unsigned char charName {'B'};
        if (getColour() == PieceColour::black) {
            charName = std::tolower(charName);
        }
        os << charName;
    }
};

#endif //CHECKERSMATE_BISHOP_H