#include "checkersMate/Coordinates.h"

#include <cmath>
#include <gtest/gtest.h>


TEST(ExceptionChecking, outOfBoardException) {

    EXPECT_THROW({
        try {
            Coordinates(-1,1);
        } catch( const OutOfBoardException& e ) {
            EXPECT_STREQ("Error: The value of -1 is not correct for a 8x8 board", e.what());
            throw; // Re-throw so EXPECT_THROW sees it
        }
        }, OutOfBoardException);

    EXPECT_THROW({
        try {
            Coordinates(-1,-1);
        } catch( const OutOfBoardException& e ) {
            EXPECT_STREQ("Error: The value of -1 is not correct for a 8x8 board", e.what());
            throw; // Re-throw so EXPECT_THROW sees it
        }
        }, OutOfBoardException);

    EXPECT_THROW({
        try {
            Coordinates(1,-1);
        } catch( const OutOfBoardException& e ) {
            EXPECT_STREQ("Error: The value of -1 is not correct for a 8x8 board", e.what());
            throw; // Re-throw so EXPECT_THROW sees it
        }
        }, OutOfBoardException);

    EXPECT_THROW({
    try {
        Coordinates(8,1);
    } catch( const OutOfBoardException& e ) {
        EXPECT_STREQ("Error: The value of 8 is not correct for a 8x8 board", e.what());
        throw; // Re-throw so EXPECT_THROW sees it
    }
    }, OutOfBoardException);

    EXPECT_THROW({
        try {
            Coordinates(8,8);
        } catch( const OutOfBoardException& e ) {
            EXPECT_STREQ("Error: The value of 8 is not correct for a 8x8 board", e.what());
            throw; // Re-throw so EXPECT_THROW sees it
        }
        }, OutOfBoardException);

    EXPECT_THROW({
        try {
            Coordinates(1,8);
        } catch( const OutOfBoardException& e ) {
            EXPECT_STREQ("Error: The value of 8 is not correct for a 8x8 board", e.what());
            throw; // Re-throw so EXPECT_THROW sees it
        }
        }, OutOfBoardException);
}

TEST(MethodChecking, mathOperators) {

    EXPECT_EQ(Coordinates(1,5) + Coordinates(4,0) , Coordinates(5,5));
    EXPECT_EQ(Coordinates(5,5) - Coordinates(4,0) , Coordinates(1,5));
    EXPECT_THROW(Coordinates(1,5) - Coordinates(4,0), OutOfBoardException);
}


TEST(MethodChecking, generatePosYSet) {

    Coordinates someCoord {3,3};

    for (auto coord: someCoord.generatePosYVec()) {
        EXPECT_EQ(coord.getX(), someCoord.getX());
        EXPECT_GT(coord.getY(), someCoord.getY());
        EXPECT_LE(coord.getY(), 7);
    }

    Coordinates someCoord2 {3,7};
    EXPECT_EQ(someCoord2.generatePosYVec().size(), 0);
}


TEST(MethodChecking, generateNegYSet) {

    Coordinates someCoord {3,3};

    for (auto coord: someCoord.generateNegYVec()) {
        EXPECT_EQ(coord.getX(), someCoord.getX());
        EXPECT_LT(coord.getY(), someCoord.getY());
        EXPECT_GE(coord.getY(), 0);
    }

    Coordinates someCoord2 {3,7};
    EXPECT_EQ(someCoord2.generateNegYVec().size(), 7);
}

TEST(MethodChecking, generatePosXSet) {

    Coordinates someCoord {0,3};

    for (auto coord: someCoord.generatePosXVec()) {
        EXPECT_EQ(coord.getY(), someCoord.getY());
        EXPECT_GT(coord.getX(), someCoord.getX());
        EXPECT_LE(coord.getX(), 7);
    }

    Coordinates someCoord2 {7,7};
    EXPECT_EQ(someCoord2.generatePosXVec().size(), 0);
}

TEST(MethodChecking, generateNegXSet) {

    Coordinates someCoord {3,3};

    for (auto coord: someCoord.generateNegXVec()) {
        EXPECT_EQ(coord.getY(), someCoord.getY());
        EXPECT_LT(coord.getX(), someCoord.getX());
        EXPECT_GE(coord.getX(), 0);
    }

    Coordinates someCoord2 {0,7};
    EXPECT_EQ(someCoord2.generateNegXVec().size(), 0);
}


