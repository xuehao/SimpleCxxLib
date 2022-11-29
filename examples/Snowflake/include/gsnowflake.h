/*
 * File: gsnowflake.h
 * ------------------
 * This interface exports a new GObject type, which appears as a Koch
 * fractal snowflake.
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

#ifndef _gsnowflake_h
#define _gsnowflake_h

#include <string>
#include "gobjects.h"

class GSnowflake : public GPolygon {
public:
    GSnowflake(double size, int order);
    virtual std::string getType() const;
    virtual std::string toString() const;

private:
    void addFractalEdge(double r, double theta, int order);
};

#endif
