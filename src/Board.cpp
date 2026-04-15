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

    for (int i = 0; i < 8; ++i) {
        auto pawnPtr = std::make_unique<Pawn>(i,pawnWhiteRow,this, white);
        m_pieces[white][PieceType::pawn][pawnPtr->getCoordinatesPtr()] = std::move(pawnPtr);
        pawnPtr = std::make_unique<Pawn>(i,pawnBlackRow,this, black);
        m_pieces[black][PieceType::pawn][pawnPtr->getCoordinatesPtr()] = std::move(pawnPtr);

        if (i == 0 || i == 7) {
            auto towerPtr = std::make_unique<Tower>(i, specialWhiteRow,this, white);
            m_pieces[white][PieceType::tower][towerPtr->getCoordinatesPtr()] = std::move(towerPtr);
            towerPtr = std::make_unique<Tower>(i, specialBlackRow,this, black);
            m_pieces[black][PieceType::tower][towerPtr->getCoordinatesPtr()] = std::move(towerPtr);
        } else if (i==1 || i==6) {
            auto horsePtr = std::make_unique<Horse>(i, specialWhiteRow,this, white);
            m_pieces[white][PieceType::horse][horsePtr->getCoordinatesPtr()] = std::move(horsePtr);
            horsePtr = std::make_unique<Horse>(i, specialBlackRow,this, black);
            m_pieces[black][PieceType::horse][horsePtr->getCoordinatesPtr()] = std::move(horsePtr);
        } else if (i==2 || i==5) {
            auto bishopPtr = std::make_unique<Bishop>(i, specialWhiteRow,this, white);
            m_pieces[white][PieceType::bishop][bishopPtr->getCoordinatesPtr()] = std::move(bishopPtr);
            bishopPtr = std::make_unique<Bishop>(i, specialBlackRow,this, black);
            m_pieces[black][PieceType::bishop][bishopPtr->getCoordinatesPtr()] = std::move(bishopPtr);
        } else if (i==3) {
            auto queenPtr = std::make_unique<Queen>(i,specialWhiteRow,this, white);
            m_pieces[white][PieceType::queen][queenPtr->getCoordinatesPtr()] = std::move(queenPtr);
            queenPtr = std::make_unique<Queen>(i,specialBlackRow,this, black);
            m_pieces[black][PieceType::queen][queenPtr->getCoordinatesPtr()] = std::move(queenPtr);
        } else if (i==4) {
            auto kingPtr = std::make_unique<King>(i,specialWhiteRow,this, white);
            m_pieces[white][PieceType::king][kingPtr->getCoordinatesPtr()] = std::move(kingPtr);
            kingPtr = std::make_unique<King>(i,specialBlackRow,this, black);
            m_pieces[black][PieceType::king][kingPtr->getCoordinatesPtr()] = std::move(kingPtr);
        }

    }
}

std::set<Piece *> Board::generalFilter(const PieceType& type, const PieceColour& colour, const Coordinates* coords) const {
    std::set<Piece *> result {};

    if (coords != nullptr ) {
        for (auto colourIterator=m_pieces.begin(); colourIterator != m_pieces.end(); ++colourIterator) {
            for (auto typeIterator=colourIterator->second.begin(); typeIterator != colourIterator->second.end(); ++typeIterator) {
                for (auto pieceIterator = typeIterator->second.begin(); pieceIterator != typeIterator->second.end(); ++ pieceIterator) {
                    if ((*(pieceIterator->first) == *coords) ) {
                        result.insert(pieceIterator->second.get());
                        return result;
                    }
                }
            }
        }
    } else if (colour != PieceColour::empty && type != PieceType::empty) {
        for (auto ite = m_pieces.at(colour).at(type).begin(); ite != m_pieces.at(colour).at(type).end(); ++ite) {
                result.insert(ite->second.get());
        }
    } else if (colour != PieceColour::empty) {
        for (auto typeIterator = m_pieces.at(colour).begin(); typeIterator != m_pieces.at(colour).end(); ++typeIterator) {
            for (auto pieceIterator = typeIterator->second.begin(); pieceIterator != typeIterator->second.end(); ++pieceIterator) {
                result.insert(pieceIterator->second.get());
            }
        }
    } else if (type != PieceType::empty) {
        for (auto colourIterator=m_pieces.begin(); colourIterator != m_pieces.end(); ++colourIterator) {
            for (auto typeIterator=colourIterator->second.begin(); typeIterator != colourIterator->second.end(); ++typeIterator) {
                if (typeIterator->first == type) {
                    result.insert(typeIterator->second.begin()->second.get());
                }
            }
        }
    }
    return result;
}

Piece* Board::piecePtrAtCoordinates(const Coordinates newCoords) const {
    std::set<Piece *> pieces {generalFilter(PieceType::empty, PieceColour::empty, &newCoords)};
    if (pieces.empty()) {
        return nullptr;
    } else {
        return *pieces.begin();
    }
}

