/*
 * @(#)GWindow.java   2.03.1 05/26/14
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

import java.awt.BorderLayout;
import java.util.Iterator;
import javax.swing.JFrame;

/**
 * The <code>GWindow</code> class is a <code>JFrame</code> containing
 * a <code>GCanvas</code> designed to support the use of the ACM graphics
 * library without the rest of the ACM packages.
 */

public class GWindow extends JFrame implements Iterable<GObject> {

/**
 * Creates a new <code>GWindow</code> with a default preferred size.
 *
 */

   public GWindow() {
      this(new GCanvas());
   }

/**
 * Creates a new <code>GWindow</code> and sets the size of its canvas
 * to the specified width and height.
 *
 * @param width The preferred width of the embedded <code>GCanvas</code>
 * @param height The preferred height of the embedded <code>GCanvas</code>
 */

   public GWindow(double width, double height) {
      this(new GCanvas(width, height));
   }

/**
 * Creates a new <code>GWindow</code> containing the specified
 * <code>GCanvas</code>.
 *
 * @param gc The embedded <code>GCanvas</code>
 */

   public GWindow(GCanvas gc) {
      super("Graphics Window");
      this.gc = gc;
      setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
      setLayout(new BorderLayout());
      add(gc, BorderLayout.CENTER);
      pack();
      setVisible(true);
   }

/**
 * Returns the embedded <code>GCanvas</code> object.
 *
 * @return The embedded <code>GCanvas</code>
 */

   public GCanvas getGCanvas() {
      return gc;
   }

/**
 * Gets the width of the embedded GCanvas.
 *
 * @return The width of the embedded GCanvas
 */

   public double getCanvasWidth() {
      return gc.getWidth();
   }

/**
 * Gets the height of the embedded GCanvas.
 *
 * @return The height of the embedded GCanvas
 */

   public double getCanvasHeight() {
      return gc.getHeight();
   }

/**
 * Adds the graphical object to this canvas.
 *
 * @param gobj The graphical object to add
 */

   public void add(GObject gobj) {
      gc.add(gobj);
   }

/**
 * Adds the graphical object to this canvas and sets its location
 * to the point (<code>x</code>,&nbsp;<code>y</code>).
 *
 * @param gobj The graphical object to add
 * @param x The new x-coordinate for the object
 * @param y The new y-coordinate for the object
 */

   public final void add(GObject gobj, double x, double y) {
      gc.add(gobj, x, y);
   }

/**
 * Adds the graphical object to this canvas and sets its location to
 * the specified point.
 *
 * @param gobj The graphical object to add
 * @param pt A <code>GPoint</code> object giving the coordinates of the point
 */

   public final void add(GObject gobj, GPoint pt) {
      gc.add(gobj, pt);
   }

/**
 * Removes a graphical object from this <code>GWindow</code>.
 *
 * @param gobj The graphical object to remove
 */

   public void remove(GObject gobj) {
      gc.remove(gobj);
   }

/**
 * Returns the number of graphical objects stored in this <code>GWindow</code>.
 *
 * @return The number of graphical objects in this <code>GWindow</code>
 */

   public int getElementCount() {
      return gc.getElementCount();
   }

/**
 * Returns the graphical object at the specified index, numbering from back
 * to front in the the <i>z</i> dimension.
 *
 * @param index The index of the component to return
 * @return The graphical object at the specified index
 */

   public GObject getElement(int index) {
      return gc.getElement(index);
   }

/**
 * Returns the topmost graphical object that contains the point
 * (<code>x</code>, <code>y</code>), or <code>null</code> if no such
 * object exists.
 *
 * @param x The x-coordinate of the point being tested
 * @param y The y-coordinate of the point being tested
 * @return The graphical object at the specified location, or
 *         <code>null</code> if no such object exists
 */

   public GObject getElementAt(double x, double y) {
      return gc.getElementAt(x, y);
   }

/**
 * Returns the topmost graphical object that contains the specified point,
 * or <code>null</code> if no such object exists.
 *
 * @param pt The coordinates being tested
 * @return The graphical object at the specified location, or
 *         <code>null</code> if no such object exists
 */

   public final GObject getElementAt(GPoint pt) {
      return gc.getElementAt(pt);
   }

/**
 * Returns an <code>Iterator</code> that cycles through the elements within
 * this container in the default direction, which is from back to front.
 * You can also run the iterator in the opposite direction by using the
 * <a href="#iterator(int)"><code>iterator</code></a><code>(</code><font
 * size=-1><i>direction</i></font><code>)</code> form of this method.
 *
 * @return An <code>Iterator</code> ranging over the elements of the
 *         container from back to front
 */

   public Iterator<GObject> iterator() {
      return gc.iterator();
   }

/**
 * Returns an <code>Iterator</code> that cycles through the elements within
 * this container in the specified direction, which must be one of the
 * constants <a href="GContainer.html#FRONT_TO_BACK"
 * ><code>GContainer.FRONT_TO_BACK</code></a> or
 * <a href="GContainer.html#BACK_TO_FRONT"
 * ><code>GContainer.BACK_TO_FRONT</code></a>.<p>
 *
 * @return An <code>Iterator</code> ranging over the elements of the
 *         container in the specified direction
 */

   public Iterator<GObject> iterator(int direction) {
      return gc.iterator(direction);
   }

/**
 * Changes the setting of the auto-repaint flag.  By default, any change to a
 * graphical object contained in this canvas automatically triggers a repaint
 * of the canvas as a whole.  While this behavior makes it much easier to use
 * the package, it has the disadvantage that repaint requests come much more
 * frequently than necessary.  You can disable this feature by calling
 * <code>setAutoRepaintFlag(false)</code>, but you must then make explicit
 * calls to <code>repaint()</code> whenever you want to update the display.
 * The advantage of this model is that you can then make many different changes
 * and have them all appear at once with a single <code>repaint</code> call.
 *
 * @param state <code>true</code> to enable auto-repaint mode, and
 *              <code>false</code> to disable it
 */

   public void setAutoRepaintFlag(boolean state) {
      gc.setAutoRepaintFlag(state);
   }

/**
 * Returns the current setting of the auto-repaint flag as described in
 * <a href="#setAutoRepaintFlag(boolean)"><code>setAutoRepaintFlag</code></a>.
 *
 * @return <code>true</code> if auto-repaint mode is enabled, and
 *         <code>false</code> otherwise
 */

   public boolean getAutoRepaintFlag() {
      return gc.getAutoRepaintFlag();
   }

/* Private instance variables */

   private GCanvas gc;

}
