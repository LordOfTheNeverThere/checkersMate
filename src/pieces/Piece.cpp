#include "../../include/checkersMate/pieces/Piece.h"

#include "checkersMate/Board.h"

std::vector<Coordinates> Piece::possibleMoves() { return {}; }

bool Piece::isFriendlyFire(const Coordinates &newCoords) const {
    bool returnVal {false};

    for (auto const & piece :m_currentBoard->m_pieces) {
        if (piece->getCoordinates() == newCoords && piece->getColour() == m_colour) {
            returnVal = true;
        }
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