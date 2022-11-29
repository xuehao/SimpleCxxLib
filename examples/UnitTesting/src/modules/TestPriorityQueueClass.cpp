/*
 * File: TestPriorityQueueClass.cpp
 * --------------------------------
 * This file contains a unit test of the PriorityQueue class.
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
#include "pqueue.h"
#include "strlib.h"
#include "unittest.h"
using namespace std;

void testPriorityQueueClass() {
    declare(PriorityQueue<string> pq);
    test(pq.size(), 0);
    test(pq.isEmpty(), true);
    trace(pq.enqueue("A", 1));
    test(pq.isEmpty(), false);
    test(pq.peek(), "A");
    trace(pq.enqueue("D", 3));
    trace(pq.enqueue("C", 2));
    trace(pq.enqueue("B", 1));
    test(pq.peek(), "A");
    test(pq.size(), 4);
    test(pq.toString(), "{1:\"A\", 1:\"B\", 2:\"C\", 3:\"D\"}");
    test(pq.dequeue(), "A");
    test(pq.peek(), "B");
    test(pq.dequeue(), "B");
    test(pq.dequeue(), "C");
    test(pq.dequeue(), "D");
    test(pq.isEmpty(), true);
    declare(PriorityQueue<int> intQueue);
    declare(istringstream ss("{3:30, 1:10, 2:20, 1:15}"));
    trace(ss >> intQueue);
    test(intQueue.toString(), "{1:10, 1:15, 2:20, 3:30}");
    reportResult("PriorityQueue class");
}
