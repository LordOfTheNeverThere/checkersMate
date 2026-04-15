#include "checkersMate/pieces/King.h"

#include "checkersMate/Board.h"

King::King(const Int x, const Int y,Board* currentBoard, PieceColour colour)
: Piece(x, y, currentBoard, colour) {
    setType(PieceType::king);
}

bool King::validKingsideCastling() {
    Piece* possibleTowerKing {getCurrentBoard()->piecePtrAtCoordinates(getCoordinates().getX() + 3, getCoordinates().getY())};
    Coordinates currentCoordinates {getCoordinates()};
    if (getNumOfMoves() == 0 && !getCurrentBoard()->isKingChecked(getColour()) && possibleTowerKing && possibleTowerKing->getType()==PieceType::tower && possibleTowerKing->getNumOfMoves() == 0) {
        for (int i = 1; i <= 2; ++i) {
            Coordinates newCoord {getCoordinates().getX() + i, getCoordinates().getY()};
            if (!getCurrentBoard()->isSquareFree(newCoord)) {
                return false;
            } else{
                setCoordinates(newCoord);
                bool checked {getCurrentBoard()->isKingChecked(getColour())};
                setCoordinates(currentCoordinates);// reset
                m_NumOfMoves =0;
                if (checked) return false;
            }
        }
        return true;
    } else {
        return false;
    }
}

bool King::validQueensideCastling() {
    Piece* possibleTowerQueen {getCurrentBoard()->piecePtrAtCoordinates(getCoordinates().getX() - 4, getCoordinates().getY())};
    Coordinates currentCoordinates {getCoordinates()};
    if (getNumOfMoves() == 0 && !getCurrentBoard()->isKingChecked(getColour()) && possibleTowerQueen && possibleTowerQueen->getType()==PieceType::tower && possibleTowerQueen->getNumOfMoves() == 0) {
        for (int i = 1; i <= 3; ++i) {
            Coordinates newCoord {getCoordinates().getX() - i, getCoordinates().getY()};
            if (!getCurrentBoard()->isSquareFree(newCoord)) {
                return false;
            } else if (i <= 2) {
                setCoordinates(newCoord);
                bool checked {getCurrentBoard()->isKingChecked(getColour())};
                setCoordinates(currentCoordinates);
                m_NumOfMoves =0;
                if (checked) return false;
            }
        }
        return true;
    } else {
        return false;
    }
}

std::set<Coordinates> King::possibleMoves(const Piece* lastPlayedPiece) {
    std::set<Coordinates> moves {};

    for (auto move: getCoordinates().generateCircleSet()) {
        if (!isFriendlyFire(move)) {
            moves.insert(move);
        }
    }

    if (validKingsideCastling()) {
        moves.insert({getCoordinates().getX() + 2, getCoordinates().getY()});
    }
    if (validQueensideCastling()) {
        moves.insert({getCoordinates().getX() - 2 , getCoordinates().getY()});
    }

    return moves;
}
