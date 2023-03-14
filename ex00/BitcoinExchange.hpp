#include <algorithm>
#include <map>
#include <list>
#include <iostream>
#include <iomanip>
#include <cstring>
#include <fstream>
#include <cmath>

#define BLANK       "\033[0m"
#define BLACK       "\033[90m"
#define RED         "\033[91m"
#define GREEN       "\033[92m"
#define YELLOW      "\033[93m"
#define BLUE        "\033[94m"
#define MAGENTA     "\033[95m"
#define CYAN        "\033[96m"
#define WHITE       "\033[97m"
#define BOLDBLACK   "\033[1m\033[90m"
#define BOLDRED     "\033[1m\033[91m"
#define BOLDGREEN   "\033[1m\033[92m"
#define BOLDYELLOW  "\033[1m\033[93m"
#define BOLDBLUE    "\033[1m\033[94m"
#define BOLDMAGENTA "\033[1m\033[95m"
#define BOLDCYAN    "\033[1m\033[96m"
#define BOLDWHITE   "\033[1m\033[97m"

class BitcoinExchange
{
	private:
		std::map<std::string, std::string>	_data;

	public:
		BitcoinExchange();
		BitcoinExchange(const BitcoinExchange &btc);
		BitcoinExchange(std::string path_data);
		~BitcoinExchange();

	BitcoinExchange	&operator=(const BitcoinExchange &btc);

	void								parseData(std::string path);
	std::map<std::string, std::string>	getData();
	int									doExchange(char *path);

	class DataNotFound : public std::exception
	{
		public:
			virtual const char* what() const throw()
			{
				return RED "Error: Data.csv not found." BLANK;
			}
	};

	class CorruptedDataFile : public std::exception
	{
		public:
			virtual const char* what() const throw()
			{
				return RED "Error: Corrupted data file." BLANK;
			}
	};

	class BadError : public std::exception
	{
		public:
			virtual const char* what() const throw()
			{
				return RED "Program Closed." BLANK;
			}
	};
};
