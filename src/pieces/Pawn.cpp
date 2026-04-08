#include "checkersMate/pieces/Pawn.h"

#include "checkersMate/Board.h"

Pawn::Pawn(const Int x, const Int y,Board* currentBoard, PieceColour colour)
: Piece(x, y, currentBoard, colour) {
    setType(PieceType::pawn);
}

std::vector<Coordinates> Pawn::possibleMoves() {
    std::vector<Coordinates> moves {};
    Coordinates currentCoordinate {getCoordinates()};
    // moving
    try {
        Coordinates oneForward {currentCoordinate + Coordinates(1,0)};
        if (getCurrentBoard()->isSquareFree(oneForward)) {
            moves.push_back(oneForward);
            Coordinates twoForward {oneForward + Coordinates(1,0)};
            if (getCurrentBoard()->isSquareFree(twoForward) && m_NumOfMoves == 0) moves.push_back(twoForward);
        }
    } catch (OutOfBoardException& e) {}
    //TODO: capturing

    return moves;
}