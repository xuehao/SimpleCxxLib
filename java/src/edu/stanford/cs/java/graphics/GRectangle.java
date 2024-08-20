/*
 * @(#)GRectangle.java   2.03.1 05/26/14
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

import java.awt.Rectangle;
import java.io.Serializable;

/**
 * This class is a double-precision version of the <code>Rectangle</code>
 * class in <code>java.awt</code>.
 */

public class GRectangle implements Serializable {

/**
 * Constructs a new empty <code>GRectangle</code>.
 *
 */

   public GRectangle() {
      this(0, 0, 0, 0);
   }

/**
 * Constructs a new <code>GRectangle</code> with the specified coordinates
 * and size.
 *
 * @param x The x-coordinate of the rectangle
 * @param y The y-coordinate of the rectangle
 * @param width The width of the rectangle
 * @param height The height of the rectangle
 */

   public GRectangle(double x, double y, double width, double height) {
      xc = x;
      yc = y;
      this.width = width;
      this.height = height;
   }

/**
 * Constructs a <code>GRectangle</code> at the origin with the specified
 * width and height.
 *
 * @param width The width of the rectangle
 * @param height The height of the rectangle
 */

   public GRectangle(double width, double height) {
      this(0, 0, width, height);
   }

/**
 * Constructs a new <code>GRectangle</code> with the specified location
 * and size.
 *
 * @param pt The location of the upper left corner of the rectangle
 * @param size The dimensions of the rectangle
 */

   public GRectangle(GPoint pt, GDimension size) {
      this(pt.getX(), pt.getY(), size.getWidth(), size.getHeight());
   }

/**
 * Constructs a new empty <code>GRectangle</code> at the specified location.
 *
 * @param pt The location of the upper left corner of the rectangle
 */

   public GRectangle(GPoint pt) {
      this(pt.getX(), pt.getY(), 0, 0);
   }

/**
 * Constructs a new <code>GRectangle</code> at the origin with the
 * specified size.
 *
 * @param size The dimensions of the rectangle
 */

   public GRectangle(GDimension size) {
      this(0, 0, size.getWidth(), size.getHeight());
   }

/**
 * Constructs a new <code>GRectangle</code> from an existing one.
 *
 * @param r The original rectangle
 */

   public GRectangle(GRectangle r) {
      this(r.xc, r.yc, r.width, r.height);
   }

/**
 * Returns the x coordinate of this <code>GRectangle</code>.
 *
 * @return The x coordinate of this <code>GRectangle</code>
 */

   public double getX() {
      return xc;
   }

/**
 * Returns the y coordinate of this <code>GRectangle</code>.
 *
 * @return The y coordinate of this <code>GRectangle</code>
 */

   public double getY() {
      return yc;
   }

/**
 * Returns the width of this <code>GRectangle</code>.
 *
 * @return The width of this <code>GRectangle</code>
 */

   public double getWidth() {
      return width;
   }

/**
 * Returns the height of this <code>GRectangle</code>.
 *
 * @return The height of this <code>GRectangle</code>
 */

   public double getHeight() {
      return height;
   }

/**
 * Sets the components of a <code>GRectangle</code> from the specified values.
 *
 * @param x The x-coordinate of the rectangle
 * @param y The y-coordinate of the rectangle
 * @param width The width of the rectangle
 * @param height The height of the rectangle
 */

   public void setBounds(double x, double y, double width, double height) {
      xc = x;
      yc = y;
      this.width = width;
      this.height = height;
   }

/**
 * Sets the components of a <code>GRectangle</code> from the specified
 * location and size.
 *
 * @param pt The location of the upper left corner of the rectangle
 * @param size The dimensions of the rectangle
 */

   public void setBounds(GPoint pt, GDimension size) {
      setBounds(pt.getX(), pt.getY(), size.getWidth(), size.getHeight());
   }

/**
 * Sets the bounds of one <code>GRectangle</code> equal to that of another.
 *
 * @param bounds A <code>GRectangle</code> specifying the new bounds
 */

   public void setBounds(GRectangle bounds) {
      setBounds(bounds.xc, bounds.yc, bounds.width, bounds.height);
   }

/**
 * Returns a new <code>GRectangle</code> whose bounds are the same as
 * this one.
 *
 * @return A new rectangle with the same bounds
 */

