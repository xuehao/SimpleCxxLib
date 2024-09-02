/*
 * @(#)GImageTools.java   2.03.1 05/26/14
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

import java.awt.AlphaComposite;
import java.awt.Color;
import java.awt.Component;
import java.awt.Dimension;
import java.awt.Graphics2D;
import java.awt.Image;
import java.awt.MediaTracker;
import java.awt.Point;
import java.awt.Toolkit;
import java.awt.image.BufferedImage;
import java.awt.image.ImageObserver;
import java.awt.image.ImageProducer;
import java.awt.image.MemoryImageSource;
import java.awt.image.PixelGrabber;
import java.io.BufferedOutputStream;
import java.io.BufferedReader;
import java.io.ByteArrayOutputStream;
import java.io.File;
import java.io.FileOutputStream;
import java.io.FileReader;
import java.io.IOException;
import java.io.InputStream;
import java.io.OutputStream;
import java.net.MalformedURLException;
import java.net.URI;
import java.net.URL;
import java.net.URLConnection;
import java.util.HashMap;
import java.util.StringTokenizer;
import java.util.Vector;
import javax.imageio.ImageIO;
import javax.imageio.stream.ImageOutputStream;
import javax.imageio.stream.MemoryCacheImageOutputStream;
import javax.swing.JPanel;

/**
 * This class exports a few static methods for working with images.
 */

public class GImageTools {

/**
 * Prevents anyone else from constructing this class.
 */

   private GImageTools() {
      /* Empty */
   }

/**
 * Searches the default image search path for an image with the specified name
 * and then loads it to create an <code>Image</code>.  The search process
 * consists of the following steps:
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
 * The second and third steps are repeated for each element of the image
 * search path, which consists of a list of directories separated by colons.
 *
 * <p>Unlike the <code>getImage</code> method in the <code>Applet</code>
 * class, <code>loadImage</code> waits for an image to be fully loaded
 * before returning.
 *
 * @param name The name of the image
 * @return A fully loaded <code>Image</code> object
 */

   public static Image loadImage(String name) {
      return loadImage(name, DEFAULT_IMAGE_PATH);
   }

/**
 * Searches for an image with the given name and loads it to create an
 * <code>Image</code>.  Its operation is identical to the single-argument
 * <a href="#loadImage(String)"><code>loadImage</code></a> call except
 * in that this version allows the client to specify the search path
 * explicitly.
 *
 * @param name The name of the image
 * @param path A string of directories names separated by colons
 * @return A fully loaded <code>Image</code> object
 */

   public static Image loadImage(String name, String path) {
      Image image = imageTable.get(name);
      if (image != null) return image;
      if (name.startsWith("http:")) {
         try {
            image = loadImage(URI.create(name).toURL());
            if (cachingEnabled) imageTable.put(name, image);
            return image;
         } catch (MalformedURLException ex) {
            throw new RuntimeException("loadImage: Malformed URL");
         }
      }
      Toolkit toolkit = Toolkit.getDefaultToolkit();
      StringTokenizer tokenizer = new StringTokenizer(path, ":");
      while (image == null && tokenizer.hasMoreTokens()) {
         String prefix = tokenizer.nextToken();
         prefix = (prefix.equals(".")) ? "" : prefix + "/";
         try {
            if (new File(prefix + name).canRead()) {
               image = toolkit.getImage(prefix + name);
            }
         } catch (SecurityException ex) {
            /* Empty */
         }
      }
      if (image == null) {
         throw new RuntimeException("Cannot find an image named " + name);
      }
      loadImage(image);
      if (cachingEnabled) imageTable.put(name, image);
      return image;
   }

/**
 * Loads an image from the specified URL.
 *
 * @param url The url containing the image
 * @return A fully loaded <code>Image</code> object
 */

   public static Image loadImage(URL url) {
      return loadImage(url, true);
   }

/**
 * Makes sure that the image is fully loaded before returning.
 *
 * @param image The <code>Image</code> which may not yet be loaded
 * @return The same <code>Image</code> after ensuring that it is fully loaded
 */

   public static Image loadImage(Image image) {
      MediaTracker tracker = new MediaTracker(getImageObserver());
      tracker.addImage(image, 0);
      try {
         tracker.waitForID(0);
      } catch (InterruptedException ex) {
         throw new RuntimeException("Image loading process interrupted");
      }
      return image;
   }

/**
 * Inserts the given image into the image table under the specified name.
 *
 * @param name The name for the image
 * @param image The image to be stored in the table
 */

   public static void defineImage(String name, Image image) {
      imageTable.put(name, image);
   }

/**
 * Removes the image with the given name from the cache, allowing it
 * to be freed by the garbage collector.
 *
 * @param name The name for the image
 */

   public static void flushImage(String name) {
      imageTable.remove(name);
   }

/**
 * Generates an image from a two-dimensional array of pixel values.  As in
 * standard image processing applications, the array is indexed so that the
 * first subscript determines the row and the second determines the column.
 *
 * @param array A two-dimensional integer array of pixel values
 * @return An <code>Image</code> object
 */

   public static Image createImage(int[][] array) {
      int height = array.length;
      int width = array[0].length;
      int[] pixels = new int[width * height];
      for (int i = 0; i < height; i++) {
         System.arraycopy(array[i], 0, pixels, i * width, width);
      }
      return createImage(pixels, width, height);
   }

/**
 * Generates an image from a single-dimensional array of pixel values.  The
 * pixel array is stored in row-major order, which means that the pixels for
 * the entire first row come before the pixels in the second row, and so on.
 *
 * @param pixels An array of <code>int</code>s representing the pixels
 * @param width The width of the image
 * @param height The height of the image
 * @return An <code>Image</code> object
 */

   public static Image createImage(int[] pixels, int width, int height) {
      MemoryImageSource source = new MemoryImageSource(width, height,
                                                       pixels, 0, width);
      Image image = Toolkit.getDefaultToolkit().createImage(source);
      return loadImage(image);
   }

/**
 * Generates an image from an input stream containing the data bytes for the
 * image formatted in image/gif format.
 *
 * @param in An input stream containing the data
 * @return An <code>Image</code> object
 */

   public static Image createImage(InputStream in) {
      try {
         ByteArrayOutputStream out = new ByteArrayOutputStream();
         for (int ch = in.read(); ch != -1; ch = in.read()) {
            out.write(ch);
         }
         byte[] array = out.toByteArray();
         Image image = Toolkit.getDefaultToolkit().createImage(array);
         return loadImage(image);
      } catch (Exception ex) {
         throw new RuntimeException("Exception: " + ex);
      }
   }

/**
 * Returns a two-dimensional array of the pixels in the image.  As in standard
 * image processing applications, the array is indexed so that the first
 * subscript determines the row and the second determines the column.
 *
 * @param image The image
 * @return A two-dimensional array of pixels
 */

   public static int[][] getPixelArray(Image image) {
      Component observer = getImageObserver();
      int width = image.getWidth(observer);
      int height = image.getHeight(observer);
      int[] pixels = new int[width * height];
      int[][] array = new int[height][width];
      PixelGrabber pg = new PixelGrabber(image.getSource(), 0, 0,
                                         width, height, pixels, 0, width);
      try {
         pg.grabPixels();
      } catch (InterruptedException e) {
         throw new RuntimeException("Transfer interrupted");
      }
      if ((pg.getStatus() & ImageObserver.ABORT) != 0) {
         throw new RuntimeException("Transfer aborted");
      }
      for (int i = 0; i < height; i++) {
         System.arraycopy(pixels, i * width, array[i], 0, width);
      }
      return array;
   }

/**
 * Saves an image to a file with the specified filename.  The data format
 * for the image file is determined by the suffix of the filename.  If the
 * suffix of the file is not recognized as a supported image type, calling
 * this method generates an error.
 *
 * @param image The image
 * @param filename The name of the file to which the image is saved
 */

   public static void saveImage(Image image, String filename) {
      saveImage(image, new File(filename));
   }

/**
 * Saves an image to the specified file.  The data format for the
 * image file is determined by the suffix of the filename.  If the
 * suffix of the file is not recognized as a supported image type,
 * calling this method generates an error.
 *
 * @param image The image
 * @param file The <code>File</code> to which the image is saved
 */

   public static void saveImage(Image image, File file) {
      String filename = file.getName();
      int dot = filename.lastIndexOf('.');
      if (dot <= 0) {
         throw new RuntimeException("saveImage: No image suffix in file name");
      }
      String suffix = filename.substring(dot + 1);
      ImageSaver saver = findImageSaver(suffix);
      if (saver == null) {
         throw new RuntimeException("saveImage: No support for ." +
                                    suffix + " format");
      }
      if (file.exists()) {
         if (!file.delete()) {
            throw new RuntimeException("saveImage: Cannot write " + filename);
         }
      }
      try {
         OutputStream out =
            new BufferedOutputStream(new FileOutputStream(file));
         saver.setOutputStream(out);
         saver.saveImage(image);
         out.close();
      } catch (IOException ex) {
         throw new RuntimeException("saveImage: " + ex.getMessage());
      }
   }

/**
 * Loads an image from the specified URL.  The <code>topLevel</code> flag
 * is <code>false</code> if this is invoked internally.
 */

   public static Image loadImage(URL url, boolean topLevel) {
      Image image = null;
      Toolkit toolkit = Toolkit.getDefaultToolkit();
      try {
         URLConnection connection = url.openConnection();
         if (connection.getContentLength() > 0) {
            Object content = connection.getContent();
            if (content instanceof ImageProducer) {
               image = toolkit.createImage((ImageProducer) content);
            } else if (content != null) {
               image = toolkit.getImage(url);
            }
         }
      } catch (IOException ex) {
         /* Empty */
      }
      if (topLevel) {
         if (image == null) {
            throw new RuntimeException("Cannot load image from " + url);
         }
         loadImage(image);
      }
      return image;
   }

/**
 * Finds an image saver capable of writing image files with the specified
 * subect.
 */

   private static ImageSaver findImageSaver(String suffix) {
      String cname = GImageTools.class.getName();
      String pkg = cname.substring(0, cname.lastIndexOf("."));
      suffix = suffix.toUpperCase();
      synchronized (suffixTable) {
         ImageSaver saver = suffixTable.get(suffix);
         if (saver == null) {
            try {
               cname = pkg + "." + suffix + "ImageSaver";
               Class<?> imageSaverClass = Class.forName(cname);
               saver = (ImageSaver) imageSaverClass.getDeclaredConstructor().newInstance();
            } catch (Exception ex) {
               return null;
            }
            suffixTable.put(suffix, saver);
         }
         return saver;
      }
   }

/**
 * Returns an empty container that can serve as an <code>ImageObserver</code>.
 *
 * @return An empty container
 */

