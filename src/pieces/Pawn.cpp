#include "checkersMate/pieces/Pawn.h"

#include "checkersMate/Board.h"

Pawn::Pawn(const Int x, const Int y,Board* currentBoard, PieceColour colour)
: Piece(x, y, currentBoard, colour) {
    setType(PieceType::pawn);
}

// Checks lastPlayedPiece to see if it is a pawn of the other colour with en passant possibility
// If en passant happens this pawn will move to y + 1 in regards to the piece captured.
std::vector<Coordinates> Pawn::possibleMoves(const Piece& lastPlayedPiece) {
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

    // Normal capture and with En Passant capture
    try {
        Coordinates left {currentCoordinate - Coordinates(1, 0)};
        Coordinates diagLeft {left + Coordinates(0,1) };
        Piece pieceAtDiagLeft {getCurrentBoard()->pieceAtCoordinates(diagLeft)};
        if (((currentCoordinate.getY() == 4 && getColour() == PieceColour::white) || (currentCoordinate.getY() == 3 && getColour() == PieceColour::black))
            && lastPlayedPiece.getCoordinates() == left && lastPlayedPiece.getType() == PieceType::pawn && lastPlayedPiece.getColour() != getColour()) {
            moves.push_back(diagLeft); // En passant capture
        } else if (pieceAtDiagLeft.getType() != PieceType::empty  && pieceAtDiagLeft.getColour() != getColour()) {
            moves.push_back(diagLeft);// Normal Capture
        }
    } catch (OutOfBoardException& e) {}
    try {
        Coordinates right { currentCoordinate +  Coordinates(1,0)};
        Coordinates diagRight {right + Coordinates(0,1)};
        Piece pieceAtDiagRight {getCurrentBoard()->pieceAtCoordinates(diagRight)};
        if (((currentCoordinate.getY() == 4 && getColour() == PieceColour::white) || (currentCoordinate.getY() == 3 && getColour() == PieceColour::black))
        && lastPlayedPiece.getCoordinates() == diagRight && lastPlayedPiece.getType() == PieceType::pawn && lastPlayedPiece.getColour() != getColour()) {
            moves.push_back(diagRight);
        } else if (pieceAtDiagRight.getType() != PieceType::empty  && pieceAtDiagRight.getColour() != getColour()) { // Normal Capture
            moves.push_back(diagRight);
        }
    } catch (OutOfBoardException& e) {}


    return moves;
}