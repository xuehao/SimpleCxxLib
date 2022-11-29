/*
 * File: TestStackClass.cpp
 * ------------------------
 * This file contains a unit test of the Stack class.
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
#include "stack.h"
#include "strlib.h"
#include "unittest.h"
using namespace std;

static void testStackCopy(Stack<int>& stack, Stack<int> stackByValue);

void testStackClass() {
    declare(Stack<int> intStack);
    test(intStack.size(), 0);
    test(intStack.isEmpty(), true);
    trace(intStack.push(17));
    test(intStack.isEmpty(), false);
    test(intStack.peek(), 17);
    trace(intStack.push(42));
    test(intStack.peek(), 42);
    test(intStack.size(), 2);
    test(intStack.toString(), "{17, 42}");
    testStackCopy(intStack, intStack);
    test(intStack.pop(), 42);
    test(intStack.pop(), 17);
    test(intStack.isEmpty(), true);
    declare(istringstream ss("{1, 2, 3}"));
    trace(ss >> intStack);
    test(intStack.pop(), 3);
    test(intStack.pop(), 2);
    test(intStack.pop(), 1);
    test(intStack.isEmpty(), true);
    reportResult("Stack class");
}

/* Test copy constructor and assignment operator */

static void testStackCopy(Stack<int>& stack, Stack<int> stackByValue) {
    Stack<int> stackCopy = stack;
    test(stackByValue.size() == stack.size(), true);
    test(stackCopy.size() == stackCopy.size(), true);
    string elementsByValue;
    while (!stackByValue.isEmpty()) {
        elementsByValue += integerToString(stackByValue.pop());
    }
    string elementsCopy;
    while (!stackCopy.isEmpty()) {
        elementsCopy += integerToString(stackCopy.pop());
    }
    test(elementsByValue == elementsCopy, true);
}