   public static Component getImageObserver() {
      if (emptyContainer == null) emptyContainer = new JPanel();
      return emptyContainer;
   }

/* Constants */

   public static final String DEFAULT_IMAGE_PATH = ".:images";

/* Private package variables */

   private static boolean cachingEnabled = false;
   private static HashMap<String,Image> imageTable =
      new HashMap<String,Image>();
   private static HashMap<String,ImageSaver> suffixTable =
      new HashMap<String,ImageSaver>();
   private static Component emptyContainer;

}

/**
 * This class represents the root of a package class hierarchy responsible
 * for saving images.  The class names for the subclasses in this hierarchy
 * are of the form <code>XYZImageSaver</code> where <code>XYZ</code> is the
 * extension used for image files in that format.  The abstract class
 * encapsulates the code used to write data to the output file, and the
 * specific subclasses determine what data needs to be written.
 */

class ImageSaver {

/**
 * Creates a new <code>ImageSaver</code> in which the subclass takes
 * responsibility for saving the image data.  This code is the default
 * constructor and is not ordinarily invoked explicitly.
 */

   public ImageSaver() {
      /* Empty */
   }

/**
 * Creates a new <code>ImageSaver</code> in which the subclass uses the
 * tools in the <code>javax.imageio</code> to save an image as indicated
 * by the format name and image buffer type.
 *
 * @param format The informal name of the image format
 * @param type The integer code for the <code>BufferedImage</code> type
 */

   public ImageSaver(String format, int type) {
      formatName = format;
      bufferType = type;
   }

/**
 * Sets the output stream this <code>ImageSaver</code> uses to write data.
 *
 * @param output The output stream used to write data
 */

   public void setOutputStream(OutputStream output) {
      out = output;
   }

/**
 * Returns the output stream used by this <code>ImageSaver</code>.
 *
 * @return The output stream used to write data
 */

   public OutputStream getOutputStream() {
      return out;
   }

/**
 * Saves the image to the output stream established when the client called
 * <code>setOutputStream</code>.  This implementation uses the facilities
 * from the <code>javax.imageio</code> package to write the file.  Subclasses
 * that do their own data formatting must override this method.
 *
 * @param image The image to be written
 */

   public void saveImage(Image image) {
      BufferedImage bi = createBufferedImage(image, bufferType);
      ImageOutputStream ios = new MemoryCacheImageOutputStream(out);
      try {
         if (!ImageIO.write(bi, formatName, ios)) {
            throw new IOException("ImageIO.write failed");
         }
         ios.close();
      } catch (IOException ex) {
         throw new RuntimeException("saveImage: " + ex.getMessage());
      }
   }

/**
 * Writes the low-order byte of <code>x</code> to the output stream.
 *
 * @param x A byte stored in an integer
 */

   public void dumpByte(int x) {
      try {
         out.write(x);
      } catch (IOException ex) {
         throw new RuntimeException("saveImage: " + ex.getMessage());
      }
   }

/**
 * Writes the low-order 16 bits of <code>x</code> to the output stream.
 *
 * @param x A 16-bit quantity stored in an integer
 */

   public void dumpShort(int x) {
      try {
         out.write(x >> 8);
         out.write(x);
      } catch (IOException ex) {
         throw new RuntimeException("saveImage: " + ex.getMessage());
      }
   }

/**
 * Writes the 32-bit word in <code>x</code> to the output stream.
 *
 * @param x A 32-bit integer word
 */

   public void dumpInt(int x) {
      try {
         out.write(x >> 24);
         out.write(x >> 16);
         out.write(x >> 8);
         out.write(x);
      } catch (IOException ex) {
         throw new RuntimeException("saveImage: " + ex.getMessage());
      }
   }

/**
 * Extracts the specified component of a pixel.  Transparency is simulated
 * by computing a weighted average between white and the given value.
 *
 * @param pixel The 32-bit integer pixel, including the alpha channel
 * @param color The character 'R', 'G', or 'B', indicating the component
 * @return An eight-bit component value, expanded to an integer
 */

   public int getPixelComponent(int pixel, char color) {
      int alpha = pixel >> 24 & 0xFF;
      switch (color) {
        case 'R': pixel >>= 16; break;
        case 'G': pixel >>= 8; break;
        case 'B': break;
        default: throw new RuntimeException("Illegal color");
      }
      pixel &= 0xFF;
      return (alpha * pixel + (0xFF - alpha) * 0xFF) / 0xFF;
   }

/**
 * Creates a <code>BufferedImage</code> from the specified image.  The
 * <code>type</code> parameter is used to specify the image type, as
 * described in the <code>BufferedImage</code> documentation.
 *
 * @param image The original image
 * @param type The type code used to describe the image model
 * @return A <code>BufferedImage</code> containing the image data
 */

   public static BufferedImage createBufferedImage(Image image, int type) {
      Component observer = GImageTools.getImageObserver();
      int width = image.getWidth(observer);
      int height = image.getHeight(observer);
      BufferedImage bimage = new BufferedImage(width, height, type);
      Graphics2D g = bimage.createGraphics();
      switch (type) {
        case BufferedImage.TYPE_4BYTE_ABGR:
        case BufferedImage.TYPE_4BYTE_ABGR_PRE:
        case BufferedImage.TYPE_INT_ARGB:
        case BufferedImage.TYPE_INT_ARGB_PRE:
         g.setComposite(AlphaComposite.Src);
      }
      g.drawImage(image, 0, 0, observer);
      g.dispose();
      return bimage;
   }

/* Private instance variables */

   private OutputStream out;
   private String formatName;
   private int bufferType;
}

/**
 * This class saves PNG images.
 */

class PNGImageSaver extends ImageSaver {

   public PNGImageSaver() {
      super("PNG", BufferedImage.TYPE_INT_ARGB);
   }
}

/**
 * This class saves JPEG images.
 */

class JPEGImageSaver extends ImageSaver {

   public JPEGImageSaver() {
      super("JPEG", BufferedImage.TYPE_INT_RGB);
   }

}

class JPGImageSaver extends JPEGImageSaver {

   /* Entirely inherited from JPEGImageSaver */

}

/**
 * This class saves BMP images.
 */

class BMPImageSaver extends ImageSaver {

   public BMPImageSaver() {
      super("BMP", BufferedImage.TYPE_INT_RGB);
   }

}

/**
 * This class saves GIF images.  This implementation uses one of two
 * strategies to encode the image:
 *
 * <p><ol>
 * <li>If this version of Java includes a GIF writer, use that one.
 * <li>If not, default to the public-domain GIF89 writer.
 * </ol>
 */

class GIFImageSaver extends ImageSaver {

   public GIFImageSaver() {
      super("GIF", BufferedImage.TYPE_INT_ARGB);
      if (!ImageIO.getImageWritersBySuffix("gif").hasNext()) {
         gif89Saver = new GIF89ImageSaver();
      }
   }

   public void saveImage(Image image) {
      if (gif89Saver != null) {
         gif89Saver.setOutputStream(getOutputStream());
         gif89Saver.saveImage(image);
      } else {
         super.saveImage(image);
      }
   }

/* Private instance variables */

   private GIF89ImageSaver gif89Saver;

}

/**
 * This class saves GIF89 images using the public-domain GIF package.
 */

class GIF89ImageSaver extends ImageSaver {
   public void saveImage(Image image) {
      try {
         Gif89Encoder encoder = new Gif89Encoder(image);
         encoder.setTransparentIndex(0);
         encoder.getFrameAt(0).setInterlaced(true);
         encoder.encode(getOutputStream());
      } catch (IOException ex) {
         throw new RuntimeException("saveImage: " + ex.getMessage());
      }
   }

}

/**
 * This class saves TIFF images.  The TIFF image file format is described
 * in the following document from Adobe Systems:
 *
 *<pre>
 *    <a href="http://partners.adobe.com/public/developer/en/tiff/TIFF6.pdf"
 *    >http://partners.adobe.com/public/developer/en/tiff/TIFF6.pdf</a>
 *</pre>
 */

class TIFFImageSaver extends ImageSaver {

/**
 * Saves the image in TIFF format.
 */

   public void saveImage(Image image) {
      pixels = GImageTools.getPixelArray(image);
      width = pixels[0].length;
      height = pixels.length;
      calculateOffsets();
      dumpHeader();                     /* TIFF header      */
      dumpIFD();                        /* Main IFD block   */
      dumpNullIFD();                    /* End of IFD chain */
      dumpBitsPerSampleData();          /* Data (int[3])    */
      dumpResolutionData();             /* Data (rationals) */
      dumpStripPointers();              /* Scanline offsets */
      dumpStripByteCounts();            /* Bytes per line   */
      dumpStripData();                  /* Image data       */
   }

/**
 * Dumps the header of the TIFF file.
 */

   private void dumpHeader() {
      dumpByte('M');                    /* Byte order flag  */
      dumpByte('M');                    /* MM = big-endian  */
      dumpShort(42);                    /* TIFF identifier  */
      dumpInt(HEADER_SIZE);             /* Offset of IFD    */
   }

/**
 * Dumps the Image File Directory (IFD) to the output file.  The IFD
 * block consists of a sequence of TIFF entries, each of which
 * contains the following information:
 *
 * <p><ol>
 *   <li>An operation code (2 bytes)
 *   <li>Code for type of data (2 bytes)
 *   <li>The number of data elements in an array (typically 1)
 *   <li>The data (if there is a room) or the offset for the data
 * </ol>
 *
 * In the code that follows, each IFD entry is written using a
 * separate method to improve readability of the code.  Note that
 * TIFF format requires the entries in the IFD to appear in
 * increasing order by operation code.
 */

   private void dumpIFD() {
      dumpShort(IFD_OP_COUNT);
      dumpIFDNewSubFileType();
      dumpIFDImageWidth();
      dumpIFDImageHeight();
      dumpIFDBitsPerSample();
      dumpIFDCompression();
      dumpIFDPhotometricInterpration();
      dumpIFDStripPointers();
      dumpIFDSamplesPerPixel();
      dumpIFDRowsPerStrip();
      dumpIFDStripByteCounts();
      dumpIFDXResolution();
      dumpIFDYResolution();
      dumpIFDResolutionUnit();
   }

   private void dumpIFDNewSubFileType() {
      dumpShort(0xFE);
      dumpShort(TT_LONG);
      dumpInt(1);
      dumpInt(0);
   }

   private void dumpIFDImageWidth() {
      dumpShort(0x100);
      dumpShort(TT_LONG);
      dumpInt(1);
      dumpInt(width);
   }

