#include "checkersMate/Board.h"

#include "checkersMate/ChessTools.h"
#include "gtest/gtest.h"



TEST(MethodChecking, BoardConstructor) {
    Board theBoard {};

    Int nullPtrs {0};
    Piece whiteKing {};
    Piece whiteQueen {};
    Piece blackKing {};
    Piece blackQueen {};

    // White Piece Groups
    std::vector<Piece> whiteTowers;
    std::vector<Piece> whiteBishops;
    std::vector<Piece> whiteHorses;
    std::vector<Piece> whitePawns;

    // Black Piece Groups
    std::vector<Piece> blackTowers;
    std::vector<Piece> blackBishops;
    std::vector<Piece> blackHorses;
    std::vector<Piece> blackPawns;

    for (int i = 0; i < theBoard.m_pieces.size(); i++ ) {
        if (!theBoard.m_pieces.at(i)) {
            nullPtrs++;
        }
        EXPECT_EQ(0, theBoard.m_pieces.at(i)->m_NumOfMoves);
        Piece piece {*theBoard.m_pieces.at(i)};
        if (piece.getType()==PieceType::pawn) {
            if (piece.getColour() == PieceColour::white) {
                whitePawns.push_back(piece);
            } else if (piece.getColour() == PieceColour::black) {
                blackPawns.push_back(piece);
            }
        } else if (piece.getType()==PieceType::tower) {
            if (piece.getColour() == PieceColour::white) {
                whiteTowers.push_back(piece);
            } else if (piece.getColour() == PieceColour::black) {
                blackTowers.push_back(piece);
            }
        } else if (piece.getType()==PieceType::horse) {
            if (piece.getColour() == PieceColour::white) {
                whiteHorses.push_back(piece);
            } else if (piece.getColour() == PieceColour::black) {
                blackHorses.push_back(piece);
            }
        } else if (piece.getType()==PieceType::bishop) {
            if (piece.getColour() == PieceColour::white) {
                whiteBishops.push_back(piece);
            } else if (piece.getColour() == PieceColour::black) {
                blackBishops.push_back(piece);
            }
        } else if (piece.getType()==PieceType::queen) {
            if (piece.getColour() == PieceColour::white) {
                whiteQueen = piece;
            } else if (piece.getColour() == PieceColour::black) {
                blackQueen = piece;
            }
        } else if (piece.getType()==PieceType::king) {
            if (piece.getColour() == PieceColour::white) {
                whiteKing = piece;
            } else if (piece.getColour() == PieceColour::black) {
                blackKing = piece;
            }
        }
    }

    EXPECT_EQ(0, nullPtrs);
    EXPECT_EQ(blackPawns.size(), 8); EXPECT_EQ(whitePawns.size(), 8);
    EXPECT_EQ(whiteTowers.size(), 2);EXPECT_EQ(whiteBishops.size(), 2);EXPECT_EQ(whiteHorses.size(), 2);
    EXPECT_EQ(blackTowers.size(), 2);EXPECT_EQ(blackBishops.size(), 2);EXPECT_EQ(blackHorses.size(), 2);
    EXPECT_NE(whiteKing.getCurrentBoard(), nullptr); EXPECT_NE(whiteQueen.getCurrentBoard(),nullptr);
    EXPECT_NE(blackKing.getCurrentBoard(), nullptr); EXPECT_NE(blackQueen.getCurrentBoard(),nullptr);

    EXPECT_EQ(whiteQueen.getCoordinates(), Coordinates(3,0)); EXPECT_EQ(whiteKing.getCoordinates(), Coordinates(4,0));
    EXPECT_EQ(blackQueen.getCoordinates(), Coordinates(3,7)); EXPECT_EQ(blackKing.getCoordinates(), Coordinates(4,7));

    std::set<Coordinates> whitePawnsCoords {ChessTools::getCoordinatesSet(whitePawns)};
    for (int i = 0; i < 8; ++i) {
        EXPECT_TRUE(whitePawnsCoords.find(Coordinates{i, 1}) != whitePawnsCoords.end());
    }
    std::set<Coordinates> blackPawnsCoords {ChessTools::getCoordinatesSet(blackPawns)};
    for (int i = 0; i < 8; ++i) {
        EXPECT_TRUE(blackPawnsCoords.find(Coordinates{i, 6}) != blackPawnsCoords.end());
    }
    std::set<Coordinates> whiteTowersCoords {ChessTools::getCoordinatesSet(whiteTowers)};
    EXPECT_TRUE(whiteTowersCoords.find(Coordinates{0, 0}) != whiteTowersCoords.end());
    EXPECT_TRUE(whiteTowersCoords.find(Coordinates{7, 0}) != whiteTowersCoords.end());
    std::set<Coordinates> blackTowersCoords {ChessTools::getCoordinatesSet(blackTowers)};
    EXPECT_TRUE(blackTowersCoords.find(Coordinates{0, 7}) != blackTowersCoords.end());
    EXPECT_TRUE(blackTowersCoords.find(Coordinates{7, 7}) != blackTowersCoords.end());

    std::set<Coordinates> whiteHorsesCoords {ChessTools::getCoordinatesSet(whiteHorses)};
    EXPECT_TRUE(whiteHorsesCoords.find(Coordinates{1, 0}) != whiteHorsesCoords.end());
    EXPECT_TRUE(whiteHorsesCoords.find(Coordinates{6, 0}) != whiteHorsesCoords.end());
    std::set<Coordinates> blackHorsesCoords {ChessTools::getCoordinatesSet(blackHorses)};
    EXPECT_TRUE(blackHorsesCoords.find(Coordinates{1, 7}) != blackHorsesCoords.end());
    EXPECT_TRUE(blackHorsesCoords.find(Coordinates{6, 7}) != blackHorsesCoords.end());

    std::set<Coordinates> whiteBishopsCoords {ChessTools::getCoordinatesSet(whiteBishops)};
    EXPECT_TRUE(whiteBishopsCoords.find(Coordinates{2, 0}) != whiteBishopsCoords.end());
    EXPECT_TRUE(whiteBishopsCoords.find(Coordinates{5, 0}) != whiteBishopsCoords.end());
    std::set<Coordinates> blackBishopsCoords {ChessTools::getCoordinatesSet(blackBishops)};
    EXPECT_TRUE(blackBishopsCoords.find(Coordinates{2, 7}) != blackBishopsCoords.end());
    EXPECT_TRUE(blackBishopsCoords.find(Coordinates{5, 7}) != blackBishopsCoords.end());
}

