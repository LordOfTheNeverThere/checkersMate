#include "checkersMate/pieces/Tower.h"

Tower::Tower(const Int x, const Int y,Board* currentBoard, PieceColour colour)
: Piece(x, y, currentBoard, colour) {
    setType(PieceType::tower);
}

std::vector<Coordinates> Tower::possibleMoves() { return {}; } //TODO : implementation
