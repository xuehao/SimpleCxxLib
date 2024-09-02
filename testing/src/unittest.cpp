/*
 * File: unittest.cpp
 * ------------------
 * This file implements the unittest.h interface in C++.
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

#include "unittest.h"

#include <iostream>
#include <sstream>
#include <string>
using namespace std;

/* Private variables */

static int errorCount;
static bool verbose;
static istringstream issin;

/* Exported entries */

void reportResult(string name) {
    if (errorCount == 0) {
        cout << name << " succeeded" << endl;
    } else {
        cout << name << " failed (" << errorCount << " error" << ((errorCount == 1) ? "" : "s")
             << ")" << endl;
        errorCount = 0;
    }
}

void reportError(string msg) {
    errorCount++;
    cerr << "> " << msg << " <" << endl;
}

void reportMessage(string msg) {
    if (verbose)
        cout << "  " << msg << endl;
}

void setVerboseTestingFlag(bool flag) {
    verbose = flag;
}

bool getVerboseTestingFlag() {
    return verbose;
}

void setErrorCount(int count) {
    errorCount = count;
}

int getErrorCount() {
    return errorCount;
}

void redirectConsoleInput(istream is) {
    cin.rdbuf(is.rdbuf());
}

void redirectConsoleInput(string str) {
    issin.str(str);
    cin.rdbuf(issin.rdbuf());
}

void redirectConsoleOutput(ostream os) {
    cout.rdbuf(os.rdbuf());
}

void uttest(string expString, string valueString, int exp, int value) {
    if (exp == value) {
        if (verbose) {
            cout << "  " << expString << " -> " << valueString << endl;
        }
    } else {
        errorCount++;
        if (valueString == "true" || valueString == "false") {
            cerr << "> " << expString << " -> " << (exp ? "true" : "false") << " (should be "
                 << valueString << ") <" << endl;
        } else if (valueString.length() > 0 && valueString[0] == '\'') {
            cerr << "> " << expString << " -> '" << ((char)exp) << "' (should be " << valueString
                 << ") <" << endl;
        } else {
            cerr << "> " << expString << " -> " << exp << " (should be " << valueString << ") <"
                 << endl;
        }
    }
}

void uttest(string expString, string valueString, size_t exp, int value) {
    uttest(expString, valueString, (int)exp, value);
}

void uttest(string expString, string valueString, double exp, double value) {
    if (exp == value) {
        if (verbose) {
            cout << "  " << expString << " -> " << valueString << endl;
        }
    } else {
        errorCount++;
        cerr << "> " << expString << " -> " << exp << " (should be " << valueString << ") <"
             << endl;
    }
}

void uttest(string expString, string valueString, int exp, double value) {
    uttest(expString, valueString, (double)exp, value);
}

void uttest(string expString, string valueString, double exp, int value) {
    uttest(expString, valueString, exp, (double)value);
}

void uttest(string expString, string valueString, string exp, string value) {
    if (exp == value) {
        if (verbose) {
            cout << "  " << expString << " -> " << valueString << endl;
        }
    } else {
        errorCount++;
        cerr << "> " << expString << " -> " << exp << " (should be " << valueString << ") <"
             << endl;
    }
}
