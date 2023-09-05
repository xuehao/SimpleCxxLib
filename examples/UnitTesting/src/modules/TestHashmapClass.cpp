/*
 * File: TestHashMapClass.cpp
 * --------------------------
 * This file contains a unit test of the HashMap class.
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

#include "hashmap.h"
#include "strlib.h"
#include "unittest.h"
using namespace std;

/* Prototypes */

static void testInsertionOperator(HashMap<string, string>& elements, string pattern);
static void testExtractionOperator();
static void testMapCopy(HashMap<string, string>& map, HashMap<string, string> mapByValue);
static void markElement(string name, int& elementBitSet, string& str);

class AppendKeyValueFunctor {
public:
    AppendKeyValueFunctor(string& str) {
        sp = &str;
    }

    void operator()(const string& key, const string& value) {
        if (sp->length() > 0)
            *sp += ", ";
        *sp += key + ":" + value;
    }

private:
    string* sp;
};

void testHashMapClass() {
    HashMap<string, string> elements;
    reportMessage("HashMap<string,string> elements;");
    trace(elements.put("H", "Hydrogen"));
    trace(elements.put("He", "Helium"));
    trace(elements.put("Al", "Aluminum"));
    test(elements.get("H"), "Hydrogen");
    test(elements.get("He"), "Helium");
    test(elements.get("Al"), "Aluminum");
    test(elements.containsKey("Li"), false);
    trace(elements.put("Al", "Aluminium"));
    test(elements.get("Al"), "Aluminium");
    test(elements.get("He"), "Helium");
    test(elements.containsKey("Al"), true);
    test(elements.size(), 3);
    trace(elements.remove("Al"));
    test(elements.size(), 2);
    test(elements.containsKey("Al"), false);
    test(elements.get("Al"), "");
    trace(elements.put("Li", "Lithium"));
    trace(elements.put("Be", "Beryllium"));
    test(elements.size(), 4);
    HashMap<string, string>::iterator it = elements.begin();
    reportMessage("HashMap<string,string>::iterator it = elements.begin();");
    declare(int elementBitSet = 0);
    test(it == elements.begin(), true);
    test(it == elements.end(), false);
    string pattern = "";
    trace(markElement(*it++, elementBitSet, pattern));
    trace(markElement(*it++, elementBitSet, pattern));
    trace(markElement(*it++, elementBitSet, pattern));
    trace(markElement(*it++, elementBitSet, pattern));
    test(it == elements.end(), true);
    test(elementBitSet, 15);
    testMapCopy(elements, elements);
    string str = "";
    elements.mapAll(AppendKeyValueFunctor(str));
    test(str, pattern);
    test(elements.toString(), "{" + pattern + "}");
    testInsertionOperator(elements, pattern);
    testExtractionOperator();
    reportResult("HashMap class");
}

static void markElement(string name, int& elementBitSet, string& str) {
    if (name == "H") {
        elementBitSet |= 1;
        if (str != "")
            str += ", ";
        str += "H:Hydrogen";
    } else if (name == "He") {
        elementBitSet |= 2;
        if (str != "")
            str += ", ";
        str += "He:Helium";
    } else if (name == "Li") {
        elementBitSet |= 4;
        if (str != "")
            str += ", ";
        str += "Li:Lithium";
    } else if (name == "Be") {
        elementBitSet |= 8;
        if (str != "")
            str += ", ";
        str += "Be:Beryllium";
    } else {
        elementBitSet = -1;
    }
}

/* Test copy constructor and assignment operator */

static void testMapCopy(HashMap<string, string>& map, HashMap<string, string> mapByValue) {
    int bits1 = 0;
    string junk = "";
    for (string key : map) {
        markElement(key, bits1, junk);
    }
    int bits2 = 0;
    for (string key : map) {
        markElement(key, bits2, junk);
    }
    test(bits1, bits2);
    HashMap<string, string> mapCopy = map;
    int bits3 = 0;
    for (string key : map) {
        markElement(key, bits3, junk);
    }
    test(bits2, bits3);
}

static void testInsertionOperator(HashMap<string, string>& elements, string pattern) {
    declare(ostringstream ss);
    reportMessage("HashMap<string,int> map;");
    HashMap<string, int> map;
    trace(ss << map);
    test(ss.str(), "{}");
    trace(ss.str(""));
    trace(map["one"] = 1);
    trace(map["two"] = 2);
    trace(map["three"] = 3);
    trace(ss << map);
    declare(string str = ss.str());
    test(str[0], '{');
    test(str[str.length() - 1], '}');
    test(str.find("one:1") == string::npos, false);
    test(str.find("two:2") == string::npos, false);
    test(str.find("three:3") == string::npos, false);
    trace(ss.str(""));
    trace(ss << elements);
    test(ss.str(), "{" + pattern + "}");
}

static void testExtractionOperator() {
    declare(istringstream ss("{one:1, two:2, three:3}"));
    reportMessage("HashMap<string,int> map;");
    HashMap<string, int> map;
    trace(ss >> map);
    test(map.size(), 3);
    test(map["one"], 1);
    test(map["two"], 2);
    test(map["three"], 3);
}
