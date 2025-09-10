/* Includes */
#include <iostream>
#include "config_file_parser.h"

int main() {

    /* Sample of how to use the config parser */
    try
    {
        cConfigFileReader cfgParser("config.dat");
        std::string host = cfgParser.get(Config::Keys::host);
        int port = std::stoi(cfgParser.get(Config::Keys::port));

        std::cout << "Host IP: " << host << "\n";
        std::cout << "Port: " << port << "\n";

        // Trim Function Example
        std::string messy = "   hello world   ";
        std::cout << "Trimmed: '" << cfgParser.trim_whitespace(messy) << "'\n";
    }
    catch (const std::exception& err)
    {
        std::cerr << "Error: " << err.what() << "\n";
    }

    return 0;
}