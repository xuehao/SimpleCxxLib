/*
 * File: console.h
 * ---------------
 * This file redirects the <code>cin</code>, <code>cout</code>,
 * and <code>cerr</code> channels to use a console window.  This file
 * must be included in the source file that contains the <code>main</code>
 * method, although it may be included in other source files as well.
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

#ifndef _console_h
#define _console_h

#include <string>

/*
 * Function: clearConsole
 * Usage: clearConsole();
 * ----------------------
 * Erases the contents of the console window.
 */

void clearConsole();

/*
 * Function: setConsoleFont
 * Usage: setConsoleFont(font);
 * ----------------------------
 * Changes the font used for the console.  The <code>font</code> parameter
 * is typically a string in the form <code>family-style-size</code>.
 * In this string, <code>family</code> is the name of the font family;
 * <code>style</code> is either missing (indicating a plain font) or one
 * of the strings <code>Bold</code>, <code>Italic</code>, or
 * <code>BoldItalic</code>; and <code>size</code> is an integer
 * indicating the point size.  If any of these components is
 * specified as an asterisk, the existing value is retained.
 * The <code>font</code> parameter can also be a sequence of
 * such specifications separated by semicolons, in which case the
 * first available font on the system is used.
 */

void setConsoleFont(const std::string& font);

/*
 * Function: setConsoleSize
 * Usage: setConsoleSize(width, height);
 * -------------------------------------
 * Changes the size of the console to the specified dimensions, measured
 * in pixels.
 */

void setConsoleSize(double width, double height);

#include "private/main.h"

#endif
