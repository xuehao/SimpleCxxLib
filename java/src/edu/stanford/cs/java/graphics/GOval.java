/*
 * @(#)GOval.java   2.03.1 05/26/14
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

import java.awt.Color;
import java.awt.Graphics2D;
import java.awt.Shape;
import java.awt.geom.AffineTransform;
import java.awt.geom.Ellipse2D;
import java.awt.geom.Rectangle2D;

/**
 * The <code>GOval</code> class is a graphical object whose appearance
 * consists of an oval.
 */

public class GOval extends GObject implements GFillable, GResizable {

/**
 * Constructs a new oval with the specified width and height,
 * positioned at the origin.
 *
 * @param width The width of the oval in pixels
 * @param height The height of the oval in pixels
 */

   public GOval(double width, double height) {
      this(0, 0, width, height);
   }

/**
 * Constructs a new oval with the specified bounds.
 *
 * @param x The x-coordinate of the upper left corner
 * @param y The y-coordinate of the upper left corner
 * @param width The width of the oval in pixels
 * @param height The height of the oval in pixels
 */

   public GOval(double x, double y, double width, double height) {
      frameWidth = width;
      frameHeight = height;
      setLocation(x, y);
   }

/**
 * Returns the bounding box of this object.
 *
 * @return The bounding box for this object
 */

   public GRectangle getBounds() {
      Shape shape = new Ellipse2D.Double(0, 0, frameWidth, frameHeight);
      AffineTransform matrix = getMatrix();
      if (matrix != null) {
         shape = matrix.createTransformedShape(shape);
      }
      Rectangle2D bounds = shape.getBounds();
      return new GRectangle(bounds.getX() + getX(), bounds.getY() + getY(),
                            bounds.getWidth(), bounds.getHeight());
   }

/**
 * Checks to see whether a point is inside the object.
 *
 * @param x The x-coordinate of the point being tested
 * @param y The y-coordinate of the point being tested
 * @return <code>true</code> if the point (<code>x</code>,&nbsp;<code>y</code>)
 *         is inside the object, and <code>false</code> otherwise
 */

   public boolean contains(double x, double y) {
      Shape shape = new Ellipse2D.Double(0, 0, frameWidth, frameHeight);
      AffineTransform matrix = getMatrix();
      if (matrix != null) {
         shape = matrix.createTransformedShape(shape).getBounds();
      }
      return shape.contains(x - getX(), y - getY());
   }

/**
 * Implements the <code>paint2d</code> operation for this graphical object.
 * This method is not called directly by clients.
 * @noshow
 */

   protected void paint2d(Graphics2D g) {
      Ellipse2D oval = new Ellipse2D.Double(0, 0, frameWidth, frameHeight);
      if (isFilled()) {
         g.setColor(getFillColor());
         g.fill(oval);
         g.setColor(getColor());
      }
      g.draw(oval);
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
 * Changes the size of this object to the specified width and height.
 *
 * @param width The new width of the object
 * @param height The new height of the object
 */

   public void setSize(double width, double height) {
      if (getMatrix() != null) {
         throw new RuntimeException("setSize: Object has been transformed");
      }
      frameWidth = width;
      frameHeight = height;
      repaint();
   }

/**
 * Changes the size of this object to the specified <code>GDimension</code>.
 *
 * @param size A <code>GDimension</code> object specifying the size
 * @noshow
 */

   public final void setSize(GDimension size) {
      setSize(size.getWidth(), size.getHeight());
   }

/**
 * Returns the size of this object as a <code>GDimension</code>.
 *
 * @return The size of this object
 */

   public GDimension getSize() {
      return new GDimension(frameWidth, frameHeight);
   }

/**
 * Changes the bounds of this object to the specified values.
 *
 * @param x The new x-coordinate for the object
 * @param y The new y-coordinate for the object
 * @param width The new width of the object
 * @param height The new height of the object
 */

   public void setBounds(double x, double y, double width, double height) {
      if (getMatrix() != null) {
         throw new RuntimeException("setBounds: Object has been transformed");
      }
      frameWidth = width;
      frameHeight = height;
      setLocation(x, y);
   }

/**
 * Changes the bounds of this object to the values from the specified
 * <code>Rectangle</code>.
 *
 * @param bounds A <code>GRectangle</code> specifying the new bounds
 */

   public final void setBounds(GRectangle bounds) {
      if (getMatrix() != null) {
         throw new RuntimeException("setBounds: Object has been transformed");
      }
      setBounds(bounds.getX(), bounds.getY(),
                bounds.getWidth(), bounds.getHeight());
   }

/* Private instance variables */

   private double frameWidth;
   private double frameHeight;
   private boolean isFilled;
   private Color fillColor;

/* Serial version UID */
/**
 * The serialization code for this class.  This value should be incremented
 * whenever you change the structure of this class in an incompatible way,
 * typically by adding a new instance variable.
 */

   static final long serialVersionUID = 21L;

}
