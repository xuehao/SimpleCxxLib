/*
 * File: platform.cpp
 * ------------------
 * This file implements the platform interface by passing commands to
 * a Java back end that manages the display.
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

#include <algorithm>
#include <cctype>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <fstream>
#include <iostream>
#include <sstream>
#include <streambuf>
#include <string>
#include <vector>

#ifdef _WIN32
#include <tchar.h>
#include <windows.h>
#undef MOUSE_EVENT
#undef KEY_EVENT
#undef MOUSE_MOVED
#undef HELP_KEY
#else
#include <dirent.h>
#include <errno.h>
#include <pwd.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#endif

#include "error.h"
#include "filelib.h"
#include "gevents.h"
#include "gtimer.h"
#include "gtypes.h"
#include "hashmap.h"
#include "platform.h"
#include "queue.h"
#include "stack.h"
#include "strlib.h"
#include "tokenscanner.h"
#include "vector.h"

static std::string getLineConsole();
static void putConsole(const std::string& str);
static void endLineConsole();
static int scanInt(TokenScanner& scanner);
static double scanDouble(TokenScanner& scanner);
static GDimension scanDimension(const std::string& str);
static GRectangle scanRectangle(const std::string& str);

/* Stored arguments */

static int argcMain;
static char** argvMain;

class ConsoleStreambuf : public std::streambuf {
private:
    /* Constants */

    static const int BUFFER_SIZE = 1024;

    /* Instance variables */

    char inBuffer[BUFFER_SIZE];
    char outBuffer[BUFFER_SIZE];

public:
    ConsoleStreambuf() {
        setg(inBuffer, inBuffer, inBuffer);
        setp(outBuffer, outBuffer + BUFFER_SIZE);
    }

    ~ConsoleStreambuf() {
        std::cout.flush();
    }

    virtual int underflow() {
        // Allow long strings at some point
        std::string line = getLineConsole();
        int n = line.length();
        if (n + 1 >= BUFFER_SIZE)
            error("String too long");
        for (int i = 0; i < n; i++) {
            inBuffer[i] = line[i];
        }
        inBuffer[n++] = '\n';
        inBuffer[n] = '\0';
        setg(inBuffer, inBuffer, inBuffer + n);
        return inBuffer[0];
    }

    virtual int overflow(int ch = EOF) {
        std::string line = "";
        for (char* cp = pbase(); cp < pptr(); cp++) {
            if (*cp == '\n') {
                putConsole(line);
                endLineConsole();
                line = "";
            } else {
                line += *cp;
            }
        }
        if (line != "") {
            putConsole(line);
        }
        setp(outBuffer, outBuffer + BUFFER_SIZE);
        if (ch != EOF) {
            outBuffer[0] = ch;
            pbump(1);
        }
        return ch != EOF;
    }

    virtual int sync() {
        return overflow();
    }
};

/* Private data */

static Queue<GEvent> eventQueue;
static HashMap<std::string, GTimerData*> timerTable;
static HashMap<std::string, GWindowData*> windowTable;
static HashMap<std::string, GObject*> sourceTable;
static HashMap<std::string, std::string> optionTable;
static std::string programName;
static std::ofstream logfile;
static bool tracePipe;
static int pin;
static int pout;

#ifdef _WIN32
static HANDLE rdFromJBE = nullptr;
static HANDLE wrFromJBE = nullptr;
static HANDLE rdToJBE = nullptr;
static HANDLE wrToJBE = nullptr;
#endif

/* Prototypes */

static void initPipe();
static void putPipe(std::string line);
static std::string getPipe();
static std::string getResult();
static void getStatus();
static GEvent parseEvent(std::string line);
static GEvent parseMouseEvent(TokenScanner& scanner, EventType type);
static GEvent parseKeyEvent(TokenScanner& scanner, EventType type);
static GEvent parseTimerEvent(TokenScanner& scanner, EventType type);
static GEvent parseWindowEvent(TokenScanner& scanner, EventType type);
static GEvent parseActionEvent(TokenScanner& scanner, EventType type);

/* Implementation of the Platform class */

Platform::Platform() {
    /* Empty */
}

Platform::~Platform() {
    /* Empty */
}

/* Unix implementations of filelib.h primitives */

#ifndef _WIN32

bool Platform::fileExists(std::string filename) {
    struct stat fileInfo;
    return stat(filename.c_str(), &fileInfo) == 0;
}

bool Platform::isFile(std::string filename) {
    struct stat fileInfo;
    if (stat(filename.c_str(), &fileInfo) != 0)
        return false;
    return S_ISREG(fileInfo.st_mode) != 0;
}

bool Platform::isSymbolicLink(std::string filename) {
    struct stat fileInfo;
    if (stat(filename.c_str(), &fileInfo) != 0)
        return false;
    return S_ISLNK(fileInfo.st_mode) != 0;
}

bool Platform::isDirectory(std::string filename) {
    struct stat fileInfo;
    if (stat(filename.c_str(), &fileInfo) != 0)
        return false;
    return S_ISDIR(fileInfo.st_mode) != 0;
}

