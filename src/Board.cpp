#include "checkersMate/Board.h"
#include "checkersMate/pieces/Bishop.h"
#include "checkersMate/pieces/Horse.h"
#include "checkersMate/pieces/King.h"
#include "checkersMate/pieces/Pawn.h"
#include "checkersMate/pieces/Queen.h"
#include "checkersMate/pieces/Tower.h"

Board::Board() {
    PieceColour white = PieceColour::white;
    PieceColour black = PieceColour::black;
    Int specialWhiteRow = 0;
    Int pawnWhiteRow = specialWhiteRow +1;
    Int specialBlackRow = 7;
    Int pawnBlackRow = specialBlackRow - 1;
    for (int i = 0; i < 8; i++) {
        m_pieces.at(i + 8) = std::make_unique<Pawn>(i,pawnWhiteRow,this, white);
        m_pieces.at(i + 16) = std::make_unique<Pawn>(i,pawnBlackRow,this, black);
        if (i == 0 || i == 7) {
            m_pieces.at(i) = std::make_unique<Tower>(i, specialWhiteRow,this, white);
            m_pieces.at(i + 24) = std::make_unique<Tower>(i, specialBlackRow,this, black);
        } else if (i==1 || i==6) {
            m_pieces.at(i) = std::make_unique<Horse>(i, specialWhiteRow,this, white);
            m_pieces.at(i + 24) = std::make_unique<Horse>(i, specialBlackRow,this, black);
        } else if (i==2 || i==5) {
            m_pieces.at(i) = std::make_unique<Bishop>(i, specialWhiteRow,this, white);
            m_pieces.at(i + 24) = std::make_unique<Bishop>(i, specialBlackRow,this, black);
        } else if (i==3) {
            m_pieces.at(i) = std::make_unique<Queen>(i,specialWhiteRow,this, white);
            m_pieces.at(i + 24) = std::make_unique<Queen>(i,specialBlackRow,this, black);
        } else if (i==4) {
            m_pieces.at(i) = std::make_unique<King>(i,specialWhiteRow,this, white);
            m_pieces.at(i + 24) = std::make_unique<King>(i,specialBlackRow,this, black);
        }
    }
}

Piece Board::pieceAtCoordinates(const Coordinates newCoords) const {
    Piece pieceAtPlace {};

    for (const auto& piece: m_pieces) {
        if (piece->getCoordinates() == newCoords) {
            pieceAtPlace = *piece;
        }
    }

    return pieceAtPlace;
}

bool Board::isSquareFree(const Coordinates newCoords) const {
    return pieceAtCoordinates(newCoords) == Piece();;
}

