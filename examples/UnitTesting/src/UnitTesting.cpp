/*
 * File: TestSimpleCxxLib.cpp
 * ----------------------------
 * This file tests the C++ library packages used at Stanford.
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

#include "console.h"
#include "strlib.h"
#include "unittest.h"

using namespace std;

void testFilelibLibrary();
void testRandomLibrary();
void testSimpioLibrary();
void testStrlibLibrary();
void testDirectionType();
void testGraphClass();
void testGridClass();
void testHashMapClass();
void testHashSetClass();
void testLexiconClass();
void testMapClass();
void testPriorityQueueClass();
void testQueueClass();
void testSetClass();
void testStackClass();
void testTokenScannerClass();
void testVectorClass();
void testForeachStatement();

/*
 * Type: TestEntry
 * ---------------
 * This structure associates a key with a test function.
 */

struct TestEntry {
    string name;
    void (*fn)();
};

const TestEntry TESTS[] = {{"fileliblibrary", testFilelibLibrary},
                           {"randomlibrary", testRandomLibrary},
                           {"simpiolibrary", testSimpioLibrary},
                           {"strliblibrary", testStrlibLibrary},
                           {"directiontype", testDirectionType},
                           {"graphclass", testGraphClass},
                           {"gridclass", testGridClass},
                           {"hashmapclass", testHashMapClass},
                           {"hashsetclass", testHashSetClass},
                           {"lexiconclass", testLexiconClass},
                           {"mapclass", testMapClass},
                           {"priorityqueueclass", testPriorityQueueClass},
                           {"queueclass", testQueueClass},
                           {"setclass", testSetClass},
                           {"stackclass", testStackClass},
                           {"tokenscannerclass", testTokenScannerClass},
                           {"vectorclass", testVectorClass}};
const int N_TESTS = sizeof TESTS / sizeof TESTS[0];

int findTest(string key) {
    int index = -1;
    key = toLowerCase(key);
    for (int i = 0; i < N_TESTS; i++) {
        if (startsWith(TESTS[i].name, key)) {
            if (index != -1) return -1;
            index = i;
        }
    }
    return index;
}

int main() {
    for (int i = 0; i < N_TESTS; i++) {
        TESTS[i].fn();
    }
    return 0;
}