void Platform::setCurrentDirectory(std::string path) {
    if (chdir(path.c_str()) == 0) {
        std::string msg = "setCurrentDirectory: ";
        std::string err = std::string(strerror(errno));
        error(msg + err);
    }
}

std::string Platform::getCurrentDirectory() {
    char* cwd = getcwd(nullptr, 0);
    if (cwd == nullptr) {
        std::string msg = "getCurrentDirectory: ";
        std::string err = std::string(strerror(errno));
        error(msg + err);
    }
    std::string result = std::string(cwd);
    free(cwd);
    return result;
}

void Platform::createDirectory(std::string path) {
    if (endsWith(path, "/")) {
        path = path.substr(0, path.length() - 2);
    }
    if (mkdir(path.c_str(), 0777) != 0) {
        if (errno == EEXIST && isDirectory(path))
            return;
        std::string msg = "createDirectory: ";
        std::string err = std::string(strerror(errno));
        error(msg + err);
    }
}

std::string Platform::getDirectoryPathSeparator() {
    return "/";
}

std::string Platform::getSearchPathSeparator() {
    return ":";
}

std::string Platform::expandPathname(std::string filename) {
    if (filename == "")
        return "";
    int len = filename.length();
    if (filename[0] == '~') {
        int spos = 1;
        while (spos < len && filename[spos] != '\\' && filename[spos] != '/') {
            spos++;
        }
        char* homedir = nullptr;
        if (spos == 1) {
            homedir = getenv("HOME");
            if (homedir == nullptr)
                homedir = getpwuid(getuid())->pw_dir;
        } else {
            struct passwd* pw = getpwnam(filename.substr(1, spos - 1).c_str());
            if (pw == nullptr)
                error("expandPathname: No such user");
            homedir = pw->pw_dir;
        }
        filename = std::string(homedir) + filename.substr(spos);
        len = filename.length();
    }
    for (int i = 0; i < len; i++) {
        if (filename[i] == '\\')
            filename[i] = '/';
    }
    return filename;
}

void Platform::listDirectory(std::string path, std::vector<std::string>& list) {
    if (path == "")
        path = ".";
    DIR* dir = opendir(path.c_str());
    if (dir == nullptr)
        error(std::string("listDirectory: Can't open ") + path);
    list.clear();
    while (true) {
        struct dirent* ep = readdir(dir);
        if (ep == nullptr)
            break;
        std::string name = std::string(ep->d_name);
        if (name != "." && name != "..")
            list.push_back(name);
    }
    closedir(dir);
    sort(list.begin(), list.end());
}

#else

/* Windows implementations of filelib.h primitives */

bool Platform::fileExists(std::string filename) {
    return GetFileAttributesA(filename.c_str()) != INVALID_FILE_ATTRIBUTES;
}

bool Platform::isFile(std::string filename) {
    DWORD attr = GetFileAttributesA(filename.c_str());
    return attr != INVALID_FILE_ATTRIBUTES && !(attr & FILE_ATTRIBUTE_DIRECTORY);
}

bool Platform::isSymbolicLink(std::string filename) {
    DWORD attr = GetFileAttributesA(filename.c_str());
    return attr != INVALID_FILE_ATTRIBUTES && (attr & FILE_ATTRIBUTE_REPARSE_POINT);
}

bool Platform::isDirectory(std::string filename) {
    DWORD attr = GetFileAttributesA(filename.c_str());
    return attr != INVALID_FILE_ATTRIBUTES && (attr & FILE_ATTRIBUTE_DIRECTORY);
}

void Platform::setCurrentDirectory(std::string path) {
    if (!isDirectory(path) || !SetCurrentDirectoryA(path.c_str())) {
        error("setCurrentDirectory: Can't change to " + path);
    }
}

std::string Platform::getCurrentDirectory() {
    char path[MAX_PATH + 1];
    int n = GetCurrentDirectoryA(MAX_PATH + 1, path);
    return std::string(path, n);
}

void Platform::createDirectory(std::string path) {
    if (!CreateDirectoryA(path.c_str(), nullptr)) {
        error("createDirectory: Can't create " + path);
    }
}

std::string Platform::getDirectoryPathSeparator() {
    return "\\";
}

std::string Platform::getSearchPathSeparator() {
    return ";";
}

std::string Platform::expandPathname(std::string filename) {
    if (filename == "")
        return "";
    int len = filename.length();
    for (int i = 0; i < len; i++) {
        if (filename[i] == '/')
            filename[i] = '\\';
    }
    return filename;
}

void Platform::listDirectory(std::string path, std::vector<std::string>& list) {
    if (path == "")
        path = ".";
    std::string pattern = path + "\\*.*";
    WIN32_FIND_DATAA fd;
    HANDLE h = FindFirstFileA(pattern.c_str(), &fd);
    if (h == INVALID_HANDLE_VALUE) {
        error("listDirectory: Can't list directory");
    }
    list.clear();
    while (true) {
        std::string name = std::string(fd.cFileName);
        if (name != "." && name != "..")
            list.push_back(name);
        if (!FindNextFileA(h, &fd))
            break;
    }
    FindClose(h);
    sort(list.begin(), list.end());
}

#endif

