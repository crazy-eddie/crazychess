#ifndef POSITION_HPP
#define POSITION_HPP


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
};


}

#endif
