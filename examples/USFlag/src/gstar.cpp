/*
 * File: gstar.cpp
 * ---------------
 * This file implements the GStar class.
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

#include "gstar.h"
#include <iostream>
#include <sstream>
#include <string>
#include "gmath.h"
#include "gobjects.h"
using namespace std;

GStar::GStar(double size) {
    this->size = size;
    double dx = size / 2;
    double dy = dx * tanDegrees(18);
    double edge = size / 2 - dy * tanDegrees(36);
    addVertex(-dx, -dy);
    int angle = 0;
    for (int i = 0; i < 5; i++) {
        addPolarEdge(edge, angle);
        addPolarEdge(edge, angle + 72);
        angle -= 72;
    }
}

string GStar::getType() const {
    return "GStar";
}

string GStar::toString() const {
    ostringstream oss;
    oss << "GStar(" << size << ")";
    return oss.str();
}
