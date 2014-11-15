#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE board_positions
#include <boost/test/unit_test.hpp>

#include "config.hpp"

#include "process.hpp"

void verify(std::string const& fen, std::vector<std::string> const& expected)
{
    auto proc = util::process(board_program, {fen});
    proc.start();

    BOOST_REQUIRE(proc.output().is_open());
    BOOST_REQUIRE(proc.input().is_open());

    std::vector<std::string> receive;

    std::string str;

    BOOST_MESSAGE("Ready to receive...");
    while (std::getline(proc.output(), str))
    {
        BOOST_MESSAGE("Received: " << str);
        receive.push_back(str);
    }

    BOOST_CHECK(receive == expected);

}

BOOST_AUTO_TEST_CASE(starting)
{
    auto fen = "rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1";
    std::vector<std::string> expected
    {
      "+-+-+-+-+-+-+-+-+"
    , "|r|n|b|q|k|b|n|r|"
    , "+-+-+-+-+-+-+-+-+"
    , "|p|p|p|p|p|p|p|p|"
    , "+-+-+-+-+-+-+-+-+"
    , "| | | | | | | | |    Color to move: White"
    , "+-+-+-+-+-+-+-+-+    Castling availability: KQkq"
    , "| | | | | | | | |    En passant sq: --"
    , "+-+-+-+-+-+-+-+-+    Half-moves: 0"
    , "| | | | | | | | |    Move number: 1"
    , "+-+-+-+-+-+-+-+-+"
    , "| | | | | | | | |"
    , "+-+-+-+-+-+-+-+-+"
    , "|P|P|P|P|P|P|P|P|"
    , "+-+-+-+-+-+-+-+-+"
    , "|R|N|B|Q|K|B|N|R|"
    , "+-+-+-+-+-+-+-+-+"
    };

    verify(fen, expected);
}


BOOST_AUTO_TEST_CASE(notstart)
{
    auto fen = "rnbqkbnr/pppp1ppp/8/4p3/8/8/PPPPPPPP/RNBQKBNR b Kkq c3 6 3";

    std::vector<std::string> expected
    {
      "+-+-+-+-+-+-+-+-+"
    , "|r|n|b|q|k|b|n|r|"
    , "+-+-+-+-+-+-+-+-+"
    , "|p|p|p|p| |p|p|p|"
    , "+-+-+-+-+-+-+-+-+"
    , "| | | | | | | | |    Color to move: Black"
    , "+-+-+-+-+-+-+-+-+    Castling availability: Kkq"
    , "| | | | |p| | | |    En passant sq: c3"
    , "+-+-+-+-+-+-+-+-+    Half-moves: 6"
    , "| | | | | | | | |    Move number: 3"
    , "+-+-+-+-+-+-+-+-+"
    , "| | | | | | | | |"
    , "+-+-+-+-+-+-+-+-+"
    , "|P|P|P|P|P|P|P|P|"
    , "+-+-+-+-+-+-+-+-+"
    , "|R|N|B|Q|K|B|N|R|"
    , "+-+-+-+-+-+-+-+-+"
    };

    verify(fen, expected);
}

BOOST_AUTO_TEST_CASE(invalid)
{
    auto fen = "rnbqkbnr/pppp1ppp/8/4p3/8//PPPPPPPP/RNBQKBNR w KQkq - 0 1";

    std::vector<std::string> expected
    {
      "INVALID POSITION: 'rnbqkbnr/pppp1ppp/8/4p3/8//PPPPPPPP/RNBQKBNR w KQkq - 0 1'"
    };

    verify(fen, expected);
}
