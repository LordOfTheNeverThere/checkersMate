#ifndef CHECKERSMATE_QUEEN_H
#define CHECKERSMATE_QUEEN_H
#include "Piece.h"

class Queen : public Piece {
public:
    Queen(const Int x, const Int y,Board* currentBoard, PieceColour colour);
    std::vector<Coordinates> possibleMoves(const Piece* lastPlayedPiece = nullptr) override;
    void print(std::ostream& os) const {
        unsigned char charName {'Q'};
        if (getColour() == PieceColour::black) {
            charName = std::tolower(charName);
        }
        os << charName;
    }
};
#endif //CHECKERSMATE_QUEEN_H