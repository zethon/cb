#include <iostream>
#include <optional>
#include <filesystem>
#include <fstream>

#include <boost/algorithm/string.hpp> 
#include <boost/program_options.hpp>

#include "clip.h"

#include "../lib/MyClass.h"


namespace po = boost::program_options;

struct CBConfig
{
    bool doEcho;
    bool doTrim;
    std::optional<std::string> file;
};

void process_stdin(const CBConfig& config)
{
    std::string data;
    char input;
    while ((input = std::cin.get()) != EOF)
    {
        data.append(1, input);
    }

    if (config.doTrim)
    {
        boost::trim_right(data);
    }

    clip::set_text(data);
    
    if (config.doEcho)
    {
        std::cout << data << std::endl;
    }
}

void process_file(const CBConfig& config)
{
    if (!std::filesystem::exists(config.file.value()))
    {
        std::cerr << "File does not exist: " << config.file.value() << std::endl;
        return;
    }

    std::ifstream file(config.file.value());
    std::string data((std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>());

    if (config.doTrim)
    {
        boost::trim_right(data);
    }

    clip::set_text(data);
}

int main(int argc, char* argv[])
{
    setlocale(LC_ALL, "");

    po::options_description desc("Allowed options");
    desc.add_options()
        ("help,?", "print help message")
        ("version,v", "print version string")
        ("echo,e", "echo stdin to stdout")
        ("nostrip,n", "do not strip trailing whitespace")
        ("file,f", po::value<std::string>(), "copy file contents to clipboard")
        ;

    po::variables_map vm;
    po::store(po::parse_command_line(argc, argv, desc), vm);
    po::notify(vm);

    if (vm.count("help") > 0)
    {
        std::cout << desc << '\n';
        return 0;
    }

    CBConfig config;
    config.doEcho = vm.count("echo") > 0;
    config.doTrim = vm.count("nostrip") == 0;
    if (vm.count("file") > 0)
    {
        config.file = vm["file"].as<std::string>();
    }

    if (config.file.has_value())
    {
        process_file(config);
    }
    else
    {
        process_stdin(config);
    }





    return 0;
}