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

Board::Board(bool anotherOne) {
    PieceColour white = PieceColour::white;
    PieceColour black = PieceColour::black;
    Int specialWhiteRow = 0;
    Int pawnWhiteRow = specialWhiteRow +1;
    Int specialBlackRow = 7;
    Int pawnBlackRow = specialBlackRow - 1;

    for (int i = 0; i < 8; ++i) {
        auto pawnPtr = std::make_unique<Pawn>(i,pawnWhiteRow,this, white);
        m_piecesV2[white][PieceType::pawn][pawnPtr->getCoordinatesPtr()] = std::move(pawnPtr);
        pawnPtr = std::make_unique<Pawn>(i,pawnBlackRow,this, black);
        m_piecesV2[black][PieceType::pawn][pawnPtr->getCoordinatesPtr()] = std::move(pawnPtr);

        if (i == 0 || i == 7) {
            auto towerPtr = std::make_unique<Tower>(i, specialWhiteRow,this, white);
            m_piecesV2[white][PieceType::tower][towerPtr->getCoordinatesPtr()] = std::move(towerPtr);
            towerPtr = std::make_unique<Tower>(i, specialBlackRow,this, black);
            m_piecesV2[black][PieceType::tower][towerPtr->getCoordinatesPtr()] = std::move(towerPtr);
        } else if (i==1 || i==6) {
            auto horsePtr = std::make_unique<Horse>(i, specialWhiteRow,this, white);
            m_piecesV2[white][PieceType::horse][horsePtr->getCoordinatesPtr()] = std::move(horsePtr);
            horsePtr = std::make_unique<Horse>(i, specialBlackRow,this, black);
            m_piecesV2[black][PieceType::horse][horsePtr->getCoordinatesPtr()] = std::move(horsePtr);
        } else if (i==2 || i==5) {
            auto bishopPtr = std::make_unique<Bishop>(i, specialWhiteRow,this, white);
            m_piecesV2[white][PieceType::bishop][bishopPtr->getCoordinatesPtr()] = std::move(bishopPtr);
            bishopPtr = std::make_unique<Bishop>(i, specialBlackRow,this, black);
            m_piecesV2[black][PieceType::bishop][bishopPtr->getCoordinatesPtr()] = std::move(bishopPtr);
        } else if (i==3) {
            auto queenPtr = std::make_unique<Queen>(i,specialWhiteRow,this, white);
            m_piecesV2[white][PieceType::queen][queenPtr->getCoordinatesPtr()] = std::move(queenPtr);
            queenPtr = std::make_unique<Queen>(i,specialBlackRow,this, black);
            m_piecesV2[black][PieceType::queen][queenPtr->getCoordinatesPtr()] = std::move(queenPtr);
        } else if (i==4) {
            auto kingPtr = std::make_unique<King>(i,specialWhiteRow,this, white);
            m_piecesV2[white][PieceType::king][kingPtr->getCoordinatesPtr()] = std::move(kingPtr);
            kingPtr = std::make_unique<King>(i,specialBlackRow,this, black);
            m_piecesV2[black][PieceType::king][kingPtr->getCoordinatesPtr()] = std::move(kingPtr);
        }

    }
}


//
// Piece Board::pieceAtCoordinates(const Coordinates newCoords) const {
//     Piece pieceAtPlace {};
//
//     for (const auto& piece: m_pieces) {
//         if (piece && piece->getCoordinates() == newCoords) {
//             pieceAtPlace = *piece;
//         }
//     }
//
//     return pieceAtPlace;
// }

