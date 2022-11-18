/*
 * @(#)JBEFileFilter.java   3.01.1 07/30/14
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

package edu.stanford.cs.java.spl;

import java.io.File;
import java.util.StringTokenizer;
import javax.swing.filechooser.FileFilter;

public class JBEFileFilter extends FileFilter {

/**
 * Creates a <code>JBEChooserFilter</code> that accepts filenames
 * matching the specified pattern.  This pattern consists of a
 * wildcard pattern (or a series of wildcard patterns separated
 * by semicolons) similar to those by a Unix shell.  For example, to
 * match all files ending with the extensions <code>.html</code>
 * or <code>.htm</code>, you could use the following constructor call:
 *
 *<pre>
 *    new JBEFileFilter("*.html;*.htm")
 *</pre>
 *
 * @param pattern The filename pattern
 */

   public JBEFileFilter(String path) {
      pattern = getPatternPart(path);
      description = (pattern.isEmpty() ? "All" : pattern) + " files";
      int sp = Math.max(path.lastIndexOf("/"), path.lastIndexOf('\\'));
      dir = (sp == -1) ? "" : path.substring(0, sp);
      String last = path.substring(sp + 1);
      if (!isPattern(last)) {
         if (dir.isEmpty()) dir += "/";
         dir += last;
      }
      if (dir.isEmpty()) {
         dir = System.getProperty("user.dir");
      } else if (!dir.startsWith("/")) {
         dir = System.getProperty("user.dir") + "/" + dir;
      }
   }

/**
 * Gets the directory associated with the <code>JBEFileFilter</code>.
 *
 * @return The directory associated with the <code>JBEFileFilter</code>.
 */

   public String getDirectory() {
      return dir;
   }

/**
 * Returns the last component of the original pattern argument, which is
 * the wildcard pattern.
 *
 * @return The pattern associated with the <code>JBEFileFilter</code>.
 */

   public String getPattern() {
      return pattern;
   }

/**
 * Returns a description of the accepted files.
 */

   public String getDescription() {
      return description;
   }

/**
 * Returns <code>true</code> if the specified file should be accepted by
 * the filter.
 *
 * @param file The <code>File</code> object representing the file
 * @return <code>true</code> if the specified file should be accepted
 */

   public boolean accept(File file) {
      if (file.isDirectory() || pattern.isEmpty()) return true;
      StringTokenizer tokenizer = new StringTokenizer(pattern, ";");
      while (tokenizer.hasMoreTokens()) {
         String pat = tokenizer.nextToken();
         if (pat.length() > 0 && matchPattern(file.getName(), pat)) {
            return true;
         }
      }
      return false;
   }

   private static String getPatternPart(String path) {
      int sp = Math.max(path.lastIndexOf("/"), path.lastIndexOf('\\'));
      String last = path.substring(sp + 1);
      return (isPattern(last)) ? last : null;
   }

   private static boolean isPattern(String str) {
      for (int i = 0; i < str.length(); i++) {
         switch (str.charAt(i)) {
          case ';': case '*': case '?': case '[': case ']': return true;
         }
      }
      return false;
   }

/**
 * Determines whether the filename matches the specified pattern.  The
 * pattern string is interpreted in much the same way that a Unix shell
 * expands filenames and supports the following wildcard options:
 *
 * <table>
 * <tr><td align=center><code>?</code></td>
 *     <td>Matches any single character</td></tr>
 * <tr><td align=center><code>*</code></td>
 *     <td>Matches any sequence of characters</td></tr>
 * <tr><td align=center><code>[...]</code></td>
 *     <td>Matches any of the specified characters</td></tr>
 * <tr><td align=center><code>[^...]</code></td>
 *     <td>Matches any character <i>except</i> the specified ones</td></tr>
 * </table>
 *
 * The last two options allow a range of characters to be specified in
 * the form <code>a-z</code>.
 *
 * @param filename The filename being tested
 * @param pattern The pattern including wildcards
 * @return <code>true</code> if the filename matches the pattern
 */

   private static boolean matchPattern(String filename, String pattern) {
      return recursiveMatch(filename, 0, pattern, 0);
   }

/**
 * This method implements the filename matcher in a way that requires no
 * string allocation.  The <code>sx</code> and <code>px</code> parameters
 * are the current index in their respective strings.
 */

   private static boolean recursiveMatch(String str, int sx,
                                         String pattern, int px) {
      int strlen = str.length();
      int patlen = pattern.length();
      if (px == patlen) return (sx == strlen);
      char pch = pattern.charAt(px);
      if (pch == '*') {
         for (int i = sx; i <= strlen; i++) {
            if (recursiveMatch(str, i, pattern, px + 1)) return true;
         }
         return false;
      }
      if (sx == strlen) return false;
      char sch = str.charAt(sx);
      if (pch == '[') {
         boolean match = false;
         boolean invert = false;
         px++;
         if (px == patlen) {
            throw new RuntimeException("matchFilenamePattern: missing ]");
         }
         if (pattern.charAt(px) == '^') {
            px++;
            invert = true;
         }
         while (px < patlen && pattern.charAt(px) != ']') {
            if (px + 2 < patlen && pattern.charAt(px + 1) == '-') {
               match |= (sch >= pattern.charAt(px) &&
                         sch <= pattern.charAt(px + 2));
               px += 3;
            } else {
               match |= (sch == pattern.charAt(px));
               px++;
            }
         }
         if (px == patlen) {
            throw new RuntimeException("matchFilenamePattern: missing ]");
         }
         if (match == invert) return false;
      } else if (pch != '?') {
         if (pch != sch) return false;
      }
      return recursiveMatch(str, sx + 1, pattern, px + 1);
   }

/* Private instance variables */

   private String dir;
   private String pattern;
   private String description;

}
