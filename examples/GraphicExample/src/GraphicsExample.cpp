/*
 * File: GraphicsExample.cpp
 * -------------------------
 * This program illustrates the use of graphics using the GWindow class.
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

#include <fstream>
#include <iostream>
#include "gwindow.h"
using namespace std;

/* Prototypes */

void drawDiamond(GWindow& gw);
void drawRectangleAndOval(GWindow& gw);

/* Main program */

int main() {
    GWindow gw(600, 400);
    drawDiamond(gw);
    drawRectangleAndOval(gw);
    gw.repaint();
    return 0;
}

/*
 * Function: drawDiamond
 * Usage: drawDiamond(gw);
 * -----------------------
 * Draws a diamond connecting the midpoints of the window edges.
 */

void drawDiamond(GWindow& gw) {
    double width = gw.getWidth();
    double height = gw.getHeight();
    gw.drawLine(0, height / 2, width / 2, 0);
    gw.drawLine(width / 2, 0, width, height / 2);
    gw.drawLine(width, height / 2, width / 2, height);
    gw.drawLine(width / 2, height, 0, height / 2);
}

/*
 * Function: drawRectangleAndOval
 * Usage: drawRectangleAndOval(gw);
 * --------------------------------
 * Draws a blue rectangle and a gray oval inscribed in the diamond.
 */

void drawRectangleAndOval(GWindow& gw) {
    double width = gw.getWidth();
    double height = gw.getHeight();
    gw.setColor("BLUE");
    gw.fillRect(width / 4, height / 4, width / 2, height / 2);
    gw.setColor("GRAY");
    gw.fillOval(width / 4, height / 4, width / 2, height / 2);
}
