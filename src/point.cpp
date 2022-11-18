/*
 * File: point.cpp
 * ---------------
 * This file implements the point.h interface.
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

#include "point.h"
#include <string>
#include "strlib.h"

Point::Point() {
    x = 0;
    y = 0;
}

Point::Point(int x, int y) {
    this->x = x;
    this->y = y;
}

int Point::getX() const {
    return x;
}

int Point::getY() const {
    return y;
}

std::string Point::toString() const {
    return "(" + integerToString(x) + "," + integerToString(y) + ")";
}

bool Point::operator==(const Point& p2) const {
    return (x == p2.x) && (y == p2.y);
}

bool Point::operator!=(const Point& p2) const {
    return (x != p2.x) || (y != p2.y);
}

std::ostream& operator<<(std::ostream& os, const Point& pt) {
    return os << pt.toString();
}
