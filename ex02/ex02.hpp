
#include <algorithm>
#include <set>
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

template<typename Iterator>
void insertionSort(Iterator begin, Iterator end)
{
	for (Iterator i = begin; i != end; ++i)
	{
		Iterator j = i;
		while (j != begin && *j < *(std::prev(j)))
		{
			std::iter_swap(j, std::prev(j));
			j--;
		}
	}
}

template<typename Iterator>
void mergeInsertSort(Iterator begin, Iterator end, int cutoff = 10)
{
	if (std::distance(begin, end) <= cutoff)
		insertionSort(begin, end);
	else
	{
		Iterator middle = begin;
		std::advance(middle, std::distance(begin, end) / 2);
		mergeInsertSort(begin, middle, cutoff);
		mergeInsertSort(middle, end, cutoff);
		std::inplace_merge(begin, middle, end);
	}
}

