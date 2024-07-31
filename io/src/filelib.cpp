/*
 * File: filelib.cpp
 * -----------------
 * This file implements the filelib.h interface.  All platform dependencies
 * are managed through the platform interface.
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

#include "filelib.h"

#include <algorithm>
#include <cctype>
#include <cstdio>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

#include "platform.h"
#include "vector.h"

/* Prototypes */

static void splitPath(std::string path, Vector<std::string> list);
static bool recursiveMatch(std::string str, int sx, std::string pattern, int px);

/* Implementations */

bool openFile(std::ifstream& stream, std::string filename) {
    stream.clear();
    stream.open(expandPathname(filename).c_str());
    return !stream.fail();
}

bool openFile(std::ofstream& stream, std::string filename) {
    stream.clear();
    stream.open(expandPathname(filename).c_str());
    return !stream.fail();
}

std::string promptUserForFile(std::ifstream& stream, std::string prompt) {
    while (true) {
        std::cout << prompt;
        std::string filename;
        getline(std::cin, filename);
        openFile(stream, filename);
        if (!stream.fail())
            return filename;
        stream.clear();
        std::cout << "Unable to open that file.  Try again." << std::endl;
        if (prompt == "")
            prompt = "Input file: ";
    }
}

std::string promptUserForFile(std::ofstream& stream, std::string prompt) {
    while (true) {
        std::cout << prompt;
        std::string filename;
        getline(std::cin, filename);
        openFile(stream, filename);
        if (!stream.fail())
            return filename;
        stream.clear();
        std::cout << "Unable to open that file.  Try again." << std::endl;
        if (prompt == "")
            prompt = "Output file: ";
    }
}

std::string openFileDialog(std::ifstream& stream) {
    return openFileDialog(stream, "Open File", "");
}

std::string openFileDialog(std::ifstream& stream, std::string title) {
    return openFileDialog(stream, title, "");
}

std::string openFileDialog(std::ifstream& stream, std::string title, std::string path) {
    std::string filename = getPlatform()->openFileDialog(title, "load", path);
    if (filename == "")
        return "";
    stream.open(filename.c_str());
    return (stream.fail()) ? "" : filename;
}

std::string openFileDialog(std::ofstream& stream) {
    return openFileDialog(stream, "Open File", "");
}

std::string openFileDialog(std::ofstream& stream, std::string title) {
    return openFileDialog(stream, title, "");
}

std::string openFileDialog(std::ofstream& stream, std::string title, std::string path) {
    std::string filename = getPlatform()->openFileDialog(title, "save", path);
    if (filename == "")
        return "";
    stream.open(filename.c_str());
    return (stream.fail()) ? "" : filename;
}

void readEntireFile(std::istream& is, Vector<std::string>& lines) {
    lines.clear();
    while (true) {
        std::string line;
        getline(is, line);
        if (is.fail())
            break;
        lines.add(line);
    }
}

void readEntireFile(std::istream& is, std::vector<std::string>& lines) {
    lines.clear();
    while (true) {
        std::string line;
        getline(is, line);
        if (is.fail())
            break;
        lines.push_back(line);
    }
}

std::string getRoot(std::string filename) {
    int dot = -1;
    int len = filename.length();
    for (int i = 0; i < len; i++) {
        char ch = filename[i];
        if (ch == '.')
            dot = i;
        if (ch == '/' || ch == '\\')
            dot = -1;
    }
    if (dot == -1) {
        return filename;
    } else {
        return filename.substr(0, dot);
    }
}

std::string getExtension(std::string filename) {
    int dot = -1;
    int len = filename.length();
    for (int i = 0; i < len; i++) {
        char ch = filename[i];
        if (ch == '.')
            dot = i;
        if (ch == '/' || ch == '\\')
            dot = -1;
    }
    if (dot == -1) {
        return "";
    } else {
        return filename.substr(dot);
    }
}

std::string getHead(std::string filename) {
    int slash = -1;
    int len = filename.length();
    for (int i = 0; i < len; i++) {
        char ch = filename[i];
        if (ch == '/' || ch == '\\')
            slash = i;
    }
    if (slash < 0) {
        return "";
    } else if (slash == 0) {
        return "/";
    } else {
        return filename.substr(0, slash);
    }
}

std::string getTail(std::string filename) {
    int slash = -1;
    int len = filename.length();
    for (int i = 0; i < len; i++) {
        char ch = filename[i];
        if (ch == '/' || ch == '\\')
            slash = i;
    }
    if (slash < 0) {
        return filename;
    } else {
        return filename.substr(slash + 1);
    }
}