   private void dumpIFDImageHeight() {
      dumpShort(0x101);
      dumpShort(TT_LONG);
      dumpInt(1);
      dumpInt(height);
   }

   private void dumpIFDBitsPerSample() {
      dumpShort(0x102);
      dumpShort(TT_LONG);
      dumpInt(3);
      dumpInt(offsetBitsPerSample);
   }

   private void dumpIFDCompression() {
      dumpShort(0x103);
      dumpShort(TT_SHORT);
      dumpInt(1);
      dumpShort(1);
      dumpShort(0);
   }

   private void dumpIFDPhotometricInterpration() {
      dumpShort(0x106);
      dumpShort(TT_SHORT);
      dumpInt(1);
      dumpShort(2);
      dumpShort(0);
   }

   private void dumpIFDStripPointers() {
      dumpShort(0x111);
      dumpShort(TT_LONG);
      dumpInt(height);
      dumpInt(offsetStripPointers);
   }

   private void dumpIFDSamplesPerPixel() {
      dumpShort(0x115);
      dumpShort(TT_SHORT);
      dumpInt(1);
      dumpShort(3);
      dumpShort(0);
   }

   private void dumpIFDRowsPerStrip() {
      dumpShort(0x116);
      dumpShort(TT_LONG);
      dumpInt(1);
      dumpInt(1);
   }

   private void dumpIFDStripByteCounts() {
      dumpShort(0x117);
      dumpShort(TT_LONG);
      dumpInt(height);
      dumpInt(offsetStripByteCounts);
   }

   private void dumpIFDXResolution() {
      dumpShort(0x11A);
      dumpShort(TT_RATIONAL);
      dumpInt(1);
      dumpInt(offsetXResolution);
   }

   private void dumpIFDYResolution() {
      dumpShort(0x11B);
      dumpShort(TT_RATIONAL);
      dumpInt(1);
      dumpInt(offsetYResolution);
   }

   private void dumpIFDResolutionUnit() {
      dumpShort(0x128);
      dumpShort(TT_SHORT);
      dumpInt(1);
      dumpShort(1);
      dumpShort(0);
   }

/**
 * Writes a null pointer to signal the end of he IFD chain.
 */

   private void dumpNullIFD() {
      dumpInt(0);
   }

/**
 * Writes the data used for the bits/sample IFD entry.  This value
 * is an array of three components and therefore does not fit in the
 * IFD itself.
 */

   private void dumpBitsPerSampleData() {
      dumpInt(8);
      dumpInt(8);
      dumpInt(8);
   }

/**
 * Writes the data used to specify the image resolution, which is
 * defined here to be the 72 pixels per inch.  The value for each
 * of the <i>x</i> and <i>y</i> resolution components is an 8-byte
 * <code>RATIONAL</code> value, consisting of two <code>long</code>
 * words.
 */

   private void dumpResolutionData() {
      dumpInt(72);
      dumpInt(1);
      dumpInt(72);
      dumpInt(1);
   }

/**
 * Writes the pointers to the data for each scan line in the TIFF
 * image.
 */

   private void dumpStripPointers() {
      for (int i = 0; i < height; i++) {
         dumpInt(offsetData + i * stripDelta);
      }
   }

/**
 * Writes the byte count for each scan line in the TIFF image.
 */

   private void dumpStripByteCounts() {
      for (int i = 0; i < height; i++) {
         dumpInt(3 * width);
      }
   }

/**
 * Writes the actual pixel data at the end of the TIFF file.
 */

   private void dumpStripData() {
      for (int i = 0; i < height; i++) {
         for (int j = 0; j < width; j++) {
            int pixel = pixels[i][j];
            dumpByte(getPixelComponent(pixel, 'R'));
            dumpByte(getPixelComponent(pixel, 'G'));
            dumpByte(getPixelComponent(pixel, 'B'));
         }
         for (int k = 3 * width; k < stripDelta; k++) {
            dumpByte(0);
         }
      }
   }

/**
 * Calculates the offset for every data field in the TIFF file.
 */

   private void calculateOffsets() {
      offsetIFD = HEADER_SIZE;
      offsetNullIFD = offsetIFD + IFD_OP_COUNT * 12 + 2;
      offsetBitsPerSample = offsetNullIFD + 4;
      offsetXResolution = offsetBitsPerSample + 12;
      offsetYResolution = offsetXResolution + 8;
      offsetStripPointers = offsetYResolution + 8;
      offsetStripByteCounts = offsetStripPointers + 4 * height;
      offsetData = offsetStripByteCounts + 4 * height;
      stripDelta = (3 * width + 3) & -4;
   }

/* Private constants */
   private static final int HEADER_SIZE = 8;
   private static final int IFD_OP_COUNT = 13;
   public static final int TT_BYTE = 1;
   public static final int TT_ASCII = 2;
   public static final int TT_SHORT = 3;
   public static final int TT_LONG = 4;
   public static final int TT_RATIONAL = 5;

/* Private instance variables */
   private int[][] pixels;
   private int width;
   private int height;
   private int offsetIFD;
   private int offsetNullIFD;
   private int offsetBitsPerSample;
   private int offsetXResolution;
   private int offsetYResolution;
   private int offsetStripPointers;
   private int offsetStripByteCounts;
   private int offsetData;
   private int stripDelta;
}

class TIFImageSaver extends TIFFImageSaver {
   /* Entirely inherited from TIFFImageSaver */
}

/**
 * This class saves PICT images.  The PICT image file format is described
 * in the following legacy document from Apple:
 *
 *<pre>
 *    <a href=
 * "http://developer.apple.com/documentation/mac/QuickDraw/QuickDraw-458.html"
 * >http://developer.apple.com/documentation/mac/QuickDraw/QuickDraw-458.html</a>
 *</pre>
 */

class PICTImageSaver extends ImageSaver {

/**
 * Saves the image in PICT format.
 */

   public void saveImage(Image image) {
      pixels = GImageTools.getPixelArray(image);
      Object property = image.getProperty("PSPreview", null);
      psPreview = (property instanceof String[]) ? (String[]) property : null;
      width = pixels[0].length;
      height = pixels.length;
      rowBytes = 4 * width;
      if (paddingFlag) dumpPadding();
      dumpHeader();
      dumpDefHilite();
      dumpClipRegion();
      dumpBoundsMarkers();
      if (psPreview != null) {
         dumpShort(OP_SHORT_COMMENT);
         dumpShort(PS_BEGIN);
      }
      dumpDirectBitsRect();
      if (psPreview != null) {
         dumpPSPreview();
         dumpShort(OP_SHORT_COMMENT);
         dumpShort(PS_END);
      }
      dumpEndPict();
   }

/**
 * Sets the internal flag used to control whether padding bytes are
 * added at the beginning of the file.  When a PICT file is stored
 * on disk, these bytes must be present; when a PICT file is embedded
 * in some other structure (such as an RTF file), these bytes do not
 * appear.  Padding is enabled by default.
 *
 * @param flag A flag to control padding (<code>true</code> by default)
 */

   public void setPaddingFlag(boolean flag) {
      paddingFlag = flag;
   }

/**
 * Writes out the initial padding in a PICT file.  Subclasses can
 * suppress this padding by calling <code>setPaddingFlag(false)</code>.
 */

   private void dumpPadding() {
      for (int i = 0; i < PICT_PADDING; i++) {
         dumpByte(0);
      }
   }

/**
 * Dumps the header of the PICT file.
 */

   private void dumpHeader() {
      dumpShort(0);                     /* Count (ignored)  */
      dumpShort(0);                     /* Bounds: y        */
      dumpShort(0);                     /*         x        */
      dumpShort(height);                /*         height   */
      dumpShort(width);                 /*         width    */
      dumpShort(OP_VERSION);            /* VERSION opcode   */
      dumpShort(VERSION);               /* Version 2 code   */
      dumpShort(OP_HEADER);             /* HEADER opcode    */
      dumpShort(0xFFFE);                /* Extended V2      */
      dumpShort(0);                     /* Reserved         */
      dumpShort(72);                    /* X resolution     */
      dumpShort(0);                     /* Fixed (72, 0)    */
      dumpShort(72);                    /* Y resolution     */
      dumpShort(0);                     /* Fixed (72, 0)    */
      dumpShort(0);                     /* Bounds: y        */
      dumpShort(0);                     /*         x        */
      dumpShort(height);                /*         height   */
      dumpShort(width);                 /*         width    */
      dumpInt(0);                      /* Reserved         */
   }

/**
 * Dumps the <code>DefHighlight</code> operation at the beginning of the
 * PICT file.
 */

   private void dumpDefHilite() {
      dumpShort(OP_DEF_HILITE);         /* Opcode           */
   };

/**
 * Dumps the rectangle that represents the clipping region.
 */

   private void dumpClipRegion() {
      dumpShort(OP_CLIP);               /* Opcode           */
      dumpShort(10);                    /* Region size      */
      dumpShort(0);                     /* Bounds: y        */
      dumpShort(0);                     /*         x        */
      dumpShort(height);                /*         height   */
      dumpShort(width);                 /*         width    */
   }

/**
 * Dumps <code>OP_SHORT_LINE</code> commands at each corner to ensure that
 * the bounds are correct.
 */

   private void dumpBoundsMarkers() {
      dumpShort(OP_SHORT_LINE);         /* Opcode           */
      dumpShort(0);                     /* Origin: y        */
      dumpShort(0);                     /*         x        */
      dumpShort(0);                     /* delta = (0,0)    */
      dumpShort(OP_SHORT_LINE);         /* Opcode           */
      dumpShort(height);                /* Origin: y        */
      dumpShort(width);                 /*         x        */
      dumpShort(0);                     /* delta = (0,0)    */
   }

/**
 * Inserts a <code>DirectBitsRect</code> operation along with the associated
 * data for the image.
 */

   private void dumpDirectBitsRect() {
      dumpShort(OP_DIRECT_BITS_RECT);   /* Opcode           */
      dumpPixMap();                     /* Inline pixmap    */
      dumpShort(0);                     /* srcRect: y       */
      dumpShort(0);                     /*          x       */
      dumpShort(height);                /*          height  */
      dumpShort(width);                 /*          width   */
      dumpShort(0);                     /* dstRect: y       */
      dumpShort(0);                     /*          x       */
      dumpShort(height);                /*          height  */
      dumpShort(width);                 /*          width   */
      dumpShort(SRC_COPY);              /* Transfer mode    */
      dumpPixelData();                  /* Inline data      */
   }

/**
 * Inserts a <code>PixMap</code> operation structure used to specify
 * the properties of the image.
 */

