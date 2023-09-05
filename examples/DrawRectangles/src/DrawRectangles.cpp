/*
 * File: DrawRectangles.cpp
 * ------------------------
 * This program allows users to create rectangles on the canvas
 * by clicking and dragging with the mouse.  This version of the
 * program also allows the user to change the color of a rectangle
 * by typing the first letter of the color name, or a space for black.
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

#include "gevents.h"
#include "gobjects.h"
#include "gwindow.h"
using namespace std;

int main() {
    GWindow gw(600, 400);
    GRect* rect = NULL;
    bool dragging = false;
    double startX = 0.0;
    double startY = 0.0;
    while (true) {
        GEvent e = waitForEvent();
        if (e.getEventClass() == MOUSE_EVENT) {
            GMouseEvent me = (GMouseEvent)e;
            if (me.getEventType() == MOUSE_PRESSED) {
                startX = me.getX();
                startY = me.getY();
                rect = (GRect*)gw.getGObjectAt(startX, startY);
                dragging = (rect != NULL);
                if (!dragging) {
                    rect = new GRect(startX, startY, 0, 0);
                    rect->setFilled(true);
                    gw.add(rect);
                }
            } else if (me.getEventType() == MOUSE_DRAGGED) {
                double x = me.getX();
                double y = me.getY();
                if (dragging) {
                    rect->move(x - startX, y - startY);
                    startX = x;
                    startY = y;
                } else {
                    x = min(x, startX);
                    y = min(y, startY);
                    double width = abs(me.getX() - startX);
                    double height = abs(me.getY() - startY);
                    rect->setBounds(x, y, width, height);
                }
            } else if (me.getEventType() == MOUSE_CLICKED) {
                if (rect != NULL)
                    rect->sendToFront();
            }
        } else if (e.getEventClass() == KEY_EVENT) {
            if (rect != NULL) {
                string color = "BLACK";
                switch (((GKeyEvent)e).getKeyChar()) {
                    case 'b':
                        color = "BLUE";
                        break;
                    case 'c':
                        color = "CYAN";
                        break;
                    case 'g':
                        color = "GREEN";
                        break;
                    case 'm':
                        color = "MAGENTA";
                        break;
                    case 'o':
                        color = "ORANGE";
                        break;
                    case 'r':
                        color = "RED";
                        break;
                    case 'w':
                        color = "WHITE";
                        break;
                    case 'y':
                        color = "YELLOW";
                        break;
                }
                rect->setColor(color);
            }
        }
    }
}