std::string Platform::openFileDialog(std::string title, std::string mode, std::string path) {
    std::ostringstream os;
    os << "File.openFileDialog(";
    writeQuotedString(os, title);
    os << ", \"" << mode << "\", \"" << path << "\")";
    putPipe(os.str());
    return getResult();
}

void Platform::createGWindow(const GWindow& gw, double width, double height, GObject* topCompound) {
    std::ostringstream os;
    os << gw.gwd;
    std::string id = os.str();
    windowTable.put(id, gw.gwd);
    os.str("");
    os << "GWindow.create(\"" << id << "\", " << width << ", " << height << ", \"" << topCompound
       << "\")";
    putPipe(os.str());
    getStatus();
}

void Platform::deleteGWindow(const GWindow& gw) {
    std::ostringstream os;
    os << gw.gwd;
    std::string id = os.str();
    windowTable.remove(id);
    os.str("");
    os << "GWindow.delete(\"" << gw.gwd << "\")";
    putPipe(os.str());
}

void Platform::close(const GWindow& gw) {
    std::ostringstream os;
    os << "GWindow.close(\"" << gw.gwd << "\")";
    putPipe(os.str());
}

void Platform::requestFocus(const GWindow& gw) {
    std::ostringstream os;
    os << "GWindow.requestFocus(\"" << gw.gwd << "\")";
    putPipe(os.str());
}

void Platform::clear(const GWindow& gw) {
    std::ostringstream os;
    os << "GWindow.clear(\"" << gw.gwd << "\")";
    putPipe(os.str());
}

void Platform::repaint(const GWindow& gw) {
    std::ostringstream os;
    os << "GWindow.repaint(\"" << gw.gwd << "\")";
    putPipe(os.str());
}

void Platform::setVisible(const GWindow& gw, bool flag) {
    std::ostringstream os;
    os << std::boolalpha << "GWindow.setVisible(\"" << gw.gwd << "\", " << flag << ")";
    putPipe(os.str());
}

void Platform::setWindowTitle(const GWindow& gw, std::string title) {
    std::ostringstream os;
    os << "GWindow.setTitle(\"" << gw.gwd << "\", ";
    writeQuotedString(os, title);
    os << ")";
    putPipe(os.str());
}

double Platform::getScreenWidth() {
    putPipe("GWindow.getScreenWidth()");
    return stringToReal(getResult());
}

double Platform::getScreenHeight() {
    putPipe("GWindow.getScreenHeight()");
    return stringToReal(getResult());
}

void Platform::pause(double milliseconds) {
    std::ostringstream os;
    os << "GTimer.pause(" << milliseconds << ")";
    putPipe(os.str());
    getStatus();
}

void Platform::createTimer(const GTimer& timer, double delay) {
    std::ostringstream os;
    os << timer.gtd;
    std::string id = os.str();
    timerTable.put(id, timer.gtd);
    os.str("");
    os << "GTimer.create(\"" << id << "\", " << delay << ")";
    putPipe(os.str());
}

void Platform::deleteTimer(const GTimer& timer) {
    std::ostringstream os;
    os << timer.gtd;
    std::string id = os.str();
    timerTable.remove(id);
    os.str("");
    os << "GTimer.deleteTimer(\"" << id << "\")";
    putPipe(os.str());
}

void Platform::startTimer(const GTimer& timer) {
    std::ostringstream os;
    os << "GTimer.startTimer(\"" << timer.gtd << "\")";
    putPipe(os.str());
}

void Platform::stopTimer(const GTimer& timer) {
    std::ostringstream os;
    os << "GTimer.stopTimer(\"" << timer.gtd << "\")";
    putPipe(os.str());
}

void Platform::createSound(Sound* sound, std::string filename) {
    std::ostringstream os;
    os << "Sound.create(\"" << sound << "\", \"" << filename << "\")";
    putPipe(os.str());
    getStatus();
}

void Platform::deleteSound(Sound* sound) {
    std::ostringstream os;
    os << "Sound.delete(\"" << sound << "\")";
    putPipe(os.str());
}

void Platform::playSound(Sound* sound) {
    std::ostringstream os;
    os << "Sound.play(\"" << sound << "\")";
    putPipe(os.str());
}

void Platform::deleteGObject(GObject* gobj) {
    std::ostringstream os;
    os << "GObject.delete(\"" << gobj << "\")";
    putPipe(os.str());
}

void Platform::add(GObject* compound, GObject* gobj) {
    std::ostringstream os;
    os << "GCompound.add(\"" << compound << "\", \"" << gobj << "\")";
    putPipe(os.str());
}

void Platform::remove(GObject* gobj) {
    std::ostringstream os;
    os << "GObject.remove(\"" << gobj << "\")";
    putPipe(os.str());
}

void Platform::setRegionAlignment(const GWindow& gw, std::string region, std::string align) {
    std::ostringstream os;
    os << "GWindow.setRegionAlignment(\"" << gw.gwd << "\", \"" << region << "\", \"" << align
       << "\")";
    putPipe(os.str());
}

void Platform::addToRegion(const GWindow& gw, GObject* gobj, std::string region) {
    std::ostringstream os;
    os << "GWindow.addToRegion(\"" << gw.gwd << "\", \"" << gobj << "\", \"" << region << "\")";
    putPipe(os.str());
}

