/*
 * @(#)GLine.java   2.03.1 05/26/14
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

import java.awt.Graphics2D;
import java.awt.geom.AffineTransform;
import java.awt.geom.Line2D;
import java.awt.geom.Point2D;

/**
 * The <code>GLine</code> class is a graphical object whose appearance
 * consists of a line segment.
 */

public class GLine extends GObject {

/**
 * This constant defines how close (measured in pixel units) a point has
 * to be to a line before that point is considered to be "contained" within
 * the line.
 */

   public static final double LINE_TOLERANCE = 1.5;

/**
 * Constructs a line segment from its endpoints.  The point
 * (<code>x0</code>,&nbsp;<code>y0</code>) defines the start of the
 * line and the point (<code>x1</code>,&nbsp;<code>y1</code>) defines
 * the end.
 *
 * @param x0 The x-coordinate of the start of the line
 * @param y0 The y-coordinate of the start of the line
 * @param x1 The x-coordinate of the end of the line
 * @param y1 The y-coordinate of the end of the line
 */

   public GLine(double x0, double y0, double x1, double y1) {
      setLocation(x0, y0);
      dx = x1 - x0;
      dy = y1 - y0;
   }

/**
 * Implements the <code>paint2d</code> operation for this graphical object.
 * This method is not called directly by clients.
 * @noshow
 */

   protected void paint2d(Graphics2D g) {
      Line2D line = new Line2D.Double(0, 0, GMath.round(dx), GMath.round(dy));
      g.draw(line);
   }

/**
 * Returns the bounding box for this object.
 *
 * @return The bounding box for this object
 */

   public GRectangle getBounds() {
      double x0 = getX();
      double y0 = getY();
      double x1 = x0 + dx;
      double y1 = y0 + dy;
      AffineTransform matrix = getMatrix();
      if (matrix != null) {
         Point2D pt = new Point2D.Double(x0, y0);
         matrix.transform(pt, pt);
         x0 = pt.getX();
         y0 = pt.getY();
         pt = new Point2D.Double(x1, y1);
         matrix.transform(pt, pt);
         x1 = pt.getX();
         y1 = pt.getY();
      }
      double x = Math.min(x0, x1);
      double y = Math.min(y0, y1);
      return new GRectangle(x, y, Math.abs(x1 - x0) + 1,
                                  Math.abs(y1 - y0) + 1);
   }


/**
 * Sets the initial point in the line to (<code>x</code>,&nbsp;<code>y</code>),
 * leaving the end point unchanged.  This method is therefore different from
 * <a href="#setLocation(double, double)"><code>setLocation</code></a>, which
 * moves both components of the line segment.
 *
 * @param x The new x-coordinate of the origin
 * @param y The new y-coordinate of the origin
 */

   public void setStartPoint(double x, double y) {
      dx += getX() - x;
      dy += getY() - y;
      setLocation(x, y);
   }

/**
 * Returns the coordinates of the initial point in the line.  This method is
 * identical to <a href="#getLocation()"><code>getLocation</code></a> and
 * exists only to provide symmetry with
 * <a href="#setStartPoint(double, double)"><code>setStartPoint</code></a>.
 *
 * @return The coordinates of the origin of the line
 */

   public GPoint getStartPoint() {
      return getLocation();
   }

/**
 * Sets the end point of the line to the point
 * (<code>x</code>,&nbsp;<code>y</code>).
 * The origin of the line remains unchanged.
 *
 * @param x The new x-coordinate of the end point
 * @param y The new y-coordinate of the end point
 */

   public void setEndPoint(double x, double y) {
      dx = x - getX();
      dy = y - getY();
      repaint();
   }

/**
 * Returns the end point of the line as a <code>GPoint</code> object.
 *
 * @return The coordinates of the end point of the line
 */

   public GPoint getEndPoint() {
      return new GPoint(getX() + dx, getY() + dy);
   }

/**
 * Checks to see whether a point is inside the object.  For the
 * <code>GLine</code> class, containment is defined to mean that the
 * point is within <a href="#LINE_TOLERANCE"><code>LINE_TOLERANCE</code></a>
 * pixels of the line.
 *
 * @param x The x-coordinate of the point being tested
 * @param y The y-coordinate of the point being tested
 * @return <code>true</code> if the point (<code>x</code>,&nbsp;<code>y</code>)
 *         is within a short distance of the line
 */

   public boolean contains(double x, double y) {
      double x0 = getX();
      double y0 = getY();
      double x1 = x0 + dx;
      double y1 = y0 + dy;
      AffineTransform matrix = getMatrix();
      if (matrix != null) {
         Point2D pt = new Point2D.Double(x0, y0);
         matrix.transform(pt, pt);
         x0 = pt.getX();
         y0 = pt.getY();
         pt = new Point2D.Double(x1, y1);
         matrix.transform(pt, pt);
         x1 = pt.getX();
         y1 = pt.getY();
      }
      double tSquared = LINE_TOLERANCE * LINE_TOLERANCE;
      if (distanceSquared(x, y, x0, y0) < tSquared) return true;
      if (distanceSquared(x, y, x1, y1) < tSquared) return true;
      if (x < Math.min(x0, x1) - LINE_TOLERANCE) return false;
      if (x > Math.max(x0, x1) + LINE_TOLERANCE) return false;
      if (y < Math.min(y0, y1) - LINE_TOLERANCE) return false;
      if (y > Math.max(y0, y1) + LINE_TOLERANCE) return false;
      if ((float) x0 - (float) x1 == 0 && (float) y0 - (float) y1 == 0) {
         return false;
      }
      double u = ((x - x0) * (x1 - x0) + (y - y0) * (y1 - y0))
                   / distanceSquared(x0, y0, x1, y1);
      return distanceSquared(x, y, x0 + u * (x1 - x0), y0 + u * (y1 - y0))
                < tSquared;
   }

/**
 * Returns a string indicating the parameters of this object.
 * @noshow
 */

   public String paramString() {
      String tail = super.paramString();
      tail = tail.substring(tail.indexOf(')') + 1);
      GPoint pt = getStartPoint();
      String param = "start=(" + pt.getX() + ", " + pt.getY() + ")";
      pt = getEndPoint();
      param += ", end=(" + pt.getX() + ", " + pt.getY() + ")";
      return param + tail;
   }

/**
 * Returns the square of the distance between
 * (<code>x0</code>,&nbsp;<code>y0</code>) and
 * (<code>x1</code>,&nbsp;<code>y1</code>).
 */

   private double distanceSquared(double x0, double y0, double x1, double y1) {
      return (x1 - x0) * (x1 - x0) + (y1 - y0) * (y1 - y0);
   }

/* Private instance variables */

   private double dx, dy;

/* Serial version UID */
/**
 * The serialization code for this class.  This value should be incremented
 * whenever you change the structure of this class in an incompatible way,
 * typically by adding a new instance variable.
 */

   static final long serialVersionUID = 21L;

}
