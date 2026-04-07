#ifndef CHECKERSMATE_COORDINATES_H
#define CHECKERSMATE_COORDINATES_H
#include "Exceptions.h"

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
};

inline bool operator==(const Coordinates& lhs, const Coordinates& rhs) {
    return (lhs.getX()==rhs.getX() && lhs.getY()==rhs.getY());
}

inline bool operator<(const Coordinates& lhs, const Coordinates& rhs) {
    return lhs.getIndexIn1D() < rhs.getIndexIn1D();
}

inline bool operator>(const Coordinates& lhs, const Coordinates& rhs) {
    return lhs.getIndexIn1D() > rhs.getIndexIn1D();
}

#endif //CHECKERSMATE_COORDINATES_H