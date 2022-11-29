/*
 * File: gstoplight.cpp
 * --------------------
 * This file implements the GStoplight class.
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

#include "gstoplight.h"
#include <string>
#include "error.h"
#include "gobjects.h"
using namespace std;

/* Constants */

const double FRAME_WIDTH = 50;
const double FRAME_HEIGHT = 100;
const double LAMP_RADIUS = 10;

GStoplight::GStoplight() {
    GRect* frame = new GRect(FRAME_WIDTH, FRAME_HEIGHT);
    frame->setFilled(true);
    frame->setFillColor("GRAY");
    add(frame, -FRAME_WIDTH / 2, -FRAME_HEIGHT / 2);
    double dy = FRAME_HEIGHT / 4 + LAMP_RADIUS / 2;
    redLamp = createFilledCircle(0, -dy, LAMP_RADIUS);
    add(redLamp);
    yellowLamp = createFilledCircle(0, 0, LAMP_RADIUS);
    add(yellowLamp);
    greenLamp = createFilledCircle(0, dy, LAMP_RADIUS);
    add(greenLamp);
    setState("GREEN");
}

void GStoplight::setState(string color) {
    if (color == "RED") {
        redLamp->setFillColor("RED");
        yellowLamp->setFillColor("DARK_GRAY");
        greenLamp->setFillColor("DARK_GRAY");
    } else if (color == "YELLOW") {
        redLamp->setFillColor("DARK_GRAY");
        yellowLamp->setFillColor("YELLOW");
        greenLamp->setFillColor("DARK_GRAY");
    } else if (color == "GREEN") {
        redLamp->setFillColor("DARK_GRAY");
        yellowLamp->setFillColor("DARK_GRAY");
        greenLamp->setFillColor("GREEN");
    } else {
        error("Illegal color string " + color);
    }
    state = color;
}

string GStoplight::getState() {
    return state;
}

GOval* GStoplight::createFilledCircle(double x, double y, double r) {
    GOval* circle = new GOval(x - r, y - r, 2 * r, 2 * r);
    circle->setFilled(true);
    return circle;
}
