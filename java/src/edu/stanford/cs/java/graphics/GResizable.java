/*
 * @(#)GResizable.java   2.03.1 05/26/14
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
 * <code>setSize</code> and <code>setBounds</code> methods.
 */

public interface GResizable {

/**
 * Changes the size of this object to the specified width and height.
 *
 * @param width The new width of the object
 * @param height The new height of the object
 */

   public void setSize(double width, double height);

/**
 * Changes the size of this object as specified by the <code>GDimension</code>
 * object.
 *
 * @param size A <code>GDimension</code> object specifying the new size
 */

   public void setSize(GDimension size);

/**
 * Changes the bounds of this object to the specified values.
 *
 * @param x The new x-coordinate for the object
 * @param y The new y-coordinate for the object
 * @param width The new width of the object
 * @param height The new height of the object
 */

   public void setBounds(double x, double y, double width, double height);

/**
 * Changes the bounds of this object to the values from the specified
 * <code>GRectangle</code>.
 *
 * @param bounds A <code>GRectangle</code> specifying the new bounds
 */

   public void setBounds(GRectangle bounds);

}
