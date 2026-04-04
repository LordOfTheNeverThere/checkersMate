#ifndef CHECKERSMATE_BOARD_H
#define CHECKERSMATE_BOARD_H
#include <array>
#include <memory>
#include "pieces/Piece.h"

class Board {
    std::array<std::shared_ptr<Piece>, 32> m_pieces {};
public:
    Board() {
        //TODO: Initialise all the Pieces
        // and construct the array of weak pointers to give them
    }
};

#endif CHECKERSMATE_BOARD_H