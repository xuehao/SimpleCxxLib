/*
 * File: TestMapClass.cpp
 * ----------------------
 * This file contains a unit test of the Map class.
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

#include "map.h"
#include "unittest.h"
using namespace std;

/* Prototypes */

static void testInsertionOperator(Map<string, string>& elements, string pattern);
static void testExtractionOperator();
static void testMapCopy(Map<string, string>& map, Map<string, string> mapByValue);

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

/* Test program */

void testMapClass() {
    Map<string, string> elements;
    reportMessage("Map<string,string> elements;");
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
    Map<string, string>::iterator it = elements.begin();
    reportMessage("Map<string,string>::iterator it = elements.begin();");
    declare(string pattern = "");
    trace(for (string key : elements) pattern += key);
    test(pattern, "BeHHeLi");
    testMapCopy(elements, elements);
    string str = "";
    elements.mapAll(AppendKeyValueFunctor(str));
    test(str, "Be:Beryllium, H:Hydrogen, He:Helium, Li:Lithium");
    test(elements.toString(), "{Be:Beryllium, H:Hydrogen, He:Helium, Li:Lithium}");
    testInsertionOperator(elements, "Be:Beryllium, H:Hydrogen, He:Helium, Li:Lithium");
    testExtractionOperator();
    reportResult("Map class");
}

/* Test copy constructor and assignment operator */

static void testMapCopy(Map<string, string>& map, Map<string, string> mapByValue) {
    string kvPairs;
    for (string key : map) {
        kvPairs += "<" + key + ":" + map[key] + ">";
    }
    string kvPairsInParameter;
    for (string key : map) {
        kvPairsInParameter += "<" + key + ":" + mapByValue[key] + ">";
    }
    test(kvPairs == kvPairsInParameter, true);
    Map<string, string> mapCopy = map;
    string kvPairsInCopy;
    for (string key : map) {
        kvPairsInCopy += "<" + key + ":" + mapCopy[key] + ">";
    }
    test(kvPairs == kvPairsInCopy, true);
}

static void testInsertionOperator(Map<string, string>& elements, string pattern) {
    declare(ostringstream ss);
    reportMessage("Map<string,int> map;");
    Map<string, int> map;
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
    reportMessage("Map<string,int> map;");
    Map<string, int> map;
    trace(ss >> map);
    test(map.size(), 3);
    test(map["one"], 1);
    test(map["two"], 2);
    test(map["three"], 3);
}
