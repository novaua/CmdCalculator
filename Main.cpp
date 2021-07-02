#include "ExprCalculator.h"

int main()
{
	std::string exp;
	while (true)
	{
		std::cout << "Enter your expression ('e' to exit)"
			<< std::endl << std::flush;

		std::getline(std::cin, exp);
		if (exp == "e")
			break;
		try {
			std::string post = toReversePolish(exp);
			std::cout << post << std::endl;
			std::cout << evaluate(post) << std::endl;
		}
		catch (const std::logic_error& e) {
			std::cerr << e.what() << std::endl;
		}
	}
}
