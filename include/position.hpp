#ifndef POSITION_HPP
#define POSITION_HPP

#include "board.hpp"

namespace crazychess
{

enum struct color
{
    white
  , black
};

enum struct castling
{
    king_side
  , queen_side
};


struct position
{
    position() {}

    color side_to_move() const { return color::white; }

    bool can_castle(color side, castling direction) const
    {
        return true;
    }

    int half_move_clock() const { return 0; }
    int current_move() const { return 1; }

    bool en_passant() const { return false; }

    board const& piece_placement() const
    {
        static auto b = board{ piece::r, piece::n, piece::b, piece::q, piece::k, piece::b, piece::n, piece::r
                             , piece::p, piece::p, piece::p, piece::p, piece::p, piece::p, piece::p, piece::p
                             , piece::e, piece::e, piece::e, piece::e, piece::e, piece::e, piece::e, piece::e
                             , piece::e, piece::e, piece::e, piece::e, piece::e, piece::e, piece::e, piece::e
                             , piece::e, piece::e, piece::e, piece::e, piece::e, piece::e, piece::e, piece::e
                             , piece::e, piece::e, piece::e, piece::e, piece::e, piece::e, piece::e, piece::e
                             , piece::P, piece::P, piece::P, piece::P, piece::P, piece::P, piece::P, piece::P
                             , piece::R, piece::N, piece::B, piece::Q, piece::K, piece::B, piece::N, piece::R };

        return b;
    }
};


}

#endif
