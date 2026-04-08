#include "../../include/checkersMate/pieces/Piece.h"

#include "checkersMate/Board.h"

std::vector<Coordinates> Piece::possibleMoves() { return {}; }

bool Piece::isFriendlyFire(const Coordinates &newCoords) const {
    bool returnVal {false};
    Piece* pieceAtNewCoords = getCurrentBoard()->piecePtrAtCoordinates(newCoords);
    if (pieceAtNewCoords && pieceAtNewCoords->getColour() == getColour()) {
        returnVal = true;
    }
    return returnVal;
}

Piece::Piece(){}

Piece::Piece(const Int x, const Int y, Board* currentBoard, PieceColour colour) {
    m_currentBoard = currentBoard;
    setCoordinates(x, y);
    setColour(colour);
    m_NumOfMoves = 0;
}