void Platform::removeFromRegion(const GWindow& gw, GObject* gobj, std::string region) {
    std::ostringstream os;
    os << "GWindow.removeFromRegion(\"" << gw.gwd << "\", \"" << gobj << "\", \"" << region
       << "\")";
    putPipe(os.str());
}

void Platform::sendForward(GObject* gobj) {
    std::ostringstream os;
    os << "GObject.sendForward(\"" << gobj << "\")";
    putPipe(os.str());
}

void Platform::sendToFront(GObject* gobj) {
    std::ostringstream os;
    os << "GObject.sendToFront(\"" << gobj << "\")";
    putPipe(os.str());
}

void Platform::sendBackward(GObject* gobj) {
    std::ostringstream os;
    os << "GObject.sendBackward(\"" << gobj << "\")";
    putPipe(os.str());
}

void Platform::sendToBack(GObject* gobj) {
    std::ostringstream os;
    os << "GObject.sendToBack(\"" << gobj << "\")";
    putPipe(os.str());
}

void Platform::setVisible(GObject* gobj, bool flag) {
    std::ostringstream os;
    os << std::boolalpha << "GObject.setVisible(\"" << gobj << "\", " << flag << ")";
    putPipe(os.str());
}

void Platform::setColor(GObject* gobj, std::string color) {
    std::ostringstream os;
    os << "GObject.setColor(\"" << gobj << "\", \"" << color << "\")";
    putPipe(os.str());
}

void Platform::scale(GObject* gobj, double sx, double sy) {
    std::ostringstream os;
    os << "GObject.scale(\"" << gobj << "\", " << sx << ", " << sy << ")";
    putPipe(os.str());
}

void Platform::rotate(GObject* gobj, double theta) {
    std::ostringstream os;
    os << "GObject.rotate(\"" << gobj << "\", " << theta << ")";
    putPipe(os.str());
}

// Move this computation into gobjects.cpp

bool Platform::contains(const GObject* gobj, double x, double y) {
    std::ostringstream os;
    os << "GObject.contains(\"" << gobj << "\", " << x << ", " << y << ")";
    putPipe(os.str());
    return getResult() == "true";
}

// Move this computation into gobjects.cpp

GRectangle Platform::getBounds(const GObject* gobj) {
    std::ostringstream os;
    os << "GObject.getBounds(\"" << gobj << "\")";
    putPipe(os.str());
    std::string result = getResult();
    if (!startsWith(result, "GRectangle("))
        error(result);
    return scanRectangle(result);
}

void Platform::setLineWidth(GObject* gobj, double lineWidth) {
    std::ostringstream os;
    os << "GObject.setLineWidth(\"" << gobj << "\", " << lineWidth << ")";
    putPipe(os.str());
}

void Platform::setLocation(GObject* gobj, double x, double y) {
    std::ostringstream os;
    os << "GObject.setLocation(\"" << gobj << "\", " << x << ", " << y << ")";
    putPipe(os.str());
}

void Platform::setSize(GObject* gobj, double width, double height) {
    std::ostringstream os;
    os << "GObject.setSize(\"" << gobj << "\", " << width << ", " << height << ")";
    putPipe(os.str());
}

void Platform::setFrameRectangle(GObject* gobj, double x, double y, double width, double height) {
    std::ostringstream os;
    os << "GArc.setFrameRectangle(\"" << gobj << "\", " << x << ", " << y << ", " << width << ", "
       << height << ")";
    putPipe(os.str());
}

void Platform::draw(const GWindow& gw, const GObject* gobj) {
    std::ostringstream os;
    os << "GWindow.draw(\"" << gw.gwd << "\", \"" << gobj << "\")";
    putPipe(os.str());
}

void Platform::setFilled(GObject* gobj, bool flag) {
    std::ostringstream os;
    os << std::boolalpha << "GObject.setFilled(\"" << gobj << "\", " << flag << ")";
    putPipe(os.str());
}

void Platform::setFillColor(GObject* gobj, std::string color) {
    std::ostringstream os;
    os << "GObject.setFillColor(\"" << gobj << "\", \"" << color << "\")";
    putPipe(os.str());
}

void Platform::createGRect(GObject* gobj, double width, double height) {
    std::ostringstream os;
    os << "GRect.create(\"" << gobj << "\", " << width << ", " << height << ")";
    putPipe(os.str());
}

void Platform::createGRoundRect(GObject* gobj, double width, double height, double corner) {
    std::ostringstream os;
    os << "GRoundRect.create(\"" << gobj << "\", " << width << ", " << height << ", " << corner
       << ")";
    putPipe(os.str());
}

void Platform::createG3DRect(GObject* gobj, double width, double height, bool raised) {
    std::ostringstream os;
    os << std::boolalpha << "G3DRect.create(\"" << gobj << "\", " << width << ", " << height << ", "
       << raised << ")";
    putPipe(os.str());
}

void Platform::setRaised(GObject* gobj, bool raised) {
    std::ostringstream os;
    os << std::boolalpha << "G3DRect.setRaised(\"" << gobj << "\", " << raised << ")";
    putPipe(os.str());
}

