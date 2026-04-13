#include "checkersMate/Coordinates.h"
#include <set>

#include "checkersMate/pieces/PieceColour.h"

std::set<Coordinates> Coordinates::generatePosYSet(const Int max) const {
    std::set<Coordinates> result {};
    try {
        for (int i = 1; i <= max; ++i) {
            result.emplace(getX(), getY() + i);
        }
    } catch (OutOfBoardException& e){}
    return result;
}

std::set<Coordinates> Coordinates::generateNegYSet(const Int max) const {
    std::set<Coordinates> result {};
    try {
        for (int i = 1; i <= max; ++i) {
            result.emplace(getX(), getY() - i);
        }
    } catch (OutOfBoardException& e){}
    return result;
}


std::set<Coordinates> Coordinates::generatePosXSet(const Int max) const {
    std::set<Coordinates> result {};
    try {
        for (int i = 1; i <= max; ++i) {
            result.emplace(getX() + i, getY());
        }
    } catch (OutOfBoardException& e){}
    return result;
}


std::set<Coordinates> Coordinates::generateNegXSet(const Int max) const {
    std::set<Coordinates> result {};
    try {
        for (int i = 1; i <= max; ++i) {
            result.emplace(getX() - i, getY());
        }
    } catch (OutOfBoardException& e){}
    return result;
}



std::set<Coordinates> Coordinates::generateNegXPosYSet(const Int max) const {
    std::set<Coordinates> result {};
    try {
        for (int i = 1; i <= max; ++i) {
            result.emplace(getX() - i, getY() + i);
        }
    } catch (OutOfBoardException& e){}
    return result;
}

std::set<Coordinates> Coordinates::generatePosXPosYSet(const Int max) const {
    std::set<Coordinates> result {};
    try {
        for (int i = 1; i <= max; ++i) {
            result.emplace(getX() + i, getY() + i);
        }
    } catch (OutOfBoardException& e){}
    return result;
}


std::set<Coordinates> Coordinates::generatePosXNegYSet(const Int max) const {
    std::set<Coordinates> result {};
    try {
        for (int i = 1; i <= max; ++i) {
            result.emplace(getX() + i, getY() - i);
        }
    } catch (OutOfBoardException& e){}
    return result;
}


std::set<Coordinates> Coordinates::generateNegXNegYSet(const Int max) const {
    std::set<Coordinates> result {};
    try {
        for (int i = 1; i <= max; ++i) {
            result.emplace(getX() - i, getY() - i);
        }
    } catch (OutOfBoardException& e){}
    return result;
}


std::set<Coordinates> Coordinates::generateCircleSet(const Int max) const {
    std::set<Coordinates> result {};
    result.merge(generateNegXPosYSet(max));
    result.merge(generatePosYSet(max));
    result.merge(generatePosXPosYSet(max));
    result.merge(generatePosXSet(max));
    result.merge(generatePosXNegYSet(max));
    result.merge(generateNegYSet(max));
    result.merge(generateNegXNegYSet(max));
    result.merge(generateNegXSet(max));
    return result;
}

std::set<Coordinates> Coordinates::generateEnemyPawnPositions(const PieceColour& friendlyColour) const {
    std::set<Coordinates> result {};

    if (friendlyColour == PieceColour::black) {
        result.merge(generateNegXNegYSet(1));
        result.merge(generatePosXNegYSet(1));
    } else if (friendlyColour == PieceColour::white) {
        result.merge(generateNegXPosYSet(1));
        result.merge(generatePosXPosYSet(1));
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


std::set<Coordinates> Coordinates::generatePlusPositions(const Int max) const {
    std::set<Coordinates> result {};
    for (auto set :std::set<std::set<Coordinates>>{generatePosYSet(max), generateNegYSet(max),
        generatePosXSet(max), generateNegXSet(max)}) result.merge(set);
    return result;
}

std::set<Coordinates> Coordinates::generateCrossPositions(const Int max) const {
    std::set<Coordinates> result {};
    for (auto set : std::set<std::set<Coordinates>>{generateNegXPosYSet(max), generatePosXPosYSet(max),
        generatePosXNegYSet(max), generateNegXNegYSet(max)}) result.merge(set);

    return result;
}

std::set<Coordinates> Coordinates::generatePlusCrossPositions(const Int max) const {
    std::set<Coordinates> result {};
    for (auto set : std::set<std::set<Coordinates>>{generatePlusPositions(max), generateCrossPositions(max)}) result.merge(set);

    return result;
}

