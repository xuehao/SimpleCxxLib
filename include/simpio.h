/*
 * File: simpio.h
 * --------------
 * This file exports a set of functions that simplify input/output
 * operations in C++ and provide some error-checking on console input.
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

#ifndef _simpio_h
#define _simpio_h

#include <string>

/*
 * Function: getInteger
 * Usage: int n = getInteger(prompt);
 * ----------------------------------
 * Reads a complete line from <code>cin</code> and scans it as an
 * integer. If the scan succeeds, the integer value is returned. If
 * the argument is not a legal integer or if extraneous characters
 * (other than whitespace) appear in the string, the user is given
 * a chance to reenter the value. If supplied, the optional
 * <code>prompt</code> string is printed before reading the value.
 */

int getInteger(std::string prompt = "");
long getLong(std::string prompt = "");
long long getLongLong(std::string prompt = "");

/*
 * Function: getReal
 * Usage: double x = getReal(prompt);
 * ----------------------------------
 * Reads a complete line from <code>cin</code> and scans it as a
 * floating-point number. If the scan succeeds, the floating-point
 * value is returned.  If the input is not a legal number or if
 * extraneous characters (other than whitespace) appear in the string,
 * the user is given a chance to reenter the value. If supplied, the
 * optional <code>prompt</code> string is printed before reading the value.
 */

double getReal(std::string prompt = "");

/*
 * Function: getLine
 * Usage: string line = getLine(prompt);
 * -------------------------------------
 * Reads a line of text from <code>cin</code> and returns that line
 * as a string.  The newline character that terminates the input is
 * not stored as part of the return value.  If supplied, the optional
 * <code>prompt</code> string is printed before reading the value.
 */

std::string getLine(std::string prompt = "");

#endif
