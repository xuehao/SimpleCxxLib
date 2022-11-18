/*
 * @(#)GPoint.java   2.03.1 05/26/14
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

import java.awt.Point;
import java.io.Serializable;

/**
 * This class is a double-precision version of the <code>Point</code> class
 * in <code>java.awt</code>.
 */

public class GPoint implements Serializable {

/**
 * Constructs a new <code>GPoint</code> at the origin (0, 0).
 *
 */

   public GPoint() {
      this(0, 0);
   }

/**
 * Constructs a new <code>GPoint</code> with the specified coordinates.
 *
 * @param x The x-coordinate of the point
 * @param y The y-coordinate of the point
 */

   public GPoint(double x, double y) {
      xc = x;
      yc = y;
   }

/**
 * Constructs a new <code>GPoint</code> from an existing one.
 *
 * @param p The original point
 */

   public GPoint(GPoint p) {
      this(p.xc, p.yc);
   }

/**
 * Constructs a new <code>GPoint</code> from an existing AWT
 * <code>Point</code>.
 *
 * @param p An AWT <code>Point</code>
 */

   public GPoint(Point p) {
      this(p.x, p.y);
   }

/**
 * Returns the x coordinate of this <code>GPoint</code>.
 *
 * @return The x coordinate of this <code>GPoint</code>
 */

   public double getX() {
      return xc;
   }

/**
 * Returns the y coordinate of this <code>GPoint</code>.
 *
 * @return The y coordinate of this <code>GPoint</code>
 */

   public double getY() {
      return yc;
   }

/**
 * Sets the location of the <code>GPoint</code> to the specified
 * <code>x</code> and <code>y</code> values.
 *
 * @param x The new x-coordinate for the point
 * @param y The new y-coordinate for the point
 */

   public void setLocation(double x, double y) {
      xc = x;
      yc = y;
   }

/**
 * Sets the location of the <code>GPoint</code> to that of an existing one.
 *
 * @param p An existing <code>GPoint</code> specifying the new location
 */

   public void setLocation(GPoint p) {
      setLocation(p.xc, p.yc);
   }

/**
 * Returns a new <code>GPoint</code> whose coordinates are the same as
 * this one.
 *
 * @return A new point with the same coordinates
 */

   public GPoint getLocation() {
      return new GPoint(xc, yc);
   }

/**
 * Adjusts the coordinates of a point by the specified <code>dx</code> and
 * <code>dy</code> offsets.
 *
 * @param dx The change in the x direction (positive is rightward)
 * @param dy The change in the y direction (positive is downward)
 */

   public void translate(double dx, double dy) {
      xc += dx;
      yc += dy;
   }

/**
 * Converts this <code>GPoint</code> to the nearest integer-based
 * <code>Point</code>.
 *
 * @return The closest integer-based <code>Point</code>
 */

   public Point toPoint() {
      return new Point((int) Math.round(xc), (int) Math.round(yc));
   }

/**
 * Returns an integer hash code for the point.  The hash code for a
 * <code>GPoint</code> is constructed from the hash codes from the
 * <code>float</code> values of the coordinates, which are the ones used
 * in the <code>equals</code> method.
 *
 * @return The hash code for this pt
 * @noshow
 */

   public int hashCode() {
      return new Float((float) xc).hashCode()
               ^ (37 * new Float((float) yc).hashCode());
   }

/**
 * Tests whether two <code>GPoint</code> objects are equal.
 * Because floating-point values are inexact, this method checks for
 * equality by comparing the <code>float</code> values (rather than the
 * <code>double</code> values) of the coordinates.
 *
 * @param obj Any object
 * @return <code>true</code> if the <code>obj</code> is a <code>GPoint</code>
 *         equal to this one, and <code>false</code> otherwise
 * @noshow
 */

   public boolean equals(Object obj) {
      if (!(obj instanceof GPoint)) return false;
      GPoint pt = (GPoint) obj;
      return ((float) xc == (float) pt.xc) && ((float) yc == (float) pt.yc);
   }

/**
 * Converts this <code>GPoint</code> to its string representation.
 *
 * @return A string representation of this point
 * @noshow
 */

   public String toString() {
      return "(" + (float) xc + ", " + (float) yc + ")";
   }

/* Private instance variables */

   private double xc;
   private double yc;

/* Serial version UID */
/**
 * The serialization code for this class.  This value should be incremented
 * whenever you change the structure of this class in an incompatible way,
 * typically by adding a new instance variable.
 */

   static final long serialVersionUID = 21L;

}
