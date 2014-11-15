#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE position
#include <boost/test/unit_test.hpp>

#include <position.hpp>

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
}
