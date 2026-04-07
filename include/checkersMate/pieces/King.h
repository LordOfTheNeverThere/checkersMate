#ifndef CHECKERSMATE_KING_H
#define CHECKERSMATE_KING_H
#include "Piece.h"

class King : public Piece{
public:
    King(const Int x, const Int y,Board* currentBoard, PieceColour colour);
    std::vector<Coordinates> possibleMoves() override;
    void print(std::ostream& os) const {
        unsigned char charName {'K'};
        if (getColour() == PieceColour::black) {
            charName = std::tolower(charName);
        }
        os << charName;
    }
};

#endif //CHECKERSMATE_KING_H