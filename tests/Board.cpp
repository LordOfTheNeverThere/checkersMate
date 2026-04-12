#include "checkersMate/Board.h"

#include "checkersMate/ChessTools.h"
#include "gtest/gtest.h"

TEST(MethodChecking, BoardConstructorV2) {
    Board theBoard {};

    Coordinates whiteKingCoord {4,0};
    std::set<Piece*> whiteKingSet {theBoard.generalFilter(PieceType::king, PieceColour::white, &whiteKingCoord)};
    EXPECT_EQ(whiteKingSet.size(), 1);
    Piece* whiteKing {*whiteKingSet.begin()};
    EXPECT_EQ(PieceColour::white, whiteKing->getColour());
    EXPECT_EQ(PieceType::king, whiteKing->getType());
    EXPECT_EQ(whiteKingCoord, whiteKing->getCoordinates());

    Coordinates whiteQueenCoord {3,0};
    std::set<Piece*> whiteQueenSet {theBoard.generalFilter(PieceType::queen, PieceColour::white, &whiteQueenCoord)};
    EXPECT_EQ(whiteQueenSet.size(), 1);
    Piece* whiteQueen {*whiteQueenSet.begin()};
    EXPECT_EQ(PieceColour::white, whiteQueen->getColour());
    EXPECT_EQ(PieceType::queen, whiteQueen->getType());
    EXPECT_EQ(whiteQueenCoord, whiteQueen->getCoordinates());

    Coordinates blackKingCoord {4,7};
    std::set<Piece*> blackKingSet {theBoard.generalFilter(PieceType::king, PieceColour::black, &blackKingCoord)};
    EXPECT_EQ(blackKingSet.size(), 1);
    Piece* blackKing {*blackKingSet.begin()};
    EXPECT_EQ(PieceColour::black, blackKing->getColour());
    EXPECT_EQ(PieceType::king, blackKing->getType());
    EXPECT_EQ(blackKingCoord, blackKing->getCoordinates());

    Coordinates blackQueenCoord {3,7};
    std::set<Piece*> blackQueenSet {theBoard.generalFilter(PieceType::queen, PieceColour::black, &blackQueenCoord)};
    EXPECT_EQ(blackQueenSet.size(), 1);
    Piece* blackQueen {*blackQueenSet.begin()};
    EXPECT_EQ(PieceColour::black, blackQueen->getColour());
    EXPECT_EQ(PieceType::queen, blackQueen->getType());
    EXPECT_EQ(blackQueenCoord, blackQueen->getCoordinates());

    //Piece Groups
        //Pawns
    std::set<Piece*> whitePawnsSet {theBoard.generalFilter(PieceType::pawn, PieceColour::white)};
    EXPECT_EQ(whitePawnsSet.size(), 8);

    for (int i = 0; i < 8; i++) {
        bool found {false};
        for (auto whitePawn: whitePawnsSet) {
            if (Coordinates(i, 1) == whitePawn->getCoordinates()) found = true;
        }
        EXPECT_TRUE(found);
    }

    std::set<Piece*> blackPawnsSet {theBoard.generalFilter(PieceType::pawn, PieceColour::black)};
    EXPECT_EQ(blackPawnsSet.size(), 8);

    for (int i = 0; i < 8; i++) {
        bool found {false};
        for (auto blackPawn: blackPawnsSet) {
            if (Coordinates(i, 6) == blackPawn->getCoordinates()) found = true;
        }
        EXPECT_TRUE(found);
    }
        //Towers
    std::set<Piece*> whiteTowersSet{theBoard.generalFilter(PieceType::tower, PieceColour::white)};
    bool foundLeft{false}; bool foundRight {false};

    for (auto whiteTower: whiteTowersSet) {
        if (!foundLeft && whiteTower->getCoordinates()==Coordinates(0,0)) foundLeft = true;
        else if (!foundRight && whiteTower->getCoordinates() == Coordinates(7,0)) foundRight = true;
    }
    EXPECT_TRUE(foundRight && foundLeft);

    std::set<Piece*> blackTowersSet{theBoard.generalFilter(PieceType::tower, PieceColour::black)};
    foundLeft = false; foundRight = false;

    for (auto blackTower: blackTowersSet) {
        if (!foundLeft && blackTower->getCoordinates()==Coordinates(0,7)) foundLeft = true;
        else if (!foundRight && blackTower->getCoordinates() == Coordinates(7,7)) foundRight = true;
    }
    EXPECT_TRUE(foundRight && foundLeft);

        //Horses
    std::set<Piece*> whiteHorsesSet{theBoard.generalFilter(PieceType::horse, PieceColour::white)};
    foundLeft =false;foundRight = false;

    for (auto whiteHorse: whiteHorsesSet) {
        if (!foundLeft && whiteHorse->getCoordinates()==Coordinates(1,0)) foundLeft = true;
        else if (!foundRight && whiteHorse->getCoordinates() == Coordinates(6,0)) foundRight = true;
    }
    EXPECT_TRUE(foundRight && foundLeft);

    std::set<Piece*> blackHorsesSet{theBoard.generalFilter(PieceType::horse, PieceColour::black)};
    foundLeft =false;foundRight = false;

    for (auto blackHorse: blackHorsesSet) {
        if (!foundLeft && blackHorse->getCoordinates()==Coordinates(1,7)) foundLeft = true;
        else if (!foundRight && blackHorse->getCoordinates() == Coordinates(6,7)) foundRight = true;
    }
    EXPECT_TRUE(foundRight && foundLeft);

        //Bishops
    std::set<Piece*> whiteBishopsSet{theBoard.generalFilter(PieceType::bishop, PieceColour::white)};
    foundLeft =false;foundRight = false;

    for (auto whiteBishop: whiteBishopsSet) {
        if (!foundLeft && whiteBishop->getCoordinates()==Coordinates(2,0)) foundLeft = true;
        else if (!foundRight && whiteBishop->getCoordinates() == Coordinates(5,0)) foundRight = true;
    }
    EXPECT_TRUE(foundRight && foundLeft);

    std::set<Piece*> blackBishopsSet{theBoard.generalFilter(PieceType::bishop, PieceColour::black)};
    foundLeft =false;foundRight = false;

    for (auto blackBishop: blackBishopsSet) {
        if (!foundLeft && blackBishop->getCoordinates()==Coordinates(2,7)) foundLeft = true;
        else if (!foundRight && blackBishop->getCoordinates() == Coordinates(5,7)) foundRight = true;
    }
    EXPECT_TRUE(foundRight && foundLeft);
}


