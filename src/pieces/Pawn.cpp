#include "checkersMate/pieces/Pawn.h"

Pawn::Pawn(const Int x, const Int y,Board* currentBoard, PieceColour colour)
: Piece(x, y, currentBoard, colour) {
    setType(PieceType::pawn);
}

std::vector<Coordinates> Pawn::possibleMoves() { return {}; } //TODO : implementation