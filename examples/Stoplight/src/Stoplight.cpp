/*
 * File: Stoplight.cpp
 * -------------------
 * This program draws a stoplight and three buttons for setting it.
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

#include <string>
#include "gevents.h"
#include "ginteractors.h"
#include "gobjects.h"
#include "gstoplight.h"
#include "gwindow.h"
#include "strlib.h"
using namespace std;

int main() {
    GWindow gw;
    GStoplight* stoplight = new GStoplight();
    gw.addToRegion(new GButton("Green"), "SOUTH");
    gw.addToRegion(new GButton("Yellow"), "SOUTH");
    gw.addToRegion(new GButton("Red"), "SOUTH");
    double x = (gw.getWidth() - stoplight->getWidth()) / 2;
    double y = (gw.getHeight() - stoplight->getHeight()) / 2;
    gw.add(stoplight, x, y);
    while (true) {
        GActionEvent e = waitForEvent(ACTION_EVENT);
        stoplight->setState(toUpperCase(e.getActionCommand()));
    }
}
