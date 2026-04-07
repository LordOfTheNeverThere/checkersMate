#include "checkersMate/pieces/Bishop.h"

Bishop::Bishop(const Int x, const Int y,Board* currentBoard, PieceColour colour)
: Piece(x, y, currentBoard, colour) {
    setType(PieceType::bishop);
}

std::vector<Coordinates> Bishop::possibleMoves() { return {}; } //TODO : implementation