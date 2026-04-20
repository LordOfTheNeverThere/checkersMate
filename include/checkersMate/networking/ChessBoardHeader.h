#ifndef CHECKERSMATE_CHECKERSMATEHEADER_H
#define CHECKERSMATE_CHECKERSMATEHEADER_H
#include <cstdint>
#include <stdexcept>
#include <vector>

#include "ChessPieceHeader.h"



class WrongChessBoardHeaderFormatException : public std::runtime_error {
public:
    WrongChessBoardHeaderFormatException() : std::runtime_error("The format of the buffer passed is incoherent with the ChessBoardHeader Class") {}
};


class ChessBoardHeader {
    uint8_t m_numOfPieces;
    std::vector<ChessPieceHeader> m_pieceHeaders;

public:
    ChessBoardHeader(std::vector<uint8_t>& buffer){
        unpackData(buffer);

    }

    void unpackData(std::vector<uint8_t>& buffer) {
        if (buffer.size() % 2 == 0) throw WrongChessBoardHeaderFormatException(); // Size must be odd otherwise the message received might have been corruped

        m_pieceHeaders.clear();
        for (int index = 0; index < buffer.size(); ++index) {
            if (index == 0) {
                setNumOfPieces(buffer.at(index));
                if (m_numOfPieces != (buffer.size() - 1) / 2) {
                    throw WrongChessBoardHeaderFormatException();
                }
                m_pieceHeaders.reserve(m_numOfPieces);
            } else {
                m_pieceHeaders.emplace_back(static_cast<char>(buffer.at(index)), buffer.at(index + 1));
                ++index;
            }
        }
    }

    std::vector<uint8_t> packData () const {
        std::vector<uint8_t> result {};
        result.push_back(m_pieceHeaders.size());
        for (auto pieceHeader: m_pieceHeaders) {
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

    std::vector<ChessPieceHeader> getPieceHeaders() const {
        return m_pieceHeaders;
    }

    void setPieceHeaders(const std::vector<ChessPieceHeader> &pieceHeaders) {
        m_pieceHeaders = pieceHeaders;
    }

} __attribute__((packed));

inline bool operator==(const ChessBoardHeader& lhs, const ChessBoardHeader& rhs) {
    if (lhs.getNumOfPieces()!=rhs.getNumOfPieces()) {
        return false;
    } else {
        for (int i = 0; i < lhs.getNumOfPieces(); ++i) {
            if (lhs.getPieceHeaders().at(i) != rhs.getPieceHeaders().at(i)) {
                return false;
            }
        }
    }
    return true;
}


#endif //CHECKERSMATE_CHECKERSMATEHEADER_H