void Platform::createGLabel(GObject* gobj, std::string label) {
    std::ostringstream os;
    os << "GLabel.create(\"" << gobj << "\", \"" << label << "\")";
    putPipe(os.str());
}

void Platform::createGLine(GObject* gobj, double x1, double y1, double x2, double y2) {
    std::ostringstream os;
    os << "GLine.create(\"" << gobj << "\", " << x1 << ", " << y1 << ", " << x2 << ", " << y2
       << ")";
    putPipe(os.str());
}

void Platform::setStartPoint(GObject* gobj, double x, double y) {
    std::ostringstream os;
    os << "GLine.setStartPoint(\"" << gobj << "\", " << x << ", " << y << ")";
    putPipe(os.str());
}

void Platform::setEndPoint(GObject* gobj, double x, double y) {
    std::ostringstream os;
    os << "GLine.setEndPoint(\"" << gobj << "\", " << x << ", " << y << ")";
    putPipe(os.str());
}

void Platform::createGArc(GObject* gobj, double width, double height, double start, double sweep) {
    std::ostringstream os;
    os << "GArc.create(\"" << gobj << "\", " << width << ", " << height << ", " << start << ", "
       << sweep << ")";
    putPipe(os.str());
}

void Platform::setStartAngle(GObject* gobj, double angle) {
    std::ostringstream os;
    os << "GArc.setStartAngle(\"" << gobj << "\", " << angle << ")";
    putPipe(os.str());
}

void Platform::setSweepAngle(GObject* gobj, double angle) {
    std::ostringstream os;
    os << "GArc.setSweepAngle(\"" << gobj << "\", " << angle << ")";
    putPipe(os.str());
}

GDimension Platform::createGImage(GObject* gobj, std::string filename) {
    std::ostringstream os;
    os << "GImage.create(\"" << gobj << "\", \"" << filename << "\")";
    putPipe(os.str());
    std::string result = getResult();
    if (!startsWith(result, "GDimension("))
        error(result);
    return scanDimension(result);
}

void Platform::createGPolygon(GObject* gobj) {
    std::ostringstream os;
    os << "GPolygon.create(\"" << gobj << "\")";
    putPipe(os.str());
}

void Platform::addVertex(GObject* gobj, double x, double y) {
    std::ostringstream os;
    os << "GPolygon.addVertex(\"" << gobj << "\", " << x << ", " << y << ")";
    putPipe(os.str());
}

void Platform::createGOval(GObject* gobj, double width, double height) {
    std::ostringstream os;
    os << "GOval.create(\"" << gobj << "\", " << width << ", " << height << ")";
    putPipe(os.str());
}

void Platform::setActionCommand(GObject* gobj, std::string cmd) {
    std::ostringstream os;
    os << "GInteractor.setActionCommand(\"" << gobj << "\", ";
    writeQuotedString(os, cmd);
    os << ")";
    putPipe(os.str());
}

GDimension Platform::getSize(GObject* gobj) {
    std::ostringstream os;
    os << "GInteractor.getSize(\"" << gobj << "\")";
    putPipe(os.str());
    return scanDimension(getResult());
}

void Platform::createGButton(GObject* gobj, std::string label) {
    std::ostringstream os;
    os << gobj;
    sourceTable.put(os.str(), gobj);
    os.str("");
    os << "GButton.create(\"" << gobj << "\", ";
    writeQuotedString(os, label);
    os << ")";
    putPipe(os.str());
}

void Platform::createGCheckBox(GObject* gobj, std::string label) {
    std::ostringstream os;
    os << gobj;
    sourceTable.put(os.str(), gobj);
    os.str("");
    os << "GCheckBox.create(\"" << gobj << "\", ";
    writeQuotedString(os, label);
    os << ")";
    putPipe(os.str());
}

bool Platform::isSelected(GObject* gobj) {
    std::ostringstream os;
    os << "GCheckBox.isSelected(\"" << gobj << "\")";
    putPipe(os.str());
    return getResult() == "true";
}

void Platform::setSelected(GObject* gobj, bool state) {
    std::ostringstream os;
    os << std::boolalpha << "GCheckBox.setSelected(\"" << gobj << "\", " << state << ")";
    putPipe(os.str());
}

void Platform::createGSlider(GObject* gobj, int min, int max, int value) {
    std::ostringstream os;
    os << gobj;
    sourceTable.put(os.str(), gobj);
    os.str("");
    os << "GSlider.create(\"" << gobj << "\", " << min << ", " << max << ", " << value << ")";
    putPipe(os.str());
}

int Platform::getValue(GObject* gobj) {
    std::ostringstream os;
    os << "GSlider.getValue(\"" << gobj << "\")";
    putPipe(os.str());
    return stringToInteger(getResult());
}

void Platform::setValue(GObject* gobj, int value) {
    std::ostringstream os;
    os << "GSlider.setValue(\"" << gobj << "\", " << value << ")";
    putPipe(os.str());
}

void Platform::createGTextField(GObject* gobj, int nChars) {
    std::ostringstream os;
    os << gobj;
    sourceTable.put(os.str(), gobj);
    os.str("");
    os << "GTextField.create(\"" << gobj << "\", " << nChars << ")";
    putPipe(os.str());
}