   private void dumpPixMap() {
      dumpInt(0xFF);                    /* Inline marker    */
      dumpShort(rowBytes | 0x8000);     /* Row bytes + flag */
      dumpShort(0);                     /* Bounds: y        */
      dumpShort(0);                     /*         x        */
      dumpShort(height);                /*         height   */
      dumpShort(width);                 /*         width    */
      dumpShort(0);                     /* PixMap version   */
      dumpShort(4);                     /* Packing format   */
      dumpInt(0);                       /* Packed size      */
      dumpShort(72);                    /* X resolution     */
      dumpShort(0);                     /* Fixed (72, 0)    */
      dumpShort(72);                    /* Y resolution     */
      dumpShort(0);                     /* Fixed (72, 0)    */
      dumpShort(RGB_DIRECT);            /* Pixel type       */
      dumpShort(32);                    /* Bits per pixel   */
      dumpShort(3);                     /* Component count  */
      dumpShort(8);                     /* Component size   */
      dumpInt(0);                       /* Plane bytes      */
      dumpInt(0);                       /* No color table   */
      dumpInt(0);                       /* Reserved         */
   }

/**
 * Dumps the <code>EndPict</code> operation at the end of the PICT file.
 */

   private void dumpEndPict() {
      dumpShort(OP_END_PICT);
   };

/**
 * Dumps the actual pixel data, one scan line at a time.
 */

   private void dumpPixelData() {
      int byteCount = 0;
      byte[] data = new byte[rowBytes];
      for (int i = 0; i < height; i++) {
         int nBytes = packScanLine(data, pixels[i]);
         if (rowBytes > 250) {
            dumpShort(nBytes);
            byteCount += 2;
         } else {
            dumpByte(nBytes);
            byteCount++;
         }
         for (int j = 0; j < nBytes; j++) {
            dumpByte(data[j]);
         }
         byteCount += nBytes;
      }
      if (byteCount % 2 == 1) dumpByte(0);
   }

/**
 * Packs the data from the pixel scan line into the data buffer.
 * This packing method always uses Macintosh QuickTime (type 4)
 * encoding, because that is the only packing type that most
 * applications understand.
 *
 * <p>Each packed scanline uses run-length encoding to compress
 * the data for each component of the scan line independently,
 * starting with the red values.  Each sequence of bytes in the
 * encoding is preceded by a flag byte <code>b</code>, which has
 * two interpretations depending on its high-order bit:
 *
 * <p><ul>
 *    <li>If the high-order bit is 0, the flag byte is followed by
 *        <code>b + 1</code> data bytes.
 *    <li>If that bit is 1, the flag byte is followed by (-b)
 *        <code>-b + 1</code> copies of the next byte.
 * </ul>
 *
 * <p>Some PICT readers seem to preallocate space for a scan line
 * based on the maximal size of the optimal run-length encoding.
 * Unfortunately, in a scan line with short matching sequences
 * alternating with short independent sequences, the naive
 * implementation of run-length encoding can exceed this limit.
 * To avoid this problem, this implementation encodes a component
 * and then tests to see whether it is longer than the same encoding
 * assuming all bytes are independent.  If so, it replaces the
 * naive encoding with the shorter brute-force one.
 */

   private int packScanLine(byte[] data, int[] scanline) {
      int flagIndex = 0;
      for (int rgbIndex = 0; rgbIndex < 3; rgbIndex++) {
         char rgb = "RGB".charAt(rgbIndex);
         int baseIndex = flagIndex;
         int dataIndex = flagIndex + 1;
         int scanIndex = 0;
         while (scanIndex < width) {
            int b0 = getPixelComponent(scanline[scanIndex++], rgb);
            data[dataIndex++] = (byte) b0;
            int runLength = 1;
            boolean matching = false;
            if (scanIndex < width) {
               int b1 = getPixelComponent(scanline[scanIndex], rgb);
               matching = (b0 == b1);
               if (matching) {
                  while (runLength < 128 && scanIndex < width) {
                     b1 = getPixelComponent(scanline[scanIndex], rgb);
                     if (b0 != b1) break;
                     runLength++;
                     scanIndex++;
                  }
               } else {
                  while (runLength < 128 && scanIndex < width) {
                     b1 = getPixelComponent(scanline[scanIndex], rgb);
                     if (b0 == b1) {
                        dataIndex--;
                        runLength--;
                        scanIndex--;
                        break;
                     }
                     data[dataIndex++] = (byte) b1;
                     b0 = b1;
                     runLength++;
                     scanIndex++;
                  }
               }
            }
            if (matching) {
               data[flagIndex] = (byte) (0x80 | (129 - runLength));
            } else {
               data[flagIndex] = (byte) (runLength - 1);
            }
            flagIndex = dataIndex++;
         }
         if (flagIndex - baseIndex > width + width / 128) {
            int count = width;
            flagIndex = baseIndex;
            for (int i = 0; i < width; i++) {
               if (i % 128 == 0) {
                  int nBytes = (count > 128) ? 128 : count;
                  data[flagIndex++] = (byte) (nBytes - 1);
                  count -= nBytes;
               }
               data[flagIndex++] = (byte) getPixelComponent(scanline[i], rgb);
            }
         }
      }
      return flagIndex;
   }

/**
 * Writes out the code for the PostScript preview, which is embedded in
 * the picture comments.
 */

   private void dumpPSPreview() {
      addPSComment("/dictCount countdictstack def");
      addPSComment("/opCount count 1 sub def");
      addPSComment(PS_DICT_SIZE + " dict begin");
      addPSComment("/showpage {} def");
      addPSComment("0 setgray 0 setlinecap");
      addPSComment("1 setlinewidth 0 setlinejoin");
      addPSComment("10 setmiterlimit [] 0 setdash");
      addPSComment("/languagelevel where {");
      addPSComment("  pop languagelevel");
      addPSComment("  1 ne { false setstrokeadjust false setoverprint } if");
      addPSComment("} if");
      addPSComment("gsave");
      addPSComment("clippath pathbbox");
      addPSComment("pop pop " + height + " add translate");
      addPSComment("1 -1 scale");
      for (int i = 0; i < psPreview.length; i++) {
         addPSComment(psPreview[i]);
      }
      addPSComment("grestore");
      addPSComment("end");
      addPSComment("count opCount sub {pop} repeat");
      addPSComment("countdictstack dictCount sub {end} repeat");
   }

/**
 * Adds a PostScript comment line.
 */

   private void addPSComment(String line) {
      if (line.length() % 2 == 0) line += " ";
      dumpShort(OP_LONG_COMMENT);
      dumpShort(PS_HANDLE);
      dumpShort(line.length() + 1);
      for (int i = 0; i < line.length(); i++) {
         dumpByte(line.charAt(i));
      }
      dumpByte('\r');
   }

/* Private constants */
   private static final int OP_CLIP = 0x0001;
   private static final int OP_VERSION = 0x0011;
   private static final int OP_DEF_HILITE = 0x001E;
   private static final int OP_SHORT_LINE = 0x0022;
   private static final int OP_DIRECT_BITS_RECT = 0x009A;
   private static final int OP_SHORT_COMMENT = 0x00A0;
   private static final int OP_LONG_COMMENT = 0x00A1;
   private static final int OP_END_PICT = 0x00FF;
   private static final int OP_HEADER = 0x0C00;
   private static final int PS_BEGIN = 190;
   private static final int PS_END = 191;
   private static final int PS_HANDLE = 192;
   private static final int PS_DICT_SIZE = 500;
   private static final int VERSION = 0x02FF;
   private static final int PICT_PADDING = 512;
   private static final int RGB_DIRECT = 16;
   private static final int SRC_COPY = 0;

/* Private instance variables */
   private int[][] pixels;
   private String[] psPreview;
   private int width;
   private int height;
   private int rowBytes;
   private boolean paddingFlag = true;

}

class PICImageSaver extends PICTImageSaver {
   /* Entirely inherited from PICTImageSaver */
}

/* Package class: EPSImageSaver */
/**
 * This class saves EPS images.
 */
class EPSImageSaver extends ImageSaver {
   public void saveImage(Image image) {
      throw new RuntimeException("saveImage: Not yet implemented");
   }
}

/*+--------------------------------------------------------------------+*/
/*| NOTE:                                                              |*/
/*|   The remainder of this file consists of the public-domain GIF     |*/
/*|   encoder released by J. M. G. Elliott (tep@jmge.net), which is    |*/
/*|   available from http://jmge.net/java/gifenc/.                     |*/
/*|                                                                    |*/
/*|   The only changes made here are:                                  |*/
/*|     1. Change to comment format (reserving double-slash for        |*/
/*|        change markers)                                             |*/
/*|     2. Make all classes package private                            |*/
/*|     3. Fix all warnings generated by Eclipse                       |*/
/*+--------------------------------------------------------------------+*/

/*----------------------------------------------------------------------*/
/* DirectGif89Frame                                                     */
/*----------------------------------------------------------------------*/

/**
 * Instances of this Gif89Frame subclass are constructed from RGB image info,
 *  either in the form of an Image object or a pixel array.
 *  <p>
 *  There is an important restriction to note.  It is only permissible to add
 *  DirectGif89Frame objects to a Gif89Encoder constructed without an explicit
 *  color map.  The GIF color table will be automatically generated from pixel
 *  information.
 *
 * @version 0.90 beta (15-Jul-2000)
 * @author J. M. G. Elliott (tep@jmge.net)
 * @see Gif89Encoder
 * @see Gif89Frame
 * @see IndexGif89Frame
 */

class DirectGif89Frame extends Gif89Frame {

   private int[] argbPixels;

/**
 * Construct an DirectGif89Frame from a Java image.
 *
 * @param img
 *   A java.awt.Image object that supports pixel-grabbing.
 * @exception IOException
 *   If the image is unencodable due to failure of pixel-grabbing.
 */

   public DirectGif89Frame(Image img) throws IOException {
      PixelGrabber pg = new PixelGrabber(img, 0, 0, -1, -1, true);

      String errmsg = null;
      try {
         if (!pg.grabPixels())
            errmsg = "can't grab pixels from image";
      } catch (InterruptedException e) {
         errmsg = "interrupted grabbing pixels from image";
      }

      if (errmsg != null)
         throw new IOException(errmsg + " (" + getClass().getName() + ")");

      theWidth = pg.getWidth();
      theHeight = pg.getHeight();
      argbPixels = (int[]) pg.getPixels();
      ciPixels = new byte[argbPixels.length];
   }

/**
 * Construct an DirectGif89Frame from ARGB pixel data.
 *
 * @param width
 *   Width of the bitmap.
 * @param height
 *   Height of the bitmap.
 * @param argb_pixels
 *   Array containing at least width*height pixels in the format returned by
 *   java.awt.Color.getRGB().
 */

