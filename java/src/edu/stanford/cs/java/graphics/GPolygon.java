/*
 * @(#)GPolygon.java   2.03.1 05/26/14
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
import java.awt.geom.AffineTransform;
import java.awt.geom.Path2D;
import java.awt.geom.Point2D;
import java.io.Serializable;
import java.util.ArrayList;

/**
 * The <code>GPolygon</code> class is a graphical object whose appearance
 * consists of a polygon.
 */

public class GPolygon extends GObject implements GFillable {

/**
 * Constructs a new empty polygon at the origin.
 *
 */

   public GPolygon() {
      vertices = new VertexList();
      clear();
   }

/**
 * Constructs a new empty polygon at (<code>x</code>, <code>y</code>).
 *
 * @param x The x-coordinate of the origin of the polygon
 * @param y The y-coordinate of the origin of the polygon
 */

   public GPolygon(double x, double y) {
      this();
      setLocation(x, y);
   }

/**
 * Constructs a new polygon from the specified array of <code>GPoint</code>
 * objects.  The polygon is automatically marked as complete.
 *
 * @param points An array of <code>GPoint</code> objects specifying the
 *               vertices
 */

   public GPolygon(GPoint[] points) {
      this();
      vertices.add(points);
      markAsComplete();
   }

/**
 * Adds a vertex at (<code>x</code>, <code>y</code>) relative to the
 * polygon origin.
 *
 * @param x The x-coordinate of the vertex relative to the polygon origin
 * @param y The y-coordinate of the vertex relative to the polygon origin
 */

   public void addVertex(double x, double y) {
      if (complete) {
         throw new RuntimeException("You can't add vertices to a GPolygon that "
                                  + "has been marked as complete.");
      }
      vertices.addVertex(x, y);
   }

/**
 * Adds an edge to the polygon whose components are given by the displacements
 * <code>dx</code> and <code>dy</code> from the last vertex.
 *
 * @param dx The x displacement through which the edge moves
 * @param dy The y displacement through which the edge moves
 */

   public void addEdge(double dx, double dy) {
      if (complete) {
         throw new RuntimeException("You can't add edges to a GPolygon that "
                                  + "has been marked as complete.");
      }
      vertices.addEdge(dx, dy);
   }

/**
 * Adds an edge to the polygon specified in polar coordinates.  The length
 * of the edge is given by <code>r</code>, and the edge extends in
 * direction <code>theta</code>, measured in degrees counterclockwise from
 * the +<i>x</i> axis.
 *
 * @param r The length of the edge
 * @param theta The angle at which the edge extends measured in degrees
 */

   public final void addPolarEdge(double r, double theta) {
      if (complete) {
         throw new RuntimeException("You can't add edges to a GPolygon that "
                                  + "has been marked as complete.");
      }
      vertices.addEdge(r * GMath.cosDegrees(theta),
                       -r * GMath.sinDegrees(theta));
   }

/**
 * Adds a series of edges to the polygon that simulates the arc specified by
 * the parameters.  The <i>x</i> and <i>y</i> parameters for the arc bounding
 * box are computed implicitly by figuring out what values would place the
 * current vertex at the starting position.
 *
 * @param arcWidth The width of the oval from which the arc is taken
 * @param arcHeight The height of the oval from which the arc is taken
 * @param start The angle at which the arc begins
 * @param sweep The extent of the arc
 */

   public void addArc(double arcWidth, double arcHeight,
                      double start, double sweep) {
      if (complete) {
         throw new RuntimeException("You can't add edges to a GPolygon that "
                                  + "has been marked as complete.");
      }
      vertices.addArc(arcWidth, arcHeight, start, sweep);
   }

/**
 * Returns the coordinates of the last vertex added to the polygon,
 * or <code>null</code> if the polygon is empty.
 *
 * @return The last vertex added to the polygon, or <code>null</code> if empty
 */

   public GPoint getCurrentPoint() {
      return vertices.getCurrentPoint();
   }

/**
 * Rotates the polygon around its origin by the angle theta, measured in
 * degrees.
 *
 * @param theta The angle of rotation in degrees counterclockwise
 */

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
 * Returns the bounding box of this object, which is defined to be the
 * smallest rectangle that covers everything drawn by the figure.
 *
 * @return The bounding box for this object
 */

