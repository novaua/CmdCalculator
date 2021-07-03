#include "ExprCalculator.h"

const char delimiter = ' ';

void print(const List& inputList)
{
	for (const auto& element : inputList)
	{
		if (std::holds_alternative<double>(element))
		{
			std::cout << std::get<double>(element) << delimiter;
		}
		else
		{
			std::cout << std::get<std::string>(element) << delimiter;
		}
	}

	if (!inputList.empty())
		std::cout << std::endl;
}

int parseAndPrint(const std::string& exp) {
	try {
		auto post = toReversePolish(exp);
#ifdef _DEBUG
		print(post);
#endif
		std::cout << evaluate(post) << std::endl;
	}
	catch (const std::logic_error& e) {
		std::cerr << e.what() << std::endl;
		return 0;
	}
	catch (const std::exception& e)
	{
		std::cerr << e.what() << std::endl;
		return -1;
	}

	return 0;
}

int main(int argc, char* argv[])
{
	if (argc > 1) {
		std::string cmdInput;
		for (int i = 1; i < argc; ++i) {
			cmdInput += argv[i];
		}

		parseAndPrint(cmdInput);
		return 0;
	}

	std::string exp;
	while (true)
	{
		std::cout << "Enter expression ('e' or enter to exit)"
			<< std::endl << std::flush;

		std::getline(std::cin, exp);
		if (exp == "e" || exp.empty())
			break;

		int stat = parseAndPrint(exp);
		if (stat != 0)
			return stat;
	}

	return 0;
}
