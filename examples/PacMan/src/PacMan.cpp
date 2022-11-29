/*
 * File: PacMan.cpp
 * ----------------
 * This program creates a 270-degree filled arc that resembles the
 * character in the PacMan game.  Clicking the mouse causes the
 * PacMan character to move across the screen opening and shutting
 * its jaws.
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
#include "gobjects.h"
#include "gwindow.h"
using namespace std;

/* Constants */

const double PACMAN_SIZE = 60;
const double PAUSE_TIME = 20;
const double DELTA_X = 2;
const int DELTA_THETA = 5;

int main() {
    GWindow gw(600, 400);
    GArc* pacman = new GArc(PACMAN_SIZE, PACMAN_SIZE, 45, 270);
    pacman->setFilled(true);
    pacman->setFillColor("YELLOW");
    gw.add(pacman, 0, (gw.getHeight() - PACMAN_SIZE) / 2);
    waitForClick();
    int angle = 45;
    int sign = -1;
    double limit = gw.getWidth() - PACMAN_SIZE;
    while (pacman->getX() < limit) {
        pacman->move(DELTA_X, 0);
        angle += sign * DELTA_THETA;
        if (angle == 0 || angle == 45)
            sign = -sign;
        pacman->setStartAngle(angle);
        pacman->setSweepAngle(360 - 2 * angle);
        pause(PAUSE_TIME);
    }
    delete pacman;
    return 0;
}