std::string Platform::getText(GObject* gobj) {
    std::ostringstream os;
    os << "GTextField.getText(\"" << gobj << "\")";
    putPipe(os.str());
    return getResult();
}

void Platform::setText(GObject* gobj, std::string str) {
    std::ostringstream os;
    os << "GTextField.setText(\"" << gobj << "\", ";
    writeQuotedString(os, str);
    os << ")";
    putPipe(os.str());
}

void Platform::createGChooser(GObject* gobj) {
    std::ostringstream os;
    os << gobj;
    sourceTable.put(os.str(), gobj);
    os.str("");
    os << "GChooser.create(\"" << gobj << "\")";
    putPipe(os.str());
}

void Platform::addItem(GObject* gobj, std::string item) {
    std::ostringstream os;
    os << "GChooser.addItem(\"" << gobj << "\", ";
    writeQuotedString(os, item);
    os << ")";
    putPipe(os.str());
}

std::string Platform::getSelectedItem(GObject* gobj) {
    std::ostringstream os;
    os << "GChooser.getSelectedItem(\"" << gobj << "\")";
    putPipe(os.str());
    return getResult();
}

void Platform::setSelectedItem(GObject* gobj, std::string item) {
    std::ostringstream os;
    os << "GChooser.setSelectedItem(\"" << gobj << "\", ";
    writeQuotedString(os, item);
    os << ")";
    putPipe(os.str());
}

void Platform::createGCompound(GObject* gobj) {
    std::ostringstream os;
    os << "GCompound.create(\"" << gobj << "\")";
    putPipe(os.str());
}

void Platform::setFont(GObject* gobj, std::string font) {
    std::ostringstream os;
    os << "GLabel.setFont(\"" << gobj << "\", \"" << font << "\")";
    putPipe(os.str());
}

void Platform::setLabel(GObject* gobj, std::string str) {
    std::ostringstream os;
    os << "GLabel.setLabel(\"" << gobj << "\", ";
    writeQuotedString(os, str);
    os << ")";
    putPipe(os.str());
}

double Platform::getFontAscent(const GObject* gobj) {
    std::ostringstream os;
    os << "GLabel.getFontAscent(\"" << gobj << "\")";
    putPipe(os.str());
    return stringToReal(getResult());
}

double Platform::getFontDescent(const GObject* gobj) {
    std::ostringstream os;
    os << "GLabel.getFontDescent(\"" << gobj << "\")";
    putPipe(os.str());
    return stringToReal(getResult());
}

GDimension Platform::getGLabelSize(const GObject* gobj) {
    std::ostringstream os;
    os << "GLabel.getGLabelSize(\"" << gobj << "\")";
    putPipe(os.str());
    return scanDimension(getResult());
}

GEvent Platform::getNextEvent(int mask) {
    std::cout.flush();
    if (eventQueue.isEmpty()) {
        putPipe("GEvent.getNextEvent(" + integerToString(mask) + ")");
        getResult();
        if (eventQueue.isEmpty())
            return GEvent();
    }
    return eventQueue.dequeue();
}

GEvent Platform::waitForEvent(int mask) {
    std::cout.flush();
    while (eventQueue.isEmpty()) {
        putPipe("GEvent.waitForEvent(" + integerToString(mask) + ")");
        getResult();
    }
    return eventQueue.dequeue();
}

void Platform::exitGraphics() {
    putPipe("GWindow.exitGraphics()");
    exit(0);
}

/**
 * Even if the function is called multiple times, space for the static variable is allocated only
 * once and the value of variable in the previous call gets carried through the next function call.
 */
Platform* getPlatform() {
    static Platform gp;
    return &gp;
}

int startupMain(int argc, char** argv) {
    extern int Main();
    argcMain = argc;
    argvMain = argv;
    programName = getRoot(getTail(argv[0]));
    initPipe();
    ConsoleStreambuf cbuf;
    std::cin.rdbuf(&cbuf);
    std::cout.rdbuf(&cbuf);
    std::cerr.rdbuf(&cbuf);
    try {
        return Main();
    } catch (ErrorException& ex) {
        std::string msg = "Error: " + ex.getMessage();
        std::cerr << msg << std::endl;
        return EXIT_FAILURE;
    }
}

#ifdef _WIN32

/* Windows implementation of interface to Java back end */

