#include <iostream>
#include <vector>
#include <stack>

int calculate(int a, int b, const std::string &operation)
{
	if (operation == "+")
		return a + b;
	if (operation == "-")
		return a - b;
	if (operation == "*")
		return a * b;
	if (operation == "/")
		return a / b;
	return -1;
}

bool isOp(char op)
{
	return op == '+' || op == '-' || op == '*' || op == '/';
}

bool isOperation(const std::string& op)
{
	return op == "+" || op == "-" || op == "*" || op == "/";
}

int	RPN(std::vector<std::string> vec)
{
	std::stack<int>	numbers;
	int				size = vec.size();

	for (int i = 0; i < size; i++)
	{
		if (isOperation(vec[i]))
		{
			int n2 = numbers.top(); numbers.pop();
			int n1 = numbers.top(); numbers.pop();

			numbers.push(calculate(n1, n2, vec[i]));
		}
		else
		{
			try
			{
				numbers.push(std::stoi(vec[i]));
			}
			catch(std::exception &e)
			{
				throw std::exception();
			}
		}
	}
	return (numbers.top());
}

std::vector<std::string> parse(std::string input)
{
	int							size = input.length();
	std::vector<std::string>	vec;
	std::string					num;

	for (int x = 0; x < size; x++)
	{
		if (std::isdigit(input[x]))
		{
			num += input[x];
		}
		else if (isOp(input[x]))
		{
			num += input[x];
			vec.push_back(num);
			num = "";
		}
		else if (input[x] == ' ')
		{
			if (num != "")
				vec.push_back(num);
			num = "";
		}
		else
			throw std::exception();
	}
	return (vec);
}

int main(int argc, char **argv)
{
	try
	{
		std::vector<std::string> notation = parse(argv[1]);
		std::cout << RPN(notation) << std::endl;
	}
	catch(std::exception &e)
	{
		std::cerr << "Error: Bad input." << '\n';
	}

	return (0);
}
