/*
 * @(#)GArc.java   2.03.1 05/26/14
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
import java.awt.Graphics2D;
import java.awt.geom.Arc2D;

/**
 * The <code>GArc</code> class is a graphical object whose appearance
 * consists of an arc.  If unfilled, the arc is simply a portion of
 * the circumference of an ellipse; if filled, the arc is a pie-shaped
 * wedge connected to the center of the figure.
 */

public class GArc extends GObject implements GFillable {

/**
 * This constant defines how close (measured in pixel units) a point has
 * to be to an arc before that point is considered to be "contained" within
 * the arc.
 */

   public static final double ARC_TOLERANCE = 2.5;
   // BUG?: THIS SEEMS TO REQUIRE HITTING THE ARC EXACTLY EVEN WITH 2.5

/**
 * Creates a new <code>GArc</code> object consisting of an elliptical arc
 * located at the point (0,&nbsp;0).  For complete descriptions of the
 * other parameters, see the entry for the
 * <a href="#GArc(double, double, double, double, double, double)"
 * ><code>GArc</code></a> constructor that includes explicit
 * <code>x</code> and <code>y</code> parameters.
 *
 * @param width The width of the rectangle in which the arc is inscribed
 * @param height The height of the rectangle in which the arc is inscribed
 * @param start The angle at which the arc begins measured in degrees
 *              counterclockwise from the +x axis
 * @param sweep The extent of the arc, measured in degrees counterclockwise
 */

   public GArc(double width, double height, double start, double sweep) {
      this(0, 0, width, height, start, sweep);
   }

/**
 * Creates a new <code>GArc</code> object consisting of an elliptical
 * arc inscribed in the rectangle with the specified bounds.
 * The <code>start</code> parameter indicates the angle at which the arc
 * begins and is measured in degrees counterclockwise from the +<i>x</i>
 * axis.  Thus, a <code>start</code> angle of 0 indicates an arc
 * that begins along the line running eastward from the center (the 3:00
 * o&rsquo;clock position), a <code>start</code> angle of 135
 * begins along the line running northwest, and a <code>start</code>
 * angle of -90 begins along the line running south (the 6:00
 * o&rsquo;clock position).  The <code>sweep</code> parameter indicates
 * the extent of the arc and is also measured in degrees counterclockwise.
 * A <code>sweep</code> angle of 90 defines a quarter circle extending
 * counterclockwise from the <code>start</code> angle, and a
 * <code>sweep</code> angle of -180 defines a semicircle extending
 * clockwise.
 *
 * @param x The x-coordinate for the rectangle in which the arc is inscribed
 * @param y The y-coordinate for the rectangle in which the arc is inscribed
 * @param width The width of the rectangle in which the arc is inscribed
 * @param height The height of the rectangle in which the arc is inscribed
 * @param start The angle at which the arc begins measured in degrees
 *              counterclockwise from the +x axis
 * @param sweep The extent of the arc, measured in degrees counterclockwise
 */

   public GArc(double x, double y, double width, double height,
                                   double start, double sweep) {
      frameWidth = width;
      frameHeight = height;
      arcStart = start;
      arcSweep = sweep;
      setLocation(x, y);
   }

/**
 * Sets the starting angle for this <code>GArc</code> object.
 *
 * @param start The new starting angle
 */

   public void setStartAngle(double start) {
      arcStart = start;
      repaint();
   }

/**
 * Returns the starting angle for this <code>GArc</code> object.
 *
 * @return The starting angle for this arc
 */

   public double getStartAngle() {
      return arcStart;
   }

/**
 * Sets the sweep angle for this <code>GArc</code> object.
 *
 * @param sweep The new sweep angle
 */

   public void setSweepAngle(double sweep) {
      arcSweep = sweep;
      repaint();
   }

/**
 * Returns the sweep angle for this <code>GArc</code> object.
 *
 * @return The sweep angle for this arc
 */

   public double getSweepAngle() {
      return arcSweep;
   }

/**
 * Returns the point at which the arc starts.
 *
 * @return The point at which the arc starts
 */

