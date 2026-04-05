#include "../../include/checkersMate/pieces/Piece.h"


Piece::Piece(){}

Piece::Piece(const Int x, const Int y, Board* currentBoard, PieceColour colour) {
    m_currentBoard = currentBoard;
    setCoordinates(x, y);
    setColour(colour);
}