   public GRectangle getBounds() {
      GRectangle bounds = vertices.getBounds(getMatrix());
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
      return vertices.contains(x - getX(), y - getY(), getMatrix());
   }

/**
 * Implements the <code>paint2d</code> operation for this graphical object.
 * This method is not called directly by clients.
 * @noshow
 */

   protected void paint2d(Graphics2D g) {
      int n = vertices.size();
      Path2D path = new Path2D.Double(Path2D.WIND_EVEN_ODD);
      path.moveTo(vertices.get(0).getX(), vertices.get(0).getY());
      for (int i = 0; i < n; i++) {
         path.lineTo(vertices.get(i).getX(), vertices.get(i).getY());
      }
      path.lineTo(vertices.get(0).getX(), vertices.get(0).getY());
      if (isFilled()) {
         g.setColor(getFillColor());
         g.fill(path);
         g.setColor(getColor());
      }
      g.draw(path);
   }

/**
 * Recalculates the vertices of the polygon so that they are positioned
 * relative to the geometric center of the object.  This method allows
 * clients to take a polygon drawn using mouse clicks on the screen and
 * then to reformulate it so that it can be displayed relative to its center.
 *
 */

   public void recenter() {
      vertices.recenter();
   }

/**
 * Overrides <code>clone</code> in <code>Object</code> to make sure
 * that the vertex list is copied rather than shared.
 * @noshow
 */

   public Object clone() {
      try {
         GPolygon clone = (GPolygon) super.clone();
         clone.vertices = new VertexList(clone.vertices);
         return clone;
      } catch (Exception CloneNotSupportedException) {
         throw new RuntimeException("Impossible exception");
      }
   }

/**
 * Calling this method makes it illegal to add or remove vertices from the
 * polygon.  Subclasses can invoke this method to protect the integrity of
 * the structure from changes by the client.
 */

   protected void markAsComplete() {
      complete = true;
   }

/**
 * Calling this method deletes all vertices from the polygon.  Subclasses
 * can use this method to reconstruct a polygon.
 */

   protected void clear() {
      if (complete) {
         throw new RuntimeException("You can't clear a GPolygon that has been "
                                  + "marked as complete.");
      }
      vertices.clear();
   }

/* Private instance variables */

   private VertexList vertices;
   private boolean complete;
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

/**
 * The <code>VertexList<code> class represents a list of vertices.
 */

class VertexList implements Serializable {

/**
 * Creates a new <code>VertexList</code> with no elements.
 */

   public VertexList() {
      vertices = new ArrayList<GPoint>();
      cx = 0;
      cy = 0;
   }

/**
 * Creates a new <code>VertexList</code> that is a clone of the old one.
 */

   public VertexList(VertexList oldList) {
      this();
      for (int i = 0; i < oldList.vertices.size(); i++) {
         vertices.add(oldList.vertices.get(i));
      }
   }

/**
 * Adds the specified vertex to the end of the list.
 */

   public synchronized void addVertex(double x, double y) {
      cx = x;
      cy = y;
      vertices.add(new GPoint(cx, cy));
   }

/**
 * Adds the specified edge to the end of the list.
 */

   public synchronized void addEdge(double dx, double dy) {
      cx += dx;
      cy += dy;
      vertices.add(new GPoint(cx, cy));
   }

/**
 * Adds a series of edges to the polygon that simulates the arc specified by
 * the parameters.  The <i>x</i> and <i>y</i> parameters for the arc bounding
 * box are computed implicitly by figuring out what values would place the
 * current vertex at the starting position.
 */

   public void addArc(double arcWidth, double arcHeight,
                      double start, double sweep) {
      double aspectRatio = arcHeight / arcWidth;
      double rx = arcWidth / 2.0;
      double ry = arcHeight / 2.0;
      double x0 = cx - rx * GMath.cosDegrees(start);
      double y0 = cy + ry * GMath.sinDegrees(start);
      if (sweep > 359.99) sweep = 360;
      if (sweep < -359.99) sweep = -360;
      double dt = Math.atan2(1, Math.max(arcWidth, arcHeight));
      int nSteps = (int) (GMath.toRadians(Math.abs(sweep)) / dt);
      dt = GMath.toRadians(sweep) / nSteps;
      double theta = GMath.toRadians(start);
      for (int i = 0; i < nSteps; i++) {
         theta += dt;
         double px = x0 + rx * Math.cos(theta);
         double py = y0 - rx * Math.sin(theta) * aspectRatio;
         addVertex(px, py);
      }
   }

/**
 * Adds copies of the points to the end of the vertex list.
 */

