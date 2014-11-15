#ifndef PROCESS_HPP
#define PROCESS_HPP

#include <boost/filesystem.hpp>
#include <iostream>
#include <memory>
#include <boost/iostreams/device/file_descriptor.hpp>
#include <boost/iostreams/stream.hpp>


namespace util {

struct process
{
    process(boost::filesystem::path exe);
    process(boost::filesystem::path exe, std::vector<std::string> args);
    process(process &&);
    ~process();

    using istream = boost::iostreams::stream<boost::iostreams::file_descriptor_source>;
    using ostream = boost::iostreams::stream<boost::iostreams::file_descriptor_sink>;

    istream& output();
    ostream& input();

    void start();

private:
    struct impl;
    std::unique_ptr<impl> pimpl;
};

}

#endif
