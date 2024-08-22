/*
 * @(#)GFillable.java   2.03.1 05/26/14
 */

/*************************************************************************/
/* Stanford Portable Library (adapted from the ACM graphics library)     */
/* Copyright (C) 2014 by Eric Roberts <eroberts@cs.stanford.edu>         */
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

package graphics;

import java.awt.Color;

/**
 * Specifies the characteristics of a graphical object that supports filling.
 */

public interface GFillable {

/**
 * Sets whether this object is filled.
 *
 * @param fill <code>true</code> if the object should be filled,
 *             <code>false</code> for an outline
 */

   public void setFilled(boolean fill);

/**
 * Returns whether this object is filled.
 *
 * @return The color used to display the object
 */

   public boolean isFilled();

/**
 * Sets the color used to display the filled region of this object.
 *
 * @param color The color used to display the filled region of this object
 */

   public void setFillColor(Color color);

/**
 * Returns the color used to display the filled region of this object.  If
 * none has been set, <code>getFillColor</code> returns the color of the
 * object.
 *
 * @return The color used to display the filled region of this object
 */

   public Color getFillColor();

}
