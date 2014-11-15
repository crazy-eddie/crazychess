#include "../include/position.hpp"

#include <boost/tokenizer.hpp>

namespace crazychess
{

namespace {

piece char_to_piece(char p)
{
    switch (p)
    {
    case 'p': return piece::black_pawn;
    case 'P': return piece::white_pawn;
    case 'r': return piece::black_rook;
    case 'R': return piece::white_rook;
    case 'n': return piece::black_knight;
    case 'N': return piece::white_knight;
    case 'b': return piece::black_bishop;
    case 'B': return piece::white_bishop;
    case 'q': return piece::black_queen;
    case 'Q': return piece::white_queen;
    case 'k': return piece::black_king;
    case 'K': return piece::white_king;
    default:
        throw std::runtime_error("Invalid piece");
    }
}

template < typename T >
board parse_board(T const& str)
{
    board result{};

    auto index = 0;
    auto beg = std::begin(str);
    auto end = std::end(str);

    while (beg != end && index < 64)
    {
        if (std::isdigit(*beg))
        {
            auto count = *beg - '0';
            while (count--)
            {
                result[index++] = piece::empty;
            }
        }
        else if (*beg == '/') {}
        else
        {
            result[index++] = char_to_piece(*beg);
        }

        ++beg;
    }

    return result;
}

}
position position::from_fen(std::string const& fen)
{
    auto result = position{};

    using tokenizer = boost::tokenizer<boost::char_separator<char>>;

    auto sep = boost::char_separator<char>(" ");
    auto tok = tokenizer(fen, sep);

    auto tbeg = std::begin(tok);
    auto tend = std::end(tok);

    result.layout = parse_board(*tbeg++);

    if (tbeg->front() == 'b') result.cur_color = color::black;
    else if (tbeg->front() == 'w') result.cur_color = color::white;

    ++tbeg;

    result.castle_mask = 0;
    for (auto && c : *tbeg)
    {
        auto mask = 0;
        switch (c)
        {
        case 'K':
            mask = static_cast<int>(castling::king_side);
            break;
        case 'k':
            mask = (static_cast<int>(castling::king_side) << 2);
            break;
        case 'Q':
            mask = static_cast<int>(castling::queen_side);
            break;
        case 'q':
            mask = (static_cast<int>(castling::queen_side) << 2);
            break;
        default:
            throw std::runtime_error(std::string("Invalid castling code: ") + c);
        }
        result.castle_mask |= mask;
    }

    ++tbeg;

    if (tbeg->front() != '-')
        result.ep = place::from_ascii(std::begin(*tbeg), std::end(*tbeg));

    ++tbeg;

    result.hmove = std::stoi(*tbeg++);
    result.cmove = std::stoi(*tbeg);

    return result;
}

namespace {

board default_board()
{
    return parse_board("rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR");
}

}

position::position()
    : layout(default_board())
    , cur_color(color::white)
    , castle_mask(0xF)
    , ep()
    , hmove(0)
    , cmove(1)
{}


board const& position::piece_placement() const
{
    return layout;
}

}
