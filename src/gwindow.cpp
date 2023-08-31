/*
 * File: gwindow.cpp
 * -----------------
 * This file implements the GWindow class, passing most calls directly
 * to the appropriate methods in the Platform class, which is implemented
 * separately for each architecture.
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

#include "gwindow.h"
#include <iomanip>
#include <iostream>
#include <sstream>
#include <string>
#include "gmath.h"
#include "gobjects.h"
#include "gtypes.h"
#include "map.h"
#include "platform.h"
#include "vector.h"

/* Constants */

static const int DEFAULT_WIDTH = 640;
static const int DEFAULT_HEIGHT = 480;

/* Private function prototypes */

static void initColorTable();
static std::string canonicalColorName(std::string str);

/*
 * Global variable: colorTable
 * ---------------------------
 * This variable holds the translation table that maps colors into
 * their RGB values.  This color table is shared throughout the
 * application and cannot be manipulated by any clients.  If you
 * need to define color names for application specific colors, you
 * should do so by defining string constants with the appropriate
 * hexadecimal values, as in
 *
 *     const string MAGENTA = "#FF00FF";
 */

static Map<std::string, int> colorTable;

GWindow::GWindow() {
    initGWindow(DEFAULT_WIDTH, DEFAULT_HEIGHT, true);
}

GWindow::GWindow(bool visible) {
    initGWindow(DEFAULT_WIDTH, DEFAULT_HEIGHT, visible);
}

GWindow::GWindow(double width, double height) {
    initGWindow(width, height, true);
}

GWindow::GWindow(double width, double height, bool visible) {
    initGWindow(width, height, visible);
}

void GWindow::initGWindow(double width, double height, bool visible) {
    gwd = new GWindowData();
    gwd->windowWidth = width;
    gwd->windowHeight = height;
    gwd->top = new GCompound();
    getPlatform()->createGWindow(*this, width, height, gwd->top);
    setColor("BLACK");
    setVisible(visible);
    EVENT_FLAG = false;
}

GWindow::~GWindow() {
    if (!EVENT_FLAG) {
        if (gwd != nullptr) {
            delete gwd->top;
        }
        delete gwd;
    }
}

void GWindow::close() {
    getPlatform()->close(*this);
    getPlatform()->deleteGWindow(*this);
}

void GWindow::requestFocus() {
    getPlatform()->requestFocus(*this);
}

void GWindow::clear() {
    gwd->top->removeAll();
    getPlatform()->clear(*this);
}

void GWindow::repaint() {
    getPlatform()->repaint(*this);
}

void GWindow::setVisible(bool flag) {
    gwd->visible = flag;
    getPlatform()->setVisible(*this, flag);
}

bool GWindow::isVisible() {
    return gwd->visible;
}

void GWindow::drawLine(const GPoint& p0, const GPoint& p1) {
    drawLine(p0.getX(), p0.getY(), p1.getX(), p1.getY());
}

void GWindow::drawLine(double x0, double y0, double x1, double y1) {
    GLine line(x0, y0, x1, y1);
    line.setColor(gwd->color);
    draw(line);
}

GPoint GWindow::drawPolarLine(const GPoint& p0, double r, double theta) {
    return drawPolarLine(p0.getX(), p0.getY(), r, theta);
}

GPoint GWindow::drawPolarLine(double x0, double y0, double r, double theta) {
    double x1 = x0 + r * cosDegrees(theta);
    double y1 = y0 - r * sinDegrees(theta);
    drawLine(x0, y0, x1, y1);
    return GPoint(x1, y1);
}

void GWindow::drawRect(const GRectangle& bounds) {
    drawRect(bounds.getX(), bounds.getY(), bounds.getWidth(), bounds.getHeight());
}

void GWindow::drawRect(double x, double y, double width, double height) {
    GRect rect(x, y, width, height);
    rect.setColor(gwd->color);
    draw(rect);
}

void GWindow::fillRect(const GRectangle& bounds) {
    fillRect(bounds.getX(), bounds.getY(), bounds.getWidth(), bounds.getHeight());
}

void GWindow::fillRect(double x, double y, double width, double height) {
    GRect rect(x, y, width, height);
    rect.setColor(gwd->color);
    rect.setFilled(true);
    draw(rect);
}

void GWindow::drawOval(const GRectangle& bounds) {
    drawOval(bounds.getX(), bounds.getY(), bounds.getWidth(), bounds.getHeight());
}

void GWindow::drawOval(double x, double y, double width, double height) {
    GOval oval(x, y, width, height);
    oval.setColor(gwd->color);
    draw(oval);
}

void GWindow::fillOval(const GRectangle& bounds) {
    fillOval(bounds.getX(), bounds.getY(), bounds.getWidth(), bounds.getHeight());
}

void GWindow::fillOval(double x, double y, double width, double height) {
    GOval oval(x, y, width, height);
    oval.setColor(gwd->color);
    oval.setFilled(true);
    draw(oval);
}

void GWindow::setColor(std::string color) {
    gwd->color = color;
}

void GWindow::setColor(int rgb) {
    gwd->color = convertRGBToColor(rgb);
}

