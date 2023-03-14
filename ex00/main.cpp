#include "BitcoinExchange.hpp"

int	main(int argc, char **argv)
{
	try
	{
		BitcoinExchange	btc("data.csv");
		if (argc != 2)
		{
			std::cout << RED "Error: could not open file." BLANK << std::endl;
			return (1);
		}
		return (btc.doExchange(argv[1]));
	}
	catch(BitcoinExchange::BadError &e)
	{
		std::cerr << e.what() << std::endl;
		return (1);
	}
}
