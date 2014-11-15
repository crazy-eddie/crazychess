#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE board
#include <boost/test/unit_test.hpp>

#include <board.hpp>

BOOST_AUTO_TEST_CASE(empty_board)
{
    auto board = crazychess::board{};

    for (auto const& space : board)
    {
        BOOST_CHECK(space == crazychess::pieces::empty);
    }
}

BOOST_AUTO_TEST_CASE(occupied_spaces)
{
    auto board = crazychess::board{};

    board[0] = crazychess::pieces::white_pawn;
    board[1] = crazychess::pieces::black_king;
    board[2] = crazychess::pieces::white_rook;

    BOOST_CHECK(board[0] == crazychess::pieces::white_pawn);
    BOOST_CHECK(board[1] == crazychess::pieces::black_king);
    BOOST_CHECK(board[2] == crazychess::pieces::white_rook);

    std::for_each( std::begin(board)+3, std::end(board)
                 , [](crazychess::piece p) { BOOST_CHECK(p == crazychess::pieces::empty); });
}
