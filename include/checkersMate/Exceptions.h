
#ifndef CHECKERSMATE_EXCEPTIONS_H
#define CHECKERSMATE_EXCEPTIONS_H
#include "socks/Exceptions.h"

class OutOfBoardException : public ConfigException {
public:
    OutOfBoardException(uint8_t coord) : ConfigException("Error: The value of " + std::to_string(coord) + " is not correct for a 8x8 board") {}
};

#endif //CHECKERSMATE_EXCEPTIONS_H