TEST(MethodChecking, pieceAtCoordinates) {
    Board theBoard {};

    for (Int row = 6; row < 8; row++) {
        for (int col = 0; col < 8; col++) {
            Piece somePiece {theBoard.pieceAtCoordinates(Coordinates(col, row))};
            EXPECT_TRUE(somePiece.getColour() == PieceColour::black);
            if (row == 6) {
                EXPECT_TRUE(somePiece.getType() == PieceType::pawn);
            } else {
                if (col == 0 || col == 7) {
                    EXPECT_TRUE(somePiece.getType() == PieceType::tower);
                } else if (col == 1 || col == 6) {
                    EXPECT_TRUE(somePiece.getType() == PieceType::horse);
                } else if (col == 2 || col == 5) {
                    EXPECT_TRUE(somePiece.getType() == PieceType::bishop);
                } else if (col == 3) {
                    EXPECT_TRUE(somePiece.getType() == PieceType::queen);
                } else if (col == 4) {
                    EXPECT_TRUE(somePiece.getType() == PieceType::king);
                }
            }
        }
    }

    for (Int row = 0; row < 2; row++) {
        for (int col = 0; col < 8; col++) {
            Piece somePiece {theBoard.pieceAtCoordinates(Coordinates(col, row))};
            EXPECT_TRUE(somePiece.getColour() == PieceColour::white);
            if (row == 1) {
                EXPECT_TRUE(somePiece.getType() == PieceType::pawn);
            } else {
                if (col == 0 || col == 7) {
                    EXPECT_TRUE(somePiece.getType() == PieceType::tower);
                } else if (col == 1 || col == 6) {
                    EXPECT_TRUE(somePiece.getType() == PieceType::horse);
                } else if (col == 2 || col == 5) {
                    EXPECT_TRUE(somePiece.getType() == PieceType::bishop);
                } else if (col == 3) {
                    EXPECT_TRUE(somePiece.getType() == PieceType::queen);
                } else if (col == 4) {
                    EXPECT_TRUE(somePiece.getType() == PieceType::king);
                }
            }
        }
    }
}