static void initPipe() {
    SECURITY_ATTRIBUTES attr;
    attr.nLength = sizeof(SECURITY_ATTRIBUTES);
    attr.bInheritHandle = true;
    attr.lpSecurityDescriptor = nullptr;
    if (!CreatePipe(&rdFromJBE, &wrFromJBE, &attr, 0)) {
        error("Can't create fromJBE");
    }
    if (!SetHandleInformation(rdFromJBE, HANDLE_FLAG_INHERIT, 0)) {
        error("SetHandleInformation failed for fromJBE");
    }
    if (!CreatePipe(&rdToJBE, &wrToJBE, &attr, 0)) {
        error("Can't create toJBE");
    }
    if (!SetHandleInformation(wrToJBE, HANDLE_FLAG_INHERIT, 0)) {
        error("SetHandleInformation failed for toJBE");
    }
    std::string cmd = "java -jar spl.jar " + programName;
    int n = cmd.length();
    char* cmdLine = new char[n + 1];
    for (int i = 0; i < n; i++) {
        cmdLine[i] = cmd[i];
    }
    cmdLine[n] = '\0';
    PROCESS_INFORMATION pInfo;
    memset(&pInfo, 0, sizeof(PROCESS_INFORMATION));
    STARTUPINFOA sInfo;
    memset(&sInfo, 0, sizeof(STARTUPINFOA));
    sInfo.cb = sizeof(STARTUPINFOA);
    sInfo.dwFlags = STARTF_USESTDHANDLES;
    sInfo.hStdInput = rdToJBE;
    sInfo.hStdOutput = wrFromJBE;
    sInfo.hStdError = wrFromJBE;
    int ok = CreateProcessA(nullptr, cmdLine, nullptr, nullptr, true, 0, nullptr, nullptr, &sInfo,
                            &pInfo);
    if (!ok) {
        DWORD err = GetLastError();
        std::cerr << err << std::endl;
    } else {
        CloseHandle(pInfo.hProcess);
        CloseHandle(pInfo.hThread);
    }
}

static void putPipe(std::string line) {
    DWORD nch;
    WriteFile(wrToJBE, line.c_str(), line.length(), &nch, nullptr);
    WriteFile(wrToJBE, "\n", 1, &nch, nullptr);
    FlushFileBuffers(wrToJBE);
}

static std::string getPipe() {
    std::string line = "";
    DWORD nch;
    while (true) {
        char ch;
        ReadFile(rdFromJBE, &ch, 1, &nch, nullptr);
        if (ch == '\n' || ch == '\r')
            break;
        line += ch;
    }
    return line;
}

#else

/* Linux/Mac implementation of interface to Java back end */

static void initPipe() {
    char* trace = getenv("JBETRACE");
    logfile.open("/dev/tty");
    tracePipe = trace != nullptr && startsWith(toLowerCase(trace), "t");
    int toJBE[2], fromJBE[2];
    pipe(toJBE);
    pipe(fromJBE);
    int child = fork();
    if (child == 0) {
        dup2(toJBE[0], 0);
        close(toJBE[0]);
        close(toJBE[1]);
        dup2(fromJBE[1], 1);
        close(fromJBE[0]);
        close(fromJBE[1]);
#ifdef __APPLE__
        std::string option = "-Xdock:name=" + programName;
        execlp("java", "java", option.c_str(), "-jar", "spl.jar", programName.c_str(), nullptr);
#else
        execlp("java", "java", "-jar", "spl.jar", programName.c_str(), nullptr);
#endif
        throw new ErrorException("Could not exec spl.jar");
    } else {
        pin = fromJBE[0];
        pout = toJBE[1];
        close(fromJBE[1]);
        close(toJBE[0]);
    }
}

static void putPipe(std::string line) {
    write(pout, line.c_str(), line.length());
    write(pout, "\n", 1);
    if (tracePipe)
        logfile << "-> " << line << std::endl;
}

static std::string getPipe() {
    std::string line = "";
    while (true) {
        char ch;
        read(pin, &ch, 1);
        if (ch == '\n')
            break;
        line += ch;
    }
    if (tracePipe)
        logfile << "<- " << line << std::endl;
    return line;
}

#endif

static std::string getResult() {
    while (true) {
        std::string line = getPipe();
        if (startsWith(line, "result:"))
            return line.substr(7);
        if (startsWith(line, "event:")) {
            eventQueue.enqueue(parseEvent(line.substr(6)));
        }
    }
}

static void getStatus() {
    std::string result = getResult();
    if (result != "ok")
        error(result);
}

static GEvent parseEvent(std::string line) {
    TokenScanner scanner(line);
    scanner.ignoreWhitespace();
    scanner.scanNumbers();
    scanner.scanStrings();
    std::string name = scanner.nextToken();
    if (name == "mousePressed") {
        return parseMouseEvent(scanner, MOUSE_PRESSED);
    } else if (name == "mouseReleased") {
        return parseMouseEvent(scanner, MOUSE_RELEASED);
    } else if (name == "mouseClicked") {
        return parseMouseEvent(scanner, MOUSE_CLICKED);
    } else if (name == "mouseMoved") {
        return parseMouseEvent(scanner, MOUSE_MOVED);
    } else if (name == "mouseDragged") {
        return parseMouseEvent(scanner, MOUSE_DRAGGED);
    } else if (name == "keyPressed") {
        return parseKeyEvent(scanner, KEY_PRESSED);
    } else if (name == "keyReleased") {
        return parseKeyEvent(scanner, KEY_RELEASED);
    } else if (name == "keyTyped") {
        return parseKeyEvent(scanner, KEY_TYPED);
    } else if (name == "actionPerformed") {
        return parseActionEvent(scanner, ACTION_PERFORMED);
    } else if (name == "timerTicked") {
        return parseTimerEvent(scanner, TIMER_TICKED);
    } else if (name == "windowClosed") {
        GWindowEvent e = parseWindowEvent(scanner, WINDOW_CLOSED);
        e.getGWindow().close();
        return e;
    } else if (name == "windowResized") {
        return parseWindowEvent(scanner, WINDOW_RESIZED);
    } else if (name == "lastWindowClosed") {
        exit(0);
    } else {
        /* Ignore for now */
    }
    return GEvent();
}

