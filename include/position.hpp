#ifndef POSITION_HPP
#define POSITION_HPP

#include "board.hpp"

#include <boost/optional.hpp>

namespace crazychess
{

enum struct color
{
    white = 0
  , black = 2
};

enum struct castling
{
    king_side = 1
  , queen_side = 2
};

struct place
{
    place(int i) : index(i) {}

    int loc() const { return index; }
    std::string code() const
    {
        std::string str(2, ' ');

        str[0] = 'a' + index % 8;
        str[1] = '1' + (7 - (index / 8));

        return str;
    }

    template < typename It >
    static place from_ascii(It beg, It end)
    {
        auto i = *beg - 'a' + 8 * (7 - (*(beg+1) - '1'));
        return place(i);
    }
private:
    int index;
};

struct position
{
    position();

    color side_to_move() const { return cur_color; }

    bool can_castle(color side, castling direction) const
    {
        auto test_mask = static_cast<int>(direction) << static_cast<int>(side);
        return (castle_mask & test_mask) != 0;
    }

    int half_move_clock() const { return hmove; }
    int current_move() const { return cmove; }

    boost::optional<place> en_passant() const { return ep; }

    board const& piece_placement() const;

    static position from_fen(std::string const& fen);

private:
    board layout;
    color cur_color;
    int castle_mask;
    boost::optional<place> ep;
    int hmove;
    int cmove;
};


}

#endif
