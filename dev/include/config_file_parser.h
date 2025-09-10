#ifndef __CONFIG_FILE_PARSER_H__
#define __CONFIG_FILE_PARSER_H__

/* Includes */
#include <iostream>
#include <fstream>
#include <string>
#include <map>
#include <cctype>
#include <algorithm> // For std::transform

/* Config Namespace */
namespace Config
{
	constexpr char delimiter = '=';
	constexpr char comment = '#';

	namespace Keys
	{
		const std::string host = "host";
		const std::string port = "port";
	}
}

/* Types */
using KeyValueMap = std::map<std::string, std::string>;

/**
* Class: cConfigFileReader
* Description: A simple configuration file reader and parser.
* Supports key-value pairs separated by a delimiter and ignores comments.
**/
class cConfigFileReader
{
public:

	/* Constructor */
	explicit cConfigFileReader(const std::string& filename);

	/**
    * Function: get
    * This function retrieves the value associated with a given key.
    * @param[in] key: The key to look up
    * @param[in] defaultValue: The default value to return if the key does not exist or conversion fails
	* @param[out] None
    * @return The value associated with the key, or an empty string if the key does not exist.
	**/
	std::string get(const std::string& key, const std::string& defaultValue = "") const
	{
		auto it = this->configMap.find(key);
		return (it != this->configMap.end()) ? it->second : defaultValue;
	}

	/**
	* Function: getInt
    * This function retrieves the value associated with a given key as an integer.
	* @param[in] key: The key to look up
    * @param[in] defaultValue: The default value to return if the key does not exist or conversion fails
	* @param[out] None
	* @return The value associated with the key, or an empty string if the key does not exist.
	**/
	int getInt(const std::string& key, const int defaultValue = 0) const
	{
		auto it = this->configMap.find(key);
		if (it == this->configMap.end())
		{
			return defaultValue;
		}

        /* Convert to int */
		try
		{
			return std::stoi(it->second);
		}
		catch (...)
		{
			return defaultValue;
		}
	}

	/**
    * Function: getBool
	* This function retrieves the value associated with a given key as a boolean.
	* @param[in] key: The key to look up
	* @param[in] defaultValue: The default value to return if the key does not exist or conversion fails
	* @param[out] None
	* @return The value associated with the key, or an empty string if the key does not exist.
	**/
	bool getBool(const std::string& key, const bool defaultValue = false) const
	{
		auto it = this->configMap.find(key);
		if (it == this->configMap.end())
		{
			return defaultValue;
		}

		std::string val = it->second;

		/* Convert to lowercase for comparison */
		std::transform(val.begin(), val.end(), val.begin(), ::tolower);

        /* Check common true/false representations */
		if (val == "1" || val == "true" || val == "yes" || val == "on")
		{
			return true;
		}
		if (val == "0" || val == "false" || val == "no" || val == "off")
		{
			return false;
		}
		
		return defaultValue;
	}

	/**
    * Function: contains
	* This function checks if a given key exists in the configuration map.
    * @param[in] key: The key to check
    * @param[out] None
    * @return True if the key exists, false otherwise.
	**/
	bool contains(const std::string& key) const
	{
		return this->configMap.find(key) != this->configMap.end();
	}

	/**
	* Function: print
    * This function prints all key-value pairs in the configuration map.
    * @param[in] None
	* @param[out] None
    * @return None
	**/
	void print() const
	{
		for (const auto& kvPair : this->configMap)
		{
			std::cout << kvPair.first << " = " << kvPair.second << "\n";
		}
	}

	/**
	* Function: trim_whitespace
	* This function trims leading and trailing whitespace from a string.
	* @param[in] str: The string to trim
	* @param[out] None
	* @return The trimmed string.
	**/
	inline std::string trim_whitespace(const std::string& str) const
	{
		/* Lambda for algorithms */
		auto notSpace = [](const int ch) {
			return std::isspace(ch) == false;
			};

		/* Trim Left side */
		auto start = std::find_if(str.begin(), str.end(), notSpace);
		if (start == str.end())
		{
			return ""; // all whitespace
		}

		/* Trim Right side */
		auto end = std::find_if(str.rbegin(), str.rend(), notSpace).base();

		return std::string(start, end);
	}

private:

	/* Variables */
	KeyValueMap configMap;

	/* Private Functions */
	void load(const std::string& filename);
};

#endif // !__CONFIG_FILE_PARSER_H__
