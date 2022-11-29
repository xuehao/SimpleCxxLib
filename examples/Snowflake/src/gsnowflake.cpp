/*
 * File: gsnowflake.cpp
 * --------------------
 * This file implements the GSnowflake class.
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

#include "gsnowflake.h"
#include <cmath>
#include "gobjects.h"
using namespace std;

GSnowflake::GSnowflake(double size, int order) {
    addVertex(-size / 2, -size / (2 * sqrt(3)));
    addFractalEdge(size, 0, order);
    addFractalEdge(size, -120, order);
    addFractalEdge(size, +120, order);
}

void GSnowflake::addFractalEdge(double r, double theta, int order) {
    if (order == 0) {
        addPolarEdge(r, theta);
    } else {
        addFractalEdge(r / 3, theta, order - 1);
        addFractalEdge(r / 3, theta + 60, order - 1);
        addFractalEdge(r / 3, theta - 60, order - 1);
        addFractalEdge(r / 3, theta, order - 1);
    }
}

string GSnowflake::getType() const {
    return "GSnowflake";
}

string GSnowflake::toString() const {
    ostringstream oss;
    oss << "GSnowflake(...)";
    return oss.str();
}
