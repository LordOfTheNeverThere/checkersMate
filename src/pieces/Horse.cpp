#include "checkersMate/pieces/Horse.h"

Horse::Horse(const Int x, const Int y,Board* currentBoard, PieceColour colour)
: Piece(x, y, currentBoard, colour) {
    setType(PieceType::horse);
}