   public DirectGif89Frame(int width, int height, int argb_pixels[]) {
      theWidth = width;
      theHeight = height;
      argbPixels = new int[theWidth * theHeight];
      System.arraycopy(argb_pixels, 0, argbPixels, 0, argbPixels.length);
      ciPixels = new byte[argbPixels.length];
   }

   Object getPixelSource() { return argbPixels; }
}

/*----------------------------------------------------------------------*/
/* Gif89Encoder                                                         */
/*----------------------------------------------------------------------*/

/**
 * This is the central class of a JDK 1.1 compatible GIF encoder that, AFAIK,
 *  supports more features of the extended GIF spec than any other Java open
 *  source encoder.  Some sections of the source are lifted or adapted from Jef
 *  Poskanzer's <cite>Acme GifEncoder</cite> (so please see the
 *  <a href="../readme.txt">readme</a> containing his notice), but much of it,
 *  including nearly all of the present class, is original code.  My main
 *  motivation for writing a new encoder was to support animated GIFs, but the
 *  package also adds support for embedded textual comments.
 *  <p>
 *  There are still some limitations.  For instance, animations are limited to
 *  a single global color table.  But that is usually what you want anyway, so
 *  as to avoid irregularities on some displays.  (So this is not really a
 *  limitation, but a "disciplinary feature" :)  Another rather more serious
 *  restriction is that the total number of RGB colors in a given input-batch
 *  mustn't exceed 256.  Obviously, there is an opening here for someone who
 *  would like to add a color-reducing preprocessor.
 *  <p>
 *  The encoder, though very usable in its present form, is at bottom only a
 *  partial implementation skewed toward my own particular needs.  Hence a
 *  couple of caveats are in order.  (1) During development it was in the back
 *  of my mind that an encoder object should be reusable - i.e., you should be
 *  able to make multiple calls to encode() on the same object, with or without
 *  intervening frame additions or changes to options.  But I haven't reviewed
 *  the code with such usage in mind, much less tested it, so it's likely I
 *  overlooked something.  (2) The encoder classes aren't thread safe, so use
 *  caution in a context where access is shared by multiple threads.  (Better
 *  yet, finish the library and re-release it :)
 *  <p>
 *  There follow a couple of simple examples illustrating the most common way to
 *  use the encoder, i.e., to encode AWT Image objects created elsewhere in the
 *  program.  Use of some of the most popular format options is also shown,
 *  though you will want to peruse the API for additional features.
 *
 *  <p>
 *  <strong>Animated GIF Example</strong>
 *  <pre>
 *  import net.jmge.gif.Gif89Encoder;
 *  ...
 *  void writeAnimatedGIF(Image[] still_images,
 *                        String annotation,
 *                        boolean looped,
 *                        double frames_per_second,
 *                        OutputStream out) throws IOException
 *  {
 *    Gif89Encoder gifenc = new Gif89Encoder();
 *    for (int i = 0; i < still_images.length; ++i)
 *      gifenc.addFrame(still_images[i]);
 *    gifenc.setComments(annotation);
 *    gifenc.setLoopCount(looped ? 0 : 1);
 *    gifenc.setUniformDelay((int) Math.round(100 / frames_per_second));
 *    gifenc.encode(out);
 *  }
 *  </pre>
 *
 *  <strong>Static GIF Example</strong>
 *  <pre>
 *  import net.jmge.gif.Gif89Encoder;
 *  ...
 *  void writeNormalGIF(Image img,
 *                      String annotation,
 *                      int transparent_index,
 *                      boolean interlaced,
 *                      OutputStream out) throws IOException
 *  {
 *    Gif89Encoder gifenc = new Gif89Encoder(img);
 *    gifenc.setComments(annotation);
 *    gifenc.setTransparentIndex(transparent_index);
 *    gifenc.getFrameAt(0).setInterlaced(interlaced);
 *    gifenc.encode(out);
 *  }
 *  </pre>
 *
 * @version 0.90 beta (15-Jul-2000)
 * @author J. M. G. Elliott (tep@jmge.net)
 * @see Gif89Frame
 * @see DirectGif89Frame
 * @see IndexGif89Frame
 */
class Gif89Encoder {

   private Dimension dispDim = new Dimension(0, 0);
   private GifColorTable colorTable;
   private int bgIndex = 0;
   private int loopCount = 1;
   private String theComments;
   private Vector<Gif89Frame> vFrames = new Vector<Gif89Frame>();

/**
 * Use this default constructor if you'll be adding multiple frames
 * constructed from RGB data (i.e., AWT Image objects or ARGB-pixel arrays).
 */

   public Gif89Encoder() {
      /* empty color table puts us into "palette autodetect" mode */
      colorTable = new GifColorTable();
   }

/**
 * Like the default except that it also adds a single frame, for conveniently
 *  encoding a static GIF from an image.
 *
 * @param static_image
 *   Any Image object that supports pixel-grabbing.
 * @exception IOException
 *   See the addFrame() methods.
 */

   public Gif89Encoder(Image static_image) throws IOException {
      this();
      addFrame(static_image);
   }

/**
 * This constructor installs a user color table, overriding the detection of
 *  of a palette from ARBG pixels.
 *
 *  Use of this constructor imposes a couple of restrictions:
 *  (1) Frame objects can't be of type DirectGif89Frame
 *  (2) Transparency, if desired, must be set explicitly.
 *
 * @param colors
 *   Array of color values; no more than 256 colors will be read, since that's
 *   the limit for a GIF.
 */

   public Gif89Encoder(Color[] colors) {
      colorTable = new GifColorTable(colors);
   }

/**
 * Convenience constructor for encoding a static GIF from index-model data.
 *  Adds a single frame as specified.
 *
 * @param colors
 *   Array of color values; no more than 256 colors will be read, since
 *   that's the limit for a GIF.
 * @param width
 *   Width of the GIF bitmap.
 * @param height
 *   Height of same.
 * @param ci_pixels
 *   Array of color-index pixels no less than width * height in length.
 * @exception IOException
 *   See the addFrame() methods.
 */

   public Gif89Encoder(Color[] colors, int width, int height, byte ci_pixels[])
   throws IOException {
      this(colors);
      addFrame(width, height, ci_pixels);
   }

/**
 * Get the number of frames that have been added so far.
 *
 * @return
 *  Number of frame items.
 */

   public int getFrameCount() { return vFrames.size(); }

/**
 * Get a reference back to a Gif89Frame object by position.
 *
 * @param index
 *   Zero-based index of the frame in the sequence.
 * @return
 *   Gif89Frame object at the specified position (or null if no such frame).
 */

   public Gif89Frame getFrameAt(int index) {
      return isOk(index) ? (Gif89Frame) vFrames.elementAt(index) : null;
   }

/**
 * Add a Gif89Frame frame to the end of the internal sequence.  Note that
 *  there are restrictions on the Gif89Frame type: if the encoder object was
 *  constructed with an explicit color table, an attempt to add a
 *  DirectGif89Frame will throw an exception.
 *
 * @param gf
 *   An externally constructed Gif89Frame.
 * @exception IOException
 *   If Gif89Frame can't be accommodated.  This could happen if either (1) the
 *   aggregate cross-frame RGB color count exceeds 256, or (2) the Gif89Frame
 *   subclass is incompatible with the present encoder object.
 */

   public void addFrame(Gif89Frame gf) throws IOException {
      accommodateFrame(gf);
      vFrames.addElement(gf);
   }

/**
 * Convenience version of addFrame() that takes a Java Image, internally
 * constructing the requisite DirectGif89Frame.
 *
 * @param image
 *   Any Image object that supports pixel-grabbing.
 * @exception IOException
 *   If either (1) pixel-grabbing fails, (2) the aggregate cross-frame RGB
 *   color count exceeds 256, or (3) this encoder object was constructed with
 *   an explicit color table.
 */

   public void addFrame(Image image) throws IOException {
      addFrame(new DirectGif89Frame(image));
   }

/**
 * The index-model convenience version of addFrame().
 *
 * @param width
 *   Width of the GIF bitmap.
 * @param height
 *   Height of same.
 * @param ci_pixels
 *   Array of color-index pixels no less than width * height in length.
 * @exception IOException
 *   Actually, in the present implementation, there aren't any unchecked
 *   exceptions that can be thrown when adding an IndexGif89Frame
 *   <i>per se</i>.  But I might add some pedantic check later, to justify the
 *   generality :)
 */

   public void addFrame(int width, int height, byte ci_pixels[])
   throws IOException {
      addFrame(new IndexGif89Frame(width, height, ci_pixels));
   }

/**
 * Like addFrame() except that the frame is inserted at a specific point in
 *  the sequence rather than appended.
 *
 * @param index
 *   Zero-based index at which to insert frame.
 * @param gf
 *   An externally constructed Gif89Frame.
 * @exception IOException
 *   If Gif89Frame can't be accommodated.  This could happen if either (1)
 *   the aggregate cross-frame RGB color count exceeds 256, or (2) the
 *   Gif89Frame subclass is incompatible with the present encoder object.
 */

   public void insertFrame(int index, Gif89Frame gf) throws IOException {
      accommodateFrame(gf);
      vFrames.insertElementAt(gf, index);
   }

/**
 * Set the color table index for the transparent color, if any.
 *
 * @param index
 *   Index of the color that should be rendered as transparent, if any.
 *   A value of -1 turns off transparency.  (Default: -1)
 */

   public void setTransparentIndex(int index) {
      colorTable.setTransparent(index);
   }

/**
 * Sets attributes of the multi-image display area, if applicable.
 *
 * @param dim
 *   Width/height of display.  (Default: largest detected frame size)
 * @param background
 *   Color table index of background color.  (Default: 0)
 * @see Gif89Frame#setPosition
 */

   public void setLogicalDisplay(Dimension dim, int background) {
      dispDim = new Dimension(dim);
      bgIndex = background;
   }

/**
 * Set animation looping parameter, if applicable.
 *
 * @param count
 *   Number of times to play sequence.  Special value of 0 specifies
 *   indefinite looping.  (Default: 1)
 */

   public void setLoopCount(int count) {
      loopCount = count;
   }

/**
 * Specify some textual comments to be embedded in GIF.
 *
 * @param comments
 *   String containing ASCII comments.
 */

   public void setComments(String comments) {
      theComments = comments;
   }

/**
 * A convenience method for setting the "animation speed".  It simply sets
 *  the delay parameter for each frame in the sequence to the supplied value.
 *  Since this is actually frame-level rather than animation-level data, take
 *  care to add your frames before calling this method.
 *
 * @param interval
 *   Interframe interval in centiseconds.
 */

