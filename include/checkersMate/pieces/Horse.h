#ifndef CHECKERSMATE_KNIGHT_H
#define CHECKERSMATE_KNIGHT_H
#include "Piece.h"

class Horse : public Piece {
public:
    Horse(const Int x, const Int y,Board* currentBoard, PieceColour colour);

    std::vector<Coordinates> possibleMoves() override;
    void print(std::ostream& os) const {
        unsigned char charName {'B'};
        if (getColour() == PieceColour::black) {
            charName = std::tolower(charName);
        }
        os << charName;
    }
};
#endif //CHECKERSMATE_KNIGHT_H