static GEvent parseMouseEvent(TokenScanner& scanner, EventType type) {
    scanner.verifyToken("(");
    std::string id = scanner.getStringValue(scanner.nextToken());
    scanner.verifyToken(",");
    double time = scanDouble(scanner);
    scanner.verifyToken(",");
    int modifiers = scanInt(scanner);
    scanner.verifyToken(",");
    double x = scanDouble(scanner);
    scanner.verifyToken(",");
    double y = scanDouble(scanner);
    scanner.verifyToken(")");
    GMouseEvent e(type, GWindow(windowTable.get(id)), x, y);
    e.setEventTime(time);
    e.setModifiers(modifiers);
    return e;
}

static GEvent parseKeyEvent(TokenScanner& scanner, EventType type) {
    scanner.verifyToken("(");
    std::string id = scanner.getStringValue(scanner.nextToken());
    scanner.verifyToken(",");
    double time = scanDouble(scanner);
    scanner.verifyToken(",");
    int modifiers = scanInt(scanner);
    scanner.verifyToken(",");
    int keyChar = scanInt(scanner);
    scanner.verifyToken(",");
    int keyCode = scanInt(scanner);
    scanner.verifyToken(")");
    GKeyEvent e(type, GWindow(windowTable.get(id)), char(keyChar), keyCode);
    e.setEventTime(time);
    e.setModifiers(modifiers);
    return e;
}

static GEvent parseTimerEvent(TokenScanner& scanner, EventType type) {
    scanner.verifyToken("(");
    std::string id = scanner.getStringValue(scanner.nextToken());
    scanner.verifyToken(",");
    double time = scanDouble(scanner);
    scanner.verifyToken(")");
    GTimerEvent e(type, GTimer(timerTable.get(id)));
    e.setEventTime(time);
    return e;
}

static GEvent parseWindowEvent(TokenScanner& scanner, EventType type) {
    scanner.verifyToken("(");
    std::string id = scanner.getStringValue(scanner.nextToken());
    scanner.verifyToken(",");
    double time = scanDouble(scanner);
    scanner.verifyToken(")");
    GWindowEvent e(type, GWindow(windowTable.get(id)));
    e.setEventTime(time);
    return e;
}

static GEvent parseActionEvent(TokenScanner& scanner, EventType type) {
    scanner.verifyToken("(");
    std::string id = scanner.getStringValue(scanner.nextToken());
    scanner.verifyToken(",");
    std::string action = scanner.getStringValue(scanner.nextToken());
    scanner.verifyToken(",");
    double time = scanDouble(scanner);
    scanner.verifyToken(")");
    GActionEvent e(type, sourceTable.get(id), action);
    e.setEventTime(time);
    return e;
}

/* Console code */

void Platform::clearConsole() {
    putPipe("JBEConsole.clear()");
}

void Platform::setConsoleFont(const std::string& font) {
    std::ostringstream os;
    os << "JBEConsole.setFont(\"" << font << "\")";
    putPipe(os.str());
}

void Platform::setConsoleSize(double width, double height) {
    std::ostringstream os;
    os << "JBEConsole.setSize(" << width << ", " << height << ")";
    putPipe(os.str());
}

static std::string getLineConsole() {
    putPipe("JBEConsole.getLine()");
    return getResult();
}

static void putConsole(const std::string& str) {
    std::ostringstream os;
    os << "JBEConsole.print(";
    writeQuotedString(os, str);
    os << ")";
    putPipe(os.str());
}

static void endLineConsole() {
    putPipe("JBEConsole.println()");
}

static int scanInt(TokenScanner& scanner) {
    std::string token = scanner.nextToken();
    if (token == "-")
        token += scanner.nextToken();
    return stringToInteger(token);
}

static double scanDouble(TokenScanner& scanner) {
    std::string token = scanner.nextToken();
    if (token == "-")
        token += scanner.nextToken();
    return stringToReal(token);
}

static GDimension scanDimension(const std::string& str) {
    TokenScanner scanner(str);
    scanner.scanNumbers();
    scanner.ignoreWhitespace();
    scanner.verifyToken("GDimension");
    scanner.verifyToken("(");
    double width = scanDouble(scanner);
    scanner.verifyToken(",");
    double height = scanDouble(scanner);
    scanner.verifyToken(")");
    return GDimension(width, height);
}

static GRectangle scanRectangle(const std::string& str) {
    TokenScanner scanner(str);
    scanner.scanNumbers();
    scanner.ignoreWhitespace();
    scanner.verifyToken("GRectangle");
    scanner.verifyToken("(");
    double x = scanDouble(scanner);
    scanner.verifyToken(",");
    double y = scanDouble(scanner);
    scanner.verifyToken(",");
    double width = scanDouble(scanner);
    scanner.verifyToken(",");
    double height = scanDouble(scanner);
    scanner.verifyToken(")");
    return GRectangle(x, y, width, height);
}
