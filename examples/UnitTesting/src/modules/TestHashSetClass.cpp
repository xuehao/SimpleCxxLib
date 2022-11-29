/*
 * File: TestHashSetClass.cpp
 * --------------------------
 * This file contains a unit test of the HashSet class.
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
#include "hashset.h"
#include "random.h"
#include "strlib.h"
#include "unittest.h"
#include "vector.h"
using namespace std;

static HashSet<char> charSet(string str);
static string charString(const HashSet<char>& set);
static string sortString(string str);
static void testCommaOperator();
static void testCharSet();
static void testInsertionOperator();
static void testExtractionOperator();
static void testSetCopy(HashSet<char>& set, HashSet<char> setByValue);

void testHashSetClass() {
    testCharSet();
    testInsertionOperator();
    testExtractionOperator();
    reportResult("HashSet class");
}

static void testCharSet() {
    declare(HashSet<char> lcletters = charSet("abcdefghijklmnopqrstuvwxyz"));
    declare(HashSet<char> vowels = charSet("aeiou"));
    declare(HashSet<char> consonants = charSet("bcdfghjklmnpqrstvwxyz"));
    declare(HashSet<char> onePointTiles = charSet("aeilnorstu"));
    declare(HashSet<char> highPointTiles = charSet("kjxqz"));
    declare(HashSet<char> descenders = charSet("gjpqy"));
    declare(HashSet<char> empty);
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
    test(charString(highPointTiles + vowels), "aeijkoquxz");
    declare(HashSet<char> mySet = highPointTiles);
    trace(mySet += vowels);
    test(charString(mySet), "aeijkoquxz");
    test(lcletters - vowels == consonants, true);
    trace(mySet = lcletters);
    trace(mySet -= vowels);
    test(mySet.isSubsetOf(consonants), true);
    test(consonants.isSubsetOf(mySet), true);
    test(mySet == consonants, true);
    test(charString(highPointTiles * descenders), "jq");
    testCommaOperator();
    testSetCopy(consonants, consonants);
    testSetCopy(empty, empty);
}

static void testInsertionOperator() {
    declare(ostringstream ss);
    declare(HashSet<int> set);
    trace(ss << set);
    test(ss.str(), "{}");
    trace(ss.str(""));
    trace(set += 3);
    trace(set += 2);
    trace(set += 2);
    trace(set += 1);
    string pattern = "";
    for (int x : set) {
        if (pattern != "")
            pattern += ", ";
        pattern += integerToString(x);
    }
    trace(ss << set);
    test(ss.str(), "{" + pattern + "}");
    trace(ss.str(""));
    declare(HashSet<string> sset);
    trace(sset += "one");
    trace(sset += "two");
    trace(sset += "three");
    pattern = "";
    for (string x : sset) {
        if (pattern != "")
            pattern += ", ";
        pattern += '"' + x + '"';
    }
    trace(ss << sset);
    test(ss.str(), "{" + pattern + "}");
    trace(ss.str(""));
}

static void testExtractionOperator() {
    declare(istringstream ss("{one, two, three}"));
    reportMessage("HashSet<string> set;");
    HashSet<string> set;
    trace(ss >> set);
    test(set.size(), 3);
    test(set.contains("one"), true);
    test(set.contains("two"), true);
    test(set.contains("three"), true);
}

static HashSet<char> charSet(string str) {
    HashSet<char> set;
    int nChars = str.length();
    for (int i = 0; i < nChars; i++) {
        set.add(str[i]);
    }
    return set;
}

static string charString(const HashSet<char>& set) {
    string str = "";
    for (char ch : set) {
        str += ch;
    }
    return sortString(str);
}

static string sortString(string str) {
    int n = str.length();
    for (int lh = 0; lh < n; lh++) {
        int rh = lh;
        for (int i = rh + 1; i < n; i++) {
            if (str[i] < str[rh])
                rh = i;
        }
        char tmp = str[lh];
        str[lh] = str[rh];
        str[rh] = tmp;
    }
    return str;
}

/* Test the comma operator in initialization */

static void testCommaOperator() {
    declare(HashSet<int> digits);
    reportMessage("digits += 0, 1, 2, 3, 4, 5, 6, 7, 8, 9;");
    digits += 0, 1, 2, 3, 4, 5, 6, 7, 8, 9;
    declare(string str);
    reportMessage("foreach (int x in digits) str += integerToString(x);");
    for (int x : digits)
        str += integerToString(x);
    test(sortString(str), "0123456789");
    reportMessage("digits -= 0, 2, 4, 6, 8;");
    digits -= 0, 2, 4, 6, 8;
    trace(str = "");
    reportMessage("foreach (int x in digits) str += integerToString(x);");
    for (int x : digits)
        str += integerToString(x);
    test(sortString(str), "13579");
}

/* Test copy constructor and assignment operator */

static void testSetCopy(HashSet<char>& set, HashSet<char> setByValue) {
    HashSet<char> setCopy = set;
    test(setByValue.size() == set.size(), true);
    test(setCopy.size() == set.size(), true);
    test(charString(set) == charString(setByValue), true);
    test(charString(set) == charString(setCopy), true);
}
