#include "checkersMate/pieces/King.h"

King::King(Int x, Int y, const std::array<std::weak_ptr<Piece>, 32>& otherPieces, PieceType type)
: Piece(x, y, otherPieces, type){}