std::string defaultExtension(std::string filename, std::string ext) {
    bool force = (ext[0] == '*');
    if (force)
        ext = ext.substr(1);
    int dot = -1;
    int len = filename.length();
    for (int i = 0; i < len; i++) {
        char ch = filename[i];
        if (ch == '.')
            dot = i;
        if (ch == '/' || ch == '\\')
            dot = -1;
    }
    if (dot == -1) {
        force = true;
        dot = len;
    }
    if (force) {
        return filename.substr(0, dot) + ext;
    } else {
        return filename;
    }
}

std::string openOnPath(std::ifstream& stream, std::string path, std::string filename) {
    Vector<std::string> paths;
    splitPath(path, paths);
    for (const std::string& dir : paths) {
        std::string pathname = dir + "/" + filename;
        if (openFile(stream, pathname))
            return pathname;
    }
    return "";
}

std::string openOnPath(std::ofstream& stream, std::string path, std::string filename) {
    Vector<std::string> paths;
    splitPath(path, paths);
    for (const std::string& dir : paths) {
        std::string pathname = dir + "/" + filename;
        if (openFile(stream, pathname))
            return pathname;
    }
    return "";
}

std::string findOnPath(std::string path, std::string filename) {
    std::ifstream stream;
    std::string result = openOnPath(stream, path, filename);
    if (result != "")
        stream.close();
    return result;
}

void deleteFile(std::string filename) {
    remove(expandPathname(filename).c_str());
}

void renameFile(std::string oldname, std::string newname) {
    oldname = expandPathname(oldname);
    newname = expandPathname(newname);
    rename(oldname.c_str(), newname.c_str());
}

void createDirectoryPath(std::string path) {
    int cp = 1;
    if (path == "")
        return;
    while ((cp = path.find('/', cp + 1)) != std::string::npos) {
        createDirectory(path.substr(0, cp - 1));
    }
    createDirectory(path);
}

bool matchFilenamePattern(std::string filename, std::string pattern) {
    return recursiveMatch(filename, 0, pattern, 0);
}

bool fileExists(std::string filename) {
    return getPlatform()->fileExists(filename);
}

bool isFile(std::string filename) {
    return getPlatform()->isFile(filename);
}

bool isSymbolicLink(std::string filename) {
    return getPlatform()->isSymbolicLink(filename);
}

bool isDirectory(std::string filename) {
    return getPlatform()->isDirectory(filename);
}

void setCurrentDirectory(std::string path) {
    return getPlatform()->setCurrentDirectory(path);
}

std::string getCurrentDirectory() {
    return getPlatform()->getCurrentDirectory();
}

void createDirectory(std::string path) {
    return getPlatform()->createDirectory(path);
}

std::string getDirectoryPathSeparator() {
    return getPlatform()->getDirectoryPathSeparator();
}

std::string getSearchPathSeparator() {
    return getPlatform()->getSearchPathSeparator();
}

std::string expandPathname(std::string filename) {
    return getPlatform()->expandPathname(filename);
}

void listDirectory(std::string path, Vector<std::string>& list) {
    std::vector<std::string> vec;
    listDirectory(path, vec);
    list.clear();
    for (const std::string& file : vec) {
        list.add(file);
    }
}

void listDirectory(std::string path, std::vector<std::string>& list) {
    return getPlatform()->listDirectory(path, list);
}

/* Private functions */

static void splitPath(std::string path, Vector<std::string> list) {
    char sep = (path.find(';') == std::string::npos) ? ':' : ';';
    path += sep;
    int start = 0;
    while (true) {
        int finish = path.find(sep, start);
        if (finish == std::string::npos)
            break;
        if (finish > start + 1) {
            list.add(path.substr(start, finish - start - 1));
        }
        start = finish + 1;
    }
}

static bool recursiveMatch(std::string str, int sx, std::string pattern, int px) {
    int slen = str.length();
    int plen = pattern.length();
    if (px == plen)
        return (sx == slen);
    char pch = pattern[px];
    if (pch == '*') {
        for (int i = sx; i <= slen; i++) {
            if (recursiveMatch(str, i, pattern, px + 1))
                return true;
        }
        return false;
    }
    if (sx == slen)
        return false;
    char sch = str[sx];
    if (pch == '[') {
        bool match = false;
        bool invert = false;
        px++;
        if (px == plen) {
            error("matchFilenamePattern: missing ]");
        }
        if (pattern[px] == '^') {
            px++;
            invert = true;
        }
        while (px < plen && pattern[px] != ']') {
            if (px + 2 < plen && pattern[px + 1] == '-') {
                match |= (sch >= pattern[px] && sch <= pattern[px + 2]);
                px += 3;
            } else {
                match |= (sch == pattern[px]);
                px++;
            }
        }
        if (px == plen) {
            error("matchFilenamePattern: missing ]");
        }
        if (match == invert)
            return false;
    } else if (pch != '?') {
        if (pch != sch)
            return false;
    }
    return recursiveMatch(str, sx + 1, pattern, px + 1);
}