   public void setUniformDelay(int interval) {
      for (int i = 0; i < vFrames.size(); ++i)
         vFrames.elementAt(i).setDelay(interval);
   }

/**
 * After adding your frame(s) and setting your options, simply call this
 * method to write the GIF to the passed stream.  Multiple calls are
 * permissible if for some reason that is useful to your application.  (The
 * method simply encodes the current state of the object with no thought
 * to previous calls.)
 *
 * @param out
 *   The stream you want the GIF written to.
 * @exception IOException
 *   If a write error is encountered.
 */

   public void encode(OutputStream out) throws IOException {
      int     nframes = getFrameCount();
      boolean is_sequence = nframes > 1;

      /* N.B. must be called before writing screen descriptor */
      colorTable.closePixelProcessing();

      /* write GIF HEADER */
      Gif89Put.ascii("GIF89a", out);

      /* write global blocks */
      writeLogicalScreenDescriptor(out);
      colorTable.encode(out);
      if (is_sequence && loopCount != 1)
         writeNetscapeExtension(out);
      if (theComments != null && theComments.length() > 0)
         writeCommentExtension(out);

      /* write out the control and rendering data for each frame */
      for (int i = 0; i < nframes; ++i)
         vFrames.elementAt(i).encode(out,
                                     is_sequence,
                                     colorTable.getDepth(),
                                     colorTable.getTransparent());

      /* write GIF TRAILER */
      out.write(';');

      out.flush();
   }

/**
 * A simple driver to test the installation and to demo usage.  Put the JAR
 * on your classpath and run ala
 * <blockquote>java net.jmge.gif.Gif89Encoder {filename}</blockquote>
 * The filename must be either (1) a JPEG file with extension 'jpg', for
 * conversion to a static GIF, or (2) a file containing a list of GIFs and/or
 * JPEGs, one per line, to be combined into an animated GIF.  The output will
 * appear in the current directory as 'gif89out.gif'.
 * <p>
 * (N.B. This test program will abort if the input file(s) exceed(s) 256 total
 * RGB colors, so in its present form it has no value as a generic JPEG to GIF
 * converter.  Also, when multiple files are input, you need to be wary of the
 * total color count, regardless of file type.)
 *
 * @param args
 *   Command-line arguments, only the first of which is used, as mentioned
 *   above.
 */

   public static void main(String[] args) {
      try {

         Toolkit      tk = Toolkit.getDefaultToolkit();
         OutputStream out = new BufferedOutputStream(
               new FileOutputStream("gif89out.gif")
         );

         if (args[0].toUpperCase().endsWith(".JPG"))
            new Gif89Encoder(tk.getImage(args[0])).encode(out);
         else {
            BufferedReader in = new BufferedReader(new FileReader(args[0]));
            Gif89Encoder   ge = new Gif89Encoder();

            String line;
            while ((line = in.readLine()) != null)
               ge.addFrame(tk.getImage(line.trim()));
            ge.setLoopCount(0);  /* let's loop indefinitely  */
            ge.encode(out);

            in.close();
         }
         out.close();

      }
      catch (Exception e) { e.printStackTrace(); }
      finally { System.exit(0); } /* must kill VM explicitly (Toolkit thread?) */
   }

   private void accommodateFrame(Gif89Frame gf) throws IOException {
      dispDim.width = Math.max(dispDim.width, gf.getWidth());
      dispDim.height = Math.max(dispDim.height, gf.getHeight());
      colorTable.processPixels(gf);
   }

   private void writeLogicalScreenDescriptor(OutputStream os) throws IOException {
      Gif89Put.leShort(dispDim.width, os);
      Gif89Put.leShort(dispDim.height, os);

      /* write 4 fields, packed into a byte  (bitfieldsize:value) */
      /*   global color map present?         (1:1)                */
      /*   bits per primary color less 1     (3:7)                */
      /*   sorted color table?               (1:0)                */
      /*   bits per pixel less 1             (3:varies)           */
      os.write(0xf0 | colorTable.getDepth() - 1);

      /* write background color index  */
      os.write(bgIndex);

      /* Jef Poskanzer's notes on the next field, for our possible edification: */
      /* Pixel aspect ratio - 1:1. */
      /*Putbyte( (byte) 49, outs ); */
      /* Java's GIF reader currently has a bug, if the aspect ratio byte is */
      /* not zero it throws an ImageFormatException.  It doesn't know that */
      /* 49 means a 1:1 aspect ratio.  Well, whatever, zero works with all */
      /* the other decoders I've tried so it probably doesn't hurt. */

      /* OK, if it's good enough for Jef, it's definitely good enough for us: */
      os.write(0);
   }

   private void writeNetscapeExtension(OutputStream os) throws IOException {
      /* n.b. most software seems to interpret the count as a repeat count */
      /* (i.e., interations beyond 1) rather than as an iteration count */
      /* (thus, to avoid repeating we have to omit the whole extension) */

      os.write('!');                 /* GIF Extension Introducer */
      os.write(0xff);                /* Application Extension Label */

      os.write(11);                  /* application ID block size */
      Gif89Put.ascii("NETSCAPE2.0", os);  /* application ID data */

      os.write(3);                   /* data sub-block size */
      os.write(1);                   /* a looping flag? dunno */

      /* we finally write the relevent data */
      Gif89Put.leShort(loopCount > 1 ? loopCount - 1 : 0, os);

      os.write(0);                   /* block terminator */
   }

   private void writeCommentExtension(OutputStream os) throws IOException {
      os.write('!');           /* GIF Extension Introducer */
      os.write(0xfe);          /* Comment Extension Label */

      int remainder = theComments.length() % 255;
      int nsubblocks_full = theComments.length() / 255;
      int nsubblocks = nsubblocks_full + (remainder > 0 ? 1 : 0);
      int ibyte = 0;
      for (int isb = 0; isb < nsubblocks; ++isb) {
         int size = isb < nsubblocks_full ? 255 : remainder;

         os.write(size);
         Gif89Put.ascii(theComments.substring(ibyte, ibyte + size), os);
         ibyte += size;
      }

      os.write(0);    /* block terminator */
   }

   private boolean isOk(int frame_index) {
      return frame_index >= 0 && frame_index < vFrames.size();
   }
}

class GifColorTable {

/* the palette of ARGB colors, packed as returned by Color.getRGB() */
   private int[] theColors = new int[256];

/* other basic attributes */
   private int   colorDepth;
   private int   transparentIndex = -1;

/* these fields track color-index info across frames */
   private int             ciCount = 0; /* count of distinct color indices */
   private ReverseColorMap ciLookup;    /* cumulative rgb-to-ci lookup table */

   GifColorTable() {
      ciLookup = new ReverseColorMap();  /* puts us into "auto-detect mode" */
   }

   GifColorTable(Color[] colors) {
      int n2copy = Math.min(theColors.length, colors.length);
      for (int i = 0; i < n2copy; ++i)
         theColors[i] = colors[i].getRGB();
   }

   int getDepth() { return colorDepth; }

   int getTransparent() { return transparentIndex; }

/* default: -1 (no transparency) */
   void setTransparent(int color_index) {
      transparentIndex = color_index;
   }

   void processPixels(Gif89Frame gf) throws IOException {
      if (gf instanceof DirectGif89Frame)
         filterPixels((DirectGif89Frame) gf);
      else
         trackPixelUsage((IndexGif89Frame) gf);
   }

   void closePixelProcessing() { /* must be called before encode() */
      colorDepth = computeColorDepth(ciCount);
   }

   void encode(OutputStream os) throws IOException {
      /* size of palette written is the smallest power of 2 that can accomdate */
      /* the number of RGB colors detected (or largest color index, in case of */
      /* index pixels) */
      int palette_size = 1 << colorDepth;
      for (int i = 0; i < palette_size; ++i) {
         os.write(theColors[i] >> 16 & 0xff);
         os.write(theColors[i] >>  8 & 0xff);
         os.write(theColors[i] & 0xff);
      }
   }

/*
 * This method accomplishes three things:
 * (1) converts the passed rgb pixels to indexes into our rgb lookup table
 * (2) fills the rgb table as new colors are encountered
 * (3) looks for transparent pixels so as to set the transparent index
 * The information is cumulative across multiple calls.
 *
 * (Note: some of the logic is borrowed from Jef Poskanzer's code.)
 */

   private void filterPixels(DirectGif89Frame dgf) throws IOException {
      if (ciLookup == null)
         throw new IOException("RGB frames require palette autodetection");

      int[]  argb_pixels = (int[]) dgf.getPixelSource();
      byte[] ci_pixels = dgf.getPixelSink();
      int    npixels = argb_pixels.length;
      for (int i = 0; i < npixels; ++i) {
         int argb = argb_pixels[i];

         /* handle transparency */
         if ((argb >>> 24) < 0x80)        /* transparent pixel? */
            if (transparentIndex == -1)    /* first transparent color encountered? */
               transparentIndex = ciCount;  /* record its index */
            else if (argb != theColors[transparentIndex]) {
               /* different pixel value? */
               /* collapse all transparent pixels into one color index */
               ci_pixels[i] = (byte) transparentIndex;
               continue;  /* CONTINUE - index already in table */
            }

         /* try to look up the index in our "reverse" color table */
         int color_index = ciLookup.getPaletteIndex(argb & 0xffffff);

         if (color_index == -1) {
            /* if it isn't in there yet */
            if (ciCount == 256)
               throw new IOException("can't encode as GIF (> 256 colors)");

            /* store color in our accumulating palette */
            theColors[ciCount] = argb;

            /* store index in reverse color table   */
            ciLookup.put(argb & 0xffffff, ciCount);

            /* send color index to our output array */
            ci_pixels[i] = (byte) ciCount;

            /* increment count of distinct color indices */
            ++ciCount;
         }
         else  /* we've already snagged color into our palette */
            ci_pixels[i] = (byte) color_index;  /* just send filtered pixel    */
      }
   }

   private void trackPixelUsage(IndexGif89Frame igf) {
      byte[] ci_pixels = (byte[]) igf.getPixelSource();
      int    npixels = ci_pixels.length;
      for (int i = 0; i < npixels; ++i)
         if (ci_pixels[i] >= ciCount)
            ciCount = ci_pixels[i] + 1;
   }

   private int computeColorDepth(int colorcount) {
      /* color depth = log-base-2 of maximum number of simultaneous colors, i.e. */
      /* bits per color-index pixel     */
      if (colorcount <= 2)
         return 1;
      if (colorcount <= 4)
         return 2;
      if (colorcount <= 16)
         return 4;
      return 8;
   }
}

