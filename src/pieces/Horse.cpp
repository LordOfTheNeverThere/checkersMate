#include "checkersMate/pieces/Horse.h"

Horse::Horse(const Int x, const Int y,Board* currentBoard, PieceColour colour)
: Piece(x, y, currentBoard, colour) {
    setType(PieceType::horse);
}

std::set<Coordinates> Horse::possibleMoves(const Piece* lastPlayedPiece){
    std::set<Coordinates> moves {};
    Coordinates currentCoordinate {getCoordinates()};
    std::set<Coordinates> allPossibleMoves {currentCoordinate.generateHorsePositions()};

    for (auto possibleMove: allPossibleMoves) {
        if (!isFriendlyFire(possibleMove)) moves.insert(possibleMove);
    }
    return moves;
}