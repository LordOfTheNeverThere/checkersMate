#ifndef CHECKERSMATE_PAWN_H
#define CHECKERSMATE_PAWN_H
#include "Piece.h"

class Pawn : public Piece {
    FRIEND_TEST(MethodChecking, possibleMovesBlack);
    FRIEND_TEST(MethodChecking, possibleMovesWhite);
public:
    Pawn(const Int x, const Int y,Board* currentBoard, PieceColour colour);
    std::set<Coordinates> possibleMoves(const Piece* lastPlayedPiece = nullptr) override;
    void print(std::ostream& os) const {
        unsigned char charName {'P'};
        if (getColour() == PieceColour::black) {
            charName = std::tolower(charName);
        }
        os << charName;
    }
};
#endif //CHECKERSMATE_PAWN_H