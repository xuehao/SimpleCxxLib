/*
 * File: gtypes.h
 * --------------
 * This file defines classes for representing points, dimensions, and
 * rectangles.
 */

/*************************************************************************/
/* Stanford Portable Library                                             */
/* Copyright (c) 2014 by Eric Roberts <eroberts@cs.stanford.edu>         */
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

#ifndef _gtypes_h
#define _gtypes_h

#include <iostream>
#include <string>

/*
 * Class: GPoint
 * -------------
 * This class contains real-valued x and y fields.  It is used to
 * represent a location on the graphics plane.
 */

class GPoint {

  public:
    /*
 * Constructor: GPoint
 * Usage: GPoint origin;
 *        GPoint pt(x, y);
 * -----------------------
 * Creates a <code>GPoint</code> object with the specified <code>x</code>
 * and <code>y</code> coordinates.  If the coordinates are not supplied,
 * the default constructor sets these fields to 0.
 */

    GPoint();
    GPoint(double x, double y);

    /*
 * Method: getX
 * Usage: double x = pt.getX();
 * ----------------------------
 * Returns the x component of the point.
 */

    double getX() const;

    /*
 * Method: getY
 * Usage: double y = pt.getY();
 * ----------------------------
 * Returns the y component of the point.
 */

    double getY() const;

    /*
 * Method: toString
 * Usage: string str = pt.toString();
 * ----------------------------------
 * Converts the <code>GPoint</code> to a string in the form
 * <code>"(</code><i>x</i><code>,</code>&nbsp;<i>y</i><code>)"</code>.
 */

    std::string toString() const;

    /* Private section */

    /**********************************************************************/
    /* Note: Everything below this point in this class is logically part  */
    /* of the implementation and should not be of interest to clients.    */
    /**********************************************************************/

  private:
    /* Instance variables */

    double x; /* The x-coordinate of the point */
    double y; /* The y-coordinate of the point */

    /* Friend declarations */

    friend bool operator==(const GPoint& p1, const GPoint& p2);
    friend bool operator!=(const GPoint& p1, const GPoint& p2);
    friend int hashCode(const GPoint& pt);
};

/*
 * Class: GDimension
 * -----------------
 * This class contains real-valued width and height fields.  It is used
 * to indicate the size of a graphical object.
 */

class GDimension {

  public:
    /*
 * Constructor: GDimension
 * Usage: GDimension empty;
 *        GDimension dim(width, height);
 * -------------------------------------
 * Creates a <code>GDimension</code> object with the specified
 * <code>width</code> and <code>height</code> coordinates.  If the
 * coordinates are not supplied, the default constructor sets these
 * fields to 0.
 */

    GDimension();
    GDimension(double width, double height);

    /*
 * Method: getWidth
 * Usage: double width = dim.getWidth();
 * -------------------------------------
 * Returns the width component of the <code>GDimension</code> object.
 */

    double getWidth() const;

    /*
 * Method: getHeight
 * Usage: double height = dim.getHeight();
 * ---------------------------------------
 * Returns the height component of the <code>GDimension</code> object.
 */

    double getHeight() const;

    /*
 * Method: toString
 * Usage: string str = dim.toString();
 * -----------------------------------
 * Converts the <code>GDimension</code> to a string in the form
 * <code>"(</code><i>width</i><code>,</code>&nbsp;<i>height</i><code>)"</code>.
 */

    std::string toString() const;

    /* Private section */

    /**********************************************************************/
    /* Note: Everything below this point in this class is logically part  */
    /* of the implementation and should not be of interest to clients.    */
    /**********************************************************************/

  private:
    /* Instance variables */

    double width;  /* The width of the GDimension       */
    double height; /* The height of the GDimension      */

    /* Friend declarations */

    friend bool operator==(const GDimension& d1, const GDimension& d2);
    friend bool operator!=(const GDimension& d1, const GDimension& d2);
    friend int hashCode(const GDimension& dim);
};

/*
 * Class: GRectangle
 * -----------------
 * This type contains real-valued x, y, width, and height fields.  It is
 * used to represent the bounding box of a graphical object.
 */

class GRectangle {

  public:
    /*
 * Constructor: GRectangle
 * Usage: GRectangle empty;
 *        GRectangle r(x, y, width, height);
 * -----------------------------------------
 * Creates a <code>GRectangle</code> object with the specified components.
 * If these parameters are not supplied, the default constructor sets
 * these fields to 0.
 */

    GRectangle();
    GRectangle(double x, double y, double width, double height);

    /*
 * Method: getX
 * Usage: double x = r.getX();
 * ---------------------------
 * Returns the x component of the rectangle.
 */

    double getX() const;

    /*
 * Method: getY
 * Usage: double y = pt.getY();
 * ----------------------------
 * Returns the y component of the rectangle.
 */

    double getY() const;

    /*
 * Method: getWidth
 * Usage: double width = r.getWidth();
 * -----------------------------------
 * Returns the width component of the rectangle.
 */

    double getWidth() const;

    /*
 * Method: getHeight
 * Usage: double height = pt.getHeight();
 * --------------------------------------
 * Returns the height component of the rectangle.
 */

    double getHeight() const;

    /*
 * Method: isEmpty
 * Usage: if (r.isEmpty()) ...
 * ---------------------------
 * Returns <code>true</code> if the rectangle is empty.
 */

    bool isEmpty() const;

    /*
 * Method: contains
 * Usage: if (r.contains(pt)) ...
 *        if (r.contains(x, y)) ...
 * --------------------------------
 * Returns <code>true</code> if the rectangle contains the given point,
 * which may be specified either as a point or as distinct coordinates.
 */

    bool contains(GPoint pt) const;
    bool contains(double x, double y) const;

    /*
 * Method: toString
 * Usage: string str = r.toString();
 * ---------------------------------
 * Converts the <code>GRectangle</code> to a string in the form
 * <code>"(</code><i>x</i><code>,</code>&nbsp;<i>y</i><code>,</code>
 * <i>width</i><code>,</code>&nbsp;<i>height</i><code>)"</code>.
 */

    std::string toString() const;

    /* Private section */

    /**********************************************************************/
    /* Note: Everything below this point in this class is logically part  */
    /* of the implementation and should not be of interest to clients.    */
    /**********************************************************************/

  private:
    /* Instance variables */

    double x;      /* The x-coordinate of the rectangle */
    double y;      /* The y-coordinate of the rectangle */
    double width;  /* The width of the rectangle        */
    double height; /* The height of the rectangle       */

    /* Friend declarations */

    friend bool operator==(const GRectangle& r1, const GRectangle& r2);
    friend bool operator!=(const GRectangle& r1, const GRectangle& r2);
    friend int hashCode(const GRectangle& r);
};

/*
 * Free functions
 * --------------
 * This section of the interface defines the insertion, comparison,
 * and hashCode functions for the geometric types.
 */

std::ostream& operator<<(std::ostream& os, const GPoint& pt);
bool operator==(const GPoint& p1, const GPoint& p2);
bool operator!=(const GPoint& p1, const GPoint& p2);
int hashCode(const GPoint& pt);

std::ostream& operator<<(std::ostream& os, const GDimension& dim);
bool operator==(const GDimension& d1, const GDimension& d2);
bool operator!=(const GDimension& d1, const GDimension& d2);
int hashCode(const GDimension& dim);

std::ostream& operator<<(std::ostream& os, const GRectangle& rect);
bool operator==(const GRectangle& r1, const GRectangle& r2);
bool operator!=(const GRectangle& r1, const GRectangle& r2);
int hashCode(const GRectangle& r);

#endif
