/*
 * @(#)GRoundRect.java   2.03.1 05/26/14
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

import java.awt.Graphics2D;
import java.awt.geom.RoundRectangle2D;

/**
 * The <code>GRoundRect</code> class is a graphical object whose appearance
 * consists of a rounded rectangle.
 */

public class GRoundRect extends GRect {

/**
 * The default arc diameter used for the corners of a rounded rectangle.
 */

   public static final double DEFAULT_ARC = 10;

/**
 * Constructs a new rounded rectangle with the specified width and height,
 * positioned at the origin.
 *
 * @param width The width of the rectangle in pixels
 * @param height The height of the rectangle in pixels
 */

   public GRoundRect(double width, double height) {
      this(0, 0, width, height, DEFAULT_ARC);
   }

/**
 * Constructs a new rounded rectangle with the specified bounds.
 *
 * @param x The x-coordinate of the upper left corner
 * @param y The y-coordinate of the upper left corner
 * @param width The width of the rectangle in pixels
 * @param height The height of the rectangle in pixels
 */

   public GRoundRect(double x, double y, double width, double height) {
      this(x, y, width, height, DEFAULT_ARC);
   }

/**
 * Constructs a new rounded rectangle with the specified bounds and a single
 * parameter describing both the  describing the curvature at the corners.
 *
 * @param x The x-coordinate of the upper left corner
 * @param y The y-coordinate of the upper left corner
 * @param width The width of the rectangle in pixels
 * @param height The height of the rectangle in pixels
 * @param arcSize The diameter of the circle in place at each corner
 */

   public GRoundRect(double x, double y, double width, double height,
                     double arcSize) {
      this(x, y, width, height, arcSize, arcSize);
   }

/**
 * Constructs a new rounded rectangle with the specified bounds and
 * arc parameters describing the curvature at the corners.
 *
 *                                             arcWidth, arcHeight);
 * @param x The x-coordinate of the upper left corner
 * @param y The y-coordinate of the upper left corner
 * @param width The width of the rectangle in pixels
 * @param height The height of the rectangle in pixels
 * @param arcWidth The width of the oval in place at each corner
 * @param arcHeight The height of the oval in place at each corner
 */

   public GRoundRect(double x, double y, double width, double height,
                     double arcWidth, double arcHeight) {
      super(x, y, width, height);
      aWidth = arcWidth;
      aHeight = arcHeight;
   }

/**
 * Returns the <i>x</i> component of the corner radius.
 *
 * @return The <i>x</i> component of the corner radius, in pixels.
 */

   public double getArcWidth() {
      return aWidth;
   }

/**
 * Returns the <i>y</i> component of the corner radius.
 *
 * @return The <i>y</i> component of the corner radius, in pixels.
 */

   public double getArcHeight() {
      return aHeight;
   }

/**
 * Implements the <code>paint2d</code> operation for this graphical object.
 * This method is not called directly by clients.
 * @noshow
 */

   protected void paint2d(Graphics2D g) {
      RoundRectangle2D rr = new RoundRectangle2D.Double(0, 0,
                                                        getFrameWidth(),
                                                        getFrameHeight(),
                                                        aWidth, aHeight);
      if (isFilled()) {
         g.setColor(getFillColor());
         g.fill(rr);
         g.setColor(getColor());
      }
      g.draw(rr);
   }

/* Private instance variables */

   private double aWidth, aHeight;

/* Serial version UID */
/**
 * The serialization code for this class.  This value should be incremented
 * whenever you change the structure of this class in an incompatible way,
 * typically by adding a new instance variable.
 */

   static final long serialVersionUID = 21L;

}
