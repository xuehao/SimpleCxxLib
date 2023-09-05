/*
 * File: TestVector.cpp
 * --------------------
 * Tests the Vector class.
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

#include <algorithm>
#include <iostream>
#include <sstream>
#include <string>

#include "direction.h"
#include "unittest.h"
#include "vector.h"
using namespace std;

static void testInsertionOperator();
static void testExtractionOperator();
static void testVectorCopy(Vector<string>& vec, Vector<string> vecByValue);
static string vectorSignature(Vector<string>& vec);

class AppendFunctor {
public:
    AppendFunctor(string& str) {
        sp = &str;
    }

    void operator()(const string& str) {
        *sp += str;
    }

private:
    string* sp;
};

void testVectorClass() {
    declare(Vector<string> v);
    trace(v.add("A"));
    trace(v.add("C"));
    trace(v.add("D"));
    trace(v.insert(1, "B"));
    test(v.size(), 4);
    test(v.get(0), "A");
    test(v.get(1), "B");
    test(v.get(2), "C");
    test(v.get(3), "D");
    trace(v.set(0, "a"));
    test(v.get(0), "a");
    trace(v.remove(0));
    test(v.size(), 3);
    testVectorCopy(v, v);
    trace(v.insert(0, "A"));
    test(v.get(0), "A");
    trace(v.insert(v.size(), "E"));
    test(v.get(4), "E");
    declare(Vector<string>::iterator it = v.begin());
    test(it == v.begin(), true);
    test(it == v.end(), false);
    test(*it++, "A");
    test(*it++, "B");
    test(*it++, "C");
    test(*it++, "D");
    test(*it++, "E");
    test(it == v.end(), true);
    declare(string str = "");
    trace(v.mapAll(AppendFunctor(str)));
    test(str, "ABCDE");
    trace(str = "");
    trace(for (string ch : v) str += ch);
    test(str, "ABCDE");
    declare(Vector<int> array(3));
    test(array.size(), 3);
    trace(array[1] = 1);
    trace(array[2] = 2);
    test(array[0], 0);
    test(array[1], 1);
    test(array[2], 2);
    reportMessage("Vector< Vector<double> > matrix(2, Vector<double>(2));");
    Vector<Vector<double>> matrix(2, Vector<double>(2));
    trace(matrix[0][0] = 1.0);
    trace(matrix[1][1] = 1.0);
    test(matrix[0][0], 1.0);
    test(matrix[0][1], 0.0);
    test(matrix[1][0], 0.0);
    test(matrix[1][1], 1.0);
    declare(Vector<char> vowels);
    reportMessage("vowels += 'a', 'e', 'i', 'o', 'u';");
    vowels += 'a', 'e', 'i', 'o', 'u';
    test(vowels.size(), 5);
    test(vowels[0], 'a');
    test(vowels[1], 'e');
    test(vowels[2], 'i');
    test(vowels[3], 'o');
    test(vowels[4], 'u');
    declare(Vector<char> uncommon);
    reportMessage("uncommon += 'q', 'z', 'j', 'x';");
    uncommon += 'q', 'z', 'j', 'x';
    test(uncommon.size(), 4);
    test(uncommon[0], 'q');
    test(uncommon[1], 'z');
    test(uncommon[2], 'j');
    test(uncommon[3], 'x');
    declare(Vector<char> combined = vowels + uncommon);
    trace(str = "");
    trace(for (char ch : combined) str += ch);
    test(str, "aeiouqzjx");
    declare(Vector<int> digits);
    reportMessage("digits += 9, 8, 7, 6, 5, 4, 3, 2, 1, 0;");
    digits += 9, 8, 7, 6, 5, 4, 3, 2, 1, 0;
    trace(sort(digits.begin(), digits.end()));
    test(digits[0], 0);
    test(digits[1], 1);
    test(digits[2], 2);
    test(digits[3], 3);
    test(digits[4], 4);
    test(digits[5], 5);
    test(digits[6], 6);
    test(digits[7], 7);
    test(digits[8], 8);
    test(digits[9], 9);
    trace(digits += 10);
    test(digits[10], 10);
    test(digits.toString(), "{0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10}");
    testInsertionOperator();
    testExtractionOperator();
    reportResult("Vector class");
}

/* Test copy constructor and assignment operator */

static void testVectorCopy(Vector<string>& vec, Vector<string> vecByValue) {
    Vector<string> vecCopy = vec;
    test(vecByValue.size() == vec.size(), true);
    test(vecCopy.size() == vec.size(), true);
    test(vectorSignature(vec) == vectorSignature(vecByValue), true);
    test(vectorSignature(vec) == vectorSignature(vecCopy), true);
}

static string vectorSignature(Vector<string>& vec) {
    string signature;
    for (int i = 0; i < vec.size(); i++) {
        if (i > 0)
            signature += "/";
        signature += vec[i];
    }
    return signature;
}

static void testInsertionOperator() {
    declare(ostringstream ss);
    declare(Vector<int> vec);
    trace(ss << vec);
    test(ss.str(), "{}");
    trace(ss.str(""));
    trace(vec += 1);
    trace(vec += 2);
    trace(vec += 3);
    trace(ss << vec);
    test(ss.str(), "{1, 2, 3}");
    trace(ss.str(""));
    declare(Vector<Direction> dirs);
    trace(dirs += NORTH);
    trace(dirs += SOUTH);
    trace(ss << dirs);
    test(ss.str(), "{NORTH, SOUTH}");
    trace(ss.str(""));
    declare(Vector<string> svec);
    trace(svec += "one");
    trace(svec += "two");
    trace(svec += "three");
    trace(ss << svec);
    test(ss.str(), "{\"one\", \"two\", \"three\"}");
    trace(ss.str(""));
    reportMessage("Vector< Vector<double> > matrix(2, Vector<double>(2));");
    Vector<Vector<double>> matrix(2, Vector<double>(2));
    trace(matrix[0][0] = 1.0);
    trace(matrix[1][1] = 1.0);
    trace(ss << matrix);
    test(ss.str(), "{{1, 0}, {0, 1}}");
}

static void testExtractionOperator() {
    declare(istringstream ss);
    declare(Vector<int> vec);
    trace(ss.str("{}"));
    trace(ss >> vec);
    test(vec.size(), 0);
    trace(ss.str("{1, 2, 3}"));
    trace(ss >> vec);
    test(vec.size(), 3);
    test(vec[0], 1);
    test(vec[1], 2);
    test(vec[2], 3);
    declare(Vector<Direction> dirs);
    trace(ss.str("{NORTH, SOUTH}"));
    trace(ss >> dirs);
    test(dirs.size(), 2);
    test(dirs[0], NORTH);
    test(dirs[1], SOUTH);
    declare(Vector<string> svec);
    trace(ss.str("{one, two, three}"));
    trace(ss >> svec);
    test(svec.size(), 3);
    test(svec[0], "one");
    test(svec[1], "two");
    test(svec[2], "three");
    declare(Vector<Vector<double>> matrix);
    trace(ss.str("{{1, 0}, {0, 1}}"));
    trace(ss >> matrix);
    test(matrix[0][0], 1.0);
    test(matrix[0][1], 0.0);
    test(matrix[1][0], 0.0);
    test(matrix[1][1], 1.0);
}
