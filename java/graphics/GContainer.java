/*
 * @(#)GContainer.java   2.03.1 05/26/14
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

import java.awt.Graphics;
import java.io.Serializable;
import java.util.ArrayList;
import java.util.Iterator;

/**
 * Defines the functionality of an object that can serve as the parent
 * of a <a href="GObject.html"><code>GObject</code></a>.
 */

public interface GContainer {

/** Specifies that iterators should run from back to front */

   public static final int BACK_TO_FRONT = 0;

/** Specifies that iterators should run from front to back */

   public static final int FRONT_TO_BACK = 1;

/**
 * Adds a new graphical object to this container.
 *
 * @param gobj The graphical object to add
 */

   public void add(GObject gobj);

/**
 * Adds the graphical object to this canvas and sets its location
 * to the point (<code>x</code>,&nbsp;<code>y</code>).
 *
 * @param gobj The graphical object to add
 * @param x The new x-coordinate for the object
 * @param y The new y-coordinate for the object
 */

   public void add(GObject gobj, double x, double y);

/**
 * Adds the graphical object to this canvas and sets its location to the
 * specified point.
 *
 * @param gobj The graphical object to add
 * @param pt A <code>GPoint</code> object giving the coordinates of the point
 */

   public void add(GObject gobj, GPoint pt);

/**
 * Removes a graphical object from this container.
 *
 * @param gobj The graphical object to remove
 */

   public void remove(GObject gobj);

/**
 * Removes all graphical objects from this container.
 *
 */

   public void removeAll();

/**
 * Returns the number of graphical objects stored in this <code>GCanvas</code>.
 *
 * @return The number of graphical objects in this <code>GCanvas</code>
 */

   public int getElementCount();

/**
 * Returns the graphical object at the specified index, numbering from back
 * to front in the the <i>z</i> dimension.
 *
 * @param index The index of the component to return
 * @return The graphical object at the specified index
 */

   public GObject getElement(int index);

/**
 * Returns the topmost graphical object that contains the point
 * (<code>x</code>, <code>y</code>), or <code>null</code> if no such
 * object exists.
 *
 * @param x The x-coordinate of the point being tested
 * @param y The y-coordinate of the point being tested
 * @return The graphical object at the specified location, or <code>null</code>
 *         if no such object exists.
 */

   public GObject getElementAt(double x, double y);

/**
 * Returns the topmost graphical object that contains the specified point,
 * or <code>null</code> if no such object exists.
 *
 * @param pt The coordinates being tested
 * @return The graphical object at the specified location, or <code>null</code>
 *         if no such object exists
 */

   public GObject getElementAt(GPoint pt);

}

/**
 * This class implements a synchronized list of <code>GObject</code> values
 * that is shared by both <code>GCompound</code> and <code>GCanvas</code>.
 * The list includes two sets of objects: one for the ordered list in the
 * container and another for objects that are enabled to receive mouse
 * events.
 */

class GObjectList implements Serializable {

/**
 * Creates a new <code>GObjectList</code> with no elements.
 *
 * @param container The <code>GCanvas</code> or <code>GCompound</code> that
 *                  owns this list.
 */

   public GObjectList(GContainer container) {
      parent = container;
      contents = new ArrayList<GObject>();
      if (parent instanceof GCanvas) enabledList = new ArrayList<GObject>();
   }

/**
 * Creates a <code>GObjectList</code> that is a clone of the specified one.
 * @noshow
 */

   public GObjectList(GContainer container, GObjectList list) {
      parent = container;
      contents = new ArrayList<GObject>();
      enabledList = new ArrayList<GObject>();
      int nElements = list.contents.size();
      for (int i = 0; i < nElements; i++) {
         contents.add((GObject) list.contents.get(i).clone());
      }
   }

/**
 * Adds the specified <code>GObject</code> to the end of the contents list,
 * and includes it in the enabled list if mouse events are enabled.
 */

   public synchronized void add(GObject gobj) {
      if (gobj.getParent() != null) gobj.getParent().remove(gobj);
      gobj.setParent(parent);
      contents.add(gobj);
      if (enabledList != null && gobj.areMouseListenersEnabled()) {
         enabledList.add(gobj);
      }
   }

/**
 * Removes the specified object from the list.
 */

   public synchronized void remove(GObject gobj) {
      contents.remove(gobj);
      gobj.setParent(null);
      if (enabledList != null) enabledList.remove(gobj);
   }

/**
 * Removes all objects from the list.
 */

   public synchronized void removeAll() {
      contents.clear();
      if (enabledList != null) enabledList.clear();
   }

/**
 * Returns the number of elements in the list.
 */

   public int getElementCount() {
      return contents.size();
   }

/**
 * Returns the graphical object at the specified index, numbering from back
 * to front in the the <i>z</i> dimension.
 */

   public GObject getElement(int index) {
      return contents.get(index);
   }

/**
 * Returns the topmost graphical object that contains the point
 * (<code>x</code>, <code>y</code>), or <code>null</code> if no such
 * object exists.
 */

   public synchronized GObject getElementAt(double x, double y,
                                            boolean requireEnabled) {
      ArrayList<GObject> list = (requireEnabled) ? enabledList : contents;
      for (int i = list.size() - 1; i >= 0; i--) {
         GObject gobj = list.get(i);
         if (gobj.contains(x, y)) return gobj;
      }
      return null;
   }

/**
 * Implements the <code>sendToFront</code> function from the
 * <code>GContainer</code> interface.
 */

   public synchronized void sendToFront(GObject gobj) {
      int index = contents.indexOf(gobj);
      if (index >= 0) {
         contents.remove(index);
         contents.add(gobj);
      }
   }

/**
 * Implements the <code>sendToBack</code> function from the
 * <code>GContainer</code> interface.
 */

