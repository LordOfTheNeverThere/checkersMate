#include "checkersMate/pieces/Queen.h"
#include "checkersMate/Board.h"

#include <bitset>

Queen::Queen(const Int x, const Int y,Board* currentBoard, PieceColour colour)
: Piece(x, y, currentBoard, colour) {
    setType(PieceType::queen);
}

std::vector<Coordinates> Queen::possibleMoves() {
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
    // Order: 0: +X; 1: -X; 2: +Y; 3: -Y;
    // 4: -X+Y; 5: +X+Y; 6: +X-Y; 7: -X-Y
    std::bitset<8> blockedBits{ 0b00000000 };
    Coordinates currentCoordinate {getCoordinates()};

    for (int i = 1; !blockedBits.all(); ++i) {
        Int position {};
        if (!blockedBits.test(position)) {
            blockedBits.set(position,handleNewCoords(currentCoordinate.getX() + i, currentCoordinate.getY()));
        }
        position++;
        if (!blockedBits.test(position)) {
            blockedBits.set(position,handleNewCoords(currentCoordinate.getX() - i, currentCoordinate.getY()));
        }
        position++;
        if (!blockedBits.test(position)) {
            blockedBits.set(position,handleNewCoords(currentCoordinate.getX(), currentCoordinate.getY() + i));
        }
        position++;
        if (!blockedBits.test(position)) {
            blockedBits.set(position, handleNewCoords(currentCoordinate.getX(), currentCoordinate.getY() - i));
        }
        position++;
        if (!blockedBits.test(position)) {
            blockedBits.set(position, handleNewCoords(currentCoordinate.getX() - i, currentCoordinate.getY() + i));
        }
        position++;
        if (!blockedBits.test(position)) {
            blockedBits.set(position, handleNewCoords(currentCoordinate.getX() + i, currentCoordinate.getY() + i));
        }
        position++;
        if (!blockedBits.test(position)) {
            blockedBits.set(position, handleNewCoords(currentCoordinate.getX() + i, currentCoordinate.getY() - i));
        }
        position++;
        if (!blockedBits.test(position)) {
            blockedBits.set(position,handleNewCoords(currentCoordinate.getX() - i, currentCoordinate.getY() - i));
        }
    }
    return moves;
}