   public GPoint getStartPoint() {
      return getArcPoint(arcStart);
   }

/**
 * Returns the point at which the arc ends.
 *
 * @return The point at which the arc ends
 */

   public GPoint getEndPoint() {
      return getArcPoint(arcStart + arcSweep);
   }

/**
 * Implements the <code>paint2d</code> operation for this graphical object.
 * This method is not called directly by clients.
 * @noshow
 */

   protected void paint2d(Graphics2D g) {
      Arc2D arc = new Arc2D.Double(0, 0, frameWidth, frameHeight,
                                   arcStart, arcSweep,
                                   isFilled() ? Arc2D.PIE : Arc2D.OPEN);
      if (isFilled()) {
         g.setColor(getFillColor());
         g.fill(arc);
         g.setColor(getColor());
      }
      g.draw(arc);
   }

/**
 * Returns the bounding box of the arc.  Note that this method returns the
 * bounds of the visible portion of the arc and will therefore not contain
 * the same values as specified in
 * <a href="#setFrameRectangle(double, double, double, double)"
 * ><code>setFrameRectangle</code></a>.  To obtain the bounds used to
 * describe the Java arc, use
 * <a href="#getFrameRectangle()"><code>getFrameRectangle</code></a>.
 *
 * @return The bounding box of this object
 */

   public GRectangle getBounds() {  // Fix
      double rx = frameWidth / 2;
      double ry = frameHeight / 2;
      double cx = getX() + rx;
      double cy = getY() + ry;
      double p1x = cx + GMath.cosDegrees(arcStart) * rx;
      double p1y = cy - GMath.sinDegrees(arcStart) * ry;
      double p2x = cx + GMath.cosDegrees(arcStart + arcSweep) * rx;
      double p2y = cy - GMath.sinDegrees(arcStart + arcSweep) * ry;
      double xMin = Math.min(p1x, p2x);
      double xMax = Math.max(p1x, p2x);
      double yMin = Math.min(p1y, p2y);
      double yMax = Math.max(p1y, p2y);
      if (containsAngle(0)) xMax = cx + rx;
      if (containsAngle(90)) yMin = cy - ry;
      if (containsAngle(180)) xMin = cx - rx;
      if (containsAngle(270)) yMax = cy + ry;
      if (isFilled()) {
         xMin = Math.min(xMin, cx);
         yMin = Math.min(yMin, cy);
         xMax = Math.max(xMax, cx);
         yMax = Math.max(yMax, cy);
      }
      return new GRectangle(xMin, yMin, xMax - xMin, yMax - yMin);
   }

/**
 * Checks to see whether a point is inside the object.  For the
 * <code>GArc</code> class, containment depends on whether the arc
 * is filled.  Filled arcs are a wedge in which containment can be
 * defined in a natural way; unfilled arcs are essentially lines,
 * which means that containment is defined to mean that the point
 * is within <a href="#ARC_TOLERANCE"><code>ARC_TOLERANCE</code></a> pixels
 * of the arc.
 *
 * @param x The x-coordinate of the point being tested
 * @param y The y-coordinate of the point being tested
 * @return <code>true</code> if the point
 *         (<code>x</code>,&nbsp;<code>y</code>) is inside the arc
 */

   public boolean contains(double x, double y) {
      double rx = frameWidth / 2;
      double ry = frameHeight / 2;
      if (rx == 0 || ry == 0) return false;
      double dx = x - (getX() + rx);
      double dy = y - (getY() + ry);
      double r = (dx * dx) / (rx * rx) + (dy * dy) / (ry * ry);
      if (isFilled()) {
         if (r > 1.0) return false;
      } else {
         double t = ARC_TOLERANCE / ((rx + ry) / 2);
         if (Math.abs(1.0 - r) > t) return false;
      }
      return containsAngle(GMath.toDegrees(Math.atan2(-dy, dx)));
   }

/**
 * Changes the arc bounds to the specified values.
 *
 * @param x The x-coordinate for the rectangle in which the arc is inscribed
 * @param y The y-coordinate for the rectangle in which the arc is inscribed
 * @param width The width of the rectangle in which the arc is inscribed
 * @param height The height of the rectangle in which the arc is inscribed
 */

