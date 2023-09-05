/*
 * File: TestFilelibLibrary.cpp
 * ----------------------------
 * This file tests the functions in the filelib.h interface.
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
#include <string>

#include "error.h"
#include "filelib.h"
#include "strlib.h"
#include "unittest.h"
using namespace std;

/* Function prototypes */

static void testGetRoot(void);
static void testGetExtension(void);
static void testGetHead(void);
static void testGetTail(void);
static void testDefaultExtension(void);
static void testFileExists(void);
static void testIsFile(void);
static void testIsDirectory(void);
static void testExpandPathname(void);
static void testMatchFilenamePattern(void);

void testFilelibLibrary() {
    testGetRoot();
    testGetExtension();
    testGetHead();
    testGetTail();
    testDefaultExtension();
    testFileExists();
    testIsFile();
    testIsDirectory();
    testExpandPathname();
    testMatchFilenamePattern();
    reportResult("filelib.h library");
}

static void testGetRoot() {
    test(getRoot("filename.ext"), "filename");
    test(getRoot("abc.def.ghi"), "abc.def");
    test(getRoot("/a/b/c/filename.ext"), "/a/b/c/filename");
    test(getRoot("A:a\\b\\c\\filename.ext"), "A:a\\b\\c\\filename");
}

static void testGetExtension() {
    test(getExtension("filename.ext"), ".ext");
    test(getExtension("abc.def.ghi"), ".ghi");
    test(getExtension("/a/b/c/filename.ext"), ".ext");
    test(getExtension("A:a\\b\\c\\filename.ext"), ".ext");
}

static void testGetHead() {
    test(getHead("/a/b/c/filename.ext"), "/a/b/c");
    test(getHead("A:a\\b\\c\\filename.ext"), "A:a\\b\\c");
    test(getHead("a/b"), "a");
    test(getHead("a"), "");
    test(getHead("/a"), "/");
    test(getHead("/"), "/");
}

static void testGetTail() {
    test(getTail("/a/b/c/filename.ext"), "filename.ext");
    test(getTail("A:a\\b\\c\\filename.ext"), "filename.ext");
    test(getTail("a/b"), "b");
    test(getTail("a"), "a");
    test(getTail("/a"), "a");
    test(getTail("/"), "");
}

static void testDefaultExtension() {
    test(defaultExtension("filename", ".ext"), "filename.ext");
    test(defaultExtension("filename.old", ".new"), "filename.old");
    test(defaultExtension("filename.old", "*.new"), "filename.new");
    test(defaultExtension("a.b.c", "*.x"), "a.b.x");
}

static void testFileExists() {
    test(fileExists("CMakeLists.txt"), true);
    test(fileExists("xyzzy.cpp"), false);
}

static void testIsFile() {
    test(isFile("TestTokenScannerClass.cpp"), true);
    test(isFile("."), false);
    test(isFile("xyzzy.cpp"), false);
}

static void testIsDirectory() {
    test(isDirectory("TestFilelibLibrary.cpp"), false);
    test(isDirectory("."), true);
    test(isDirectory("xyzzy.cpp"), false);
}

static void testExpandPathname() {
    if (getDirectoryPathSeparator() == "/") {
        test(expandPathname("a/b"), "a/b");
        test(expandPathname("a\\b"), "a/b");
    } else {
        test(expandPathname("a/b"), "a\\b");
        test(expandPathname("a\\b"), "a\\b");
    }
}

static void testMatchFilenamePattern() {
    test(matchFilenamePattern("abc", "abc"), true);
    test(matchFilenamePattern("xxx", "abc"), false);
    test(matchFilenamePattern("ab", "abc"), false);
    test(matchFilenamePattern("abcd", "abc"), false);
    test(matchFilenamePattern("axc", "a?c"), true);
    test(matchFilenamePattern("ac", "a?c"), false);
    test(matchFilenamePattern("axxc", "a?c"), false);
    test(matchFilenamePattern("axxc", "a??c"), true);
    test(matchFilenamePattern("axc", "a*c"), true);
    test(matchFilenamePattern("ac", "a*c"), true);
    test(matchFilenamePattern("axxc", "a*c"), true);
    test(matchFilenamePattern("axxcd", "a*c"), false);
    test(matchFilenamePattern("axxbyyc", "a*b*c"), true);
    test(matchFilenamePattern("abc", "[abc]bc"), true);
    test(matchFilenamePattern("bbc", "[abc]bc"), true);
    test(matchFilenamePattern("xbc", "[abc]bc"), false);
    test(matchFilenamePattern("abc", "[^abc]bc"), false);
    test(matchFilenamePattern("bbc", "[^abc]bc"), false);
    test(matchFilenamePattern("xbc", "[^abc]bc"), true);
    test(matchFilenamePattern("abc", "[a-c]bc"), true);
    test(matchFilenamePattern("bbc", "[a-c]bc"), true);
    test(matchFilenamePattern("xbc", "[a-c]bc"), false);
    test(matchFilenamePattern("abc", "[^a-c]bc"), false);
    test(matchFilenamePattern("bbc", "[^a-c]bc"), false);
    test(matchFilenamePattern("xbc", "[^a-c]bc"), true);
}
