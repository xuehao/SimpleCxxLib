/*
 * @(#)GScalable.java   2.03.1 05/26/14
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

package edu.stanford.cs.java.graphics;

/**
 * Specifies the characteristics of a graphical object that supports the
 * <code>scale</code> method.
 */

public interface GScalable {

/**
 * Scales the object on the screen by the scale factors <code>sx</code>
 * and <code>sy</code>.
 *
 * @param sx The factor used to scale all coordinates in the x direction
 * @param sy The factor used to scale all coordinates in the y direction
 */

   public void scale(double sx, double sy);

/**
 * Scales the object on the screen by the scale factor <code>sf</code>,
 * which applies in both dimensions.
 *
 * @param sf The factor used to scale all coordinates in both dimensions
 */

   public void scale(double sf);

}
