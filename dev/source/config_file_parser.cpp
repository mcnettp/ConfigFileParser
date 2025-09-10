/* Includes */
#include "config_file_parser.h"


/* Constructor */
cConfigFileReader::cConfigFileReader(const std::string& filename)
{
    this->load(filename);
}

/**
* Function: load
* Load and parse the configuration file.
* @param[in] filename: The path to the configuration file.
* @param[out] None
* @return None
**/
void cConfigFileReader::load(const std::string& filename)
{
    /* Open the Config File */
    std::ifstream file(filename);
    if (file.is_open() == false)
    {
        throw std::runtime_error("Could not open config file: " + filename);
    }

    std::string line;

    /* Parse the file line by line */
    while (std::getline(file, line))
    {
        /* Empty line or a comment */
        if (line.empty() != false || line[0] == Config::comment)
        {
            continue; // Skip line
        }

        /* Find the delimiter */
        auto delimPos = line.find(Config::delimiter);
        if (delimPos == std::string::npos)
        {
            continue; // No delimiter found, skip line
        }

        std::string key = trim_whitespace(line.substr(0, delimPos));
        std::string value = trim_whitespace(line.substr(delimPos + 1));
        if (key.empty() == false)
        {
            this->configMap[key] = value;
        }
    }
}
