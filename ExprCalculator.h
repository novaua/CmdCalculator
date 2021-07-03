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

#pragma once

#include <string>
#include <iostream>
#include <list>

typedef std::list<std::string> List;

List toReversePolish(const std::string& expr);

double evaluate(const List& postfix);

enum class Priority {
	Nop,
	Low,
	High
};

template<class T>
Priority isOperator(const T& c) {
	static const std::string OPS = "+-/*^";
	auto pos = OPS.find(c);

	if (pos == std::string::npos)
		return Priority::Nop;

	if (pos < 2)
		return Priority::Low;

	return Priority::High;
}
