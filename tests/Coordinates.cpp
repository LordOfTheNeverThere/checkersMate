#include "checkersMate/Coordinates.h"

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