   public synchronized void add(GPoint[] array) {
      for (int i = 0; i < array.length; i++) {
         vertices.add(new GPoint(array[i].getX(), array[i].getY()));
      }
   }

/**
 * Removes the specified vertex from the list.
 */

   public synchronized void remove(GPoint vertex) {
      vertices.remove(vertex);
   }

/**
 * Removes all vertices from the list.
 */

   public synchronized void clear() {
      vertices.clear();
   }

/**
 * Returns the number of vertices in the list.
 */

   public int size() {
      return vertices.size();
   }

/**
 * Returns the point at the specified index.
 */

   GPoint get(int index) {
      return vertices.get(index);
   }

/**
 * Returns the coordinates of the last vertex added to the polygon,
 * or <code>null</code> if the polygon is empty.
 */

   public GPoint getCurrentPoint() {
      return (vertices.size() == 0) ? null : new GPoint(cx, cy);
   }

/**
 * Returns the bounding box for the polygon represented by this vertex list.
 */

   public synchronized GRectangle getBounds(AffineTransform matrix) {
      int nPoints = vertices.size();
      if (nPoints == 0) return new GRectangle();
      double xMin = 0;
      double xMax = 0;
      double yMin = 0;
      double yMax = 0;
      boolean first = true;
      for (int i = 0; i < vertices.size(); i++) {
         GPoint vertex = vertices.get(i);
         Point2D pt = new Point2D.Double(vertex.getX(), vertex.getY());
         if (matrix != null) matrix.transform(pt, pt);
         double x = pt.getX();
         double y = pt.getY();
         if (first) {
            xMin = x;
            xMax = x;
            yMin = y;
            yMax = y;
            first = false;
         } else {
            xMin = Math.min(xMin, x);
            xMax = Math.max(xMax, x);
            yMin = Math.min(yMin, y);
            yMax = Math.max(yMax, y);
         }
      }
      return new GRectangle(xMin, yMin, xMax - xMin, yMax - yMin);
   }

/**
 * Returns <code>true</code> if the polygon described by this
 * <code>VertexList</code> contains the specified point.
 */

   public synchronized boolean contains(double x, double y,
                                        AffineTransform matrix) {
      int nPoints = vertices.size();
      boolean isContained = false;
      for (int i = 0; i < nPoints; i++) {
         GPoint vertex = vertices.get(i);
         Point2D v1 = new Point2D.Double(vertex.getX(), vertex.getY());
         if (matrix != null) matrix.transform(v1, v1);
         vertex = vertices.get((i + 1) % nPoints);
         Point2D v2 = new Point2D.Double(vertex.getX(), vertex.getY());
         if (matrix != null) matrix.transform(v2, v2);
         if (((v1.getY() < y) && (v2.getY() >= y))
                || ((v2.getY() < y) && (v1.getY() >= y))) {
            if (v1.getX() + (y - v1.getY())
                   / (v2.getY() - v1.getY()) * (v2.getX() - v1.getX()) < x) {
               isContained = !isContained;
            }
         }
      }
      return isContained;
   }

/**
 * Recalculates the vertices of the polygon so that they are positioned
 * relative to the geometric center of the object.  This method allows
 * clients to take a polygon drawn using mouse clicks on the screen and
 * then to reformulate it so that it can be displayed relative to its center.
 */

   public void recenter() {
      double xMin = 0;
      double xMax = 0;
      double yMin = 0;
      double yMax = 0;
      boolean first = true;
      for (int i = 0; i < vertices.size(); i++) {
         GPoint vertex = vertices.get(i);
         if (first) {
            xMin = vertex.getX();
            xMax = vertex.getX();
            yMin = vertex.getY();
            yMax = vertex.getY();
            first = false;
         } else {
            xMin = Math.min(xMin, vertex.getX());
            xMax = Math.max(xMax, vertex.getX());
            yMin = Math.min(yMin, vertex.getY());
            yMax = Math.max(yMax, vertex.getY());
         }
      }
      double xc = (xMin + xMax) / 2;
      double yc = (yMin + yMax) / 2;
      for (int i = 0; i < vertices.size(); i++ ) {
         GPoint vertex = vertices.get(i);
         vertex.translate(-xc, -yc);
      }
   }

/* Private instance variables */

   private ArrayList<GPoint> vertices;
   private double cx;
   private double cy;

};
