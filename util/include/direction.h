/*
 * File: direction.h
 * -----------------
 * This file exports an enumerated type called <code>Direction</code>
 * whose elements are the four compass points: <code>NORTH</code>,
 * <code>EAST</code>, <code>SOUTH</code>, and <code>WEST</code>.
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

#ifndef _direction_h
#define _direction_h

#include <iostream>
#include <string>

/*
 * Type: Direction
 * ---------------
 * This enumerated type is used to represent the four compass directions.
 */

enum Direction { NORTH, EAST, SOUTH, WEST };

/*
 * Function: leftFrom
 * Usage: Direction newdir = leftFrom(dir);
 * ----------------------------------------
 * Returns the direction that is to the left of the argument.
 */

Direction leftFrom(Direction dir);

/*
 * Function: rightFrom
 * Usage: Direction newdir = rightFrom(dir);
 * -----------------------------------------
 * Returns the direction that is to the right of the argument.
 */

Direction rightFrom(Direction dir);

/*
 * Function: opposite
 * Usage: Direction newdir = opposite(dir);
 * ----------------------------------------
 * Returns the direction that is opposite to the argument.
 */

Direction opposite(Direction dir);

/*
 * Function: directionToString
 * Usage: string str = directionToString(dir);
 * -------------------------------------------
 * Returns the name of the direction as a string.
 */

std::string directionToString(Direction dir);

/*
 * Operator: <<
 * Usage: os << dir;
 * -----------------
 * Overloads the <code>&lt;&lt;</code> operator so that it is able
 * to display <code>Direction</code> values.
 */

std::ostream& operator<<(std::ostream& os, const Direction& dir);

/*
 * Operator: >>
 * Usage: is >> dir;
 * -----------------
 * Overloads the <code>&gt;&gt;</code> operator so that it is able
 * to read <code>Direction</code> values.
 */

std::istream& operator>>(std::istream& os, Direction& dir);

/*
 * Operator: ++
 * Usage: dir++
 * ------------
 * Overloads the suffix version of the <code>++</code> operator to
 * work with <code>Direction</code> values.  The sole purpose of this
 * definition is to support the idiom
 *
 *<pre>
 *    for (Direction dir = NORTH; dir &lt;= WEST; dir++) ...
 *</pre>
 */

Direction operator++(Direction& dir, int);

#endif
