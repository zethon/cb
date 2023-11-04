#include <iostream>
#include <optional>
#include <filesystem>
#include <fstream>

#include <cctype>

#include <boost/algorithm/string.hpp> 
#include <boost/program_options.hpp>

#include <clip.h>

#include "Version.h"
#include "../lib/MyClass.h"

namespace po = boost::program_options;

using namespace std::string_literals;

struct CBConfig
{
    bool doEcho;
    bool doTrim;
    std::optional<std::string> file;
};

void post_process(std::string& data, const CBConfig& config)
{
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

void process_stdin(const CBConfig& config)
{
    std::string data;
    char input;
    while ((input = std::cin.get()) != EOF)
    {
        if (!static_cast<unsigned char>(input))
        {
            throw std::runtime_error("invalid input, binary data is not supported");
        }
        data.append(1, input);
    }

    post_process(data, config);
}

void process_file(const CBConfig& config)
{
    if (!std::filesystem::exists(config.file.value()))
    {
        const auto msg = "file '"s + config.file.value() + "' not found"s;
        throw std::runtime_error(msg);
    }

    std::ifstream file(config.file.value());
    std::string data((std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>());

    post_process(data, config);
}

int main(int argc, char* argv[])
{
    setlocale(LC_ALL, "");

    po::options_description desc("Allowed options");
    desc.add_options()
        ("help,?", "print help message")
        ("version,v", "print version string")
        ("about,a", "print about message")
        ("echo,e", "echo stdin to stdout")
        ("nostrip,n", "do not strip trailing whitespace")
        ("file,f", po::value<std::string>(), "copy file contents to clipboard")
        ("print,p", "print clipboard contents to stdout")
        ;

    po::variables_map vm;
    po::store(po::parse_command_line(argc, argv, desc), vm);
    po::notify(vm);

    if (vm.count("help") > 0)
    {
        std::cout << desc << '\n';
        return 0;
    }
    else if (vm.count("version") > 0)
    {
        std::cout << "cb " << VERSION << std::endl;
        return 0;
    }
    else if (vm.count("about") > 0)
    {
        std::cout << APP_TITLE << " by " << APP_DOMAIN << std::endl;
        std::cout << COPYRIGHT << std::endl;
        std::cout << "built on " << BUILDTIMESTAMP << std::endl;
        std::cout << "source code available at " << GITHUB_PAGE << std::endl;
        return 0;
    }
    else if (vm.count("print") > 0)
    {
        std::string data;
        std::cout << clip::get_text(data) << std::endl;
        std::cout << data << std::endl;
        return 0;
    }

    CBConfig config;
    config.doEcho = vm.count("echo") > 0;
    config.doTrim = vm.count("nostrip") == 0;
    if (vm.count("file") > 0)
    {
        config.file = vm["file"].as<std::string>();
    }

    try
    {
        if (config.file.has_value())
        {
            process_file(config);
        }
        else
        {
            process_stdin(config);
        }
    }
    catch(const std::exception& e)
    {
        std::cerr << "cb exception: " << e.what() << '\n';
        return 1;
    }

    return 0;
}