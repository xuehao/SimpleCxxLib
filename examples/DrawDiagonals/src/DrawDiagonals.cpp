/*
 * File: DrawDiagonals.cpp
 * -----------------------
 * This program draws the main diagonals on the graphics window.
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

#include "gevents.h"
#include "gobjects.h"
#include "gwindow.h"
using namespace std;

int main() {
    GWindow gw(600, 400);
    double width = gw.getWidth();
    double height = gw.getHeight();

    GLine* line = new GLine(0, 0, width, height);
    gw.draw(line);
    delete line;

    line = new GLine(0, height, width, 0);
    gw.draw(line);
    delete line;
    
    return 0;
}
