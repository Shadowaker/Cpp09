
#include "ex02.hpp"

void	checkDigits(char **input)
{
	int	size;
	std::set<std::string>	s;

	for (int x = 1; input[x]; x++)
	{
		size = strlen(input[x]);
		for (int y = 0; y < size; y++)
		{
			if (!std::isdigit(input[x][y]))
			{
				throw std::exception();
			}
		}
		/*
		if (s.find(input[x]) != s.end())
		{
			std::cout << "CULO" << std::endl;
			throw std::exception();
		}*/
		s.insert(input[x]);
	}
}

int main(int argc, char **argv)
{
	std::list<int> l;
	std::deque<int> d;

	if (argc < 2)
	{
		std::cerr << RED "Error: wrong number of params." BLANK << std::endl;
		return 1;
	}
	try
	{
		checkDigits(argv);
		for (int x = 1; argv[x]; x++)
		{
			int t = atoi(argv[x]);
			l.push_back(t);
			d.push_back(t);
		}
	}
	catch(const std::exception& e)
	{
		std::cerr << RED "Error: wrong param given." BLANK << std::endl;
		return 1;
	}


	std::cout << GREEN "Before: " BLANK;
	for (std::list<int>::iterator i = l.begin(); i != l.end(); i++)
		std::cout << " " << *i;
	std::cout << std::endl;
	std::cout << std::endl;

	std::clock_t start = std::clock();
	mergeInsertSort(l.begin(), l.end());
	std::clock_t end = std::clock();
	double seconds = static_cast<double> (end - start) / CLOCKS_PER_SEC;

	std::cout << YELLOW "After with std::list:" BLANK;
	for (std::list<int>::iterator i = l.begin(); i != l.end(); i++)
		std::cout << " " << *i;
	std::cout << std::endl;
	std::cout << MAGENTA "Time: " CYAN << seconds << MAGENTA " seconds" BLANK << std::endl;
	std::cout << std::endl;
	std::cout << std::endl;

	start = std::clock();
	mergeInsertSort(d.begin(), d.end());
	end = std::clock();
	seconds = static_cast<double>(end - start) / CLOCKS_PER_SEC;

	std::cout << YELLOW "After with std::deque:" BLANK;
	for (std::deque<int>::iterator i = d.begin(); i != d.end(); i++)
		std::cout << " " << *i;
	std::cout << std::endl;
	std::cout << MAGENTA "Time: " CYAN << seconds << MAGENTA " seconds" BLANK << std::endl;
	std::cout << std::endl;
}