Piece* Board::piecePtrAtCoordinates(const Int x, const Int y) const {
    Coordinates newCoords {0,0};
    try {
        newCoords.setX(x);
        newCoords.setY(y);
    } catch (OutOfBoardException& e) {
        return nullptr;
    }
    std::set<Piece *> pieces {generalFilter(PieceType::empty, PieceColour::empty, &newCoords)};
    if (pieces.empty()) {
        return nullptr;
    } else {
        return *pieces.begin();
    }
}

void Board::emptyTheBoard(std::set<Piece*> piecesToKeep) {
    auto colourIterator=m_pieces.begin();
    while (colourIterator != m_pieces.end()) {
        auto typeIterator=colourIterator->second.begin();
        while (typeIterator != colourIterator->second.end()) {
            auto pieceIterator = typeIterator->second.begin();
            while (pieceIterator != typeIterator->second.end()) {
                if (piecesToKeep.find(pieceIterator->second.get()) == piecesToKeep.end()) {
                    pieceIterator = typeIterator->second.erase(pieceIterator);
                } else ++pieceIterator;
            }
            if (typeIterator->second.empty()) {
                typeIterator = colourIterator->second.erase(typeIterator);
            } else ++typeIterator;
        }
        if (colourIterator->second.empty()) {
            colourIterator = m_pieces.erase(colourIterator);
        } else ++colourIterator;
    }
}

bool Board::isSquareFree(const Coordinates newCoords) const {
    return !piecePtrAtCoordinates(newCoords);
}

bool Board::isKingChecked(const PieceColour& colour) const {
    const std::set<Piece*> piecesThatAreKingOfSameColour {generalFilter(PieceType::king, colour)};
    if (piecesThatAreKingOfSameColour.size() == 0) {
        throw TheKingIsDeadException();
    }
    Piece* kingPtr = *piecesThatAreKingOfSameColour.begin();
    Coordinates kingCurrentPosition {kingPtr->getCoordinates()};

    //Checked by Horse
    for (auto coord: kingCurrentPosition.generateHorsePositions()) {
        Piece* possibleHorse {piecePtrAtCoordinates(coord)};
        if (possibleHorse && possibleHorse->getType() == PieceType::horse && possibleHorse->getColour() == !colour) {
            return true;
        }
    }

    // Checked by Towers/Queen
    for (auto vector : std::set<std::vector<Coordinates>>{kingCurrentPosition.generatePosYVec(), kingCurrentPosition.generateNegYVec(),
        kingCurrentPosition.generatePosXVec(), kingCurrentPosition.generateNegXVec()}) {
        for (auto coord : vector) {
            Piece * otherPiece {piecePtrAtCoordinates(coord)};
            if (otherPiece) {
                if (otherPiece->getColour() == !colour && (otherPiece->getType() == PieceType::queen || otherPiece->getType() == PieceType::tower)) {
                    return true;
                } else {
                    break;
                }
            }
        }
    }

    // Checked by Bishop/Queen
    for (auto vector : std::set<std::vector<Coordinates>>{kingCurrentPosition.generateNegXPosYVec(), kingCurrentPosition.generatePosXPosYVec(),
    kingCurrentPosition.generatePosXNegYVec(), kingCurrentPosition.generateNegXNegYVec()}) {
        for (auto coord : vector) {
            Piece * otherPiece {piecePtrAtCoordinates(coord)};
            if (otherPiece) {
                if (otherPiece->getColour() == !colour && (otherPiece->getType() == PieceType::queen || otherPiece->getType() == PieceType::bishop)) {
                    return true;
                } else {
                    break;
                }
            }
        }
    }

    //Checked by King
    for (auto coord: kingCurrentPosition.generateCircleSet(1)) {
        Piece* possibleKing {piecePtrAtCoordinates(coord)};
        if (possibleKing && possibleKing->getType() == PieceType::king && possibleKing->getColour() == !colour) {
            return true;
        }
    }

    //Checked by pawns
    for (auto coord: kingCurrentPosition.generateEnemyPawnPositions(colour)) {
        Piece* possiblePawn {piecePtrAtCoordinates(coord)};
        if (possiblePawn && possiblePawn->getType() == PieceType::pawn && possiblePawn->getColour() == !colour) {
            return true;
        }
    }
    return false;
}

// A function that trims possible moves that might place you in check
void Board::checkChecker(std::set<Coordinates> &moves, Piece *piecePtr) {
    Coordinates currCoordsPiece {piecePtr->getCoordinates()};

    auto movIte = moves.begin();
    while (movIte != moves.end()) {
        piecePtr->setCoordinates(*movIte);
        if (isKingChecked(piecePtr->getColour())) {
            movIte = moves.erase(movIte);
        } else {
            ++movIte;
        }
    }

    piecePtr->setCoordinates(currCoordsPiece);
}
