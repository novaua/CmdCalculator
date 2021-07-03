/*
 ******************************************************************
 *           C++ Basic Mathematical Calculator                    *
 *                                                                *
 * Author: VitalyG (2021)                                   *
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

#include "ExprCalculator.h"

#include <string>
#include <stack>
#include <stdexcept>
#include <cmath> // std::pow

List toReversePolish(const std::string& expr)
{
	std::stack<std::string> opStack;
	List result;

	opStack.push("(");
	auto input = expr + ')';
	size_t i = 0;
	for (; !opStack.empty(); i++)
	{
		auto currentToken = input[i];
		if (std::isblank(currentToken))
			continue;

		if (currentToken == '(') {
			opStack.push("(");
		}
		else if (currentToken == ')')
		{
			while (opStack.top() != "(")
			{
				result.push_back(opStack.top());
				opStack.pop();
				if (opStack.empty())
					throw std::logic_error("Invalid input:'No opening bracket found.'");
			}

			opStack.pop();
		}
		else if (std::isdigit(currentToken))
		{
			std::string digit;
			while (i < input.size() && (input[i] == '.' || std::isdigit(input[i])))
			{
				digit += input[i];
				i++;
			}

			i--;
			result.push_back(digit);
		}
		else if (isOperator(currentToken) == Priority::High)
		{
			while (!opStack.empty() && isOperator(opStack.top()) == Priority::High)
			{
				result.push_back(opStack.top());
				opStack.pop();
			}

			opStack.push(std::string(1, currentToken));
		}
		else if (isOperator(currentToken) == Priority::Low)
		{
			while (!opStack.empty() && isOperator(opStack.top()) != Priority::Nop)
			{
				result.push_back(opStack.top());
				opStack.pop();
			}

			opStack.push(std::string(1, currentToken));
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

double evaluate(const List& postfix)
{
	std::stack<double> valueStack;
	for (const auto& element : postfix)
	{
		if (isOperator(element) == Priority::Nop)
		{
			valueStack.push(stod(element));
		}
		else
		{
			auto rightValue = valueStack.top();
			valueStack.pop();
			switch (element[0])
			{
			case '+':
				valueStack.top() += rightValue;
				break;

			case '-':
				valueStack.top() -= rightValue;
				break;

			case '*':
				valueStack.top() *= rightValue;
				break;

			case '/':
				valueStack.top() /= rightValue;
				break;

			case '^':
				valueStack.top() = std::pow(valueStack.top(), rightValue);
				break;

			default:
				throw std::logic_error(std::string("Unknown operator: '") + element + "'.");
			}
		}
	}

	return valueStack.top();
}