   public synchronized void sendToBack(GObject gobj) {
      int index = contents.indexOf(gobj);
      if (index >= 0) {
         contents.remove(index);
         contents.add(0, gobj);
      }
   }

/**
 * Implements the <code>sendForward</code> function from the
 * <code>GContainer</code> interface.
 */

   public synchronized void sendForward(GObject gobj) {
      int index = contents.indexOf(gobj);
      if (index >= 0) {
         contents.remove(index);
         contents.add(Math.min(contents.size(), index + 1), gobj);
      }
   }

/**
 * Implements the <code>sendBackward</code> function from the
 * <code>GContainer</code> interface.
 */

   public synchronized void sendBackward(GObject gobj) {
      int index = contents.indexOf(gobj);
      if (index >= 0) {
         contents.remove(index);
         contents.add(Math.max(0, index - 1), gobj);
      }
   }

/**
 * Returns the bounding rectangle for the objects in the list.
 */

   public synchronized GRectangle getBounds() {
      GRectangle bounds = new GRectangle();
      int nElements = contents.size();
      for (int i = 0; i < nElements; i++) {
         if (i == 0) {
            bounds = new GRectangle(contents.get(i).getBounds());
         } else {
            bounds.add(contents.get(i).getBounds());
         }
      }
      return bounds;
   }

/**
 * Checks to see whether a point is "inside" one of the objects on the list.
 */

   public synchronized boolean contains(double x, double y) {
      int nElements = contents.size();
      for (int i = 0; i < nElements; i++) {
         if (contents.get(i).contains(x, y)) return true;
      }
      return false;
   }

/**
 * Paints all the elements of this container using the graphics context
 * <code>g</code>.
 */

   public synchronized void mapPaint(Graphics g) {
      int nElements = contents.size();
      for (int i = 0; i < nElements; i++) {
         contents.get(i).paint(g);
      }
   }

/**
 * Returns <code>true</code> if mouse listeners have ever been assigned to
 * this object or to any of the contained objects.
 */

   public synchronized boolean areMouseListenersEnabled() {
      int nElements = contents.size();
      for (int i = 0; i < nElements; i++) {
         GObject gobj = contents.get(i);
         if (gobj.areMouseListenersEnabled()) return true;
      }
      return false;
   }

/**
 * Reconstructs the enabledList list in the correct order.
 */

   public synchronized void updateEnabledList() {
      enabledList.clear();
      int nElements = contents.size();
      for (int i = 0; i < nElements; i++) {
         GObject gobj = contents.get(i);
         if (gobj.areMouseListenersEnabled()) enabledList.add(gobj);
      }
   }

/* Private instance variables */

   private transient GContainer parent;
   private ArrayList<GObject> contents;
   private ArrayList<GObject> enabledList;

}

/**
 * Implements an iterator class for any object that implements
 * <code>GContainer</code> (<a href="GCanvas.html"><code>GCanvas</code></a>
 * and <a href="GCompound.html"><code>GCompound</code></a>).
 *
 * The enumeration supports traversal in two directions.  By default, it
 * starts with the front element and works toward the back (as would be
 * appropriate, for example, when trying to find the topmost component for
 * a mouse click).  You can, however, also process the elements of the
 * container from back to front (as would be useful when drawing elements
 * of the container, when the front objects should be drawn last).
 * To specify the direction of the traversal, specify either
 * <code>GContainer.FRONT_TO_BACK</code> or
 * <code>GContainer.BACK_TO_FRONT</code> in the <code>iterator</code> call.
 */

class GIterator implements Iterator<GObject> {

/**
 * Creates a new <code>GIterator</code> that runs through the
 * container in the specified direction (<code>GContainer.FRONT_TO_BACK</code>
 * or <code>GContainer.BACK_TO_FRONT</code>).
 *
 * @param container The <code>GContainer</code> whose elements the iterator
 *                  should return
 * @param direction The direction in which to process the elements
 */

   public GIterator(GContainer container, int direction) {
      switch (direction) {
        case GContainer.FRONT_TO_BACK: case GContainer.BACK_TO_FRONT:
         dir = direction;
         break;
        default:
         throw new RuntimeException("Illegal direction for iterator");
      }
      cont = container;
      index = 0;
      nElements = container.getElementCount();
   }

/**
 * Returns <code>true</code> if the iterator has more elements.  Implements
 * the <code>hasNext</code> method for the <code>Iterator</code> interface.
 *
 * @return <code>true</code> if the iterator has more elements,
 *         <code>false</code> otherwise
 */

   public boolean hasNext() {
      return index < nElements;
   }

/**
 * Returns the next element from the iterator.
 *
 * @return The next element from the iterator
 */

   public GObject next() {
      if (dir == GContainer.FRONT_TO_BACK) {
         return cont.getElement(nElements - index++ - 1);
      } else {
         return cont.getElement(index++);
      }
   }

/**
 * Returns the next element from the iterator as a <code>GObject</code>.
 * This method is callable only if the iterator is declared as a
 * <code>GIterator</code>.
 *
 * @return The next element from the iterator as a <code>GObject</code>
 */

   public GObject nextElement() {
      return next();
   }

/**
 * Removes the current element from its container.
 *
 */

   public void remove() {
      if (dir == GContainer.FRONT_TO_BACK) {
         cont.remove(cont.getElement(nElements - --index - 1));
      } else {
         cont.remove(cont.getElement(--index));
      }
      nElements--;
   }

/* Private instance variables */

   private GContainer cont;
   private int dir;
   private int index;
   private int nElements;

}
