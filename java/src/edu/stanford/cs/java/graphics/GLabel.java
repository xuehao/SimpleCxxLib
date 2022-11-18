/*
 * @(#)GLabel.java   2.03.1 05/26/14
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

import java.awt.Component;
import java.awt.Font;
import java.awt.FontMetrics;
import java.awt.Graphics2D;
import java.awt.Shape;
import java.awt.geom.AffineTransform;
import java.awt.geom.Rectangle2D;

/**
 * The <code>GLabel</code> class is a graphical object whose appearance
 * consists of a text string.
 */

public class GLabel extends GObject {

/**
 * The default font used to display strings.  You can change the font by
 * invoking the <a href="#setFont(Font)"><code>setFont</code></a> method.
 */

   public static final Font DEFAULT_FONT = new Font("Default", Font.PLAIN, 12);

/**
 * Creates a new <code>GLabel</code> object initialized to contain the
 * specified string.
 *
 * @param str The initial contents of the <code>GLabel</code>
 */

   public GLabel(String str) {
      this(str, 0, 0);
   }

/**
 * Creates a new <code>GLabel</code> object with its baseline origin at the
 * specified position.
 *
 * @param str The initial contents of the <code>GLabel</code>
 * @param x The x-coordinate of the label origin
 * @param y The y-coordinate of the baseline for the label
 */

   public GLabel(String str, double x, double y) {
      label = str;
      setFont(DEFAULT_FONT);
      setLocation(x, y);
   }

/**
 * Changes the font used to display the <code>GLabel</code>.  This call
 * will usually change the size of the displayed object and will
 * therefore affect the result of calls to
 * <a href="GObject.html#getSize()"><code>getSize</code></a>
 * and <a href="GObject.html#getBounds()"><code>getBounds</code></a>.
 *
 * @param font A <code>Font</code> object indicating the new font
 */

   public void setFont(Font font) {
      labelFont = font;
      repaint();
   }

/**
 * Changes the font used to display the <code>GLabel</code> as specified by
 * the string <code>str</code>, which is interpreted in the style of
 * <code>Font.decode</code>.  The usual format of the font string is
 *
 *<pre>
 *    family-style-size
 *</pre>
 *
 * where both <code>style</code> and <code>size</code> are optional.
 * If any of these parts are specified as an asterisk, the existing
 * value is retained.
 *
 * @param str A <code>String</code> specifying the new font
 */

   public void setFont(String str) {
      setFont(Font.decode(str));
   }

/**
 * Returns the font in which the <code>GLabel</code> is displayed.
 *
 * @return The font in use by this object
 */

   public Font getFont() {
      return labelFont;
   }

/**
 * Changes the string stored within the <code>GLabel</code> object, so that
 * a new text string appears on the display.
 *
 * @param str The new string to display
 */

   public void setLabel(String str) {
      label = str;
      repaint();
   }

/**
 * Returns the string displayed by this object.
 *
 * @return The string displayed by this object
 */

   public String getLabel() {
      return label;
   }

/**
 * Implements the <code>paint2d</code> operation for this graphical object.
 * This method is not called directly by clients.
 * @noshow
 */

   protected void paint2d(Graphics2D g) {
      g.setFont(labelFont);
      g.drawString(label, 0, 0);
   }

/**
 * Returns the distance this string extends above the baseline.
 *
 * @return The ascent of this string in pixels
 */

   public double getAscent() {
      return getFontMetrics().getAscent();
   }

/**
 * Returns the distance this string descends below the baseline.
 *
 * @return The descent of this string in pixels
 */

   public double getDescent() {
      return getFontMetrics().getDescent();
   }

/**
 * Returns a <code>FontMetrics</code> object describing the dimensions of
 * this string.
 *
 * @return A <code>FontMetrics</code> object describing the dimensions of
 *         this string
 * @noshow
 */

   public FontMetrics getFontMetrics() {
      Component comp = getComponent();
      if (comp == null) comp = DUMMY_COMPONENT;
      return comp.getFontMetrics(labelFont);
   }

/**
 * Returns a <code>GRectangle</code> that specifies the bounding box for
 * the string.
 *
 * @return The bounding box for this object
 */

   public GRectangle getBounds() {
      FontMetrics fm = getFontMetrics();
      Shape shape = new Rectangle2D.Double(0, -fm.getAscent(),
                                           fm.stringWidth(label),
                                           fm.getHeight());
      AffineTransform matrix = getMatrix();
      if (matrix != null) shape = matrix.createTransformedShape(shape);
      Rectangle2D rect = shape.getBounds();
      return new GRectangle(getX() + rect.getX(), getY() + rect.getY(),
                            rect.getWidth(), rect.getHeight());
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
      FontMetrics fm = getFontMetrics();
      Shape shape = new Rectangle2D.Double(0, -fm.getAscent(),
                                           fm.stringWidth(label),
                                           fm.getHeight());
      AffineTransform matrix = getMatrix();
      if (matrix != null) shape = matrix.createTransformedShape(shape);
      return shape.contains(x - getX(), y - getY());
   }

/**
 * Returns a string indicating the parameters of this object.
 * @noshow
 */

   public String paramString() {
      return super.paramString() + ", string=\"" + label + "\"";
   }

/* Private instance variables */

   private String label;
   private Font labelFont;

   private static final Component
     DUMMY_COMPONENT = GImageTools.getImageObserver();

/* Serial version UID */
/**
 * The serialization code for this class.  This value should be incremented
 * whenever you change the structure of this class in an incompatible way,
 * typically by adding a new instance variable.
 */

   static final long serialVersionUID = 21L;

}
