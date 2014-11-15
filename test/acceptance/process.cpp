#include "process.hpp"
#include <fcntl.h>
#include <cstdio>

namespace util {

struct process::impl
{
    boost::filesystem::path exe;
    std::vector<std::string> args;

    boost::iostreams::stream<boost::iostreams::file_descriptor_source> source;
    boost::iostreams::stream<boost::iostreams::file_descriptor_sink> sink;

    impl(boost::filesystem::path e)
        : exe{std::move(e)}
        , args{}
        , source{}
        , sink{}
    {}

    impl(boost::filesystem::path e, std::vector<std::string> a)
        : exe{std::move(e)}
        , args{std::move(a)}
        , source{}
        , sink{}
    {}
};

process::process(boost::filesystem::path exe)
    : pimpl(new impl(std::move(exe)))
{}


process::process(boost::filesystem::path exe, std::vector<std::string> args)
    : pimpl(new impl(std::move(exe), std::move(args)))
{}

process::process(process && other)
    : pimpl(std::move(other.pimpl))
{}

process::~process() {}


void process::start()
{
    int output[] = {0,0};
    int input[] = {0,0};

    pipe(output);
    pipe(input);

    int pid = -1;

    switch (pid = fork())
    {
    case -1:
        throw std::runtime_error("Couldn't fork.");
        break;
    case 0:
        {
            // Calling C function that isn't const correct.
            std::vector<char*> c_args{pimpl->args.size()+2};
            c_args[0] = const_cast<char*>(pimpl->exe.c_str());
            std::transform( std::begin(pimpl->args), std::end(pimpl->args)
                          , std::begin(c_args)+1
                          , [](std::string const& str) { return const_cast<char*>(str.c_str()); });
            c_args[c_args.size()-1] = nullptr;

            close(output[0]);
            close(input[1]);

            dup2(output[1], STDOUT_FILENO);
            dup2(input[0], STDIN_FILENO);

            execvp(pimpl->exe.c_str(), c_args.data());
        }
        break;
    default:
        close(output[1]);
        close(input[0]);
        pimpl->source.open(boost::iostreams::file_descriptor_source(output[0], boost::iostreams::close_handle));
        pimpl->sink.open(boost::iostreams::file_descriptor_sink(input[1], boost::iostreams::close_handle));
        break;
    }
}

process::istream& process::output() { return pimpl->source; }
process::ostream& process::input() { return pimpl->sink; }


}