   public GRectangle getBounds() {
      return new GRectangle(this);
   }

/**
 * Sets the location of the <code>GRectangle</code> to the specified
 * <code>x</code> and <code>y</code> values.
 *
 * @param x The new x-coordinate for the rectangle
 * @param y The new y-coordinate for the rectangle
 */

   public void setLocation(double x, double y) {
      xc = x;
      yc = y;
   }

/**
 * Sets the location of the <code>GRectangle</code> to the specified point.
 *
 * @param pt The new location for the rectangle
 */

   public void setLocation(GPoint pt) {
      setLocation(pt.getX(), pt.getY());
   }

/**
 * Returns a new <code>GPoint</code> with the location of the rectangle.
 *
 * @return The location of the rectangle as a <code>GPoint</code>
 */

   public GPoint getLocation() {
      return new GPoint(xc, yc);
   }

/**
 * Adjusts the coordinates of a rectangle by the specified <code>dx</code> and
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
 * Sets the size of the <code>GRectangle</code> to the specified values.
 *
 * @param width The new width of the rectangle
 * @param height The new height of the rectangle
 */

   public void setSize(double width, double height) {
      this.width = width;
      this.height = height;
   }

/**
 * Sets the size of the <code>GRectangle</code> to the specified dimension.
 *
 * @param size The new dimensions of the rectangle
 */

   public void setSize(GDimension size) {
      setSize(size.getWidth(), size.getHeight());
   }

/**
 * Returns a new <code>GDimension</code> object with the size of the
 * <code>GRectangle</code>.
 *
 * @return The size of the rectangle as a <code>GDimension</code>
 */

   public GDimension getSize() {
      return new GDimension(width, height);
   }

/**
 * Adjusts the edges of a rectangle by the specified <code>dx</code> and
 * <code>dy</code> offsets along each of its borders.
 *
 * @param dx The offset to extend each of the left and right borders
 * @param dy The offset to extend each of the top and bottom borders
 */

   public void grow(double dx, double dy) {
      xc -= dx;
      yc -= dy;
      width += 2 * dx;
      height += 2 * dy;
   }

/**
 * Returns <code>true</code> if the rectangle is empty.
 *
 * @return <code>true</code> if the rectangle is empty, and
 *         <code>false</code> otherwise
 */

   public boolean isEmpty() {
      return width <= 0 || height <= 0;
   }

/**
 * Returns <code>true</code> if the <code>GRectangle</code> contains the
 * specified point.
 *
 * @param x The x-coordinate of the point being tested
 * @param y The y-coordinate of the point being tested
 * @return <code>true</code> if the rectangle contains
 *         (<code>x</code>,&nbsp;<code>y</code>),
 *         and <code>false</code> otherwise
 */

   public boolean contains(double x, double y) {
      return x >= xc && y >= yc && x < xc + width && y < yc + height;
   }

/**
 * Returns <code>true</code> if the <code>GRectangle</code> contains the
 * specified point.
 *
 * @param pt The point being tested
 * @return <code>true</code> if the rectangle contains <code>pt</code>,
 *         and <code>false</code> otherwise
 */

   public boolean contains(GPoint pt) {
      return contains(pt.getX(), pt.getY());
   }

/**
 * Returns <code>true</code> if <code>r1</code> and <code>r2</code> have a
 * nonempty intersection.
 *
 * @param r2 A second rectangle
 * @return <code>true</code> if the two rectangles intersect, and
 *         <code>false</code> otherwise
 */

   public boolean intersects(GRectangle r2) {
      GRectangle r1 = this;
      if (r1.xc > r2.xc + r2.width) return false;
      if (r1.yc > r2.yc + r2.height) return false;
      if (r2.xc > r1.xc + r1.width) return false;
      if (r2.yc > r1.yc + r1.height) return false;
      return true;
   }

/**
 * Returns the largest rectangle that is contained in both
 * <code>r1</code> and <code>r2</code>.
 *
 * @param r2 A second rectangle
 * @return The intersection of this rectangle and <code>r2</code>
 */

