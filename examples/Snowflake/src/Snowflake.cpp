/*
 * File: Snowflake.cpp
 * -------------------
 * This program draws a Koch fractal snowflake in the middle of the window.
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
#include "gsnowflake.h"
#include "gwindow.h"
using namespace std;

/* Prototypes */

int main() {
    GWindow gw(600, 400);
    GSnowflake* snowflake = new GSnowflake(300, 4);
    snowflake->setColor("RED");
    snowflake->setFilled(true);
    gw.add(snowflake, gw.getWidth() / 2, gw.getHeight() / 2);
    delete snowflake;
    return 0;
}
