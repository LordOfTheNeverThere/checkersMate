#include "checkersMate/Coordinates.h"
#include <set>
#include <vector>

#include "checkersMate/pieces/PieceColour.h"

// set used where order does not matter, vector where it does


std::vector<Coordinates> Coordinates::generatePosYVec(const Int max) const {
    std::vector<Coordinates> result {};
    try {
        for (int i = 1; i <= max; ++i) {
            result.emplace_back(getX(), getY() + i);
        }
    } catch (OutOfBoardException& e){}
    return result;
}

std::vector<Coordinates> Coordinates::generateNegYVec(const Int max) const {
    std::vector<Coordinates> result {};
    try {
        for (int i = 1; i <= max; ++i) {
            result.emplace_back(getX(), getY() - i);
        }
    } catch (OutOfBoardException& e){}
    return result;
}


std::vector<Coordinates> Coordinates::generatePosXVec(const Int max) const {
    std::vector<Coordinates> result {};
    try {
        for (int i = 1; i <= max; ++i) {
            result.emplace_back(getX() + i, getY());
        }
    } catch (OutOfBoardException& e){}
    return result;
}


std::vector<Coordinates> Coordinates::generateNegXVec(const Int max) const {
    std::vector<Coordinates> result {};
    try {
        for (int i = 1; i <= max; ++i) {
            result.emplace_back(getX() - i, getY());
        }
    } catch (OutOfBoardException& e){}
    return result;
}


std::vector<Coordinates> Coordinates::generateNegXPosYVec(const Int max) const {
    std::vector<Coordinates> result {};
    try {
        for (int i = 1; i <= max; ++i) {
            result.emplace_back(getX() - i, getY() + i);
        }
    } catch (OutOfBoardException& e){}
    return result;
}

std::vector<Coordinates> Coordinates::generatePosXPosYVec(const Int max) const {
    std::vector<Coordinates> result {};
    try {
        for (int i = 1; i <= max; ++i) {
            result.emplace_back(getX() + i, getY() + i);
        }
    } catch (OutOfBoardException& e){}
    return result;
}


std::vector<Coordinates> Coordinates::generatePosXNegYVec(const Int max) const {
    std::vector<Coordinates> result {};
    try {
        for (int i = 1; i <= max; ++i) {
            result.emplace_back(getX() + i, getY() - i);
        }
    } catch (OutOfBoardException& e){}
    return result;
}


std::vector<Coordinates> Coordinates::generateNegXNegYVec(const Int max) const {
    std::vector<Coordinates> result {};
    try {
        for (int i = 1; i <= max; ++i) {
            result.emplace_back(getX() - i, getY() - i);
        }
    } catch (OutOfBoardException& e){}
    return result;
}


std::set<Coordinates> Coordinates::generateCircleSet(const Int max) const {
    std::set<Coordinates> result {};
    for (int x = getX() - max; x <= getX() + max; ++x) {
        for (int y = getY() - max; y <= getY() + max; ++y) {
            if (x != getX() || y != getY()) {
                try {
                    result.emplace(x,y);
                } catch (OutOfBoardException) {}
            }
        }
    }
    return result;
}

std::set<Coordinates> Coordinates::generateEnemyPawnPositions(const PieceColour& friendlyColour) const {
    std::set<Coordinates> result {};

    if (friendlyColour == PieceColour::black) {
        std::vector<Coordinates> negXnegYPosition {generateNegXNegYVec(1)};
        std::vector<Coordinates> posXnegYPosition {generatePosXNegYVec(1)};
        if (negXnegYPosition.size() == 1) result.insert(*negXnegYPosition.begin());
        if (posXnegYPosition.size() == 1) result.insert(*posXnegYPosition.begin());

    } else if (friendlyColour == PieceColour::white) {
        std::vector<Coordinates> negXposYPosition {generateNegXPosYVec(1)};
        std::vector<Coordinates> posXPosYPosition {generatePosXPosYVec(1)};
        if (negXposYPosition.size() == 1) result.insert(*negXposYPosition.begin());
        if (posXPosYPosition.size() == 1) result.insert(*posXPosYPosition.begin());
    }

    return result;
}

// Due to its Jerusalem cross shape and its symmetry a Horse in x,y can capture in x+1,y+2, and the latter can capture the former
std::set<Coordinates> Coordinates::generateHorsePositions() const {
    std::set<Coordinates> result {};
    // Search for moves that have a bigger change on the x-axis
    for (Int x = getX() - 2; x <= getX() +2; x = x + 4 ) {
        try {
            Coordinates newCoords {x, getY() - 1};
            result.insert(newCoords);
        } catch (OutOfBoardException& e) {} // will not add as coord is out of bounds
        try {
            Coordinates newCoords {x, getY() + 1};
            result.insert(newCoords);
        } catch (OutOfBoardException& e) {}
    }
    // Search for moves that have a bigger change on the y-axis
    for (Int y = getY() -2 ; y <= getY() + 2; y = y +4) {
        try {
            Coordinates newCoords {getX() - 1, y};
            result.insert(newCoords);
        } catch (OutOfBoardException& e) {
        }
        try {
            Coordinates newCoords {getX() + 1, y};
            result.insert(newCoords);
        } catch (OutOfBoardException& e) {
        }
    }

    return result;
}


// std::set<Coordinates> Coordinates::generatePlusPositions(const Int max) const {
//     std::set<Coordinates> result {};
//     for (auto set :std::set<std::set<Coordinates>>{generatePosYVec(max), generateNegYVec(max),
//         generatePosXVec(max), generateNegXVec(max)}) result.merge(set);
//     return result;
// }
//
// std::set<Coordinates> Coordinates::generateCrossPositions(const Int max) const {
//     std::set<Coordinates> result {};
//     for (auto set : std::set<std::set<Coordinates>>{generateNegXPosYVec(max), generatePosXPosYVec(max),
//         generatePosXNegYVec(max), generateNegXNegYVec(max)}) result.merge(set);
//
//     return result;
// }
//
// std::set<Coordinates> Coordinates::generatePlusCrossPositions(const Int max) const {
//     std::set<Coordinates> result {};
//     for (auto set : std::set<std::set<Coordinates>>{generatePlusPositions(max), generateCrossPositions(max)}) result.merge(set);
//
//     return result;
// }

