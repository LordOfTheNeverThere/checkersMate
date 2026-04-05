#ifndef CHECKERSMATE_BOARD_H
#define CHECKERSMATE_BOARD_H
#include <array>
#include <memory>

#include "../../cmake-build-debug/_deps/googletest-src/googletest/include/gtest/gtest_prod.h"
#include "pieces/Piece.h"

class Board{
    FRIEND_TEST(MethodChecking, BoardConstructor);
    std::array<std::unique_ptr<Piece>, 32> m_pieces {};
public:
    Board();
};

#endif //CHECKERSMATE_BOARD_H