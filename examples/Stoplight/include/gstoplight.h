/*
 * File: gstoplight.h
 * ------------------
 * This file defines the GStoplight class.
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

#ifndef _gstoplight_h
#define _gstoplight_h

#include <string>

#include "gobjects.h"

class GStoplight : public GCompound {

public:
    GStoplight();
    std::string getState();
    void setState(std::string color);

    /* Private instance variables */

    std::string state;
    GOval* redLamp;
    GOval* yellowLamp;
    GOval* greenLamp;

    GOval* createFilledCircle(double x, double y, double r);
};

#endif
