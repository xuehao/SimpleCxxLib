/*
 * File: TestGraphClass.cpp
 * ------------------------
 * This file contains a unit test of the Set class.
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
#include "graph.h"
#include "strlib.h"
#include "tokenscanner.h"
#include "unittest.h"
#include "vector.h"
using namespace std;

/* Forward references to MyNode and MyArc */

struct MyNode;
struct MyArc;

/* Sort MyNode and MyArc alphabetically */
static Graph<MyNode, MyArc>::GraphComparator comparator;

/*
 * Type: MyNode
 * ------------
 * This type represents a minimal node in a graph.
 */

struct MyNode {
    string name;
    Set<MyArc*> arcs = Set<MyArc*>(comparator);  // alphabetically
};

/*
 * Type: MyArc
 * -----------
 * This type represents a minimal arc in a graph that includes a cost field.
 */

struct MyArc {
    MyNode *start, *finish;
    double cost;
};

/*
 * Class: MyGraph
 * --------------
 * This class subclasses Graph<MyNode,MyArc> with one that can read and write
 * cost data.
 */

class MyGraph : public Graph<MyNode, MyArc> {

public:
    virtual void writeArcData(std::ostream& os, MyArc* arc) const {
        os << " (" << arc->cost << ")";
    }

    virtual void scanArcData(TokenScanner& scanner, MyArc* forward, MyArc* backward) {
        double cost = 1;
        string token = scanner.nextToken();
        if (token == "(") {
            token = scanner.nextToken();
            if (token == "-")
                token += scanner.nextToken();
            scanner.verifyToken(")");
            cost = stringToReal(token);
        }
        forward->cost = cost;
        if (backward != NULL)
            backward->cost = cost;
    }
};

/* Prototypes */

static void createMyGraph(MyGraph& g);
static void addArc(MyGraph& g, string start, string finish, double cost);
static void testBasicMethods(MyGraph& g);
static void testStringConversion(MyGraph& g);
static void testDeletionMethods(MyGraph& g);
static void deleteArcsWithCost(MyGraph& g, double cost);
static void testStructureMatch(MyGraph& g1, MyGraph& g2);
static string toString(Set<MyNode*> nodes);
static string toString(Set<MyArc*> arcs);

void testGraphClass() {
    reportMessage("MyGraph g;");
    MyGraph g;
    createMyGraph(g);
    testBasicMethods(g);
    testStringConversion(g);
    testDeletionMethods(g);
    reportMessage("MyGraph gcopy = g;");
    MyGraph gcopy = g;
    trace(testStructureMatch(g, gcopy));
    reportResult("Graph class");
}

/*
 * Implementation notes: CreateMyGraph
 * -----------------------------------
 * This method creates a very simple four-node graph with the
 * following structure:
 *
 *    +----+       1       +----+
 *    | n1 |-------------->| n2 |
 *    +----+               +----+  \
 *     |  |                   ^     |
 *   3 |  | 4                  \   / 2
 *     |  |                     ---
 *     v  v
 *    +----+       5       +----+
 *    | n3 |-------------->| n4 |
 *    +----+               +----+
 *
 * Note that the graph contains two important special cases: a self
 * arc joining n2 to itself and parallel arcs between n1 and n3.
 */

static void createMyGraph(MyGraph& g) {
    trace(g.addNode("n1"));
    trace(g.addNode("n2"));
    trace(g.addNode("n3"));
    trace(g.addNode("n4"));
    trace(addArc(g, "n1", "n2", 1));
    trace(addArc(g, "n2", "n2", 2));
    trace(addArc(g, "n1", "n3", 3));
    trace(addArc(g, "n1", "n3", 4));
    trace(addArc(g, "n3", "n4", 5));
}

static void addArc(MyGraph& g, string start, string finish, double cost) {
    MyArc* arc = new MyArc;
    arc->start = g.getNode(start);
    arc->finish = g.getNode(finish);
    arc->cost = cost;
    g.addArc(arc);
}

static void testBasicMethods(MyGraph& g) {
    test(g.size(), 4);
    test(g.isEmpty(), false);
    test(g.isConnected("n1", "n2"), true);
    test(g.isConnected("n1", "n3"), true);
    test(g.isConnected("n3", "n4"), true);
    test(g.isConnected("n4", "n3"), false);
    test(g.isConnected("n1", "n1"), false);
    test(g.isConnected("n2", "n2"), true);
    test(g.getArcSet("n1").first()->cost, 1);
    test(g.getArcSet("n2").first()->cost, 2);
    test(g.getArcSet("n3").first()->cost, 5);
    test(toString(g.getNodeSet()), "{ n1, n2, n3, n4 }");
    test(toString(g.getArcSet()), "{ n1->n2, n1->n3, n1->n3, n2->n2, n3->n4 }");
    test(toString(g.getArcSet("n1")), "{ n1->n2, n1->n3, n1->n3 }");
    test(toString(g.getArcSet("n2")), "{ n2->n2 }");
    test(toString(g.getArcSet("n3")), "{ n3->n4 }");
    test(toString(g.getArcSet("n4")), "{ }");
    test(toString(g.getNeighbors("n1")), "{ n2, n3 }");
    test(toString(g.getNeighbors("n2")), "{ n2 }");
    test(toString(g.getNeighbors("n3")), "{ n4 }");
    test(toString(g.getNeighbors("n4")), "{ }");
}