TEST(MethodChecking, generateNegXPosYSet) {
    Coordinates someCoord {7,0};
    EXPECT_EQ(someCoord.generateNegXPosYVec().size(), 7);
    for (auto coord: someCoord.generateNegXPosYVec()) {
        EXPECT_LT(coord.getX(), someCoord.getX());
        EXPECT_GT(coord.getY(), someCoord.getY());
    }
    someCoord = {0,7};
    EXPECT_EQ(someCoord.generateNegXPosYVec().size(), 0);
}

TEST(MethodChecking, generatePosXPosYSet) {
    Coordinates someCoord {0,0};
    EXPECT_EQ(someCoord.generatePosXPosYVec().size(), 7);
    for (auto coord: someCoord.generatePosXPosYVec()) {
        EXPECT_GT(coord.getX(), someCoord.getX());
        EXPECT_GT(coord.getY(), someCoord.getY());
    }
    someCoord = {7,7};
    EXPECT_EQ(someCoord.generatePosXPosYVec().size(), 0);
}

TEST(MethodChecking, generatePosXNegYSet) {
    Coordinates someCoord {0,7};
    EXPECT_EQ(someCoord.generatePosXNegYVec().size(), 7);

    for (auto coord: someCoord.generatePosXNegYVec()) {
        EXPECT_GT(coord.getX(), someCoord.getX());
        EXPECT_LT(coord.getY(), someCoord.getY());
    }

    someCoord = {7,0};
    EXPECT_EQ(someCoord.generatePosXNegYVec().size(), 0);
}

TEST(MethodChecking, generateNegXNegYSet) {

    Coordinates someCoord {7,7};
    EXPECT_EQ(someCoord.generateNegXNegYVec().size(), 7);

    for (auto coord: someCoord.generateNegXNegYVec()) {
        EXPECT_LT(coord.getX(), someCoord.getX());
        EXPECT_LT(coord.getY(), someCoord.getY());
    }

    someCoord = {0,0};
    EXPECT_EQ(someCoord.generateNegXNegYVec().size(), 0);

}

TEST(MethodChecking, generateCircleSet) {

    Coordinates someCoord {4,4};
    std::set<Coordinates> expectedPositions {};

    for (int i = 2; i <= 6; ++i) {
        for (int j = 2; j <= 6; ++j) {
            if (i!=4 || j!=4) {
                expectedPositions.emplace(i ,j);
            }
        }
    }
    EXPECT_EQ(expectedPositions, someCoord.generateCircleSet(2));

    for (auto coord: someCoord.generateCircleSet(2)) {
        EXPECT_TRUE(coord.getX() <= someCoord.getX() || coord.getX() >= someCoord.getX());
        EXPECT_TRUE(coord.getY() <= someCoord.getY() || coord.getY() >= someCoord.getY());
    }
}

TEST(MethodChecking, generateEnemyPawnPositions) {


    //black
    Coordinates blackPawn {4,5};
    std::set<Coordinates> possiblePawnPosition {blackPawn.generateEnemyPawnPositions(PieceColour::black)};
    EXPECT_TRUE(possiblePawnPosition.find(Coordinates(3,4)) != possiblePawnPosition.end());
    EXPECT_TRUE(possiblePawnPosition.find(Coordinates(5,4)) != possiblePawnPosition.end());
    //white
    Coordinates whitePawn {0,2};
    possiblePawnPosition = whitePawn.generateEnemyPawnPositions(PieceColour::white);
    EXPECT_TRUE(possiblePawnPosition.find(Coordinates(1,3)) != possiblePawnPosition.end());

}

TEST(MethodChecking, generateHorsePositions) {
    Coordinates horseyCoordinates {3,4};
    std::set<Coordinates> expectedPositions {Coordinates(1,5), Coordinates(1,3), Coordinates(5, 5), Coordinates(5,3), Coordinates(2,6), Coordinates(4,6), Coordinates(2,2), Coordinates(4,2)};
    EXPECT_EQ(horseyCoordinates.generateHorsePositions(),expectedPositions);
}