   public void setFrameRectangle(double x, double y,
                                 double width, double height) {
      frameWidth = width;
      frameHeight = height;
      setLocation(x, y);
   }

/**
 * Changes the arc bounds to the values from the specified
 * <code>GRectangle</code>.
 *
 * @param bounds A <code>GRectangle</code> specifying the new arc bounds
 */

   public final void setFrameRectangle(GRectangle bounds) {
      setFrameRectangle(bounds.getX(), bounds.getY(),
                        bounds.getWidth(), bounds.getHeight());
   }

/**
 * Returns the bounds of the <code>GRectangle</code> in which this arc is
 * inscribed.  Note that this is usually different from the bounding box
 * returned by <a href="#getBounds()"><code>getBounds</code></a>, which
 * returns the bounding box in which the displayed portion of the arc
 * is contained.
 *
 * @return The <code>GRectangle</code> in which this arc is inscribed
 */

   public GRectangle getFrameRectangle() {
      return new GRectangle(getX(), getY(), frameWidth, frameHeight);
   }

/**
 * Sets whether this object is filled.
 *
 * @param fill <code>true</code> if the object should be filled,
 *             <code>false</code> for an outline
 */

   public void setFilled(boolean fill) {
      isFilled = fill;
      repaint();
   }

/**
 * Returns whether this object is filled.
 *
 * @return The color used to display the object
 */

   public boolean isFilled() {
      return isFilled;
   }

/**
 * Sets the color used to display the filled region of this object.
 *
 * @param color The color used to display the filled region of this object
 */

   public void setFillColor(Color color) {
      fillColor = color;
      repaint();
   }

/**
 * Returns the color used to display the filled region of this object.  If
 * none has been set, <code>getFillColor</code> returns the color of the
 * object.
 *
 * @return The color used to display the filled region of this object
 */

   public Color getFillColor() {
      return (fillColor == null) ? getColor() : fillColor;
   }

/**
 * Returns a string indicating the parameters of this object.
 * @noshow
 */

   public String paramString() {
      String tail = super.paramString();
      tail = tail.substring(tail.indexOf(')') + 1);
      GRectangle r = getFrameRectangle();
      String param = "frame=(" + r.getX() + ", " + r.getY() + ", "
                     + r.getWidth() + ", " + r.getHeight() + ")";
      param += ", start=" + arcStart + ", sweep=" + arcSweep;
      return param + tail;
   }

/** Private method: getArcPoint(angle) */
/**
 * Returns the point on the ellipse for the arc at the specified angle.
 */

   private GPoint getArcPoint(double angle) {
      double rx = frameWidth / 2;
      double ry = frameHeight / 2;
      double cx = getX() + rx;
      double cy = getY() + ry;
      return new GPoint(cx + rx * GMath.cosDegrees(angle),
                        cy - ry * GMath.sinDegrees(angle));
   }

/**
 * Returns <code>true</code> if the arc contains the specified angle.
 */

   private boolean containsAngle(double theta) {
      double start = Math.min(getStartAngle(),
                              getStartAngle() + getSweepAngle());
      double sweep = Math.abs(getSweepAngle());
      if (sweep >= 360) return true;
      theta = (theta < 0) ? 360 - (-theta % 360) : theta % 360;
      start = (start < 0) ? 360 - (-start % 360) : start % 360;
      if (start + sweep > 360) {
         return theta >= start || theta <= start + sweep - 360;
      } else {
         return theta >= start && theta <= start + sweep;
      }
   }

/* Private instance variables */

   private double frameWidth;
   private double frameHeight;
   private double arcStart;
   private double arcSweep;
   private Color fillColor;
   private boolean isFilled;

/* Serial version UID */
/**
 * The serialization code for this class.  This value should be incremented
 * whenever you change the structure of this class in an incompatible way,
 * typically by adding a new instance variable.
 */

   static final long serialVersionUID = 21L;

}