   public GRectangle intersection(GRectangle r2) {
      GRectangle r1 = this;
      double x1 = Math.max(r1.xc, r2.xc);
      double y1 = Math.max(r1.yc, r2.yc);
      double x2 = Math.min(r1.xc + r1.width, r2.xc + r2.width);
      double y2 = Math.min(r1.yc + r1.height, r2.yc + r2.height);
      return new GRectangle(x1, y1, x2 - x1, y2 - y1);
   }

/**
 * Returns the smallest rectangle that contains both
 * <code>r1</code> and <code>r2</code>.
 *
 * @param r2 A second rectangle
 * @return The union of this rectangle and <code>r2</code>
 */

   public GRectangle union(GRectangle r2) {
      if (isEmpty()) return new GRectangle(r2);
      if (r2.isEmpty()) return new GRectangle(this);
      GRectangle r1 = this;
      double x1 = Math.min(r1.xc, r2.xc);
      double y1 = Math.min(r1.yc, r2.yc);
      double x2 = Math.max(r1.xc + r1.width, r2.xc + r2.width);
      double y2 = Math.max(r1.yc + r1.height, r2.yc + r2.height);
      return new GRectangle(x1, y1, x2 - x1, y2 - y1);
   }

/**
 * Adjusts the bounds of the current <code>GRectangle</code> so that it
 * contains the rectangle represented by the argument.
 *
 * @param r A new rectangle to include in this one
 */

   public void add(GRectangle r) {
      if (r.isEmpty()) return;
      if (isEmpty()) {
         setBounds(r);
         return;
      }
      double x2 = Math.max(xc + width, r.xc + r.width);
      double y2 = Math.max(yc + height, r.yc + r.height);
      xc = Math.min(r.xc, xc);
      yc = Math.min(r.yc, yc);
      width = x2 - xc;
      height = y2 - yc;
   }

/**
 * Adds the specified point to the rectangle.
 *
 * @param x The x coordinate of the new point
 * @param y The y coordinate of the new point
 */

   public void add(double x, double y) {
      if (isEmpty()) {
         setBounds(x, y, 0, 0);
         return;
      }
      double x2 = Math.max(x + width, x);
      double y2 = Math.max(y + height, y);
      xc = Math.min(x, xc);
      yc = Math.min(y, yc);
      width = x2 - xc;
      height = y2 - yc;
   }

/**
 * Converts this <code>GRectangle</code> to the nearest integer-based
 * <code>Rectangle</code>.
 *
 * @return The closest integer-based <code>Rectangle</code>
 */

   public Rectangle toRectangle() {
      return new Rectangle(GMath.round(xc), GMath.round(yc),
                           GMath.round(width), GMath.round(height));
   }

/**
 * Returns an integer hash code for the rectangle.  The hash code for a
 * <code>GRectangle</code> is constructed from the hash codes from the
 * <code>float</code> values of the coordinates, which are the ones used
 * in the <code>equals</code> method.
 *
 * @return The hash code for this rectangle
 * @noshow
 */

   public int hashCode() {
      int hash = Float.valueOf((float) xc).hashCode();
      hash = (37 * hash) ^ Float.valueOf((float) yc).hashCode();
      hash = (37 * hash) ^ Float.valueOf((float) width).hashCode();
      hash = (37 * hash) ^ Float.valueOf((float) height).hashCode();
      return hash;
   }

/**
 * Tests whether two <code>GRectangle</code> objects are equal.
 * Because floating-point values are inexact, this method checks for
 * equality by comparing the <code>float</code> values (rather than the
 * <code>double</code> values) of the coordinates.
 *
 * @param obj Any object
 * @return <code>true</code> if the <code>obj</code> is a
 *         <code>GRectangle</code> equal to this one,
 *         and <code>false</code> otherwise
 * @noshow
 */

   public boolean equals(Object obj) {
      if (!(obj instanceof GRectangle)) return false;
      GRectangle r = (GRectangle) obj;
      if ((float) xc != (float) r.xc) return false;
      if ((float) yc != (float) r.yc) return false;
      if ((float) width != (float) r.width) return false;
      if ((float) height != (float) r.height) return false;
      return true;
   }

/**
 * Converts this <code>GRectangle</code> to its string representation.
 *
 * @return A string representation of this rectangle
 * @noshow
 */

   public String toString() {
      return "[" + (float) xc + ", " + (float) yc + ", "
                 + (float) width + "x" + (float) height + "]";
   }

/* Private instance variables */

   private double xc;
   private double yc;
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
