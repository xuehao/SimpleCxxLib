/*
 * @(#)GCompound.java   2.03.1 05/26/14
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
import java.awt.Shape;
import java.awt.event.MouseEvent;
import java.awt.geom.AffineTransform;
import java.awt.geom.NoninvertibleTransformException;
import java.awt.geom.Point2D;
import java.awt.geom.Rectangle2D;
import java.util.Iterator;

/**
 * This class defines a graphical object that consists of a collection
 * of other graphical objects.  Once assembled, the internal objects
 * can be manipulated as a unit.
 */

public class GCompound extends GObject
implements GContainer, Iterable<GObject> {

/**
 * Creates a new <code>GCompound</code> object with no internal components.
 *
 */

   public GCompound() {
      contents = new GObjectList(this);
      complete = false;
   }

/**
 * Adds a new graphical object to this <code>GCompound</code>.
 *
 * @param gobj The graphical object to add
 */

   public void add(GObject gobj) {
      if (complete) {
         throw new RuntimeException("You can't add objects to a GCompound "
                                  + "that has been marked as complete.");
      }
      contents.add(gobj);
      repaint();
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
      gobj.setLocation(x, y);
      add(gobj);
   }

/**
 * Adds the graphical object to this canvas and sets its location to the
 * specified point.
 *
 * @param gobj The graphical object to add
 * @param pt A <code>GPoint</code> object giving the coordinates of the point
 */

   public final void add(GObject gobj, GPoint pt) {
      add(gobj, pt.getX(), pt.getY());
   }

/**
 * Removes a graphical object from this <code>GCompound</code>.
 *
 * @param gobj The graphical object to remove
 */

   public void remove(GObject gobj) {
      if (complete) {
         throw new RuntimeException("You can't remove objects from a GCompound "
                                  + "that has been marked as complete.");
      }
      contents.remove(gobj);
      repaint();
   }

/**
 * Removes all graphical objects from this <code>GCompound</code>.
 *
 */

   public void removeAll() {
      if (complete) {
         throw new RuntimeException("You can't remove objects from a GCompound "
                                  + "that has been marked as complete.");
      }
      contents.removeAll();
      repaint();
   }

/**
 * Returns the number of graphical objects stored in this container.
 *
 * @return The number of graphical objects in this container
 */

   public int getElementCount() {
      return contents.getElementCount();
   }

/**
 * Returns the graphical object at the specified index, numbering from back
 * to front in the the <i>z</i> dimension.
 *
 * @param index The index of the component to return
 * @return The graphical object at the specified index
 */

   public GObject getElement(int index) {
      return contents.getElement(index);
   }

/**
 * Returns the topmost graphical object that contains the point
 * (<code>x</code>, <code>y</code>), or <code>null</code> if no such
 * object exists.  Note that these coordinates are relative to the
 * location of the compound object and not to the canvas in which
 * it is displayed.
 *
 * @param x The x-coordinate of the point being tested
 * @param y The y-coordinate of the point being tested
 * @return The graphical object at the specified location, or
 *         <code>null</code> if no such object exists
 */

   public GObject getElementAt(double x, double y) {
      return contents.getElementAt(x, y, false);
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
      return getElementAt(pt.getX(), pt.getY());
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
      return new GIterator(this, GContainer.BACK_TO_FRONT);
   }

/**
 * Returns an <code>Iterator</code> that cycles through the elements
 * within this container in the specified direction, which must be one
 * of the constants <a href="GContainer.html#FRONT_TO_BACK"
 * ><code>GContainer.FRONT_TO_BACK</code></a> or
 * <a href="GContainer.html#BACK_TO_FRONT"
 * ><code>GContainer.BACK_TO_FRONT</code></a>.<p>
 *
 * @return An <code>Iterator</code> ranging over the elements of the
 *         container in the specified direction
 */

   public Iterator<GObject> iterator(int direction) {
      return new GIterator(this, direction);
   }

/**
 * Overrides <code>clone</code> in <code>GObject</code> to make sure that
 * the contents vector is copied.
 *
 * @noshow
 */

   public Object clone() {
      try {
         GCompound clone = (GCompound) super.clone();
         clone.contents = new GObjectList(clone, contents);
for (int i = 0; i < contents.getElementCount(); i++) {
    System.err.println("original = " + contents.getElement(i).hashCode());
    System.err.println("clone    = " + clone.contents.getElement(i).hashCode());

}
         return clone;
      } catch (Exception CloneNotSupportedException) {
         throw new RuntimeException("Impossible exception");
      }
   }

/**
 * Implements the <code>paint2d</code> operation for this graphical object.
 * This method is not called directly by clients.
 * @noshow
 */

   protected void paint2d(Graphics2D g) {
      contents.mapPaint(g);
   }

/**
 * Returns the bounding rectangle for this compound object, which consists of
 * the union of the bounding rectangles for each of the components.
 *
 * @return A <code>GRectangle</code> that bounds the components of this object
 */

   public GRectangle getBounds() {
      GRectangle bounds = contents.getBounds();
      Shape shape = new Rectangle2D.Double(bounds.getX(), bounds.getY(),
                                           bounds.getWidth(),
                                           bounds.getHeight());
      AffineTransform matrix = getMatrix();
      if (matrix != null) shape = matrix.createTransformedShape(shape);
      Rectangle2D rect = shape.getBounds();
      return new GRectangle(getX() + rect.getX(), getY() + rect.getY(),
                            rect.getWidth(), rect.getHeight());
   }

/**
 * Checks to see whether a point is "inside" the compound, which means
 * that it is inside one of the components.
 *
 * @param x The x-coordinate of the point being tested
 * @param y The y-coordinate of the point being tested
 * @return <code>true</code> if the point (<code>x</code>,&nbsp;<code>y</code>)
 *         is inside the compound, and <code>false</code> otherwise
 */

   public boolean contains(double x, double y) {
      x -= getX();
      y -= getY();
      AffineTransform matrix = getMatrix();
      if (matrix != null) {
         try {
            matrix = matrix.createInverse();
            Point2D pt = new Point2D.Double(x, y);
            matrix.transform(pt, pt);
            x = pt.getX();
            y = pt.getY();
         } catch (NoninvertibleTransformException ex) {
            throw new RuntimeException(ex);
         }
      }
      return contents.contains(x, y);
   }

/**
 * Converts the location of the specified point in this compound to
 * the corresponding point in the enclosing canvas.
 *
 * @param localPoint The coordinates in the space of the compound
 * @return The coordinates in the space of the enclosing <code>GCanvas</code>
 */

   public final GPoint getCanvasPoint(GPoint localPoint) {
      return getCanvasPoint(localPoint.getX(), localPoint.getY());
   }

/**
 * Converts the location of the specified point in this compound to
 * the corresponding point in the enclosing canvas.
 *
 * @param x The x coordinate in the space of the compound
 * @param y The y coordinate in the space of the compound
 * @return The coordinates in the space of the enclosing <code>GCanvas</code>
 */

   public GPoint getCanvasPoint(double x, double y) {
      // Add transformation code
      for (GContainer c = this; c instanceof GCompound; ) {
         GCompound comp = (GCompound) c;
         x += comp.getX();
         y += comp.getY();
         c = comp.getParent();
      }
      return new GPoint(x, y);
   }

/**
 * Converts the location of the specified point on the enclosing canvas
 * to the corresponding point in the space of this compound.
 *
 * @param canvasPoint The coordinates in the space of the enclosing
 *                    <code>GCanvas</code>
 * @return The coordinates in the space of the compound
 */

   public final GPoint getLocalPoint(GPoint canvasPoint) {
      return getLocalPoint(canvasPoint.getX(), canvasPoint.getY());
   }

/**
 * Converts the specified point on the enclosing canvas to the
 * corresponding point in the space of this compound.
 *
 * @param x The x coordinate in the space of the space of the enclosing
 *          <code>GCanvas</code>
 * @param y The y coordinate in the space of the space of the enclosing
 *          <code>GCanvas</code>
 * @return The coordinates in the space of the compound
 */

   public GPoint getLocalPoint(double x, double y) {
      // Add transformation code
      for (GContainer c = this; c instanceof GCompound; ) {
         GCompound comp = (GCompound) c;
         x -= comp.getX();
         y -= comp.getY();
         c = comp.getParent();
      }
      return new GPoint(x, y);
   }

/**
 * Calling this method makes it illegal to add or remove elements from the
 * compound object.  Subclasses can invoke this method to protect the
 * integrity of the structure from changes by the client.
 *
 */

   public void markAsComplete() {
      complete = true;
   }

/**
 * Implements the <code>sendToFront</code> function from the
 * <code>GContainer</code> interface.  Clients should not call this
 * method, but the semantics of interfaces forces it to be exported.
 * @noshow
 */

   protected void sendToFront(GObject gobj) {
      contents.sendToFront(gobj);
      repaint();
   }

/**
 * Implements the <code>sendToBack</code> function from the
 * <code>GContainer</code> interface.  Clients should not call this
 * method, but the semantics of interfaces forces it to be exported.
 * @noshow
 */

   protected void sendToBack(GObject gobj) {
      contents.sendToBack(gobj);
      repaint();
   }

/**
 * Implements the <code>sendForward</code> function from the
 * <code>GContainer</code> interface.  Clients should not call this
 * method, but the semantics of interfaces forces it to be exported.
 * @noshow
 */

   protected void sendForward(GObject gobj) {
      contents.sendForward(gobj);
      repaint();
   }

/**
 * Implements the <code>sendBackward</code> function from the
 * <code>GContainer</code> interface.  Clients should not call this
 * method, but the semantics of interfaces forces it to be exported.
 * @noshow
 */

   protected void sendBackward(GObject gobj) {
      contents.sendBackward(gobj);
      repaint();
   }

/**
 * Dispatches a mouse event to the topmost child that covers the location
 * in the event <code>e</code>.
 * @noshow
 */

   protected void fireMouseListeners(MouseEvent e) {
      if (super.areMouseListenersEnabled()) {
         super.fireMouseListeners(e);
         return;
      }
      GPoint pt = new GPoint(e.getX() - getX(), e.getY() - getY());
      GObject gobj = getElementAt(pt);
      MouseEvent newEvent = null;
      if (gobj != lastObject) {
         if (lastObject != null) {
            newEvent = GCanvas.createMouseEvent(lastObject,
                                                MouseEvent.MOUSE_EXITED, e);
            lastObject.fireMouseListeners(newEvent);
         }
         if (gobj != null) {
            newEvent = GCanvas.createMouseEvent(gobj,
                                                MouseEvent.MOUSE_ENTERED, e);
            gobj.fireMouseListeners(newEvent);
         }
      }
      lastObject = gobj;
      if (dragObject != null) gobj = dragObject;
      if (gobj != null) {
         int id = e.getID();
         if (id != MouseEvent.MOUSE_EXITED && id != MouseEvent.MOUSE_ENTERED) {
            if (id == MouseEvent.MOUSE_PRESSED) {
               dragObject = gobj;
            } else if (id == MouseEvent.MOUSE_RELEASED) {
               dragObject = null;
            }
            newEvent = GCanvas.createMouseEvent(gobj, id, e);
            gobj.fireMouseListeners(newEvent);
         }
      }
      if (newEvent != null && newEvent.isConsumed()) e.consume();
   }

/**
 * Returns <code>true</code> if mouse listeners have ever been assigned to
 * this object or to any of the contained objects.
 *
 * @return <code>true</code> if mouse listeners have been enabled in
 *         this object
 * @noshow
 */

   protected boolean areMouseListenersEnabled() {
      if (super.areMouseListenersEnabled()) return true;
      return contents.areMouseListenersEnabled();
   }

/* Private instance variables */

   private boolean complete;
   private GObjectList contents;
   private transient GObject lastObject;
   private transient GObject dragObject;

/* Serial version UID */
/**
 * The serialization code for this class.  This value should be incremented
 * whenever you change the structure of this class in an incompatible way,
 * typically by adding a new instance variable.
 */

   static final long serialVersionUID = 21L;

}
