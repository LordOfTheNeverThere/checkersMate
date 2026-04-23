#ifndef CHECKERSMATE_CHECKERSMATEHEADER_H
#define CHECKERSMATE_CHECKERSMATEHEADER_H
#include <cstdint>
#include <stdexcept>
#include <vector>

#include "ChessPieceSegment.h"
#include "checkersMate/Board.h"


class WrongChessBoardHeaderFormatException : public std::runtime_error {
public:
    WrongChessBoardHeaderFormatException() : std::runtime_error("The format of the buffer passed is incoherent with the ChessBoardHeader Class") {}
};


class ChessBoardSegment {
    uint8_t m_numOfPieces;
    std::vector<ChessPieceSegment> m_pieceSegments;

public:
    ChessBoardSegment(std::vector<uint8_t>& buffer){
        unpackData(buffer);
    }

    ChessBoardSegment(const Board& board){
        createFromCurrentBoard(board);
    }

    //TODO: Create this Data structure from the current board so that it might be packed and sent over the wire
    void createFromCurrentBoard(const Board& buffer) {

    }

    void unpackData(std::vector<uint8_t>& buffer) {
        if (buffer.size() % 2 == 0) throw WrongChessBoardHeaderFormatException(); // Size must be odd otherwise the message received might have been corruped

        m_pieceSegments.clear();
        for (int index = 0; index < buffer.size(); ++index) {
            if (index == 0) {
                setNumOfPieces(buffer.at(index));
                if (m_numOfPieces != (buffer.size() - 1) / 2) {
                    throw WrongChessBoardHeaderFormatException();
                }
                m_pieceSegments.reserve(m_numOfPieces);
            } else {
                m_pieceSegments.emplace_back(static_cast<char>(buffer.at(index)), buffer.at(index + 1));
                ++index;
            }
        }
    }

    std::vector<uint8_t> packData () const {
        std::vector<uint8_t> result {};
        result.push_back(m_pieceSegments.size());
        for (auto pieceHeader: m_pieceSegments) {
            result.push_back(static_cast<uint8_t>(pieceHeader.getPieceChar()));
            result.push_back(pieceHeader.getPosition1D());
        }
        return result;
    }

    uint8_t getNumOfPieces() const {
        return m_numOfPieces;
    }

    void setNumOfPieces(const uint8_t numOfPieces) {
        m_numOfPieces = numOfPieces;
    }

    std::vector<ChessPieceSegment> getPieceSegments() const {
        return m_pieceSegments;
    }

    void setPieceSegments(const std::vector<ChessPieceSegment> &pieceSegments) {
        m_pieceSegments = pieceSegments;
    }

} __attribute__((packed));

inline bool operator==(const ChessBoardSegment& lhs, const ChessBoardSegment& rhs) {
    if (lhs.getNumOfPieces()!=rhs.getNumOfPieces()) {
        return false;
    } else {
        for (int i = 0; i < lhs.getNumOfPieces(); ++i) {
            if (lhs.getPieceSegments().at(i) != rhs.getPieceSegments().at(i)) {
                return false;
            }
        }
    }
    return true;
}


#endif //CHECKERSMATE_CHECKERSMATEHEADER_H