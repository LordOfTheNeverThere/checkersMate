#include "checkersMate/pieces/King.h"

King::King(const Int x, const Int y,Board* currentBoard, PieceColour colour)
: Piece(x, y, currentBoard, colour) {
    setType(PieceType::king);
}

std::vector<Coordinates> King::possibleMoves() { return {}; } //TODO : implementation