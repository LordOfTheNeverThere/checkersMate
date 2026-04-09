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
    Int signal {getColour() == PieceColour::white ? 1 : -1}; // depending on the colour the moves must alter
    // moving
    try {
        Coordinates oneForward {currentCoordinate}; oneForward.setY(oneForward.getY() + signal *1);
        if (getCurrentBoard()->isSquareFree(oneForward)) {
            moves.push_back(oneForward);
            Coordinates twoForward {oneForward}; twoForward.setY(twoForward.getY() + signal * 1);
            if (getCurrentBoard()->isSquareFree(twoForward) && m_NumOfMoves == 0) moves.push_back(twoForward);
        }
    } catch (OutOfBoardException& e) {}

    // Normal capture and with En Passant capture
    try {
        Coordinates left {currentCoordinate}; left.setX(left.getX() - signal * 1 );
        Coordinates diagLeft {left}; diagLeft.setY(diagLeft.getY() + signal * 1);
        Piece* pieceAtDiagLeft {getCurrentBoard()->piecePtrAtCoordinates(diagLeft)};
        if (((currentCoordinate.getY() == 4 && getColour() == PieceColour::white) || (currentCoordinate.getY() == 3 && getColour() == PieceColour::black))
            && lastPlayedPiece.getCoordinates() == left && lastPlayedPiece.getType() == PieceType::pawn && lastPlayedPiece.getColour() != getColour()
            && lastPlayedPiece.getNumOfMoves() == 1) {
            moves.push_back(diagLeft); // En passant capture
        } else if (pieceAtDiagLeft && pieceAtDiagLeft->getColour() != getColour()) {
            moves.push_back(diagLeft);// Normal Capture
        }
    } catch (OutOfBoardException& e) {}
    try {
        Coordinates right {currentCoordinate}; right.setX(right.getX() + signal * 1);
        Coordinates diagRight {right}; diagRight.setY(diagRight.getY() + signal * 1);
        Piece* pieceAtDiagRight {getCurrentBoard()->piecePtrAtCoordinates(diagRight)};
        if (((currentCoordinate.getY() == 4 && getColour() == PieceColour::white) || (currentCoordinate.getY() == 3 && getColour() == PieceColour::black))
        && lastPlayedPiece.getCoordinates() == right && lastPlayedPiece.getType() == PieceType::pawn && lastPlayedPiece.getColour() != getColour()
        && lastPlayedPiece.getNumOfMoves() == 1) {
            moves.push_back(diagRight);
        } else if (pieceAtDiagRight && pieceAtDiagRight->getColour() != getColour()) { // Normal Capture
            moves.push_back(diagRight);
        }
    } catch (OutOfBoardException& e) {}


    return moves;
}