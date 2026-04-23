#include "checkersMate/networking/ChessBoardSegment.h"
#include <gtest/gtest.h>


TEST(MethodChecking, unpackAndPack) {

    std::vector<uint8_t> buffer (11, 0);
    buffer.at(0) = (buffer.size() - 1)/2;
    buffer.at(1) = 42;
    buffer.at(2) = 8;
    buffer.at(buffer.size() - 2) = 45;
    buffer.at(buffer.size() - 1) = 10;
    ChessBoardSegment header {buffer};
    std::vector<uint8_t> packedBuffer {header.packData()};

    EXPECT_EQ(buffer, packedBuffer);
}


TEST(ExceptionChecking, unpackAndPack) {

    // First value does not hold the number of pieces in the message
    std::vector<uint8_t> buffer (11, 0);
    EXPECT_THROW(ChessBoardSegment header {buffer}, WrongChessBoardHeaderFormatException);

    // The vector must be odd otherwise the structure has been corrupted in transit
    std::vector<uint8_t> evenBuffer (20, 0);
    EXPECT_THROW(ChessBoardSegment header {evenBuffer}, WrongChessBoardHeaderFormatException);
}
