#include "checkersMate/pieces/Bishop.h"
#include "checkersMate/Board.h"

Bishop::Bishop(const Int x, const Int y,Board* currentBoard, PieceColour colour)
: Piece(x, y, currentBoard, colour) {
    setType(PieceType::bishop);
}

std::vector<Coordinates> Bishop::possibleMoves(const Piece* lastPlayedPiece) {
    std::vector<Coordinates> moves {};
    Board* currentBoard {getCurrentBoard()};

    auto handleNewCoords {[&moves, &currentBoard,this](Int x, Int y) -> bool {
        try {
            Coordinates putativeCoord {x, y};
            if (currentBoard->isSquareFree(putativeCoord)) {
                moves.push_back(putativeCoord);
                return false;
            } else if (!isFriendlyFire(putativeCoord)) {
                moves.push_back(putativeCoord); // Will be the last position where moving is allowed, will return true since it will go to the end of the function
            }
        } catch (OutOfBoardException& e) {}
        return true;
    }};

    bool blockedUpLeft {false};
    bool blockedUpRight {false};
    bool blockedDownRight {false};
    bool blockedDownLeft {false};
    Coordinates currentCoordinate {getCoordinates()};


    for (int i = 1; !blockedUpLeft || !blockedUpRight || !blockedDownRight || !blockedDownLeft; ++i) {

        if (!blockedUpLeft) {
            blockedUpLeft = handleNewCoords(currentCoordinate.getX() - i, currentCoordinate.getY() + i);
        }
        if (!blockedUpRight) {
            blockedUpRight = handleNewCoords(currentCoordinate.getX() + i, currentCoordinate.getY() + i);
        }
        if (!blockedDownRight) {
            blockedDownRight = handleNewCoords(currentCoordinate.getX() + i, currentCoordinate.getY() - i);
        }
        if (!blockedDownLeft) {
            blockedDownLeft = handleNewCoords(currentCoordinate.getX() - i, currentCoordinate.getY() - i);
        }

    }
    return moves;
}