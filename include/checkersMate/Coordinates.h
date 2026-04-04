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
        if (x < 0 || x > 8) {
            throw OutOfBoardException(x);
        }
        m_x = x;
    }

    [[nodiscard]] uint8_t getY() const {
        return m_y;
    }

    void setY(const Int y) {
        if (y < 0 || y > 8) {
            throw OutOfBoardException(y);
        }
        m_y = y;
    }
};

#endif //CHECKERSMATE_COORDINATES_H