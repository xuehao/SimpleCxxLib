/*
 * File: unittest.h
 * ----------------
 * This interface uses the preprocessor to support testing.
 * Clients of this library should look at the examples in the
 * tests directory for illustrations of how to use this package.
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

#ifndef _unittest_h
#define _unittest_h

#include <iomanip>
#include <iostream>
#include <sstream>
#include "error.h"
#include "timer.h"
#undef _error_h
using std::cout;
using std::endl;
using std::istream;
using std::ostream;
using std::string;

/*
 * Macro: declare
 * Usage: declare(decl);
 * ---------------------
 * Executes a declaration and logs it to cout if verbose tracing is in
 * effect.
 */

#define declare(decl)                   \
    reportMessage(string(#decl) + ";"); \
    decl;

/*
 * Macro: test
 * Usage: test(exp, value);
 * ------------------------
 * Tests to make sure that a function computes a specified value.  The
 * first argument is an expression (typically a function call in the
 * module under test), and the second argument is the expected value.
 */

#define test(exp, value)                                                       \
    do {                                                                       \
        try {                                                                  \
            uttest(string(#exp), string(#value), exp, value);                  \
        } catch (ErrorException & ex) {                                        \
            reportError(string(#exp) + " throws \"" + ex.getMessage() + "\""); \
        }                                                                      \
    } while (0)

/*
 * Macro: trace
 * Usage: trace(stmt);
 * -------------------
 * Executes the statement, but also logs it to cout if verbose testing
 * is enabled.
 */

#define trace(stmt)                                                             \
    do {                                                                        \
        try {                                                                   \
            stmt;                                                               \
            reportMessage(string(#stmt) + ";");                                 \
        } catch (ErrorException & ex) {                                         \
            reportError(string(#stmt) + " throws \"" + ex.getMessage() + "\""); \
        }                                                                       \
    } while (0)

/*
 * Macro: checkError
 * Usage: checkError(exp, msg);
 * ----------------------------
 * Evaluates the expression and makes sure that it generates the
 * specified error message.
 */

#define checkError(exp, msg)                                                       \
    do {                                                                           \
        try {                                                                      \
            exp;                                                                   \
            reportError(string(#exp) + " returned without throwing an error");     \
        } catch (ErrorException & ex) {                                            \
            if (ex.getMessage() == msg) {                                          \
                reportMessage(string(#exp) + " throws \"" + msg + "\"");           \
            } else {                                                               \
                reportError(string(#exp) + " throws \"" + ex.getMessage() + "\""); \
            }                                                                      \
        }                                                                          \
    } while (0)

/*
 * Macro: checkTime
 * Usage: checkTime(vec.size(), vec.sort());
 * -----------------------------------------
 * Time the evaluation of an expression report the time in seconds in test results.
 * The argument size is the size of the input.
 */

#define checkTime(n, expr)                                                                   \
    do {                                                                                     \
        Timer t;                                                                             \
        t.start();                                                                           \
        (void)(expr);                                                                        \
        double elapsed_ms = t.stop();                                                        \
        cout << "Line " << __LINE__ << ": " << #expr << "(" << n << ")"                      \
             << " finished in " << std::fixed << std::setprecision(3) << (elapsed_ms / 1000) \
             << " secs" << endl;                                                             \
    } while (0)

/*
 * Function: reportResult
 * Usage: reportResult(name);
 * --------------------------
 * Reports the result of a module test.
 */

void reportResult(string moduleName);

/*
 * Function: reportMessage
 * Usage: reportMessage(msg);
 * --------------------------
 * Generates a line of output if verbose tracing in enabled.
 */

void reportMessage(string msg);

/*
 * Function: reportError
 * Usage: reportError(msg);
 * ------------------------
 * Reports an error and bumps the error count for the module.
 */

void reportError(string msg);

/*
 * Function: setVerboseTestingFlag
 * Usage: setVerboseTestingFlag(flag);
 * -----------------------------------
 * Sets a global flag that determines whether the test process
 * traces all the test operations.
 */

void setVerboseTestingFlag(bool flag);

/*
 * Function: flag
 * Usage: bool flag = getVerboseTestingFlag();
 * -------------------------------------------
 * Returns the setting of the verbose testing flag.
 */

bool getVerboseTestingFlag();

/*
 * Function: setErrorCount
 * Usage: setErrorCount(count);
 * ----------------------------
 * Sets the error count to the specified value.
 */

void setErrorCount(int count);

/*
 * Function: count
 * Usage: int count = getErrorCount();
 * -----------------------------------
 * Returns the current error count.
 */

int getErrorCount();

/*
 * Function: redirectConsoleInput
 * Usage: redirectConsoleInput(is);
 *        redirectConsoleInput(str);
 * ---------------------------------
 * Redirects standard input so that it comes from the specified
 * input stream.  This function makes it possible to test programs
 * that read input from cin.  As a convenience, this method also
 * allows the argument to be a string, which is then stored in an
 * internal input stream.
 */

void redirectConsoleInput(istream is);
void redirectConsoleInput(string str);

/*
 * Function: redirectConsoleOutput
 * Usage: redirectConsoleOutput(os);
 * ---------------------------------
 * Redirects standard output so that it goes to the specified
 * output stream.
 */

void redirectConsoleOutput(ostream os);

/* Internal functions used in the implementation */

void uttest(string expString, string valueString, int exp, int value);
void uttest(string expString, string valueString, size_t exp, int value);
void uttest(string expString, string valueString, int exp, double value);
void uttest(string expString, string valueString, double exp, int value);
void uttest(string expString, string valueString, double exp, double value);
void uttest(string expString, string valueString, string exp, string value);

#endif
