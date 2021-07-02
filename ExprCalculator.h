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

#pragma once

#include <string>
#include <iostream>

std::string toReversePolish(const std::string& input);

double evaluate(const std::string& postfix);
