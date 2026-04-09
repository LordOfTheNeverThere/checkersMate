#include "checkersMate/pieces/Tower.h"

#include "checkersMate/Board.h"

Tower::Tower(const Int x, const Int y,Board* currentBoard, PieceColour colour)
: Piece(x, y, currentBoard, colour) {
    setType(PieceType::tower);
}

std::vector<Coordinates> Tower::possibleMoves() {
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

    bool blockedPosX {false};
    bool blockedNegX {false};
    bool blockedPosY {false};
    bool blockedNegY {false};
    Coordinates currentCoordinate {getCoordinates()};

    for (int i = 1; !blockedPosX || !blockedNegX || !blockedPosY || !blockedNegY; ++i) {

        if (!blockedPosX) {
            blockedPosX = handleNewCoords(currentCoordinate.getX() + i, currentCoordinate.getY());
        }
        if (!blockedNegX) {
            blockedNegX = handleNewCoords(currentCoordinate.getX() - i, currentCoordinate.getY());
        }
        if (!blockedPosY) {
            blockedPosY = handleNewCoords(currentCoordinate.getX(), currentCoordinate.getY() + i);
        }
        if (!blockedNegY) {
            blockedNegY = handleNewCoords(currentCoordinate.getX(), currentCoordinate.getY() - i);
        }

    }
    return moves;
}
