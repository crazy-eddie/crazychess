#include <iostream>
#include <unistd.h>


int main(int argc, char ** argv)
{
    std::cout << "+-+-+-+-+-+-+-+-+\n"
              << "|r|n|b|q|k|b|n|r|\n"
              << "+-+-+-+-+-+-+-+-+\n"
              << "|p|p|p|p|p|p|p|p|\n"
              << "+-+-+-+-+-+-+-+-+\n"
              << "| | | | | | | | |\n"
              << "+-+-+-+-+-+-+-+-+\n"
              << "| | | | | | | | |\n"
              << "+-+-+-+-+-+-+-+-+\n"
              << "| | | | | | | | |\n"
              << "+-+-+-+-+-+-+-+-+\n"
              << "| | | | | | | | |\n"
              << "+-+-+-+-+-+-+-+-+\n"
              << "|P|P|P|P|P|P|P|P|\n"
              << "+-+-+-+-+-+-+-+-+\n"
              << "|R|N|B|Q|K|B|N|R|\n"
              << "+-+-+-+-+-+-+-+-+\n"
          ;
    std::cout.flush();
    usleep(500); // gives test enough time to read.
}