std::string GWindow::getColor() {
    return convertRGBToColor(convertColorToRGB(gwd->color));
}

double GWindow::getWidth() {
    return gwd->windowWidth;
}

double GWindow::getHeight() {
    return gwd->windowHeight;
}

void GWindow::setWindowTitle(std::string title) {
    gwd->windowTitle = title;
    getPlatform()->setWindowTitle(*this, title);
}

std::string GWindow::getWindowTitle() {
    return gwd->windowTitle;
}

void GWindow::draw(const GObject& gobj) {
    draw(&gobj);
}

void GWindow::draw(GObject* gobj) {
    getPlatform()->draw(*this, gobj);
}

void GWindow::draw(const GObject* gobj) {
    getPlatform()->draw(*this, gobj);
}

void GWindow::draw(GObject& gobj, double x, double y) {
    draw(&gobj, x, y);
}

void GWindow::draw(GObject* gobj, double x, double y) {
    gobj->setLocation(x, y);
    getPlatform()->draw(*this, gobj);
}

void GWindow::add(GObject* gobj) {
    gwd->top->add(gobj);
}

void GWindow::add(GObject* gobj, double x, double y) {
    gobj->setLocation(x, y);
    add(gobj);
}

void GWindow::addToRegion(GInteractor* gobj, std::string region) {
    getPlatform()->addToRegion(*this, (GObject*)gobj, region);
}

void GWindow::addToRegion(GLabel* gobj, std::string region) {
    getPlatform()->addToRegion(*this, (GObject*)gobj, region);
}

void GWindow::removeFromRegion(GInteractor* gobj, std::string region) {
    getPlatform()->removeFromRegion(*this, (GObject*)gobj, region);
}

void GWindow::removeFromRegion(GLabel* gobj, std::string region) {
    getPlatform()->removeFromRegion(*this, (GObject*)gobj, region);
}

void GWindow::remove(GObject* gobj) {
    gwd->top->remove(gobj);
}

GObject* GWindow::getGObjectAt(double x, double y) {
    int n = gwd->top->getElementCount();
    for (int i = n - 1; i >= 0; i--) {
        GObject* gobj = gwd->top->getElement(i);
        if (gobj->contains(x, y))
            return gobj;
    }
    return nullptr;
}

void GWindow::setRegionAlignment(std::string region, std::string align) {
    getPlatform()->setRegionAlignment(*this, region, align);
}

bool GWindow::operator==(GWindow w2) {
    return gwd == w2.gwd;
}

bool GWindow::operator!=(GWindow w2) {
    return gwd != w2.gwd;
}

GWindow::GWindow(GWindowData* gwd) {
    this->gwd = gwd;
    EVENT_FLAG = true;
}

void pause(double milliseconds) {
    getPlatform()->pause(milliseconds);
}

double getScreenWidth() {
    return getPlatform()->getScreenWidth();
}

double getScreenHeight() {
    return getPlatform()->getScreenHeight();
}

int convertColorToRGB(std::string colorName) {
    if (colorName[0] == '#') {
        unsigned aa = 0xFF;
        if (colorName.length() == 8)
            aa = 0;
        std::istringstream is(colorName.substr(1) + "@");
        unsigned rgb;
        char terminator = '\0';
        is >> std::hex >> rgb >> terminator;
        if (terminator != '@')
            error("setColor: Illegal color - " + colorName);
        rgb |= aa << 24;
        return *((int*)&rgb);
    }
    std::string name = canonicalColorName(colorName);
    if (colorTable.size() == 0)
        initColorTable();
    if (!colorTable.containsKey(name)) {
        error("setColor: Undefined color - " + colorName);
    }
    return colorTable[name];
}

std::string convertRGBToColor(int rgb) {
    std::ostringstream os;
    os << std::hex << std::setfill('0') << std::uppercase << "#";
    int aa = (rgb >> 24 & 0xFF);
    if (aa != 0xFF)
        os << std::setw(2) << aa;
    os << std::setw(6) << (rgb & 0xFFFFFF);
    return os.str();
}

void exitGraphics() {
    getPlatform()->exitGraphics();
    exit(0);
}

static void initColorTable() {
    colorTable["black"] = 0xFF000000;
    colorTable["darkgray"] = 0xFF595959;
    colorTable["gray"] = 0xFF999999;
    colorTable["lightgray"] = 0xFFBFBFBF;
    colorTable["white"] = 0xFFFFFFFF;
    colorTable["red"] = 0xFFFF0000;
    colorTable["yellow"] = 0xFFFFFF00;
    colorTable["green"] = 0xFF00FF00;
    colorTable["cyan"] = 0xFF00FFFF;
    colorTable["blue"] = 0xFF0000FF;
    colorTable["magenta"] = 0xFFFF00FF;
    colorTable["orange"] = 0xFFFFC800;
    colorTable["pink"] = 0xFFFFAFAF;
}

static std::string canonicalColorName(std::string str) {
    std::string result = "";
    int nChars = str.length();
    for (int i = 0; i < nChars; i++) {
        char ch = str[i];
        if (!isspace(ch) && ch != '_')
            result += tolower(ch);
    }
    return result;
}
