/*
 * File: TestDirectionType.cpp
 * ---------------------------
 * This file tests the Direction enumerated type.
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
#include "direction.h"
#include "unittest.h"
using namespace std;

static void testLeftFrom();
static void testRightFrom();
static void testOpposite();
static void testToString();
static void testForLoopIdiom();
static void testInsertionOperator();
static void testExtractionOperator();

void testDirectionType() {
    testLeftFrom();
    testRightFrom();
    testOpposite();
    testToString();
    testForLoopIdiom();
    testInsertionOperator();
    testExtractionOperator();
    reportResult("Direction type");
}

static void testLeftFrom() {
    test(leftFrom(NORTH), WEST);
    test(leftFrom(EAST), NORTH);
    test(leftFrom(SOUTH), EAST);
    test(leftFrom(WEST), SOUTH);
}

static void testRightFrom() {
    test(rightFrom(NORTH), EAST);
    test(rightFrom(EAST), SOUTH);
    test(rightFrom(SOUTH), WEST);
    test(rightFrom(WEST), NORTH);
}

static void testOpposite() {
    test(opposite(NORTH), SOUTH);
    test(opposite(EAST), WEST);
    test(opposite(SOUTH), NORTH);
    test(opposite(WEST), EAST);
}

static void testToString() {
    test(directionToString(NORTH), "NORTH");
    test(directionToString(EAST), "EAST");
    test(directionToString(SOUTH), "SOUTH");
    test(directionToString(WEST), "WEST");
}

static void testForLoopIdiom() {
    declare(ostringstream os);
    trace(for (Direction dir = NORTH; dir <= WEST; dir++) os << dir);
    test(os.str(), "NORTHEASTSOUTHWEST");
}

static void testInsertionOperator() {
    declare(ostringstream ss);
    trace(ss << NORTH << EAST << SOUTH << WEST);
    test(ss.str(), "NORTHEASTSOUTHWEST");
}

static void testExtractionOperator() {
    declare(istringstream ss);
    declare(Direction dir);
    trace(ss.str("NORTH EAST SOUTH WEST N E S W"));
    trace(ss >> dir);
    test(dir, NORTH);
    trace(ss >> dir);
    test(dir, EAST);
    trace(ss >> dir);
    test(dir, SOUTH);
    trace(ss >> dir);
    test(dir, WEST);
    trace(ss >> dir);
    test(dir, NORTH);
    trace(ss >> dir);
    test(dir, EAST);
    trace(ss >> dir);
    test(dir, SOUTH);
    trace(ss >> dir);
    test(dir, WEST);
}
