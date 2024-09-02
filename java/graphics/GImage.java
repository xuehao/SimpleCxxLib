/*
 * @(#)GImage.java   2.03.1 05/26/14
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
import java.awt.Graphics2D;
import java.awt.Image;
import java.awt.Shape;
import java.awt.geom.AffineTransform;
import java.awt.geom.Rectangle2D;
import java.io.File;

/**
 * The <code>GImage</code> class is a graphical object whose appearance is
 * defined by an image.
 */

public class GImage extends GObject implements GResizable {

/**
 * Creates a new <code>GImage</code> object at the origin that displays
 * the specified image.
 *
 * @param image The image to use as the contents of this <code>GImage</code>
 */

   public GImage(Image image) {
      this(image, 0, 0);
   }

/**
 * Creates a new <code>GImage</code> object by looking for an image with that
 * name.  The search for an image by name consists of the following steps:
 *
 * <p><ol>
 * <li>Check to see if an image with that name has already been defined.  If
 *     so, return that image.<p>
 *
 * <li>Check to see if there is a resource available with that name whose
 *     contents can be read as an <code>Image</code>.  If so, read the image
 *     from the resource file.<p>
 *
 * <li>Load the image from a file with the specified name, relative to the
 *     application directory or the applet code base.
 * </ol><p>
 *
 * @param name The name used to search for the contents of this image
 */

   public GImage(String name) {
      this(name, 0, 0);
   }

/**
 * Creates a new <code>GImage</code> object at the origin.  The
 * <code>array</code> parameter is a two-dimensional pixel array in
 * which each pixel value consists of an integer that is subdivided
 * into four eight-bit bytes, as follows:
 *
 * <center>
 *    <i>alpha</i> <code>&lt;&lt;</code> 24  <code>|</code>
 *    <i>red</i>   <code>&lt;&lt;</code> 16  <code>|</code>
 *    <i>green</i> <code>&lt;&lt;</code>  8  <code>|</code>
 *    <i>blue</i>
 * </center>
 *
 * The <i>alpha</i> value indicates the transparency, and the other values
 * are the red, green, and blue components of the color.
 *
 * @param array A two-dimensional pixel array
 */

   public GImage(int[][] array) {
      this(array, 0, 0);
   }

/**
 * Creates a new <code>GImage</code> object at the specified coordinates.
 * The <code>image</code> parameter is used to initialize the appearance
 * of the image.
 *
 * @param image The image to use as the contents of this <code>GImage</code>
 * @param x The x-coordinate of the upper left corner of the image
 * @param y The y-coordinate of the upper left corner of the image
 */

   public GImage(Image image, double x, double y) {
      setImage(image);
      setLocation(x, y);
   }

/**
 * Creates a new <code>GImage</code> object at the specified coordinates.  The
 * <code>name</code> parameter is used to identify an image to display, as
 * described in the single-argument version of the
 * <a href="#GImage(String)"><code>GImage</code></a> constructor.
 *
 * @param name The name used to search for the contents of this image
 * @param x The x-coordinate of the upper left corner of the image
 * @param y The y-coordinate of the upper left corner of the image
 */

   public GImage(String name, double x, double y) {
      this(GImageTools.loadImage(name), x, y);
   }

/**
 * Creates a new <code>GImage</code> object at the specified coordinates.
 * The <code>array</code> parameter is a two-dimensional pixel array in
 * which each pixel value consists of an integer that is subdivided into
 * four eight-bit bytes, as follows:
 *
 * <center>
 *    <i>alpha</i> <code>&lt;&lt;</code> 24  <code>|</code>
 *    <i>red</i>   <code>&lt;&lt;</code> 16  <code>|</code>
 *    <i>green</i> <code>&lt;&lt;</code>  8  <code>|</code>
 *    <i>blue</i>
 * </center>
 *
 * The <i>alpha</i> value indicates the transparency, and the other values
 * are the red, green, and blue components of the color.
 *
 * @param array A two-dimensional pixel array
 * @param x The x-coordinate of the upper left corner of the image
 * @param y The y-coordinate of the upper left corner of the image
 */

   public GImage(int[][] array, double x, double y) {
      this(GImageTools.createImage(array), x, y);
   }

/**
 * Resets the image used by this <code>GImage</code> object to the new image
 * specified as an argument.  Calling <code>setImage</code> automatically
 * changes the size of the image to be equal to that of the image data.
 *
 * @param image The image to use as the contents of this <code>GImage</code>
 */

   public void setImage(Image image) {
      this.image = GImageTools.loadImage(image);
      sizeDetermined = false;
      determineSize();
      repaint();
   }

/**
 * Resets the image used by this <code>GImage</code> object to the one
 * identified by the argument <code>name</code>, which is processed
 * as described in the constructors.  Calling <code>setImage</code>
 * automatically changes the size of the image to be equal to that of
 * the image data.
 *
 * @param name The name used to search for the contents of this image
 */

   public void setImage(String name) {
      setImage(GImageTools.loadImage(name));
   }

/**
 * Returns the image stored inside this <code>GImage</code>.
 *
 * @return The <code>Image</code> object stored inside this <code>GImage</code>
 */

