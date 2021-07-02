/*
 ******************************************************************
 *           C++ Basic Mathematical Calculator                    *
 *                                                                *
 * Author: Vitaly German (2021)                                   *
 * URL: https://github.com/novaua/							      *
 *                                                                *
 * Copyright notice:                                              *
 * Free use of the  C++ Basic Mathematical Calculator is          *
 * permitted under the guidelines and in accordance with the most *
 * current version of the MIT License.                            *
 * http://www.opensource.org/licenses/MIT                         *
 *                                                                *
 * Example expressions:                                           *
 * (3 + 4 / 2) * (6 - 2 / 2)                                      *
 * (3 ^ 2 / 2)                                                    *
 ******************************************************************
*/

#include <string>
#include <stack>
#include <stdexcept>
#include <cmath> // std::pow

enum class Priority {
	Nop,
	Low,
	High
};

const char DELIM = '|';

Priority isOperator(char c) {
	static const std::string OPS = "+-/*^";
	auto pos = OPS.find(c);

	if (pos == std::string::npos)
		return Priority::Nop;

	if (pos < 2)
		return Priority::Low;

	return Priority::High;
}

std::string toReversePolish(const std::string& expr)
{
	std::stack<char> opStack;
	std::string result;

	opStack.push('(');
	auto input = expr + ')';
	size_t i = 0;
	for (; !opStack.empty(); i++)
	{
		auto currentToken = input[i];
		if (std::isblank(currentToken))
			continue;

		if (currentToken == '(') {
			opStack.push('(');
		}
		else if (currentToken == ')')
		{
			while (opStack.top() != '(')
			{
				result += opStack.top();
				opStack.pop();
				if (opStack.empty())
					throw std::logic_error("Invalid input:'No opening bracket found.'");
			}

			opStack.pop();
		}
		else if (std::isdigit(currentToken))
		{
			result += DELIM;
			while (i < input.size() && (input[i] == '.' || std::isdigit(input[i])))
			{
				result += input[i];
				i++;
			}

			i--;
			result += DELIM;
		}
		else if (isOperator(currentToken) == Priority::High)
		{
			while (!opStack.empty() && isOperator(opStack.top()) == Priority::High)
			{
				result += opStack.top();
				opStack.pop();
			}

			opStack.push(currentToken);
		}
		else if (isOperator(currentToken) == Priority::Low)
		{
			while (!opStack.empty() && isOperator(opStack.top()) != Priority::Nop)
			{
				result += opStack.top();
				opStack.pop();
			}

			opStack.push(currentToken);
		}
		else
		{
			if (!opStack.empty() && currentToken == '\0')
				throw std::logic_error("Invalid input: 'No closing bracket found.'");

			throw std::logic_error(std::string("Invalid input: '") + currentToken + "'.");
		}
	}

	input.pop_back();
	auto unparsed = input.substr(i - 1);

	if (!unparsed.empty())
		throw std::logic_error(std::string("Invalid input: Unparsed '") + unparsed + "'.");

	return result;
}

double evaluate(const std::string& postfix)
{
	std::stack<double> valueStack;
	for (size_t i = 0; i < postfix.length(); i++)
	{
		if (postfix[i] == DELIM)
		{
			i++;
			std::string tmp;
			while (postfix[i] != DELIM)
				tmp += postfix[i++];

			valueStack.push(stod(tmp));
		}
		else
		{
			double raval = valueStack.top();
			valueStack.pop();
			switch (postfix[i])
			{
			case '+':
				valueStack.top() += raval;
				break;

			case '-':
				valueStack.top() -= raval;
				break;

			case '*':
				valueStack.top() *= raval;
				break;

			case '/':
				valueStack.top() /= raval;
				break;

			case '^':
				valueStack.top() = std::pow(valueStack.top(), raval);
				break;
			}
		}
	}

	return valueStack.top();
}
