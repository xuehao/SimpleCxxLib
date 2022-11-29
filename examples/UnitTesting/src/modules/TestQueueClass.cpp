/*
 * File: TestQueueClass.cpp
 * ------------------------
 * This file contains a unit test of the Queue class.
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
#include "queue.h"
#include "strlib.h"
#include "unittest.h"
using namespace std;

static string enqueueTest(Queue<int>& queue, int n);
static string dequeueTest(Queue<int>& queue, int n);
static void testQueueCopy(Queue<string>& queue, Queue<string> queueByValue);

void testQueueClass() {
    declare(Queue<string> queue);
    test(queue.size(), 0);
    test(queue.isEmpty(), true);
    trace(queue.enqueue("A"));
    test(queue.isEmpty(), false);
    test(queue.peek(), "A");
    trace(queue.enqueue("B"));
    trace(queue.enqueue("C"));
    test(queue.toString(), "{\"A\", \"B\", \"C\"}");
    test(queue.peek(), "A");
    test(queue.size(), 3);
    testQueueCopy(queue, queue);
    test(queue.dequeue(), "A");
    test(queue.peek(), "B");
    test(queue.front(), "B");
    test(queue.back(), "C");
    test(queue.dequeue(), "B");
    test(queue.dequeue(), "C");
    test(queue.isEmpty(), true);
    declare(Queue<int> intQueue);
    reportMessage(enqueueTest(intQueue, 100));
    reportMessage(dequeueTest(intQueue, 100));
    declare(istringstream ss("{1, 2, 3}"));
    trace(ss >> intQueue);
    test(intQueue.dequeue(), 1);
    test(intQueue.dequeue(), 2);
    test(intQueue.dequeue(), 3);
    test(intQueue.isEmpty(), true);
    reportResult("Queue class");
}

/* Functions to test large queues */

static string enqueueTest(Queue<int>& queue, int n) {
    string callStr = "enqueueTest(intQueue, " + integerToString(n) + ")";
    for (int i = 0; i < n; i++) {
        queue.enqueue(i);
    }
    return callStr + ((queue.size() == n) ? " succeeded" : " failed");
}

static string dequeueTest(Queue<int>& queue, int n) {
    string callStr = "dequeueTest(intQueue, " + integerToString(n) + ")";
    for (int i = 0; i < n; i++) {
        if (i != queue.dequeue()) {
            return callStr + " failed at index " + integerToString(i);
        }
    }
    return callStr + ((queue.size() == 0) ? " succeeded" : " failed");
}

/* Test copy constructor and assignment operator */

static void testQueueCopy(Queue<string>& queue, Queue<string> queueByValue) {
    Queue<string> queueCopy = queue;
    test(queueByValue.size() == queue.size(), true);
    test(queueCopy.size() == queueCopy.size(), true);
    string elementsByValue;
    while (!queueByValue.isEmpty()) {
        elementsByValue += queueByValue.dequeue();
    }
    string elementsCopy;
    while (!queueCopy.isEmpty()) {
        elementsCopy += queueCopy.dequeue();
    }
    test(elementsByValue == elementsCopy, true);
}
