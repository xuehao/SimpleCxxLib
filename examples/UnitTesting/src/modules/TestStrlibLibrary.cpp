/*
 * File: TestStrlibLibrary.cpp
 * ---------------------------
 * This file tests the functions in the strlib.h interface.
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

#include <iostream>
#include <sstream>
#include <string>
#include "error.h"
#include "strlib.h"
#include "unittest.h"
using namespace std;

/* Function prototypes */

static void testEqualsIgnoreCase();
static void testStartsWith();
static void testEndsWith();
static void testToLowerCase();
static void testToUpperCase();
static void testIntegerToString();
static void testStringToInteger();
static void testRealToString();
static void testStringToReal();
static void testTrim();
static void testReadQuotedString();
static void testWriteQuotedString();

/* Unit test */

void testStrlibLibrary() {
    testEqualsIgnoreCase();
    testStartsWith();
    testEndsWith();
    testToLowerCase();
    testToUpperCase();
    testIntegerToString();
    testStringToInteger();
    testRealToString();
    testStringToReal();
    testTrim();
    testReadQuotedString();
    testWriteQuotedString();
    reportResult("strlib.h library");
}

/* Private functions */

static void testEqualsIgnoreCase() {
    test(equalsIgnoreCase("cat", "dog"), false);
    test(equalsIgnoreCase("abcde", "abcde"), true);
    test(equalsIgnoreCase("ABCDE", "abcde"), true);
    test(equalsIgnoreCase("abc", "abcde"), false);
    test(equalsIgnoreCase("abcde", "abc"), false);
    test(equalsIgnoreCase("", ""), true);
}

static void testStartsWith() {
    test(startsWith("", ""), true);
    test(startsWith("", "xyz"), false);
    test(startsWith("start", ""), true);
    test(startsWith("start", "star"), true);
    test(startsWith("start", "start"), true);
    test(startsWith("start", "startx"), false);
    test(startsWith("start", 's'), true);
    test(startsWith("", 's'), false);
}

static void testEndsWith() {
    test(endsWith("", ""), true);
    test(endsWith("", "xyz"), false);
    test(endsWith("start", ""), true);
    test(endsWith("start", "tart"), true);
    test(endsWith("start", "start"), true);
    test(endsWith("start", "xstart"), false);
    test(endsWith("start", 't'), true);
    test(endsWith("", 't'), false);
}

static void testToLowerCase() {
    test(toLowerCase("ABC"), "abc");
    test(toLowerCase("#A1"), "#a1");
    declare(string str = "ABC");
}

static void testToUpperCase() {
    test(toUpperCase("abc"), "ABC");
    test(toUpperCase("#a1"), "#A1");
    declare(string str = "abc");
}

static void testIntegerToString() {
    test(integerToString(0), "0");
    test(integerToString(1234567), "1234567");
    test(integerToString(-17), "-17");
}

static void testStringToInteger() {
    test(stringToInteger("1234"), 1234);
    test(stringToInteger("-42"), -42);
    checkError(stringToInteger("X"), "stringToInteger: Illegal integer format (X)");
}

static void testRealToString() {
    test(realToString(0), "0");
    test(realToString(3.1416), "3.1416");
    test(realToString(-2.3), "-2.3");
    test(realToString(1.75E+15), "1.75E+15");
}

static void testStringToReal() {
    test(stringToReal("1234"), 1234.0);
    test(stringToReal("-4.2"), -4.2);
    test(stringToReal("1.28E-15"), 1.28E-15);
    checkError(stringToReal("X"), "stringToReal: Illegal floating-point format (X)");
}

static void testTrim() {
    test(trim("abcde"), "abcde");
    test(trim("\tabcde  "), "abcde");
    test(trim(""), "");
}

static void testReadQuotedString() {
    declare(istringstream iss("two words, abc , ' quoted ', '\\a\\101\\''"));
    declare(string str);
    trace(readQuotedString(iss, str));
    test(str, "two words");
    test(iss.get(), ',');
    trace(readQuotedString(iss, str));
    test(str, "abc");
    test(iss.get(), ',');
    trace(readQuotedString(iss, str));
    test(str, " quoted ");
    test(iss.get(), ',');
    trace(readQuotedString(iss, str));
    test(str, "\aA'");
    trace(readQuotedString(iss, str));
    test(iss.fail(), true);
}

static void testWriteQuotedString() {
    declare(ostringstream oss);
    trace(writeQuotedString(oss, "\a\101\""));
    test(oss.str(), "\"\\aA\\042\"");
}
