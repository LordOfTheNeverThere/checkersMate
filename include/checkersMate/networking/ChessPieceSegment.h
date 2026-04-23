
#ifndef CHECKERSMATE_CHESSPIECEHEADER_H
#define CHECKERSMATE_CHESSPIECEHEADER_H
#include <cstdint>


class ChessPieceSegment {
    char m_piece;
    uint8_t m_position1D;

public:

    ChessPieceSegment(char piece, uint8_t position1D) {
        setPieceChar(piece);
        setPosition1D(position1D);
    }

    char getPieceChar() const {
        return m_piece;
    }

    void setPieceChar(const char piece) {
        m_piece = piece;
    }

    uint8_t getPosition1D() const {
        return m_position1D;
    }

    void setPosition1D(const uint8_t position) {
        m_position1D = position;
    }
} __attribute__((packed));


inline bool operator==(const ChessPieceSegment& lhs, const ChessPieceSegment& rhs) {
    return (lhs.getPieceChar()==rhs.getPieceChar() && lhs.getPosition1D()==rhs.getPosition1D());
}

inline bool operator!=(const ChessPieceSegment& lhs, const ChessPieceSegment& rhs) {
    return !operator==(lhs, rhs);
}

#endif //CHECKERSMATE_CHESSPIECEHEADER_H