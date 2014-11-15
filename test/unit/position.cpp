#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE position
#include <boost/test/unit_test.hpp>

#include <position.hpp>

std::string quick_board_string(crazychess::board const& board)
{
    auto result = std::string(64, ' ');

    std::transform( std::begin(board), std::end(board)
                  , std::begin(result)
                  , [](crazychess::piece p)
                    {
                        constexpr auto pc = " PRNBQKprnbqk";
                        return pc[static_cast<int>(p)];
                    } );

    return result;
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

BOOST_AUTO_TEST_CASE(position_from_good_fen)
{
    auto pos = crazychess::position::from_fen("rnbqkbnr/pppp1ppp/8/4p3/8/8/PPPPPPPP/RNBQKBNR b Kkq c3 6 3");

    BOOST_CHECK_EQUAL( quick_board_string(pos.piece_placement())
                     , "rnbqkbnrpppp ppp            p                   PPPPPPPPRNBQKBNR");

    BOOST_CHECK(pos.side_to_move() == crazychess::color::black);

    BOOST_CHECK(pos.can_castle(crazychess::color::white, crazychess::castling::king_side));
    BOOST_CHECK(!pos.can_castle(crazychess::color::white, crazychess::castling::queen_side));
    BOOST_CHECK(pos.can_castle(crazychess::color::black, crazychess::castling::king_side));
    BOOST_CHECK(pos.can_castle(crazychess::color::black, crazychess::castling::queen_side));

    BOOST_CHECK(pos.en_passant());
    BOOST_CHECK_EQUAL(pos.en_passant()->code(), "c3");
    BOOST_CHECK_EQUAL(pos.en_passant()->loc(), 5 * 8 + 2);

    BOOST_CHECK_EQUAL(pos.half_move_clock(), 6);
    //BOOST_CHECK_EQUAL(pos.current_move(), 3);
}

#if 0
BOOST_AUTO_TEST_CASE(bad_fen)
{
}
#endif
