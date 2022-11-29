/*
 * File: TestLexiconClass.cpp
 * --------------------------
 * This file contains a unit test of the Lexicon class.
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
#include <string>
#include "filelib.h"
#include "lexicon.h"
#include "set.h"
#include "unittest.h"
using namespace std;

#define LEXICON_PATH ".:~/lib"

static void testSetLexicon();
static void testDAWGLexicon();
static void testLexCopy(Lexicon& lex, Lexicon lexByValue);
static string lexSignature(Lexicon& lex);

class CountLettersFunctor {
public:
    CountLettersFunctor(int& count) {
        ip = &count;
    }

    void operator()(const string& str) {
        *ip += str.length();
    }

private:
    int* ip;
};

class CountWordsFunctor {
public:
    CountWordsFunctor(int& count) {
        ip = &count;
    }

    void operator()(const string& str) {
        *ip += 1;
    }

private:
    int* ip;
};

void testLexiconClass() {
    testSetLexicon();
    testDAWGLexicon();
    reportResult("Lexicon class");
}

static void testSetLexicon() {
    declare(Lexicon lexicon);
    test(lexicon.size(), 0);
    trace(lexicon.add("one"));
    trace(lexicon.add("two"));
    trace(lexicon.add("three"));
    trace(lexicon.add("four"));
    trace(lexicon.add("five"));
    trace(lexicon.add("six"));
    trace(lexicon.add("seven"));
    trace(lexicon.add("eight"));
    test(lexicon.size(), 8);
    test(lexicon.contains("three"), true);
    test(lexicon.contains("nine"), false);
    test(lexicon.containsPrefix("tw"), true);
    declare(Lexicon::iterator iter = lexicon.begin());
    test(iter == lexicon.begin(), true);
    test(iter == lexicon.end(), false);
    test(*iter++, "eight");
    test(*iter++, "five");
    test(*iter++, "four");
    test(*iter++, "one");
    test(*iter++, "seven");
    test(*iter++, "six");
    test(*iter++, "three");
    test(*iter++, "two");
    test(iter == lexicon.end(), true);
    declare(int letters = 0);
    trace(lexicon.mapAll(CountLettersFunctor(letters)));
    test(letters, 32);
    testLexCopy(lexicon, lexicon);
}

static void testDAWGLexicon() {
    string lexfile;
    lexfile = findOnPath(LEXICON_PATH, "EnglishWords.dat");
    if (lexfile == "")
        return;
    lexfile = expandPathname(lexfile);
    reportMessage("Reading EnglishWords.dat");
    declare(Lexicon lexicon(lexfile));
    testLexCopy(lexicon, lexicon);
    test(lexicon.size(), 127145);
    declare(Vector<string> twoLetterXWords);
    for (string word : lexicon) {
        if (word.length() == 2 && word.find('x') != string::npos) {
            twoLetterXWords.add(word);
        }
    }
    test(twoLetterXWords[0], "ax");
    test(twoLetterXWords[1], "ex");
    test(twoLetterXWords[2], "ox");
    test(twoLetterXWords[3], "xi");
    test(twoLetterXWords[4], "xu");
    test(twoLetterXWords.size(), 5);
    declare(string str = "");
    trace(for (string word : twoLetterXWords) str += word);
    test(str, "axexoxxixu");
    trace(lexicon.add("ax"));
    test(lexicon.size(), 127145);
    trace(lexicon.add("cx"));
    test(lexicon.size(), 127146);
    trace(lexicon.add("xx"));
    declare(int words = 0);
    trace(lexicon.mapAll(CountWordsFunctor(words)));
    test(words, 127147);
}

/* Test copy constructor and assignment operator */

static void testLexCopy(Lexicon& lex, Lexicon lexByValue) {
    Lexicon lexCopy = lex;
    test(lex.size() == lexByValue.size(), true);
    test(lex.size() == lexCopy.size(), true);
    test(lexSignature(lex) == lexSignature(lexByValue), true);
    test(lexSignature(lex) == lexSignature(lexCopy), true);
}

static string lexSignature(Lexicon& lex) {
    string signature = "";
    int count = 0;
    for (string word : lex) {
        if (count > 0)
            signature += "/";
        signature += word;
        if (count++ == 100)
            break;
    }
    return signature;
}
