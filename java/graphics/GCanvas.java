/*
 * @(#)GCanvas.java   2.03.1 05/26/14
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
import java.awt.Component;
import java.awt.Dimension;
import java.awt.Graphics;
import java.awt.event.MouseEvent;
import java.awt.event.MouseListener;
import java.awt.event.MouseMotionListener;
import java.util.Iterator;
import javax.swing.JComponent;

/**
 * The <code>GCanvas</code> class is a lightweight component that also
 * serves as a container for graphical objects.  As such, this class
 * provides the link between graphical objects and the window system.
 * Conceptually, the <code>GCanvas</code> provides a background canvas
 * to which other graphical objects can be added.
 */

public class GCanvas extends JComponent
implements GContainer, Iterable<GObject> {

/**
 * Creates an empty <code>GCanvas</code> with a default preferred size.
 *
 */

   public GCanvas() {
      this(DEFAULT_WIDTH, DEFAULT_HEIGHT);
   }

/**
 * Creates a new <code>GCanvas</code> and sets its preferred and current
 * size values to the specified width and height.
 *
 * @param width The preferred width of the <code>GCanvas</code>
 * @param height The preferred height of the <code>GCanvas</code>
 */

   public GCanvas(double width, double height) {
      contents = new GObjectList(this);
      setBackground(Color.WHITE);
      setForeground(Color.BLACK);
      setOpaque(true);
      setAutoRepaintFlag(true);
      setNativeArcFlag(false);
      setLayout(null);
      gCanvasListener = new GCanvasListener(this);
      addMouseListener(gCanvasListener);
      addMouseMotionListener(gCanvasListener);
      Dimension size = new Dimension(GMath.round(width), GMath.round(height));
      setPreferredSize(size);
      setSize(size);
   }

/**
 * Adds the graphical object to this canvas.
 *
 * @param gobj The graphical object to add
 */

   public void add(GObject gobj) {
      contents.add(gobj);
      conditionalRepaint();
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
 * Adds the graphical object to this canvas and sets its location to
 * the specified point.
 *
 * @param gobj The graphical object to add
 * @param pt A <code>GPoint</code> object giving the coordinates of the point
 */

   public final void add(GObject gobj, GPoint pt) {
      add(gobj, pt.getX(), pt.getY());
   }

/**
 * Removes a graphical object from this <code>GCanvas</code>.
 *
 * @param gobj The graphical object to remove
 */

   public void remove(GObject gobj) {
      contents.remove(gobj);
      conditionalRepaint();
   }

/**
 * Removes all graphical objects from this <code>GCanvas</code>.
 *
 */

   public void removeAll() {
      contents.removeAll();
      super.removeAll();
      repaint();
   }

/**
 * Adds the component to this canvas without changing its location.
 * If the component has no size, its size is set to its preferred size.
 * The return type is <code>Component</code> to match the method in
 * the <code>Container</code> class, but the result is typically
 * ignored.
 *
 * @param comp The component to add
 */

   public Component add(Component comp) {
      super.add(comp);
      Dimension size = comp.getSize();
      if (size.width == 0 || size.height == 0) {
         Dimension preferredSize = comp.getPreferredSize();
         if (size.width == 0) size.width = preferredSize.width;
         if (size.height == 0) size.height = preferredSize.height;
         comp.setSize(size);
      }
      return comp;
   }

/**
 * Adds the component to this canvas and sets its location
 * to the point (<code>x</code>,&nbsp;<code>y</code>).
 *
 * @param comp The component to add
 * @param x The new x-coordinate for the object
 * @param y The new y-coordinate for the object
 */

   public final void add(Component comp, double x, double y) {
      comp.setLocation(GMath.round(x), GMath.round(y));
      add(comp);
   }

/**
 * Adds the component to this canvas and sets its location to the
 * specified point.
 *
 * @param comp The component to add
 * @param pt A <code>GPoint</code> object giving the coordinates of the point
 */

   public final void add(Component comp, GPoint pt) {
      add(comp, pt.getX(), pt.getY());
   }

/**
 * Removes the component from the canvas.
 *
 * @param comp The component to remove
 */

   public void remove(Component comp) {
      super.remove(comp);
      conditionalRepaint();
   }

/**
 * Returns the number of graphical objects stored in this
 * <code>GCanvas</code>.
 *
 * @return The number of graphical objects in this <code>GCanvas</code>
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
 * object exists.
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
 * Sets the preferred size for the window.
 *
 * @param width The preferred width of the window
 * @param height The preferred height of the window
 */

   public final void setPreferredSize(double width, double height) {
      setPreferredSize(new Dimension((int) Math.round(width),
                                     (int) Math.round(height)));
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
      return new GIterator(this, direction);
   }

/**
 * Paints the component on the canvas.  This method is not ordinarily
 * called by clients.  The override of the standard Swing paint method
 * is necessary only to clear the background.
 *
 * @param g The graphics context into which the canvas is painted
 * @noshow
 */

   public void paint(Graphics g) {
      if (isOpaque()) {
         g.setColor(getBackground());
         g.fillRect(0, 0, getWidth(), getHeight());
         g.setColor(getForeground());
      }
      super.paint(g);
   }

/**
 * Paints the <code>GObject</code> components on the canvas.  This method
 * is not ordinarily called by clients.
 *
 * @param g The graphics context into which the canvas is painted
 * @noshow
 */

   public void paintComponent(Graphics g) {
      contents.mapPaint(g);
      super.paintComponent(g);
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
      autoRepaint = state;
   }

/**
 * Returns the current setting of the auto-repaint flag as described in
 * <a href="#setAutoRepaintFlag(boolean)"><code>setAutoRepaintFlag</code></a>.
 *
 * @return <code>true</code> if auto-repaint mode is enabled, and
 *         <code>false</code> otherwise
 */

   public boolean getAutoRepaintFlag() {
      return autoRepaint;
   }

/**
 * Sets the obsolete "native arc" flag.  All arcs and ovals are now
 * rendered using <code>Graphics2D</code> shapes.
 *
 * @param state <code>true</code> to enable native arcs,
 *              <code>false</code> to use polygons
 */

   public void setNativeArcFlag(boolean state) {
      nativeArcFlag = state;
   }

/**
 * Returns the current setting of the native-arc flag as described in
 * <a href="#setNativeArcFlag(boolean)"><code>setNativeArcFlag</code></a>.
 *
 * @return <code>true</code> if native arcs are enabled, and
 *         <code>false</code> otherwise
 */

   public boolean getNativeArcFlag() {
      return nativeArcFlag;
   }

/**
 * Implements the <code>sendToFront</code> function from the
 * <code>GContainer</code> interface.  Clients should not call this
 * method, but the semantics of interfaces forces it to be exported.
 * @noshow
 */

   protected void sendToFront(GObject gobj) {
      contents.sendToFront(gobj);
      conditionalRepaint();
   }

/**
 * Implements the <code>sendToBack</code> function from the
 * <code>GContainer</code> interface.  Clients should not call this
 * method, but the semantics of interfaces forces it to be exported.
 * @noshow
 */

   protected void sendToBack(GObject gobj) {
      contents.sendToBack(gobj);
      conditionalRepaint();
   }

/**
 * Implements the <code>sendForward</code> function from the
 * <code>GContainer</code> interface.  Clients should not call this
 * method, but the semantics of interfaces forces it to be exported.
 * @noshow
 */

   protected void sendForward(GObject gobj) {
      contents.sendForward(gobj);
      conditionalRepaint();
   }

/**
 * Implements the <code>sendBackward</code> function from the
 * <code>GContainer</code> interface.  Clients should not call this
 * method, but the semantics of interfaces forces it to be exported.
 * @noshow
 */

   protected void sendBackward(GObject gobj) {
      contents.sendBackward(gobj);
      conditionalRepaint();
   }

/**
 * Dispatches this mouse event to the uppermost graphical object for which
 * the active point is within the object bounds.
 *
 * @param e The event that triggered this response
 * @noshow
 */

   protected void dispatchMouseEvent(MouseEvent e) {
      GObject gobj = contents.getElementAt(e.getX(), e.getY(), true);
      MouseEvent newEvent = null;
      if (gobj != lastObject) {
         if (lastObject != null) {
            newEvent = new GMouseEvent(lastObject, MouseEvent.MOUSE_EXITED, e);
            lastObject.fireMouseListeners(newEvent);
         }
         if (gobj != null) {
            newEvent = new GMouseEvent(gobj, MouseEvent.MOUSE_ENTERED, e);
            gobj.fireMouseListeners(newEvent);
         }
      }
      lastObject = gobj;
      if (dragObject != null) gobj = dragObject;
      if (gobj != null) {
         int id = e.getID();
         if (id != MouseEvent.MOUSE_EXITED && id != MouseEvent.MOUSE_ENTERED) {
            if (id != MouseEvent.MOUSE_DRAGGED || dragObject != null) {
               if (id == MouseEvent.MOUSE_PRESSED) {
                  dragObject = gobj;
               } else if (id == MouseEvent.MOUSE_RELEASED) {
                  dragObject = null;
               }
               newEvent = new GMouseEvent(gobj, id, e);
               gobj.fireMouseListeners(newEvent);
            }
         }
      }
      if (newEvent != null && newEvent.isConsumed()) e.consume();
   }

/**
 * Repaints the canvas if auto-repaint is in effect.  This method is called
 * only by the <a href="GObject.html#repaint()"><code>repaint</code></a>
 * method in <code>GObject</code> and is not accessible outside the package.
 *
 * @noshow
 */

   protected void conditionalRepaint() {
      if (autoRepaint) repaint();
   }

/**
 * Reconstructs the enabledList list in the correct order.
 *
 */

   protected void updateEnabledList() {
      contents.updateEnabledList();
   }

/**
 * Creates a new <code>GMouseEvent</code> object with <code>gobj</code>
 * effective source and <code>eventID</code>; all other fields are
 * copied from the event <code>e</code>.  This method must be included
 * in this class to avoid cross-file references to GMouseEvent from
 * the GCompound class.
 */

   static MouseEvent createMouseEvent(Object gobj, int eventID, MouseEvent e) {
      return new GMouseEvent(gobj, eventID, e);
   }

/* Constants */

   private static final int DEFAULT_WIDTH = 500;
   private static final int DEFAULT_HEIGHT = 300;

/* Private instance variables */

   private GCanvasListener gCanvasListener;
   private GObject lastObject;
   private GObject dragObject;
   private GObjectList contents;
   private boolean autoRepaint;
   private boolean nativeArcFlag;

}

/**
 * This class fields mouse events that occur in the <code>GCanvas</code>.
 */

class GCanvasListener implements MouseListener, MouseMotionListener {

/**
 * Creates a new listener object that watches for mouse events in the
 * <code>GCanvas</code>.
 *
 * @param gc The <code>GCanvas</code> object to which this listens
 */

   public GCanvasListener(GCanvas gc) {
      gCanvas = gc;
   }

/* MouseListener interface */

   public void mouseClicked(MouseEvent e) { gCanvas.dispatchMouseEvent(e); }
   public void mousePressed(MouseEvent e) {
      gCanvas.requestFocus();
      gCanvas.dispatchMouseEvent(e);
   }
   public void mouseReleased(MouseEvent e) { gCanvas.dispatchMouseEvent(e); }
   public void mouseEntered(MouseEvent e) { gCanvas.dispatchMouseEvent(e); }
   public void mouseExited(MouseEvent e) { gCanvas.dispatchMouseEvent(e); }

/* MouseMotionListener interface */

   public void mouseDragged(MouseEvent e) { gCanvas.dispatchMouseEvent(e); }
   public void mouseMoved(MouseEvent e) { gCanvas.dispatchMouseEvent(e); }

/* Private instance variables */

   private GCanvas gCanvas;

}

class GMouseEvent extends MouseEvent {

/**
 * Creates a new <code>GMouseEvent</code> object with <code>gobj</code>
 * effective source and <code>eventID</code>; all other fields are
 * copied from the event <code>e</code>.
 */

   public GMouseEvent(Object gobj, int eventID, MouseEvent e) {
      super(e.getComponent(), eventID, e.getWhen(), e.getModifiersEx(),
            e.getX(), e.getY(), e.getClickCount(), e.isPopupTrigger());
      effectiveSource = gobj;
   }

/**
 * Overrides <code>getSource</code> to return the effective source of this
 * event, which will typically be a <code>GObject</code> rather than the
 * <code>GCanvas</code> that triggered the event.
 */

   public Object getSource() {
      return effectiveSource;
   }

/**
 * Overrides <code>getComponent</code> to return the <code>GCanvas</code>
 * that triggered the event.
 */

   public Component getComponent() {
      return (Component) super.getSource();
   }

/**
 * Overrides <code>toString</code> to display the correct source for this
 * event.
 */

   public String toString() {
      return getClass().getName() + "[" + paramString() + "] on "
                                  + getSource();
   }

/* Private instance variables */

   private Object effectiveSource;

}
