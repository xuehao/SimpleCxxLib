/*
 * File: USFlag.cpp
 * ----------------
 * This program draws a US flag that fills the window.
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

#include <cmath>
#include <string>

#include "gobjects.h"
#include "gstar.h"
#include "gwindow.h"
using namespace std;

/* Constants */

const double FLAG_WIDTH = 740;
const double FLAG_HEIGHT = 400;
const double FIELD_FRACTION = 0.40;
const double STAR_FRACTION = 0.40;

/* Prototypes */

static void drawStripes(GWindow& gw);
static void drawField(GWindow& gw);
static void drawObama(GWindow& gw);

int main() {
    GWindow gw(FLAG_WIDTH, FLAG_HEIGHT);
    drawStripes(gw);
    drawField(gw);
    waitForClick();
    drawObama(gw);
    return 0;
}

/* Draw the stripes */

static void drawStripes(GWindow& gw) {
    double width = gw.getWidth();
    double height = gw.getHeight();
    double stripeHeight = height / 13;
    for (int i = 12; i >= 0; i--) {
        GRect stripe(0, i * stripeHeight, width, stripeHeight);
        stripe.setFilled(true);
        stripe.setColor((i % 2 == 0) ? "RED" : "WHITE");
        gw.draw(stripe);
    }
}

/* Draw the star field */

static void drawField(GWindow& gw) {
    double width = gw.getWidth();
    double height = gw.getHeight();
    double fieldWidth = FIELD_FRACTION * width;
    double fieldHeight = height * 7 / 13;
    GRect field(0, 0, fieldWidth, fieldHeight);
    field.setColor("BLUE");
    field.setFilled(true);
    gw.draw(field);
    double dx = fieldWidth / 6;
    double dy = fieldHeight / 5;
    double starSize = STAR_FRACTION * min(dx, dy);
    GStar star(starSize);
    star.setColor("WHITE");
    star.setFilled(true);
    for (int row = 0; row < 5; row++) {
        double y = (row + 0.5) * dy;
        for (int col = 0; col < 6; col++) {
            double x = (col + 0.5) * dx;
            gw.draw(star, x, y);
        }
    }
    for (int row = 0; row < 4; row++) {
        double y = (row + 1) * dy;
        for (int col = 0; col < 5; col++) {
            double x = (col + 1) * dx;
            gw.draw(star, x, y);
        }
    }
}

/* Draw a picture of President Obama */

static void drawObama(GWindow& gw) {
    double width = gw.getWidth();
    double height = gw.getHeight();
    double fieldWidth = FIELD_FRACTION * width;
    GImage obama("Obama.png");
    double x = fieldWidth + (width - fieldWidth - obama.getWidth()) / 2;
    double y = (height - obama.getHeight()) / 2;
    gw.draw(obama, x, y);
}
