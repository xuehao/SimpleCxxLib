/*
 * File: TestSetClass.cpp
 * ----------------------
 * This file contains a unit test of the Set class.
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
#include "direction.h"
#include "filelib.h"
#include "lexicon.h"
#include "random.h"
#include "set.h"
#include "strlib.h"
#include "unittest.h"
#include "vector.h"
using namespace std;

#define LEXICON_PATH ".:~/lib"

static Set<char> charSet(string str);
static string charString(const Set<char>& set);
static void shuffle(Vector<string>);
static void testCommaOperator();
static void testCharSet();
static void testLexiconSet();
static void testSetIO();
static void testInsertionOperator();
static void testExtractionOperator();
static void testSetCopy(Set<char>& set, Set<char> setByValue);
static string setSignature(Set<char>& set);

void testSetClass() {
    testCharSet();
    testLexiconSet();
    testInsertionOperator();
    testExtractionOperator();
    reportResult("Set class");
}

static void testCharSet() {
    declare(Set<char> lcletters = charSet("abcdefghijklmnopqrstuvwxyz"));
    declare(Set<char> vowels = charSet("aeiou"));
    declare(Set<char> consonants = charSet("bcdfghjklmnpqrstvwxyz"));
    declare(Set<char> onePointTiles = charSet("aeilnorstu"));
    declare(Set<char> highPointTiles = charSet("kjxqz"));
    declare(Set<char> descenders = charSet("gjpqy"));
    declare(Set<char> empty);
    test(lcletters.size(), 26);
    test(vowels.size(), 5);
    test(charString(highPointTiles), "jkqxz");
    test(vowels.contains('a'), true);
    test(vowels.contains('x'), false);
    test(empty.contains('x'), false);
    test(vowels.isSubsetOf(onePointTiles), true);
    test(vowels.isSubsetOf(highPointTiles), false);
    test(empty.isSubsetOf(highPointTiles), true);
    test(empty.isEmpty(), true);
    test(consonants.isEmpty(), false);
    test(vowels.first(), 'a');
    test(highPointTiles.first(), 'j');
    checkError(empty.first(), "first: set is empty");
    test(charString(highPointTiles + vowels), "aeijkoquxz");
    declare(Set<char> mySet = highPointTiles);
    trace(mySet += vowels);
    test(charString(mySet), "aeijkoquxz");
    test(lcletters - vowels == consonants, true);
    trace(mySet = lcletters);
    trace(mySet -= vowels);
    test(mySet == consonants, true);
    test(charString(highPointTiles * descenders), "jq");
    declare(string str = "");
    trace(for (char ch : vowels) str += ch);
    test(str, "aeiou");
    testCommaOperator();
    testSetCopy(consonants, consonants);
    testSetCopy(empty, empty);
}

static void testLexiconSet() {
    string lexfile;
    lexfile = findOnPath(LEXICON_PATH, "EnglishWords.dat");
    if (lexfile == "")
        return;
    lexfile = expandPathname(lexfile);
    reportMessage("Reading EnglishWords.dat");
    declare(Lexicon lexicon(lexfile));
    reportMessage("Lexicon complete");
    Vector<string> words;
    Lexicon::iterator iter1 = lexicon.begin();
    Lexicon::iterator end1 = lexicon.end();
    reportMessage("Creating word vector");
    while (iter1 != end1) {
        words.add(*iter1++);
    }
    reportMessage("Word vector complete");
    shuffle(words);
    reportMessage("Word vector shuffled");
    reportMessage("Creating word set");
    Set<string> wordSet;
    for (int i = 0; i < words.size(); i++) {
        wordSet.add(words[i]);
    }
    reportMessage("Word set complete");
    iter1 = lexicon.begin();
    end1 = lexicon.end();
    Set<string>::iterator iter2 = wordSet.begin();
    Set<string>::iterator end2 = wordSet.end();
    int lexSetMatches = 0;
    while (iter1 != end1 && iter2 != end2) {
        if (*iter1++ == *iter2++)
            lexSetMatches++;
    }
    test(lexSetMatches, 127145);
}

static void testInsertionOperator() {
    declare(ostringstream ss);
    declare(Set<int> set);
    trace(ss << set);
    test(ss.str(), "{}");
    trace(ss.str(""));
    trace(set += 3);
    trace(set += 2);
    trace(set += 2);
    trace(set += 1);
    trace(ss << set);
    test(ss.str(), "{1, 2, 3}");
    trace(ss.str(""));
    declare(Set<Direction> dirset);
    trace(dirset += SOUTH);
    trace(dirset += NORTH);
    trace(ss << dirset);
    test(ss.str(), "{NORTH, SOUTH}");
    trace(ss.str(""));
    declare(Set<string> sset);
    trace(sset += "one");
    trace(sset += "two");
    trace(sset += "three");
    trace(ss << sset);
    test(ss.str(), "{\"one\", \"three\", \"two\"}");
    trace(ss.str(""));
}

static void testExtractionOperator() {
    declare(istringstream ss("{one, two, three}"));
    reportMessage("Set<string> set;");
    Set<string> set;
    trace(ss >> set);
    test(set.size(), 3);
    test(set.contains("one"), true);
    test(set.contains("two"), true);
    test(set.contains("three"), true);
}

static void shuffle(Vector<string> vec) {
    int n = vec.size();
    for (int lh = 0; lh < n - 1; lh++) {
        int rh = randomInteger(lh, n - 1);
        string str = vec[rh];
        vec[rh] = vec[lh];
        vec[lh] = str;
    }
}

static Set<char> charSet(string str) {
    Set<char> set;
    int nChars = str.length();
    for (int i = 0; i < nChars; i++) {
        set.add(str[i]);
    }
    return set;
}

static string charString(const Set<char>& set) {
    string str = "";
    for (char ch : set) {
        str += ch;
    }
    return str;
}

/* Test the comma operator in initialization */

static void testCommaOperator() {
    declare(Set<int> digits);
    reportMessage("digits += 0, 1, 2, 3, 4, 5, 6, 7, 8, 9;");
    digits += 0, 1, 2, 3, 4, 5, 6, 7, 8, 9;
    declare(string str);
    reportMessage("foreach (int x in digits) str += integerToString(x);");
    for (int x : digits)
        str += integerToString(x);
    test(str, "0123456789");
    reportMessage("digits -= 0, 2, 4, 6, 8;");
    digits -= 0, 2, 4, 6, 8;
    trace(str = "");
    reportMessage("foreach (int x in digits) str += integerToString(x);");
    for (int x : digits)
        str += integerToString(x);
    test(str, "13579");
}

/* Test copy constructor and assignment operator */

static void testSetCopy(Set<char>& set, Set<char> setByValue) {
    Set<char> setCopy = set;
    test(setByValue.size() == set.size(), true);
    test(setCopy.size() == set.size(), true);
    test(setSignature(set) == setSignature(setByValue), true);
    test(setSignature(set) == setSignature(setCopy), true);
}

static string setSignature(Set<char>& set) {
    string signature;
    for (char ch : set) {
        signature += ch;
    }
    return signature;
}
