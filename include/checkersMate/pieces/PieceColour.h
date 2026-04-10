
#ifndef CHECKERSMATE_PIECECOLOUR_H
#define CHECKERSMATE_PIECECOLOUR_H

enum class PieceColour {
    empty,
    white,
    black,
};

inline PieceColour operator!(const PieceColour& currentColour) {
    if (currentColour == PieceColour::black) return PieceColour::white;
    else if (currentColour == PieceColour::white) return PieceColour::black;
    else return PieceColour::empty;
}
#endif //CHECKERSMATE_PIECECOLOUR_H