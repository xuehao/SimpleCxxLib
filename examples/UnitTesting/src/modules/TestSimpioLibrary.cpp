/*
 * File: TestSimpioLibrary.cpp
 * ---------------------------
 * This file tests the functions in the simpio.h interface.
 * Unlike the other test files, this example has to redirect
 * console input so that it can control the input without
 * actually having a user type on the console.
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
#include "simpio.h"
#include "unittest.h"
using namespace std;

/* Function prototypes */

static void testGetInteger();
static void testGetReal();

/* Unit test */

void testSimpioLibrary() {
    testGetInteger();
    testGetReal();
    reportResult("simpio.h library");
}

/* Private functions */

static void testGetInteger() {
    trace(redirectConsoleInput("1234\n-42\n999\n"));
    test(getInteger(), 1234);
    test(getInteger(), -42);
    test(getInteger(), 999);
}

static void testGetReal() {
    trace(redirectConsoleInput("1234\n-4.2\n1.28E-15\n999\n"));
    test(getReal(), 1234.0);
    test(getReal(), -4.2);
    test(getReal(), 1.28E-15);
    test(getReal(), 999);
}
