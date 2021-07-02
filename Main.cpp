#include "ExprCalculator.h"

void parseAndPrint(const std::string& exp) {
	try {
		std::string post = toReversePolish(exp);
#ifdef _DEBUG
		std::cout << post << std::endl;
#endif
		std::cout << evaluate(post) << std::endl;
	}
	catch (const std::logic_error& e) {
		std::cerr << e.what() << std::endl;
	}
}

int main(int argc, char* argv[])
{
	if (argc > 1) {
		std::string cmdInput;
		for (int i = 1; i < argc; ++i) {
			cmdInput += argv[i];
		};

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
		try {
			std::string post = toReversePolish(exp);
#ifdef _DEBUG
			std::cout << post << std::endl;
#endif
			std::cout << evaluate(post) << std::endl;
		}
		catch (const std::logic_error& e) {
			std::cerr << e.what() << std::endl;
		}
	}
}