static void testStringConversion(MyGraph& g) {
    string pattern =
        "{n1, n2, n3, n4,"
        " n1 -> n2 (1),"
        " n1 -> n3 (3),"
        " n1 -> n3 (4),"
        " n2 -> n2 (2),"
        " n3 -> n4 (5)}";
    test(g.toString(), pattern);
    declare(istringstream iss(pattern));
    declare(MyGraph g2);
    trace(iss >> g2);
    testBasicMethods(g2);
}

static void testDeletionMethods(MyGraph& g) {
    trace(g.removeNode("n2"));
    test(g.size(), 3);
    test(toString(g.getNodeSet()), "{ n1, n3, n4 }");
    test(toString(g.getArcSet()), "{ n1->n3, n1->n3, n3->n4 }");
    test(toString(g.getArcSet("n1")), "{ n1->n3, n1->n3 }");
    test(toString(g.getNeighbors("n1")), "{ n3 }");
    trace(deleteArcsWithCost(g, 4));
    test(toString(g.getArcSet()), "{ n1->n3, n3->n4 }");
    test(toString(g.getArcSet("n1")), "{ n1->n3 }");
}

static void deleteArcsWithCost(MyGraph& g, double cost) {
    Vector<MyArc*> toRemove;
    for (MyArc* arc : g.getArcSet()) {
        if (arc->cost == cost) {
            toRemove.add(arc);
        }
    }
    for (MyArc* arc : toRemove) {
        g.removeArc(arc);
    }
}

static void testStructureMatch(MyGraph& g1, MyGraph& g2) {
    Set<MyNode*>::iterator ni1 = g1.getNodeSet().begin();
    Set<MyNode*>::iterator ni2 = g2.getNodeSet().begin();
    Set<MyNode*>::iterator ne1 = g1.getNodeSet().end();
    Set<MyNode*>::iterator ne2 = g2.getNodeSet().end();
    while (ni1 != ne1) {
        if (ni2 == ne2) {
            reportError("g2 smaller than g1");
        }
        MyNode* n1 = *ni1++;
        MyNode* n2 = *ni2++;
        if (n1 == n2) {
            reportError("graphs share node structure for " + n1->name);
            return;
        }
        if (n1->name != n2->name) {
            reportError(n1->name + " doesn't match " + n2->name);
        }
    }
    if (ni2 != ne2) {
        reportError("g1 smaller than g2");
    }
    Set<MyArc*>::iterator ai1 = g1.getArcSet().begin();
    Set<MyArc*>::iterator ai2 = g2.getArcSet().begin();
    Set<MyArc*>::iterator ae1 = g1.getArcSet().end();
    Set<MyArc*>::iterator ae2 = g2.getArcSet().end();
    while (ai1 != ae1) {
        if (ai2 == ae2) {
            reportError("g2 has fewer arcs than g1");
        }
        MyArc* a1 = *ai1++;
        MyArc* a2 = *ai2++;
        string a1Name = a1->start->name + "->" + a1->finish->name;
        string a2Name = a2->start->name + "->" + a2->finish->name;
        if (a1 == a2) {
            reportError("graphs share arc structure for " + a1Name);
        }
        if (a1Name != a2Name) {
            reportError(a1Name + " doesn't match " + a2Name);
        }
        if (a1->cost != a2->cost) {
            reportError("costs for " + a1Name + " do not match");
        }
    }
    if (ai2 != ae2) {
        reportError("g1 has fewer arcs than g2");
    }
}

static string toString(Set<MyNode*> nodes) {
    string str = "{";
    for (MyNode* node : nodes) {
        if (str.length() > 1)
            str += ",";
        str += " " + node->name;
    }
    str += " }";

    return str;
}

static string toString(Set<MyArc*> arcs) {
    string str = "{";

    for (MyArc* arc : arcs) {
        if (str.length() > 1)
            str += ",";
        str += " " + arc->start->name + "->" + arc->finish->name;
    }
    str += " }";

    return str;
}
