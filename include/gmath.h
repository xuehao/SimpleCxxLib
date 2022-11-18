/*
 * File: gmath.h
 * -------------
 * This file exports several functions for working with graphical
 * geometry along with the mathematical constants <code>PI</code>
 * and <code>E</code>.
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

#ifndef _gmath_h
#define _gmath_h

#include "gtypes.h"

/*
 * Constant: PI
 * ------------
 * The mathematical constant pi, which is the ratio of the circumference
 * of a circle to its diameter.
 */

extern const double PI;

/*
 * Constant: E
 * -----------
 * The mathematical constant e, which is the base of natural logarithms.
 */

extern const double E;

/*
 * Function: sinDegrees
 * Usage: double sine = sinDegrees(angle);
 * ---------------------------------------
 * Returns the trigonometric sine of <code>angle</code>, which is
 * expressed in degrees.
 */

double sinDegrees(double angle);

/*
 * Function: cosDegrees
 * Usage: double cosine = cosDegrees(angle);
 * -----------------------------------------
 * Returns the trigonometric cosine of <code>angle</code>, which is
 * expressed in degrees.
 */

double cosDegrees(double angle);

/*
 * Function: tanDegrees
 * Usage: double tangent = tanDegrees(angle);
 * ------------------------------------------
 * Returns the trigonometric tangent of <code>angle</code>, which is
 * expressed in degrees.
 */

double tanDegrees(double angle);

/*
 * Function: toDegrees
 * Usage: double degrees = toDegrees(radians);
 * -------------------------------------------
 * Converts an angle from radians to degrees.
 */

double toDegrees(double radians);

/*
 * Function: toRadians
 * Usage: double radians = toRadians(degrees);
 * -------------------------------------------
 * Converts an angle from degrees to radians.
 */

double toRadians(double degrees);

/*
 * Function: vectorDistance
 * Usage: double r = vectorDistance(pt);
 *        double r = vectorDistance(x, y);
 * ---------------------------------------
 * Computes the distance between the origin and the specified point.
 */

double vectorDistance(const GPoint& pt);
double vectorDistance(double x, double y);

/*
 * Function: vectorAngle
 * Usage: double angle = vectorAngle(pt);
 *        double angle = vectorAngle(x, y);
 * ----------------------------------------
 * Returns the angle in degrees from the origin to the specified point.
 * This function takes account of the fact that the graphics coordinate
 * system is flipped in the <i>y</i> direction from the traditional
 * Cartesian plane.
 */

double vectorAngle(const GPoint& pt);
double vectorAngle(double x, double y);

#endif