std::set<Piece *> Board::generalFilter(const PieceType& type, const PieceColour& colour, const Coordinates* coords) {
    std::set<Piece *> result {};
    if (colour != PieceColour::empty && type != PieceType::empty) {
        for (auto ite = m_piecesV2[colour][type].begin(); ite != m_piecesV2[colour][type].end(); ++ite) {
            if (coords == nullptr || (*(ite->first) == *coords) ) {
                result.insert(ite->second.get());
            }
        }
    } else if (colour != PieceColour::empty) {
        for (auto typeIterator = m_piecesV2[colour].begin(); typeIterator != m_piecesV2[colour].end(); ++typeIterator) {
            for (auto pieceIterator = typeIterator->second.begin(); pieceIterator != typeIterator->second.end(); ++pieceIterator) {
                if (coords == nullptr || (*(pieceIterator->first) == *coords) ) {
                    result.insert(pieceIterator->second.get());
                }
            }
        }
    } else if (type != PieceType::empty) {
        for (auto colourIterator=m_piecesV2.begin(); colourIterator != m_piecesV2.end(); ++colourIterator) {
            for (auto typeIterator=colourIterator->second.begin(); typeIterator != colourIterator->second.end(); ++typeIterator) {
                if (typeIterator->first == type) {
                    auto pieceIterator = typeIterator->second.begin();
                    if (coords == nullptr || (*(pieceIterator->first) == *coords) ) {
                        result.insert(pieceIterator->second.get());
                    }
                }
            }
        }
    }
    return result;
}

Piece* Board::piecePtrAtCoordinates(const Coordinates newCoords) const { // TODO: Redo for new m_pieces
    Piece* pieceAtPlace {};

    for (const auto& piece: m_pieces) {
        if (piece && piece->getCoordinates() == newCoords) {
            pieceAtPlace = piece.get();
        }
    }

    return pieceAtPlace;
}

void Board::emptyTheBoard(std::set<Piece*> piecesToKeep = {}) { // TODO: Redo for new m_pieces
    for (auto& piece: m_pieces) {
        if (piecesToKeep.find(piece.get()) == piecesToKeep.end()) {
            piece.reset();
        }
    }
}

std::set<Piece*> Board::queryPieces(const PieceType& type, const PieceColour& colour) { // TODO: Redo for new m_pieces
    std::set<Piece*> pieces {};
    for (const auto& piece : m_pieces) {
        if ((type == PieceType::empty || piece->getType() == type)
            && ( colour == PieceColour::empty || piece->getColour() == colour)) {
            pieces.insert(piece.get());
        }
    }
    return  pieces;
}

bool Board::isSquareFree(const Coordinates newCoords) const { // TODO: Redo for new m_pieces
    return !piecePtrAtCoordinates(newCoords);
}

// bool Board::isKingChecked(const PieceColour& colour) {
//
//     const std::set<Piece*> piecesThatAreKingOfSameColour {queryPieces(PieceType::king, colour)};
//     if (piecesThatAreKingOfSameColour.size() == 0) {
//         throw TheKingIsDeadException();
//     }
//     Piece* kingPtr = *piecesThatAreKingOfSameColour.begin();
//     Coordinates kingCurrentPosition {kingPtr->getCoordinates()};
//
// }

// A function that trims possible moves that might place you in check
// std::vector<Coordinates> Board::checkChecker(std::vector<Coordinates>& moves, Piece* piecePtr) {
//
//     Piece* kingPtr {};
//     // Populate pointer
//     if (piecePtr->getType() == PieceType::king) {
//         kingPtr = piecePtr;
//     } else {
//         const std::set<Piece*> piecesThatAreKingOfSameColour {queryPieces(PieceType::king, piecePtr->getColour())};
//         if (piecesThatAreKingOfSameColour.size() == 0) {
//             throw TheKingIsDeadException();
//         }
//         kingPtr = *piecesThatAreKingOfSameColour.begin();
//     }
//     std::set<Piece *> enemyPieces {queryPieces(PieceType::empty, !kingPtr->getColour())};
//     if (enemyPieces.size() == 0) {
//         throw TheKingIsDeadException();
//     }
//
//     Coordinates currentCoordinates {piecePtr->getCoordinates()};
//     for (auto& move: moves) {
//         piecePtr->setCoordinates(move); // Mock move
//         bool inCheck {false};
//         for (auto& enemyPiece: enemyPieces) { // Check if king is in check
//             if (enemyPiece->getCoordinates() == move) continue; // This piece has been hypothetically captured
//             auto enemyMoves {enemyPiece->possibleMoves(piecePtr)};
//             for (auto enemyMove: enemyMoves) {
//                 if (enemyMove == kingPtr->getCoordinates()) {
//                     inCheck = true;
//                     break;
//                 }
//             }
//             if (inCheck) break;
//         }
//         if (inCheck) {
//             // remove
//         }
//
//     }
//     piecePtr->setCoordinates(currentCoordinates); // Undo mock moves
//
//     return moves;
// }
