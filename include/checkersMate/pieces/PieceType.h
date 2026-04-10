
#ifndef CHECKERSMATE_PIECETYPE_H
#define CHECKERSMATE_PIECETYPE_H
#include <iosfwd>
#include <ostream>

enum class PieceType {
    empty,
    pawn,
    tower,
    horse,
    bishop,
    queen,
    king,
};

inline std::string typeToString(const PieceType& type) {

    switch (type) {
        case PieceType::king:  return "King";
        case PieceType::queen:  return "Queen";
        case PieceType::tower:   return "Tower";
        case PieceType::bishop: return "Bishop";
        case PieceType::horse: return "Horse";
        case PieceType::pawn: return "Pawn";
        default:                return "empty";
    }
}

inline std::ostream& operator<<(std::ostream& os, PieceType type) {

    return os << typeToString(type);
}
#endif //CHECKERSMATE_PIECETYPE_H