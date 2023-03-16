/*
 * File: simpio.cpp
 * ----------------
 * This file implements the simpio.h interface.
 */

/*************************************************************************/
/* Stanford Portable Library                                             */
/* Copyright (c) 2014 by Eric Roberts <eroberts@cs.stanford.edu>         */
/*                                                                       */
/* This program is free software: you can redistribute it and/or modify  */
/* it under the terms of the GNU General Public License as published by  */
/* the Free Software Foundation, either version 3 of the License, or     */
/* (at your option) any later version.                                   */
/*                                                                       */
/* This program is distributed in the hope that it will be useful,       */
/* but WITHOUT ANY WARRANTY; without even the implied warranty of        */
/* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the         */
/* GNU General Public License for more details.                          */
/*                                                                       */
/* You should have received a copy of the GNU General Public License     */
/* along with this program.  If not, see <http://www.gnu.org/licenses/>. */
/*************************************************************************/

#include "simpio.h"
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>

/*
 * Implementation notes: getInteger, getLong, getReal
 * --------------------------------------------------
 * Each of these functions reads a complete input line and then uses the
 * <sstream> library to parse that line into a value of the desired type.
 * If that fails, the implementation asks the user for a new value.
 */

int getInteger(std::string prompt) {
    int value;
    std::string line;
    while (true) {
        std::cout << prompt;
        getline(std::cin, line);
        std::istringstream stream(line);
        stream >> value;
        if (!stream.fail() && stream.eof())
            break;
        std::cout << "Illegal integer format. Try again." << std::endl;
        if (prompt == "")
            prompt = "Enter an integer: ";
    }
    return value;
}

long getLong(std::string prompt) {
    long value;
    std::string line;
    while (true) {
        std::cout << prompt;
        getline(std::cin, line);
        std::istringstream stream(line);
        stream >> value;
        if (!stream.fail() && stream.eof())
            break;
        std::cout << "Illegal long integer format. Try again." << std::endl;
        if (prompt == "")
            prompt = "Enter a long integer: ";
    }
    return value;
}

long long getLongLong(std::string prompt) {
    long long value;
    std::string line;
    while (true) {
        std::cout << prompt;
        getline(std::cin, line);
        std::istringstream stream(line);
        stream >> value;
        if (!stream.fail() && stream.eof())
            break;
        std::cout << "Illegal long long integer format. Try again." << std::endl;
        if (prompt == "")
            prompt = "Enter a long long integer: ";
    }
    return value;
}

double getReal(std::string prompt) {
    double value;
    std::string line;
    while (true) {
        std::cout << prompt;
        getline(std::cin, line);
        std::istringstream stream(line);
        stream >> value;
        if (!stream.fail() && stream.eof())
            break;
        std::cout << "Illegal numeric format. Try again." << std::endl;
        if (prompt == "")
            prompt = "Enter a number: ";
    }
    return value;
}

/*
 * Implementation notes: getLine
 * -----------------------------
 * The getLine function simply combines the process of displaying a
 * prompt and reading an input line into a single call.  The primary
 * reason for including this function in the library is to ensure
 * that the process of reading integers, floating-point numbers, and
 * strings remains as consistent as possible.
 */

std::string getLine(std::string prompt) {
    std::string line;
    std::cout << prompt;
    getline(std::cin, line);
    return line;
}
