#include "../../include/checkersMate/pieces/Piece.h"



Piece::Piece(const Int x, const Int y, const std::array<std::weak_ptr<Piece>, 32>& otherPieces, PieceType type) {
    setOtherPieces(otherPieces);
    setCoordinates(x, y);
    setType(type);
}