/*
 * @(#)GDimension.java   2.03.1 05/26/14
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

import java.awt.Dimension;
import java.io.Serializable;

/**
 * This class is a double-precision version of the <code>Dimension</code>
 * class in <code>java.awt</code>.
 */

public class GDimension implements Serializable {

/**
 * Constructs a new dimension object with zero values for width and height.
 *
 */

   public GDimension() {
      this(0, 0);
   }

/**
 * Constructs a new dimension object with the specified components.
 *
 * @param width The width of the dimension object
 * @param height The height of the dimension object
 */

   public GDimension(double width, double height) {
      this.width = width;
      this.height = height;
   }

/**
 * Constructs a new <code>GDimension</code> object from an existing one.
 *
 * @param size An existing <code>GDimension</code> object specifying the size
 */

   public GDimension(GDimension size) {
      this(size.width, size.height);
   }

/**
 * Constructs a new <code>GDimension</code> object from an AWT
 * <code>Dimension</code>.
 *
 * @param size An AWT <code>Dimension</code> object specifying the size
 */

   public GDimension(Dimension size) {
      this(size.width, size.height);
   }

/**
 * Returns the width of this <code>GDimension</code>.
 *
 * @return The width of this <code>GDimension</code>
 */

   public double getWidth() {
      return width;
   }

/**
 * Returns the height of this <code>GDimension</code>.
 *
 * @return The height of this <code>GDimension</code>
 */

   public double getHeight() {
      return height;
   }

/**
 * Sets the components of the dimension object from the specified parameters.
 *
 * @param width The new width of the dimension object
 * @param height The new height of the dimension object
 */

   public void setSize(double width, double height) {
      this.width = width;
      this.height = height;
   }

/**
 * Sets the width and height of one <code>GDimension</code> object equal
 * to that of another.
 *
 * @param size A <code>GDimension</code> object specifying the new size
 */

   public void setSize(GDimension size) {
      setSize(size.width, size.height);
   }

/**
 * Returns a new <code>GDimension</code> object equal to this one.
 *
 * @return A new <code>GDimension</code> object with the same size
 */

   public GDimension getSize() {
      return new GDimension(width, height);
   }

/**
 * Converts this <code>GDimension</code> to the nearest integer-based
 * <code>Dimension</code>.
 *
 * @return The closest integer-based <code>Dimension</code> object
 */

   public Dimension toDimension() {
      return new Dimension((int) Math.round(width),
                           (int) Math.round(height));
   }

/**
 * Returns an integer hash code for the dimension object.  The hash code for
 * a <code>GDimension</code> is constructed from the hash codes from the
 * <code>float</code> values of the width and height, which are the ones
 * used in the <code>equals</code> method.
 *
 * @return The hash code for this dimension object
 * @noshow
 */

   public int hashCode() {
      return Float.valueOf((float) width).hashCode()
                       ^ (37 * Float.valueOf((float) height).hashCode());
   }

/**
 * Tests whether two <code>GDimension</code> objects are equal.
 * Because floating-point values are inexact, this method checks for
 * equality by comparing the <code>float</code> values (rather than the
 * <code>double</code> values) of the coordinates.
 *
 * @param obj Any object
 * @return <code>true</code> if the <code>obj</code> is a
 *         <code>GDimension</code> equal to this one, and
 *         <code>false</code> otherwise
 * @noshow
 */

   public boolean equals(Object obj) {
      if (!(obj instanceof GDimension)) return false;
      GDimension dim = (GDimension) obj;
      return ((float) width == (float) dim.width)
          && ((float) height == (float) dim.height);
   }

/**
 * Converts this <code>GDimension</code> to its string representation.
 *
 * @return A string representation of this dimension object
 * @noshow
 */

   public String toString() {
      return "(" + (float) width + "x" + (float) height + ")";
   }

/* Private instance variables */

   private double width;
   private double height;

/* Serial version UID */
/**
 * The serialization code for this class.  This value should be incremented
 * whenever you change the structure of this class in an incompatible way,
 * typically by adding a new instance variable.
 */

   static final long serialVersionUID = 21L;

}