/*
 * We're doing a very simple linear hashing thing here, which seems sufficient
 * for our needs.  I make no claims for this approach other than that it seems
 * an improvement over doing a brute linear search for each pixel on the one
 * hand, and creating a Java object for each pixel (if we were to use a Java
 * Hashtable) on the other.  Doubtless my little hash could be improved by
 * tuning the capacity (at the very least).  Suggestions are welcome.
 */
class ReverseColorMap {

   private static class ColorRecord {
      int rgb;
      int ipalette;
      ColorRecord(int rgb, int ipalette) {
         this.rgb = rgb;
         this.ipalette = ipalette;
      }
   }

/*
 * I wouldn't really know what a good hashing capacity is, having missed out
 * on data structures and algorithms class :)  Alls I know is, we've got a lot
 * more space than we have time.  So let's try a sparse table with a maximum
 * load of about 1/8 capacity.
 */

   private static final int HCAPACITY = 2053;  /* a nice prime number */

/* our hash table proper */
   private ColorRecord[] hTable = new ColorRecord[HCAPACITY];

/*
 * Assert: rgb is not negative (which is the same as saying, be sure the
 * alpha transparency byte - i.e., the high byte - has been masked out).
 */

   int getPaletteIndex(int rgb) {
      ColorRecord rec;

      for ( int itable = rgb % hTable.length;
      (rec = hTable[itable]) != null && rec.rgb != rgb;
      itable = ++itable % hTable.length
      )
         ;

      if (rec != null)
         return rec.ipalette;

      return -1;
   }

/*
 * Assert: (1) same as above; (2) rgb key not already present
 */

   void put(int rgb, int ipalette) {
      int itable;

      for ( itable = rgb % hTable.length;
      hTable[itable] != null;
      itable = ++itable % hTable.length
      )
         ;

      hTable[itable] = new ColorRecord(rgb, ipalette);
   }
}

/*----------------------------------------------------------------------*/
/* Gif89Frame                                                           */
/*----------------------------------------------------------------------*/

/**
 * First off, just to dispel any doubt, this class and its subclasses have
 *  nothing to do with GUI "frames" such as java.awt.Frame.  We merely use the
 *  term in its very common sense of a still picture in an animation sequence.
 *  It's hoped that the restricted context will prevent any confusion.
 *  <p>
 *  An instance of this class is used in conjunction with a Gif89Encoder object
 *  to represent and encode a single static image and its associated "control"
 *  data.  A Gif89Frame doesn't know or care whether it is encoding one of the
 *  many animation frames in a GIF movie, or the single bitmap in a "normal"
 *  GIF. (FYI, this design mirrors the encoded GIF structure.)
 *  <p>
 *  Since Gif89Frame is an abstract class we don't instantiate it directly, but
 *  instead create instances of its concrete subclasses, IndexGif89Frame and
 *  DirectGif89Frame.  From the API standpoint, these subclasses differ only
 *  in the sort of data their instances are constructed from.  Most folks will
 *  probably work with DirectGif89Frame, since it can be constructed from a
 *  java.awt.Image object, but the lower-level IndexGif89Frame class offers
 *  advantages in specialized circumstances.  (Of course, in routine situations
 *  you might not explicitly instantiate any frames at all, instead letting
 *  Gif89Encoder's convenience methods do the honors.)
 *  <p>
 *  As far as the public API is concerned, objects in the Gif89Frame hierarchy
 *  interact with a Gif89Encoder only via the latter's methods for adding and
 *  querying frames.  (As a side note, you should know that while Gif89Encoder
 *  objects are permanently modified by the addition of Gif89Frames, the reverse
 *  is NOT true.  That is, even though the ultimate encoding of a Gif89Frame may
 *  be affected by the context its parent encoder object provides, it retains
 *  its original condition and can be reused in a different context.)
 *  <p>
 *  The core pixel-encoding code in this class was essentially lifted from
 *  Jef Poskanzer's well-known <cite>Acme GifEncoder</cite>, so please see the
 *  <a href="../readme.txt">readme</a> containing his notice.
 *
 * @version 0.90 beta (15-Jul-2000)
 * @author J. M. G. Elliott (tep@jmge.net)
 * @see Gif89Encoder
 * @see DirectGif89Frame
 * @see IndexGif89Frame
 */
abstract class Gif89Frame {

/* Public "Disposal Mode" constants */

/**
 * The animated GIF renderer shall decide how to dispose of this Gif89Frame's
 *  display area.
 * @see Gif89Frame#setDisposalMode
 */

   public static final int DM_UNDEFINED = 0;

/**
 * The animated GIF renderer shall take no display-disposal action.
 * @see Gif89Frame#setDisposalMode
 */

   public static final int DM_LEAVE     = 1;

/**
 * The animated GIF renderer shall replace this Gif89Frame's area with the
 * background color.
 * @see Gif89Frame#setDisposalMode
 */

   public static final int DM_BGCOLOR   = 2;

/**
 * The animated GIF renderer shall replace this Gif89Frame's area with the
 * previous frame's bitmap.
 * @see Gif89Frame#setDisposalMode
 */

   public static final int DM_REVERT    = 3;

/* Bitmap variables set in package subclass constructors */
   int    theWidth = -1;
   int    theHeight = -1;
   byte[] ciPixels;

/* GIF graphic frame control options  */
   private Point   thePosition = new Point(0, 0);
   private boolean isInterlaced;
   private int     csecsDelay;
   private int     disposalCode = DM_LEAVE;

/**
 * Set the position of this frame within a larger animation display space.
 *
 * @param p
 *   Coordinates of the frame's upper left corner in the display space.
 *   (Default: The logical display's origin [0, 0])
 * @see Gif89Encoder#setLogicalDisplay
 */

   public void setPosition(Point p) {
      thePosition = new Point(p);
   }

/**
 * Set or clear the interlace flag.
 *
 * @param b
 *   true if you want interlacing.  (Default: false)
 */

   public void setInterlaced(boolean b) {
      isInterlaced = b;
   }

/**
 * Set the between-frame interval.
 *
 * @param interval
 *   Centiseconds to wait before displaying the subsequent frame.
 *   (Default: 0)
 */

   public void setDelay(int interval) {
      csecsDelay = interval;
   }

/**
 * Setting this option determines (in a cooperative GIF-viewer) what will be
 *  done with this frame's display area before the subsequent frame is
 *  displayed.  For instance, a setting of DM_BGCOLOR can be used for erasure
 *  when redrawing with displacement.
 *
 * @param code
 *   One of the four int constants of the Gif89Frame.DM_* series.
 *  (Default: DM_LEAVE)
 */

   public void setDisposalMode(int code) {
      disposalCode = code;
   }

   Gif89Frame() {}  /* package-visible default constructor */

   abstract Object getPixelSource();

   int getWidth() { return theWidth; }

   int getHeight() { return theHeight; }

   byte[] getPixelSink() { return ciPixels; }

   void encode(OutputStream os, boolean epluribus, int color_depth,
         int transparent_index) throws IOException {
      writeGraphicControlExtension(os, epluribus, transparent_index);
      writeImageDescriptor(os);
      new GifPixelsEncoder(
            theWidth, theHeight, ciPixels, isInterlaced, color_depth
      ).encode(os);
         }

   private void writeGraphicControlExtension(OutputStream os, boolean epluribus,
         int itransparent) throws IOException {
      int transflag = itransparent == -1 ? 0 : 1;
      if (transflag == 1 || epluribus) {  /* using transparency or animating ? */
         os.write('!');                   /* GIF Extension Introducer */
         os.write(0xf9);                  /* Graphic Control Label */
         os.write(4);                     /* subsequent data block size */
         os.write((disposalCode << 2) | transflag); /* packed fields (1 byte) */
         Gif89Put.leShort(csecsDelay, os);  /* delay field (2 bytes) */
         os.write(itransparent);          /* transparent index field */
         os.write(0);                     /* block terminator */
            }
         }

   private void writeImageDescriptor(OutputStream os) throws IOException {
      os.write(',');                       /* Image Separator */
      Gif89Put.leShort(thePosition.x, os);
      Gif89Put.leShort(thePosition.y, os);
      Gif89Put.leShort(theWidth, os);
      Gif89Put.leShort(theHeight, os);
      os.write(isInterlaced ? 0x40 : 0);  /* packed fields (1 byte) */
   }
}

class GifPixelsEncoder {

   private static final int EOF = -1;

   private int     imgW, imgH;
   private byte[]  pixAry;
   private boolean wantInterlaced;
   private int     initCodeSize;

/* raster data navigators */
   private int     countDown;
   private int     xCur, yCur;
   private int     curPass;

   GifPixelsEncoder(int width, int height, byte[] pixels, boolean interlaced,
         int color_depth) {
      imgW = width;
      imgH = height;
      pixAry = pixels;
      wantInterlaced = interlaced;
      initCodeSize = Math.max(2, color_depth);
         }

   void encode(OutputStream os) throws IOException {
      os.write(initCodeSize);         /* write "initial code size" byte */

      countDown = imgW * imgH;        /* reset navigation variables */
      xCur = yCur = curPass = 0;

      compress(initCodeSize + 1, os); /* compress and write the pixel data */

      os.write(0);                    /* write block terminator */
   }

/*
 * (J.E.) The logic of the next two methods is largely intact from
 * Jef Poskanzer.  Some stylistic changes were made for consistency sake,
 * plus the second method accesses the pixel value from a prefiltered linear
 * array.  That's about it.
 */

/* Bump the 'xCur' and 'yCur' to point to the next pixel. */
   private void bumpPosition() {
      /* Bump the current X position */
      ++xCur;

      /* If we are at the end of a scan line, set xCur back to the beginning */
      /* If we are interlaced, bump the yCur to the appropriate spot, */
      /* otherwise, just increment it. */
      if (xCur == imgW) {
         xCur = 0;

         if (!wantInterlaced)
            ++yCur;
         else
            switch (curPass) {
            case 0:
               yCur += 8;
               if (yCur >= imgH) {
                  ++curPass;
                  yCur = 4;
               }
               break;
            case 1:
               yCur += 8;
               if (yCur >= imgH) {
                  ++curPass;
                  yCur = 2;
               }
               break;
            case 2:
               yCur += 4;
               if (yCur >= imgH) {
                  ++curPass;
                  yCur = 1;
               }
               break;
            case 3:
               yCur += 2;
               break;
            }
      }
   }

/* Return the next pixel from the image */
   private int nextPixel() {
      if (countDown == 0)
         return EOF;

      --countDown;

      byte pix = pixAry[yCur * imgW + xCur];

      bumpPosition();

      return pix & 0xff;
   }

/*
 * (J.E.) I didn't touch Jef Poskanzer's code from this point on.  (Well, OK,
 * I changed the name of the sole outside method it accesses.)  I figure
 * if I have no idea how something works, I shouldn't play with it :)
 *
 * Despite its unencapsulated structure, this section is actually highly
 * self-contained.  The calling code merely calls compress(), and the present
 * code calls nextPixel() in the caller.  That's the sum total of their
 * communication.  I could have dumped it in a separate class with a callback
 * via an interface, but it didn't seem worth messing with.
 */

/* GIFCOMPR.C       - GIF Image compression routines */

/* Lempel-Ziv compression based on 'compress'.  GIF modifications by */
/* David Rowley (mgardi@watdcsu.waterloo.edu) */

/* General DEFINEs */

