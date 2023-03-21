#include "BitcoinExchange.hpp"


static std::string	getFile(std::string path)
{
	std::ifstream	f;
	std::string		buff;
	std::string		res;

	f.open(path);
	if (!f)
	{
		res = "";
	}
	else
	{
		while (std::getline(f, buff))
		{
			if (f.eof())
				break;
			res += buff;
			res += "\n";
		}
		res += buff;
	}
	f.close();
	return (res);
}

static std::string	freplace(std::string str, std::string src, std::string pst)
{
	std::string	res;
	std::string buff;

	for (int x=0; x < str.size(); x++)
	{
		if (str[x] == src[0])
		{
			buff = str.substr(x, src.size());
			if (!buff.compare(src))
			{
				res += pst;
				x += src.size() - 1;
			}
		}
		else
			res += str[x];
	}
	return (res);
}

static bool checkDigits(std::string str)
{
	int		size = str.length();

	for (int x = 0; x < size; x++)
	{
		if ((str[x] < 48 || str[x] > 57) && str[x] != '.')
			return (true);
	}
	return (false);
}

BitcoinExchange::BitcoinExchange()
{
	try
	{
		this->parseData("data.csv");
	}
	catch (BitcoinExchange::DataNotFound &a)
	{
		std::cout << a.what() << std::endl;
		throw BitcoinExchange::BadError();
	}
	catch (BitcoinExchange::CorruptedDataFile &a)
	{
		std::cout << a.what() << std::endl;
		throw BitcoinExchange::BadError();
	}
}

BitcoinExchange::BitcoinExchange(const BitcoinExchange &btc)
{
	*this = btc;
}


BitcoinExchange::BitcoinExchange(std::string path_data)
{
	try
	{
		this->parseData(path_data);
	}
	catch (BitcoinExchange::DataNotFound &a)
	{
		std::cout << a.what() << std::endl;
		throw BitcoinExchange::BadError();
	}
	catch (BitcoinExchange::CorruptedDataFile &a)
	{
		std::cout << a.what() << std::endl;
		throw BitcoinExchange::BadError();
	}
}

BitcoinExchange::~BitcoinExchange() {}


void	BitcoinExchange::parseData(std::string path)
{
	std::string	raw, line, date, value;
	size_t		pos2 = 0;
	size_t		pos;
	std::string	del = "\n";


	raw = getFile(path);

	if (raw == "")
		throw BitcoinExchange::DataNotFound();
	pos = raw.find(del);
	raw.erase(0, pos + del.length());
	while ((pos = raw.find(del)) != std::string::npos)
	{
		line = raw.substr(0, pos);
		raw.erase(0, pos + del.length());
		pos2 = line.find(",");
		if (pos2 == -1)
			BitcoinExchange::CorruptedDataFile();
		date = line.substr(0, pos2);
		value = line.substr(pos2 + 1, line.length() - 2);
		this->_data[date] = value;
	}
}

BitcoinExchange	&BitcoinExchange::operator=(const BitcoinExchange &btc)
{
	if (this == &btc)
		return *(this);
	return *(this);
}

std::map<std::string, std::string>	BitcoinExchange::getData()
{
	return this->_data;
}

int	BitcoinExchange::doExchange(char *path)
{
	int				i;
	float			fvalue;
	char			date[100], value[100];
	FILE			*f = fopen(path, "r");

	if (!f)
	{
		std::cout << RED "Error: bad input: wrong path." BLANK << std::endl;
		return (1);
	}

	i = fscanf(f, "%s | %s\n", date, value);
	if (i != 2)
	{
		std::cout << RED "Error: bad input: header not present." BLANK << std::endl;
		fclose(f);
		return (1);
	}
	while ((i = fscanf(f, "%s | %s\n", date, value)) != -1)
	{
		if (i != 2)
		{
			std::cout << RED "Error: bad input." BLANK << std::endl;
			continue ;
		}

		if (checkDigits(value))
		{
			std::cout << RED "Error: bad input: value has digits" BLANK << std::endl;
			continue ;
		}

		std::map<std::string, std::string>::iterator temp = this->_data.find(date);
		if (temp == this->_data.end())
		{
			std::cout << RED "Error: bad input: date not found." BLANK << std::endl;
			continue ;
		}

		if (std::atof(value) > 1000)
		{
			std::cout << RED "Error: bad input: too large number." BLANK << std::endl;
			continue ;
		}
		else if (std::atof(value) < 0)
		{
			std::cout << RED "Error: bad input: negative number." BLANK << std::endl;
			continue ;
		}
		fvalue = std::stof((std::string) temp->second) * std::atof(value);

		std::cout << date << " => " << value << " = " << fvalue << std::endl;
		memset(date, 0, 100);
		memset(value, 0, 100);
	}
	fclose(f);
	return (0);
}