TEST(MethodChecking, piecePtrAtCoordinates) {
    Board theBoard {};

    for (Int row = 6; row < 8; row++) {
        for (int col = 0; col < 8; col++) {
            Piece* somePiece {theBoard.piecePtrAtCoordinates(Coordinates(col, row))};
            EXPECT_TRUE(somePiece);
            EXPECT_TRUE(somePiece->getColour() == PieceColour::black);
            if (row == 6) {
                EXPECT_TRUE(somePiece->getType() == PieceType::pawn);
            } else {
                if (col == 0 || col == 7) {
                    EXPECT_TRUE(somePiece->getType() == PieceType::tower);
                } else if (col == 1 || col == 6) {
                    EXPECT_TRUE(somePiece->getType() == PieceType::horse);
                } else if (col == 2 || col == 5) {
                    EXPECT_TRUE(somePiece->getType() == PieceType::bishop);
                } else if (col == 3) {
                    EXPECT_TRUE(somePiece->getType() == PieceType::queen);
                } else if (col == 4) {
                    EXPECT_TRUE(somePiece->getType() == PieceType::king);
                }
            }
        }
    }

    for (Int row = 0; row < 2; row++) {
        for (int col = 0; col < 8; col++) {
            Piece* somePiece {theBoard.piecePtrAtCoordinates(Coordinates(col, row))};
            EXPECT_TRUE(somePiece->getColour() == PieceColour::white);
            if (row == 1) {
                EXPECT_TRUE(somePiece->getType() == PieceType::pawn);
            } else {
                if (col == 0 || col == 7) {
                    EXPECT_TRUE(somePiece->getType() == PieceType::tower);
                } else if (col == 1 || col == 6) {
                    EXPECT_TRUE(somePiece->getType() == PieceType::horse);
                } else if (col == 2 || col == 5) {
                    EXPECT_TRUE(somePiece->getType() == PieceType::bishop);
                } else if (col == 3) {
                    EXPECT_TRUE(somePiece->getType() == PieceType::queen);
                } else if (col == 4) {
                    EXPECT_TRUE(somePiece->getType() == PieceType::king);
                }
            }
        }
    }
}


TEST(MethodChecking, isSquareFree) {
    Board theBoard {};
    for (Int row = 2; row < 6; row++) {
        for (int col = 0; col < 8; col++) {
            Piece somePiece {theBoard.pieceAtCoordinates(Coordinates(col, row))};
            EXPECT_EQ(somePiece, Piece());
            EXPECT_EQ(somePiece.getType(), PieceType::empty);
            EXPECT_EQ(somePiece.getColour(), PieceColour::empty);
            EXPECT_TRUE(theBoard.isSquareFree(Coordinates(col, row)));
        }
    }
}

TEST(MethodChecking, isSquareFreePtr) {
    Board theBoard {};
    for (Int row = 2; row < 6; row++) {
        for (int col = 0; col < 8; col++) {
            Piece* somePiece {theBoard.piecePtrAtCoordinates(Coordinates(col, row))};
            EXPECT_FALSE(somePiece);
        }
    }
}