   public Image getImage() {
      return image;
   }

/**
 * Saves the image to a file with the specified filename.  The data format
 * for the image file is determined by the suffix of the filename.  If the
 * suffix of the file is not recognized as a supported image type, calling
 * this method generates an error.
 *
 * @param filename The name of the file to which the image is saved
 */

   public void saveImage(String filename) {
      GImageTools.saveImage(image, filename);
   }

/**
 * Saves the image to the specified file.  The data format for the
 * image file is determined by the suffix of the filename.  If the
 * suffix of the file is not recognized as a supported image type,
 * calling this method generates an error.
 *
 * @param file The <code>File</code> to which the image is saved
 */

   public void saveImage(File file) {
      GImageTools.saveImage(image, file);
   }

/**
 * Implements the <code>paint2d</code> operation for this graphical object.
 * This method is not called directly by clients.
 * @noshow
 */

   protected void paint2d(Graphics2D g) {
      Component imageObserver = getComponent();
      if (imageObserver == null) {
         imageObserver = GImageTools.getImageObserver();
      }
      if (image != null && imageObserver != null) {
         determineSize();
         Color color = getObjectColor();
         if (color == null) {
            g.drawImage(image, 0, 0,
                        GMath.round(width), GMath.round(height),
                        imageObserver);
         } else {
            g.drawImage(image, 0, 0,
                        GMath.round(width), GMath.round(height),
                        color, imageObserver);
         }
      }
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
      this.width = width;
      this.height = height;
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
      return new GDimension(width, height);
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
      this.width = width;
      this.height = height;
      setLocation(x, y);
   }

/**
 * Changes the bounds of this object to the values from the specified
 * <code>GRectangle</code>.
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

/**
 * Returns the bounding box of this object.
 *
 * @return The bounding box for this object
 */

   public GRectangle getBounds() {
      determineSize();
      Shape shape = new Rectangle2D.Double(0, 0, width, height);
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
      determineSize();
      Shape shape = new Rectangle2D.Double(0, 0, width, height);
      AffineTransform matrix = getMatrix();
      if (matrix != null) shape = matrix.createTransformedShape(shape);
      return shape.contains(x - getX(), y - getY());
   }

/**
 * Returns a two-dimensional array of pixel values from the stored image.
 *
 * @return A two-dimensional array of pixel values from the stored image
 */

   public int[][] getPixelArray() {
      return GImageTools.getPixelArray(image);
   }

/**
 * Returns the alpha component from an RGB value.
 *
 * @param pixel An <code>int</code> containing a pixel value as
 *              alpha/red/green/blue
 * @return The alpha component of the pixel
 */

   public static int getAlpha(int pixel) {
      return (pixel >> 24) & 0xFF;
   }

/**
 * Returns the red component from an RGB value.
 *
 * @param pixel An <code>int</code> containing a pixel value as
 *              alpha/red/green/blue
 * @return The red component of the pixel
 */

   public static int getRed(int pixel) {
      return (pixel >> 16) & 0xFF;
   }

/**
 * Returns the green component from an RGB value.
 *
 * @param pixel An <code>int</code> containing a pixel value as
 *               alpha/red/green/blue
 * @return The green component of the pixel
 */

   public static int getGreen(int pixel) {
      return (pixel >> 8) & 0xFF;
   }

/**
 * Returns the blue component from an RGB value.
 *
 * @param pixel An <code>int</code> containing a pixel value as
 *              alpha/red/green/blue
 * @return The blue component of the pixel
 */

   public static int getBlue(int pixel) {
      return pixel & 0xFF;
   }

/**
 * Creates an opaque pixel value with the color components given by
 * <code>red</code>, <code>green</code>, and <code>blue</code>.
 *
 * @param red The red component of the pixel (0 to 255)
 * @param green The green component of the pixel (0 to 255)
 * @param blue The blue component of the pixel (0 to 255)
 * @return An opaque pixel value containing these components
 */

   public static int createRGBPixel(int red, int green, int blue) {
      return createRGBPixel(red, green, blue, 0xFF);
   }

/**
 * Creates a pixel value with the color components given by
 * <code>red</code>, <code>green</code>, and <code>blue</code>
 * and the transparency value <code>alpha</code>.
 *
 * @param red The red component of the pixel (0 to 255)
 * @param green The green component of the pixel (0 to 255)
 * @param blue The blue component of the pixel (0 to 255)
 * @param alpha The transparency value of the pixel (0 to 255)
 * @return A pixel value containing these components
 */

   public static int createRGBPixel(int red, int green, int blue, int alpha) {
      return (alpha << 24) | (red << 16) | (green << 8) | blue;
   }

/**
 * Computes the size of the image.
 */

   private void determineSize() {
      if (sizeDetermined) return;
      Component component = getComponent();
      if (component == null) component = GImageTools.getImageObserver();
      width = image.getWidth(component);
      height = image.getHeight(component);
      sizeDetermined = true;
   }

/* Private instance variables */

   private Image image;
   private double width;
   private double height;
   private boolean sizeDetermined;

/* Serial version UID */
/**
 * The serialization code for this class.  This value should be incremented
 * whenever you change the structure of this class in an incompatible way,
 * typically by adding a new instance variable.
 */

   static final long serialVersionUID = 21L;

}
