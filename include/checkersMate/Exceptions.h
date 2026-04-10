
#ifndef CHECKERSMATE_EXCEPTIONS_H
#define CHECKERSMATE_EXCEPTIONS_H
#include "pieces/PieceType.h"
#include "socks/Exceptions.h"

class OutOfBoardException : public ConfigException {
public:
    OutOfBoardException(Int coord) : ConfigException("Error: The value of " + std::to_string(coord) + " is not correct for a 8x8 board") {}
};


class WrongPieceDynamicCast : public ConfigException {
public:
    WrongPieceDynamicCast(const PieceType &type) : ConfigException("The piece of type " + typeToString(type) + " is being cast into an incorrect piece.") {}
};

class TheKingIsDeadException : public ConfigException {
public:
    TheKingIsDeadException() : ConfigException("The game has reached an invalid state since a king is dead!") {}
};

#endif //CHECKERSMATE_EXCEPTIONS_H