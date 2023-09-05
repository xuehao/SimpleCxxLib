/*
 * File: DrawLines.cpp
 * -------------------
 * This program allows users to create lines on the graphics
 * canvas by clicking and dragging with the mouse.
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
    GLine* line = nullptr;
    while (true) {
        GMouseEvent e = waitForEvent(MOUSE_EVENT);
        if (e.getEventType() == MOUSE_PRESSED) {
            line = new GLine(e.getX(), e.getY(), e.getX(), e.getY());
            gw.add(line);
        } else if (e.getEventType() == MOUSE_DRAGGED) {
            line->setEndPoint(e.getX(), e.getY());
        } else if (e.getEventType() == MOUSE_RELEASED) {
            delete line;
            line = nullptr;
        }
    }
    return 0;
}
