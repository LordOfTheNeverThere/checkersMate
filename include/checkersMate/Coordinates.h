#ifndef CHECKERSMATE_COORDINATES_H
#define CHECKERSMATE_COORDINATES_H
#include <set>
#include <vector>

#include "Exceptions.h"
#include "pieces/PieceColour.h"

class Coordinates {

private:
    uint8_t m_x {};
    uint8_t m_y {};

public:

    Coordinates(const Int x, const Int y) {
        setX(x);
        setY(y);
    }

    [[nodiscard]] uint8_t getX() const {
        return m_x;
    }

    void setX(const Int x) {
        if (x < 0 || x > 7) {
            throw OutOfBoardException(x);
        }
        m_x = x;
    }

    [[nodiscard]] uint8_t getY() const {
        return m_y;
    }

    void setY(const Int y) {
        if (y < 0 || y > 7) {
            throw OutOfBoardException(y);
        }
        m_y = y;
    }

    uint8_t getIndexIn1D() const {
        return (m_y * 8) + m_x;
    }

    std::vector<Coordinates> generatePosYVec(Int max = 8) const;

    std::vector<Coordinates> generateNegYVec(Int max = 8) const;

    std::vector<Coordinates> generatePosXVec(Int max = 8) const;

    std::vector<Coordinates> generateNegXVec(Int max = 8) const;

    std::vector<Coordinates> generateNegXPosYVec(Int max = 8) const;

    std::vector<Coordinates> generatePosXPosYVec(Int max = 8) const;

    std::vector<Coordinates> generatePosXNegYVec(Int max = 8) const;

    std::vector<Coordinates> generateNegXNegYVec(Int max = 8) const;

    std::set<Coordinates> generateCircleSet(Int max = 1) const;

    std::set<Coordinates> generateEnemyPawnPositions(const PieceColour &friendlyColour) const;

    std::set<Coordinates> generateHorsePositions() const;

    std::set<Coordinates> generatePlusPositions(Int max = 8) const;

    std::set<Coordinates> generateCrossPositions(Int max = 8) const;

    std::set<Coordinates> generatePlusCrossPositions(Int max = 8) const;
};

inline bool operator==(const Coordinates& lhs, const Coordinates& rhs) {
    return (lhs.getX()==rhs.getX() && lhs.getY()==rhs.getY());
}

inline bool operator!=(const Coordinates& lhs, const Coordinates& rhs) {
    return !operator==(lhs,rhs);
}

inline bool operator<(const Coordinates& lhs, const Coordinates& rhs) {
    return lhs.getIndexIn1D() < rhs.getIndexIn1D();
}

inline bool operator>(const Coordinates& lhs, const Coordinates& rhs) {
    return lhs.getIndexIn1D() > rhs.getIndexIn1D();
}

inline Coordinates operator+(const Coordinates& lhs, const Coordinates& rhs) {

    return Coordinates {lhs.getX() + rhs.getX(), lhs.getY() + rhs.getY()};
}

inline Coordinates operator-(const Coordinates& lhs, const Coordinates& rhs) {

    return Coordinates {lhs.getX() - rhs.getX(), lhs.getY() - rhs.getY()};
}

#endif //CHECKERSMATE_COORDINATES_H