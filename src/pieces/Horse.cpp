#include "checkersMate/pieces/Horse.h"

Horse::Horse(const Int x, const Int y,Board* currentBoard, PieceColour colour)
: Piece(x, y, currentBoard, colour) {
    setType(PieceType::horse);
}

std::set<Coordinates> Horse::possibleMoves(const Piece* lastPlayedPiece){
    std::set<Coordinates> moves {};
    Coordinates currentCoordinate {getCoordinates()};


    // Search for moves that have a bigger change on the x axis
    for (Int x = currentCoordinate.getX() - 2; x <= currentCoordinate.getX() +2; x = x + 4 ) {
        try {
            Coordinates newCoords {x, currentCoordinate.getY() - 1};
            if (!isFriendlyFire(newCoords)) moves.insert(newCoords);
        } catch (OutOfBoardException& e) {} // will not add as possible move if it is out of bounds
        try {
            Coordinates newCoords {x, currentCoordinate.getY() + 1};
            if (!isFriendlyFire(newCoords)) moves.insert(newCoords);
        } catch (OutOfBoardException& e) {}
    }
    // Search for moves that have a bigger change on the y axis
    for (Int y = currentCoordinate.getY() -2 ; y <= currentCoordinate.getY() + 2; y = y +4) {
        try {
            Coordinates newCoords {currentCoordinate.getX() - 1, y};
            if (!isFriendlyFire(newCoords)) moves.insert(newCoords);
        } catch (OutOfBoardException& e) {
        }
        try {
            Coordinates newCoords {currentCoordinate.getX() + 1, y};
            if (!isFriendlyFire(newCoords)) moves.insert(newCoords);
        } catch (OutOfBoardException& e) {
        }
    }

    return moves;
}