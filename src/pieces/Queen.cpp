#include "checkersMate/pieces/Queen.h"

Queen::Queen(const Int x, const Int y,Board* currentBoard, PieceColour colour)
: Piece(x, y, currentBoard, colour) {
    setType(PieceType::queen);
}

std::vector<Coordinates> Queen::possibleMoves() { return {}; } //TODO : implementation