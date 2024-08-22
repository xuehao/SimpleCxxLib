/*
 * @(#)G3DRect.java   2.03.1 05/26/14
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
import java.awt.Graphics;

/**
 * The <code>G3DRect</code> class is used to represent a rectangle whose
 * borders are drawn to create a three-dimensional effect.  The
 * <code>G3DRect</code> class is a subclass of
 * <a href="GRect.html"><code>GRect</code></a>, and therefore
 * implements all the methods defined for that class.  In addition, the
 * <code>G3DRect</code> class supports the following methods:
 *
 * <p><table cellpadding=0 cellspacing=0 border=0><tr>
 * <td width=20>&nbsp;</td>
 * <td><table cellpadding=2 cellspacing=0 border=1>
 * <tr><td><code>void setRaised(boolean raised)</code><br>
 * <code>&nbsp;&nbsp;&nbsp;</code>Sets the <code>G3DRect</code> to appear
 * raised or lowered as specified by the parameter</td></tr>
 * <tr><td><code>boolean isRaised()</code><br>
 * <code>&nbsp;&nbsp;&nbsp;</code>Returns <code>true</code> if this
 * <code>G3DRect</code> is raised.</td></tr>
 * </table></td></tr></table>
 * <p>The appearance of a <code>G3DRect</code> object depends on the system on
 * which it is displayed and is typically more effective if the
 * <code>G3DRect</code> is filled.
 */

public class G3DRect extends GRect {

/**
 * Constructs a new 3D rectangle with the specified width and height,
 * positioned at the origin.
 *
 * @param width The width of the rectangle in pixels
 * @param height The height of the rectangle in pixels
 */

   public G3DRect(double width, double height) {
      this(0, 0, width, height, false);
   }

/**
 * Constructs a new 3D rectangle with the specified bounds.
 *
 * @param x The x-coordinate of the upper left corner
 * @param y The y-coordinate of the upper left corner
 * @param width The width of the rectangle in pixels
 * @param height The height of the rectangle in pixels
 */

   public G3DRect(double x, double y, double width, double height) {
      this(x, y, width, height, false);
   }

/**
 * Constructs a new 3D rectangle with the specified bounds which is
 * raised if the final parameter is <code>true</code>.
 *
 * @param x The x-coordinate of the upper left corner
 * @param y The y-coordinate of the upper left corner
 * @param width The width of the rectangle in pixels
 * @param height The height of the rectangle in pixels
 * @param raised <code>true</code> if this rectangle should appear raised
 */

   public G3DRect(double x, double y, double width, double height,
                                      boolean raised) {
      super(x, y, width, height);
      isRaised = raised;
   }

/**
 * Implements the <code>paint</code> operation for this graphical object.
 * This method is not called directly by clients.
 * @noshow
 */

   public void paint(Graphics g) {
      if (!isVisible()) return;
      Graphics2D g2d = createTransformedGraphics(g);
      if (isFilled()) {
         g2d.setColor(getFillColor());
         g2d.fill3DRect(0, 0, GMath.round(getFrameWidth()),
                              GMath.round(getFrameHeight()), isRaised);
         g2d.setColor(getColor());
      }
      g2d.draw3DRect(0, 0, GMath.round(getFrameWidth()),
                           GMath.round(getFrameHeight()), isRaised);
      g2d.dispose();
   }

/**
 * Sets whether this object appears raised.
 *
 * @param raised <code>true</code> if the object appears raised,
 *               <code>false</code> otherwise
 */

   public void setRaised(boolean raised) {
      isRaised = raised;
   }

/**
 * Tests whether this object appears raised.
 *
 * @return <code>true</code> if the object appears raised,
 *         <code>false</code> otherwise
 */

   public boolean isRaised() {
      return isRaised;
   }

/* Private instance variables */

   private boolean isRaised;

/* Serial version UID */
/**
 * The serialization code for this class.  This value should be incremented
 * whenever you change the structure of this class in an incompatible way,
 * typically by adding a new instance variable.
 */

   static final long serialVersionUID = 21L;

}
