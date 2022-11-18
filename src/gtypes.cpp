/*
 * File: gtypes.cpp
 * ----------------
 * This file implements the classes in the gtypes.h interface.
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

#include "gtypes.h"
#include <cmath>
#include <string>
#include "error.h"
#include "strlib.h"

static const double PI = 3.14159265358979;
static const int HASH_MASK = int(unsigned(-1) >> 1);

/*
 * Implementation notes: GPoint class
 * ----------------------------------
 * The GPoint class itself is entirely straightforward.  The relational
 * operators compare the x components first, followed by the y component.
 * The hashCode function computes the exclusive-or of the individual words.
 */

GPoint::GPoint() {
    x = 0;
    y = 0;
}

GPoint::GPoint(double x, double y) {
    this->x = x;
    this->y = y;
}

double GPoint::getX() const {
    return x;
}

double GPoint::getY() const {
    return y;
}

std::string GPoint::toString() const {
    return "(" + realToString(x) + ", " + realToString(y) + ")";
}

std::ostream& operator<<(std::ostream& os, const GPoint& pt) {
    return os << pt.toString();
}

bool operator==(const GPoint& p1, const GPoint& p2) {
    return p1.x == p2.x && p1.y == p2.y;
}

bool operator!=(const GPoint& p1, const GPoint& p2) {
    return !(p1 == p2);
}

int hashCode(const GPoint& pt) {
    int hash = 0;
    for (int i = 0; i < sizeof(double) / sizeof(int); i++) {
        hash ^= ((int*)&pt.x)[i] ^ ((int*)&pt.y)[i];
    }
    return HASH_MASK & hash;
}

/*
 * Implementation notes: GDimension class
 * --------------------------------------
 * The GDimension class itself is entirely straightforward.  The
 * relational operators compare the width first, followed by the height.
 * The hashCode function computes the exclusive-or of the individual words.
 */

GDimension::GDimension() {
    width = 0;
    height = 0;
}

GDimension::GDimension(double width, double height) {
    this->width = width;
    this->height = height;
}

double GDimension::getWidth() const {
    return width;
}

double GDimension::getHeight() const {
    return height;
}

std::string GDimension::toString() const {
    return "(" + realToString(width) + ", " + realToString(height) + ")";
}

std::ostream& operator<<(std::ostream& os, const GDimension& dim) {
    return os << dim.toString();
}

bool operator==(const GDimension& d1, const GDimension& d2) {
    return d1.width == d2.width && d1.height == d2.height;
}

bool operator!=(const GDimension& d1, const GDimension& d2) {
    return !(d1 == d2);
}

int hashCode(const GDimension& dim) {
    int hash = 0;
    for (int i = 0; i < sizeof(double) / sizeof(int); i++) {
        hash ^= ((int*)&dim.width)[i] ^ ((int*)&dim.height)[i];
    }
    return HASH_MASK & hash;
}

/*
 * Implementation notes: GRectangle class
 * --------------------------------------
 * The GRectangle class itself is entirely straightforward.  The
 * relational operators compare the components in the following order:
 * x, y, width, height.  The hashCode function computes the exclusive-or
 * of the individual words.
 */

GRectangle::GRectangle() {
    x = 0;
    y = 0;
    width = 0;
    height = 0;
}

GRectangle::GRectangle(double x, double y, double width, double height) {
    this->x = x;
    this->y = y;
    this->width = width;
    this->height = height;
}

double GRectangle::getX() const {
    return x;
}

double GRectangle::getY() const {
    return y;
}

double GRectangle::getWidth() const {
    return width;
}

double GRectangle::getHeight() const {
    return height;
}

bool GRectangle::isEmpty() const {
    return width <= 0 || height <= 0;
}

bool GRectangle::contains(double x, double y) const {
    return x >= this->x && y >= this->y && x < this->x + width && y < this->y + height;
}

bool GRectangle::contains(GPoint pt) const {
    return contains(pt.getX(), pt.getY());
}

std::string GRectangle::toString() const {
    return "(" + realToString(x) + ", " + realToString(y) + ", " + realToString(width) + ", " +
           realToString(height) + ")";
}

std::ostream& operator<<(std::ostream& os, const GRectangle& rect) {
    return os << rect.toString();
}

bool operator==(const GRectangle& r1, const GRectangle& r2) {
    return r1.x == r2.x && r1.y == r2.y && r1.width == r2.width && r1.height == r2.height;
}

bool operator!=(const GRectangle& r1, const GRectangle& r2) {
    return !(r1 == r2);
}

int hashCode(const GRectangle& r) {
    int hash = 0;
    for (int i = 0; i < sizeof(double) / sizeof(int); i++) {
        hash ^= ((int*)&r.x)[i] ^ ((int*)&r.y)[i];
        hash ^= ((int*)&r.width)[i] ^ ((int*)&r.height)[i];
    }
    return HASH_MASK & hash;
}