TEST(MethodChecking, checkIfBoardConstructorMapWorksWithCoordinatesPtr) {
    Board theBoard {};
    auto whiteQueenMap {theBoard.m_piecesV2.at(PieceColour::white).at(PieceType::queen).begin()};
    EXPECT_EQ(*(whiteQueenMap->first), Coordinates(3,0));
    whiteQueenMap->second->setCoordinates(5,5);
    EXPECT_EQ(*(whiteQueenMap->first), Coordinates(5,5));
    whiteQueenMap = theBoard.m_piecesV2.at(PieceColour::white).at(PieceType::queen).begin();
    EXPECT_EQ(*(whiteQueenMap->first), whiteQueenMap->second->getCoordinates());
    EXPECT_EQ(*(whiteQueenMap->first), Coordinates(5,5));
}
TEST(MethodChecking, pieceAtCoordinates) {
    Board theBoard {};

    for (Int row = 6; row < 8; row++) {
        for (int col = 0; col < 8; col++) {
            Piece* somePiece {theBoard.piecePtrAtCoordinates(Coordinates(col, row))};
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
            Piece* somePiece {theBoard.piecePtrAtCoordinates(Coordinates(col, row))};
            EXPECT_EQ(somePiece, nullptr);
            EXPECT_EQ(somePiece->getType(), PieceType::empty);
            EXPECT_EQ(somePiece->getColour(), PieceColour::empty);
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