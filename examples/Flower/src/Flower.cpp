/*
 * File: Flower.cpp
 * ----------------
 * This program draws an orange flower by rotating an oval.
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

#include "gobjects.h"
#include "gwindow.h"
using namespace std;

/* Prototypes */

GObject* createPetal(double length, double breadth, double theta);

int main() {
    GWindow gw(600, 400);
    double cx = gw.getWidth() / 2;
    double cy = gw.getHeight() / 2;
    for (int theta = 0; theta < 360; theta += 10) {
        GObject* petal = createPetal(150, 30, theta);
        gw.add(petal, cx, cy);
        delete petal;
    }
    return 0;
}

GObject* createPetal(double length, double breadth, double theta) {
    GOval* oval = new GOval(length, breadth);
    oval->setColor("ORANGE");
    GCompound* petal = new GCompound();
    petal->add(oval, 0, -breadth / 2);
    petal->rotate(theta);
    delete oval;
    return petal;
}
