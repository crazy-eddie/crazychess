#ifndef BOARD_HPP
#define BOARD_HPP

#include <array>

namespace crazychess
{

enum struct piece
{
    empty = 0
  , white_pawn
  , white_rook
  , white_knight
  , white_bishop
  , white_queen
  , white_king
  , black_pawn
  , black_rook
  , black_bishop
  , black_queen
  , black_king
};
using pieces = piece;

using board = std::array<piece, 64>;

}

#endif