   static final int BITS = 12;

   static final int HSIZE = 5003;                /* 80% occupancy */

/*
 * GIF Image compression - modified 'compress'
 *
 * Based on: compress.c - File compression ala IEEE Computer, June 1984.
 *
 * By Authors:  Spencer W. Thomas      (decvax!harpo!utah-cs!utah-gr!thomas)
 *              Jim McKie              (decvax!mcvax!jim)
 *              Steve Davies           (decvax!vax135!petsd!peora!srd)
 *              Ken Turkowski          (decvax!decwrl!turtlevax!ken)
 *              James A. Woods         (decvax!ihnp4!ames!jaw)
 *              Joe Orost              (decvax!vax135!petsd!joe)
 */

   int n_bits;                     /* number of bits/code */
   int maxbits = BITS;             /* user settable max # bits/code */
   int maxcode;                    /* maximum code, given n_bits */
   int maxmaxcode = 1 << BITS;     /* should NEVER generate this code */

   final int MAXCODE( int n_bits ) {
      return ( 1 << n_bits ) - 1;
   }

   int[] htab = new int[HSIZE];
   int[] codetab = new int[HSIZE];

   int hsize = HSIZE;                /* for dynamic table sizing */

   int free_ent = 0;                        /* first unused entry */

/* block compression parameters -- after all codes are used up, */
/* and compression rate changes, start over. */
   boolean clear_flg = false;

/*
 * Algorithm:  use open addressing double hashing (no chaining) on the
 * prefix code / next character combination.  We do a variant of Knuth's
 * algorithm D (vol. 3, sec. 6.4) along with G. Knott's relatively-prime
 * secondary probe.  Here, the modular division first probe is gives way
 * to a faster exclusive-or manipulation.  Also do block compression with
 * an adaptive reset, whereby the code table is cleared when the compression
 * ratio decreases, but after the table fills.  The variable-length output
 * codes are re-sized at this point, and a special CLEAR code is generated
 * for the decompressor.  Late addition:  construct the table according to
 * file size for noticeable speed improvement on small files.  Please direct
 * questions about this implementation to ames!jaw.
 */

   int g_init_bits;

   int ClearCode;
   int EOFCode;

   void compress( int init_bits, OutputStream outs ) throws IOException {
      int fcode;
      int i /* = 0 */;
      int c;
      int ent;
      int disp;
      int hsize_reg;
      int hshift;

      /* Set up the globals:  g_init_bits - initial number of bits */
      g_init_bits = init_bits;

      /* Set up the necessary values */
      clear_flg = false;
      n_bits = g_init_bits;
      maxcode = MAXCODE( n_bits );

      ClearCode = 1 << ( init_bits - 1 );
      EOFCode = ClearCode + 1;
      free_ent = ClearCode + 2;

      char_init();

      ent = nextPixel();

      hshift = 0;
      for ( fcode = hsize; fcode < 65536; fcode *= 2 )
         ++hshift;
      hshift = 8 - hshift;         /* set hash code range bound */

      hsize_reg = hsize;
      cl_hash( hsize_reg );        /* clear hash table */

      output( ClearCode, outs );

      outer_loop:
         while ( (c = nextPixel()) != EOF ) {
            fcode = ( c << maxbits ) + ent;
            i = ( c << hshift ) ^ ent; /* xor hashing */

            if ( htab[i] == fcode ) {
               ent = codetab[i];
               continue;
            }
            else if ( htab[i] >= 0 ) { /* non-empty slot */
               disp = hsize_reg - i;   /* secondary hash (after G. Knott) */
               if ( i == 0 )
                  disp = 1;
               do {
                  if ( (i -= disp) < 0 )
                     i += hsize_reg;

                  if ( htab[i] == fcode ) {
                     ent = codetab[i];
                     continue outer_loop;
                  }
               }
               while ( htab[i] >= 0 );
            }
            output( ent, outs );
            ent = c;
            if ( free_ent < maxmaxcode ) {
               codetab[i] = free_ent++; /* code -> hashtable */
               htab[i] = fcode;
            }
            else
               cl_block( outs );
         }
      /* Put out the final code. */
      output( ent, outs );
      output( EOFCode, outs );
   }

/*
 * output
 *
 * Output the given code.
 * Inputs:
 *      code:   A n_bits-bit integer.  If == -1, then EOF.  This assumes
 *              that n_bits =< wordsize - 1.
 * Outputs:
 *      Outputs code to the file.
 * Assumptions:
 *      Chars are 8 bits long.
 * Algorithm:
 *      Maintain a BITS character long buffer (so that 8 codes will
 * fit in it exactly).  Use the VAX insv instruction to insert each
 * code in turn.  When the buffer fills up empty it and start over.
 */

   int cur_accum = 0;
   int cur_bits = 0;

   int masks[] = { 0x0000, 0x0001, 0x0003, 0x0007, 0x000F,
         0x001F, 0x003F, 0x007F, 0x00FF,
         0x01FF, 0x03FF, 0x07FF, 0x0FFF,
         0x1FFF, 0x3FFF, 0x7FFF, 0xFFFF };

   void output( int code, OutputStream outs ) throws IOException {
      cur_accum &= masks[cur_bits];

      if ( cur_bits > 0 )
         cur_accum |= ( code << cur_bits );
      else
         cur_accum = code;

      cur_bits += n_bits;

      while ( cur_bits >= 8 ) {
         char_out( (byte) ( cur_accum & 0xff ), outs );
         cur_accum >>= 8;
         cur_bits -= 8;
      }

      /* If the next entry is going to be too big for the code size, */
      /* then increase it, if possible. */
      if ( free_ent > maxcode || clear_flg ) {
         if ( clear_flg ) {
            maxcode = MAXCODE(n_bits = g_init_bits);
            clear_flg = false;
         }
         else {
            ++n_bits;
            if ( n_bits == maxbits )
               maxcode = maxmaxcode;
            else
               maxcode = MAXCODE(n_bits);
         }
      }

      if ( code == EOFCode ) {
         /* At EOF, write the rest of the buffer. */
         while ( cur_bits > 0 ) {
            char_out( (byte) ( cur_accum & 0xff ), outs );
            cur_accum >>= 8;
      cur_bits -= 8;
         }

         flush_char( outs );
      }
   }

/* Clear out the hash table */

/* table clear for block compress */
   void cl_block( OutputStream outs ) throws IOException {
      cl_hash( hsize );
      free_ent = ClearCode + 2;
      clear_flg = true;

      output( ClearCode, outs );
   }

/* reset code table */
   void cl_hash( int hsize ) {
      for ( int i = 0; i < hsize; ++i )
         htab[i] = -1;
   }

/* GIF Specific routines */

/* Number of characters so far in this 'packet' */
   int a_count;

/* Set up the 'byte output' routine */
   void char_init() {
      a_count = 0;
   }

/* Define the storage for the packet accumulator */
   byte[] accum = new byte[256];

/* Add a character to the end of the current packet, and if it is 254 */
/* characters, flush the packet to disk. */
   void char_out( byte c, OutputStream outs ) throws IOException {
      accum[a_count++] = c;
      if ( a_count >= 254 )
         flush_char( outs );
   }

/* Flush the packet to disk, and reset the accumulator */
   void flush_char( OutputStream outs ) throws IOException {
      if ( a_count > 0 ) {
         outs.write( a_count );
         outs.write( accum, 0, a_count );
         a_count = 0;
      }
   }
}

/*----------------------------------------------------------------------*/
/* IndexGif89Frame                                                      */
/*----------------------------------------------------------------------*/

/**
 * Instances of this Gif89Frame subclass are constructed from bitmaps in the
 * form of color-index pixels, which accords with a GIF's native palettized
 * color model.  The class is useful when complete control over a GIF's color
 * palette is desired.  It is also much more efficient when one is using an
 * algorithmic frame generator that isn't interested in RGB values (such
 * as a cellular automaton).
 * <p>
 * Objects of this class are normally added to a Gif89Encoder object that has
 * been provided with an explicit color table at construction.  While you may
 * also add them to "auto-map" encoders without an exception being thrown,
 * there obviously must be at least one DirectGif89Frame object in the sequence
 * so that a color table may be detected.
 *
 * @version 0.90 beta (15-Jul-2000)
 * @author J. M. G. Elliott (tep@jmge.net)
 * @see Gif89Encoder
 * @see Gif89Frame
 * @see DirectGif89Frame
 */
class IndexGif89Frame extends Gif89Frame {

/**
 * Construct a IndexGif89Frame from color-index pixel data.
 *
 * @param width
 *   Width of the bitmap.
 * @param height
 *   Height of the bitmap.
 * @param ci_pixels
 *   Array containing at least width*height color-index pixels.
 */

   public IndexGif89Frame(int width, int height, byte ci_pixels[]) {
      theWidth = width;
      theHeight = height;
      ciPixels = new byte[theWidth * theHeight];
      System.arraycopy(ci_pixels, 0, ciPixels, 0, ciPixels.length);
   }

   Object getPixelSource() { return ciPixels; }
}

/*----------------------------------------------------------------------*/
/* Gif89Put                                                             */
/*----------------------------------------------------------------------*/

/**
 * Just a couple of trivial output routines used by other classes in the
 * package.  Normally this kind of stuff would be in a separate IO package, but
 * I wanted the present package to be self-contained for ease of distribution
 * and use by others.
 */

final class Gif89Put {

/**
 * Write just the low bytes of a String.  (This sucks, but the concept of an
 *  encoding seems inapplicable to a binary file ID string.  I would think
 *  flexibility is just what we don't want - but then again, maybe I'm slow.)
 */

   static void ascii(String s, OutputStream os) throws IOException {
      byte[] bytes = new byte[s.length()];
      for (int i = 0; i < bytes.length; ++i)
         bytes[i] = (byte) s.charAt(i);  /* discard the high byte      */
      os.write(bytes);
   }

/**
 * Write a 16-bit integer in little endian byte order.
 */

   static void leShort(int i16, OutputStream os) throws IOException {
      os.write(i16 & 0xff);
      os.write(i16 >> 8 & 0xff);
   }

}
