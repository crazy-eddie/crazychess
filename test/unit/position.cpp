#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE position
#include <boost/test/unit_test.hpp>

#include <position.hpp>

std::string quick_board_string(crazychess::board const& board)
{
    return std::accumulate( std::begin(board), std::end(board)
                          , std::string()
                          , [](std::string str, crazychess::piece p)
                            {
                                constexpr auto pc = " PRNBQKprnbqk";
                                str.push_back(pc[static_cast<int>(p)]);
                                return str;
                            });
}

BOOST_AUTO_TEST_CASE(default_position)
{
    // default to startposition
    auto pos = crazychess::position{};

    BOOST_CHECK(pos.side_to_move() == crazychess::color::white);

    BOOST_CHECK(pos.can_castle(crazychess::color::white, crazychess::castling::king_side));
    BOOST_CHECK(pos.can_castle(crazychess::color::white, crazychess::castling::queen_side));
    BOOST_CHECK(pos.can_castle(crazychess::color::black, crazychess::castling::king_side));
    BOOST_CHECK(pos.can_castle(crazychess::color::black, crazychess::castling::queen_side));

    BOOST_CHECK_EQUAL(pos.half_move_clock(), 0);
    BOOST_CHECK_EQUAL(pos.current_move(), 1);

    BOOST_CHECK(!pos.en_passant());

    BOOST_CHECK_EQUAL( quick_board_string(pos.piece_placement())
                     , "rnbqkbnrpppppppp                                PPPPPPPPRNBQKBNR");
}
