/*
 * File: strlib.cpp
 * ----------------
 * This file implements the strlib.h interface.
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

#include "strlib.h"
#include <cctype>
#include <iomanip>
#include <iostream>
#include <sstream>
#include "error.h"

/* Function prototypes */

/*
 * Implementation notes: numeric conversion
 * ----------------------------------------
 * These functions use the <sstream> library to perform the conversion.
 */

std::string integerToString(int n) {
    std::ostringstream stream;
    stream << n;
    return stream.str();
}

int stringToInteger(std::string str) {
    std::istringstream stream(str);
    int value;
    stream >> value;
    if (stream.fail() || !stream.eof()) {
        error("stringToInteger: Illegal integer format (" + str + ")");
    }
    return value;
}

std::string realToString(double d) {
    std::ostringstream stream;
    stream << std::uppercase << d;
    return stream.str();
}

double stringToReal(std::string str) {
    std::istringstream stream(str);
    double value;
    stream >> value;
    if (stream.fail() || !stream.eof()) {
        error("stringToReal: Illegal floating-point format (" + str + ")");
    }
    return value;
}

/*
 * Implementation notes: case conversion
 * -------------------------------------
 * The functions toUpperCase and toLowerCase return a new string whose
 * characters appear in the desired case. These implementations rely on
 * the fact that the characters in the string are copied when the
 * argument is passed to the function, which makes it possible to change
 * the case of the copy without affecting the original.
 */

std::string toUpperCase(std::string str) {
    int nChars = str.length();
    for (int i = 0; i < nChars; i++) {
        str[i] = toupper(str[i]);
    }
    return str;
}

std::string toLowerCase(std::string str) {
    int nChars = str.length();
    for (int i = 0; i < nChars; i++) {
        str[i] = tolower(str[i]);
    }
    return str;
}

/*
 * Implementation notes: equalsIgnoreCase
 * --------------------------------------
 * This implementation uses a for loop to cycle through the characters in
 * each string.  Converting each string to uppercase and then comparing
 * the results makes for a shorter but less efficient implementation.
 */

bool equalsIgnoreCase(std::string s1, std::string s2) {
    if (s1.length() != s2.length())
        return false;
    int nChars = s1.length();
    for (int i = 0; i < nChars; i++) {
        if (tolower(s1[i]) != tolower(s2[i]))
            return false;
    }
    return true;
}

/*
 * Implementation notes: startsWith, endsWith
 * ------------------------------------------
 * These implementations are overloaded to allow the second argument to
 * be either a string or a character.
 */

bool startsWith(std::string str, std::string prefix) {
    if (str.length() < prefix.length())
        return false;
    int nChars = prefix.length();
    for (int i = 0; i < nChars; i++) {
        if (str[i] != prefix[i])
            return false;
    }
    return true;
}

bool startsWith(std::string str, char prefix) {
    return str.length() > 0 && str[0] == prefix;
}

bool endsWith(std::string str, std::string suffix) {
    int nChars = suffix.length();
    int start = str.length() - nChars;
    if (start < 0)
        return false;
    for (int i = 0; i < nChars; i++) {
        if (str[start + i] != suffix[i])
            return false;
    }
    return true;
}

bool endsWith(std::string str, char suffix) {
    return str.length() > 0 && str[str.length() - 1] == suffix;
}

std::string trim(std::string str) {
    int finish = str.length() - 1;
    while (finish >= 0 && isspace(str[finish])) {
        finish--;
    }
    int start = 0;
    while (start <= finish && isspace(str[start])) {
        start++;
    }
    return str.substr(start, finish - start + 1);
}

/*
 * Implementation notes: readQuotedString and writeQuotedString
 * ------------------------------------------------------------
 * Most of the work in these functions has to do with escape sequences.
 */

static const std::string STRING_DELIMITERS = ",:)}]\n";

bool stringNeedsQuoting(const std::string& str) {
    int n = str.length();
    for (int i = 0; i < n; i++) {
        char ch = str[i];
        if (isspace(ch))
            return false;
        if (STRING_DELIMITERS.find(ch) != std::string::npos)
            return true;
    }
    return false;
}

void readQuotedString(std::istream& is, std::string& str) {
    str = "";
    char ch;
    while (is.get(ch) && isspace(ch)) {
        /* Empty */
    }
    if (is.fail())
        return;
    if (ch == '\'' || ch == '"') {
        char delim = ch;
        while (is.get(ch) && ch != delim) {
            if (is.fail())
                error("Unterminated string");
            if (ch == '\\') {
                if (!is.get(ch))
                    error("Unterminated string");
                if (isdigit(ch) || ch == 'x') {
                    int maxDigits = 3;
                    int base = 8;
                    if (ch == 'x') {
                        base = 16;
                        maxDigits = 2;
                    }
                    int result = 0;
                    int digit = 0;
                    for (int i = 0; i < maxDigits && ch != delim; i++) {
                        if (isdigit(ch)) {
                            digit = ch - '0';
                        } else if (base == 16 && isxdigit(ch)) {
                            digit = toupper(ch) - 'A' + 10;
                        } else {
                            break;
                        }
                        result = base * result + digit;
                        if (!is.get(ch))
                            error("Unterminated string");
                    }
                    ch = char(result);
                    is.unget();
                } else {
                    switch (ch) {
                        case 'a':
                            ch = '\a';
                            break;
                        case 'b':
                            ch = '\b';
                            break;
                        case 'f':
                            ch = '\f';
                            break;
                        case 'n':
                            ch = '\n';
                            break;
                        case 'r':
                            ch = '\r';
                            break;
                        case 't':
                            ch = '\t';
                            break;
                        case 'v':
                            ch = '\v';
                            break;
                        case '"':
                            ch = '"';
                            break;
                        case '\'':
                            ch = '\'';
                            break;
                        case '\\':
                            ch = '\\';
                            break;
                    }
                }
            }
            str += ch;
        }
    } else {
        str += ch;
        int endTrim = 0;
        while (is.get(ch) && STRING_DELIMITERS.find(ch) == std::string::npos) {
            str += ch;
            if (!isspace(ch))
                endTrim = str.length();
        }
        if (is)
            is.unget();
        str = str.substr(0, endTrim);
    }
}

void writeQuotedString(std::ostream& os, const std::string& str, bool forceQuotes) {
    if (!forceQuotes && stringNeedsQuoting(str))
        forceQuotes = true;
    if (forceQuotes)
        os << '"';
    int len = str.length();
    for (int i = 0; i < len; i++) {
        char ch = str.at(i);
        switch (ch) {
            case '\a':
                os << "\\a";
                break;
            case '\b':
                os << "\\b";
                break;
            case '\f':
                os << "\\f";
                break;
            case '\n':
                os << "\\n";
                break;
            case '\r':
                os << "\\r";
                break;
            case '\t':
                os << "\\t";
                break;
            case '\v':
                os << "\\v";
                break;
            case '\\':
                os << "\\\\";
                break;
            default:
                if (isprint(ch) && ch != '"') {
                    os << ch;
                } else {
                    std::ostringstream oss;
                    oss << std::oct << std::setw(3) << std::setfill('0') << (int(ch) & 0xFF);
                    os << "\\" << oss.str();
                }
        }
    }
    if (forceQuotes)
        os << '"';
}
