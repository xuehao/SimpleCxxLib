/*
 * File: TestTokenScannerClass.cpp
 * -------------------------------
 * This file contains a unit test of the TokenScanner class.
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

#include <fstream>
#include <iostream>
#include <string>
#include "tokenscanner.h"
#include "unittest.h"
using namespace std;

static void testStringScanner();
static void testStreamScanner();
static void testScannerNoOptions();
static void testScannerLanguageOptions();
static void testScanNumbers();
static void testScanEscapeSequences();

void testTokenScannerClass() {
    testStringScanner();
    testStreamScanner();
    testScanEscapeSequences();
    reportResult("TokenScanner class");
}

static void testStringScanner() {
    testScannerNoOptions();
    testScannerLanguageOptions();
    testScanNumbers();
}

static void testStreamScanner() {
    declare(TokenScanner scanner);
    declare(ifstream infile);
    trace(infile.open("TestTokenScannerClass.cpp"));
    test(infile.fail(), false);
    trace(scanner.setInput(infile));
    test(scanner.hasMoreTokens(), true);
    test(scanner.nextToken(), "/");
    test(scanner.nextToken(), "*");
    test(scanner.hasMoreTokens(), true);
    test(scanner.nextToken(), "\n");
    test(scanner.hasMoreTokens(), true);
    test(scanner.nextToken(), " ");
    test(scanner.nextToken(), "*");
    test(scanner.nextToken(), " ");
    test(scanner.nextToken(), "File");
    trace(scanner.ignoreWhitespace());
    trace(scanner.scanStrings());
    test(scanner.nextToken(), ":");
    test(scanner.nextToken(), "TestTokenScannerClass");
    test(scanner.nextToken(), ".");
    test(scanner.nextToken(), "cpp");
    test(scanner.nextToken(), "*");
    test(scanner.nextToken(), "-");
    trace(infile.close());
}

static void testScannerNoOptions() {
    declare(TokenScanner scanner);
    declare(string token);
    trace(scanner.setInput("cout << \"pi = \" << 3.14159265 << endl;"));
    test(scanner.hasMoreTokens(), true);
    test(token = scanner.nextToken(), "cout");
    test(scanner.getTokenType(token), WORD);
    test(token = scanner.nextToken(), " ");
    test(scanner.getTokenType(token), SEPARATOR);
    test(token = scanner.nextToken(), "<");
    test(scanner.getTokenType(token), OPERATOR);
    test(scanner.nextToken(), "<");
    test(scanner.nextToken(), " ");
    test(scanner.nextToken(), "\"");
    test(scanner.nextToken(), "pi");
    test(scanner.nextToken(), " ");
    test(scanner.nextToken(), "=");
    test(scanner.nextToken(), " ");
    test(scanner.nextToken(), "\"");
    test(scanner.nextToken(), " ");
    test(scanner.nextToken(), "<");
    test(scanner.nextToken(), "<");
    test(scanner.nextToken(), " ");
    test(token = scanner.nextToken(), "3");
    test(scanner.getTokenType(token), NUMBER);
    test(scanner.nextToken(), ".");
    test(scanner.nextToken(), "14159265");
    test(scanner.nextToken(), " ");
    test(scanner.nextToken(), "<");
    test(scanner.nextToken(), "<");
    test(scanner.nextToken(), " ");
    test(scanner.nextToken(), "endl");
    test(scanner.nextToken(), ";");
    test(scanner.hasMoreTokens(), false);
    test(token = scanner.nextToken(), "");
    test(scanner.getTokenType(token), EOF);
}

static void testScannerLanguageOptions() {
    declare(TokenScanner scanner);
    declare(string token);
    trace(scanner.ignoreWhitespace());
    trace(scanner.scanStrings());
    trace(scanner.scanNumbers());
    trace(scanner.addWordCharacters("_"));
    trace(scanner.addOperator("=="));
    trace(scanner.addOperator("!="));
    trace(scanner.addOperator("<="));
    trace(scanner.addOperator(">="));
    trace(scanner.addOperator("<<"));
    trace(scanner.addOperator(">>"));
    trace(scanner.addOperator("++"));
    trace(scanner.addOperator("--"));
    trace(scanner.addOperator("->"));
    trace(scanner.addOperator("&&"));
    trace(scanner.addOperator("||"));
    trace(scanner.setInput("cout << \"pi = \" << 3.14159265 << endl;"));
    test(scanner.hasMoreTokens(), true);
    test(scanner.nextToken(), "cout");
    test(scanner.nextToken(), "<<");
    test(token = scanner.nextToken(), "\"pi = \"");
    test(scanner.getTokenType(token), STRING);
    test(scanner.nextToken(), "<<");
    test(token = scanner.nextToken(), "3.14159265");
    test(scanner.getTokenType(token), NUMBER);
    test(scanner.nextToken(), "<<");
    test(scanner.nextToken(), "endl");
    test(scanner.nextToken(), ";");
    test(scanner.hasMoreTokens(), false);
    test(scanner.nextToken(), "");
    trace(scanner.setInput("if (a_1<=b+++_c &&&x!=4)"));
    test(scanner.nextToken(), "if");
    test(scanner.nextToken(), "(");
    test(token = scanner.nextToken(), "a_1");
    test(scanner.getTokenType(token), WORD);
    test(scanner.nextToken(), "<=");
    test(scanner.nextToken(), "b");
    test(scanner.nextToken(), "++");
    test(scanner.nextToken(), "+");
    test(token = scanner.nextToken(), "_c");
    test(scanner.getTokenType(token), WORD);
    test(scanner.nextToken(), "&&");
    test(scanner.nextToken(), "&");
    test(scanner.nextToken(), "x");
    test(scanner.nextToken(), "!=");
    test(scanner.nextToken(), "4");
    test(scanner.nextToken(), ")");
    test(scanner.hasMoreTokens(), false);
    test(scanner.nextToken(), "");
}

static void testScanNumbers() {
    declare(TokenScanner scanner);
    trace(scanner.ignoreWhitespace());
    trace(scanner.scanNumbers());
    trace(scanner.setInput("42 73x 3.14159265 6.28E-25"));
    test(scanner.getChar(), '4');
    trace(scanner.ungetChar('4'));
    test(scanner.nextToken(), "42");
    test(scanner.nextToken(), "73");
    test(scanner.nextToken(), "x");
    test(scanner.nextToken(), "3.14159265");
    test(scanner.nextToken(), "6.28E-25");
    test(scanner.hasMoreTokens(), false);
}

static void testScanEscapeSequences() {
    declare(TokenScanner scanner);
    declare(string token);
    trace(scanner.scanStrings());
    trace(scanner.setInput("'A'"));
    trace(token = scanner.nextToken());
    test(token, "'A'");
    test(scanner.getStringValue(token), "A");
    trace(scanner.setInput("\"Quoted String\""));
    trace(token = scanner.nextToken());
    test(token, "\"Quoted String\"");
    test(scanner.getStringValue(token), "Quoted String");
    trace(scanner.setInput("\"\\\"Bother\\\" said Pooh.\""));
    trace(token = scanner.nextToken());
    test(token, "\"\\\"Bother\\\" said Pooh.\"");
    test(scanner.getStringValue(token), "\"Bother\" said Pooh.");
    trace(scanner.setInput("\"\\xFF\\007\\a\\t\""));
    trace(token = scanner.nextToken());
    test(token, "\"\\xFF\\007\\a\\t\"");
    test(scanner.getStringValue(token), "\377\007\a\t");
}
