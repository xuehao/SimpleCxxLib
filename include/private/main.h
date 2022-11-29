/*
 * File: main.h
 * ------------
 * This file renames the <code>main</code> method in the client's
 * program to <code>Main</code>, thereby allowing a custom
 * <code>main</code> method in the libraries to take control
 * before passing control back to the client program.  The main macro
 * also defines a function getMainFlags that returns an int whose bits
 * indicate which of the various interfaces have been loaded by this
 * definition of main.
 *
 * Note: This file can be loaded more than once and must therefore
 * check to see what has already been defined.
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

#include <cstdlib>
#include <iostream>
#include "error.h"

#ifdef main
#undef main
#else
#define MAIN_USES_CONSOLE (1 << 0)
#define MAIN_USES_GRAPHICS (1 << 1)
#endif

#ifdef CONSOLE_FLAG
#undef CONSOLE_FLAG
#endif
#ifdef _console_h
#define CONSOLE_FLAG MAIN_USES_CONSOLE
#else
#define CONSOLE_FLAG 0
#endif

#ifdef GRAPHICS_FLAG
#undef GRAPHICS_FLAG
#endif
#ifdef _gwindow_h
#define GRAPHICS_FLAG MAIN_USES_GRAPHICS
#else
#define GRAPHICS_FLAG 0
#endif

#if CONSOLE_FLAG | GRAPHICS_FLAG
// mingw/linux
#define main                                               \
    main(int argc, char** argv) {                          \
        extern int Main();                                 \
        extern int startupMain(int argc, char** argv);     \
        extern int _mainFlags;                             \
        _mainFlags = GRAPHICS_FLAG + CONSOLE_FLAG;         \
        try {                                              \
            return startupMain(argc, argv);                \
        } catch (ErrorException & ex) {                    \
            std::string msg = "Error: " + ex.getMessage(); \
            std::cerr << msg << std::endl;                 \
            return EXIT_FAILURE;                           \
        }                                                  \
    }                                                      \
    int Main
#else
// macOS
#define main                                           \
    main(int argc, char** argv) {                      \
        extern int mainWrapper(int argc, char** argv); \
        extern int _mainFlags;                         \
        _mainFlags = GRAPHICS_FLAG + CONSOLE_FLAG;     \
        return mainWrapper(argc, argv);                \
    }                                                  \
    int Main
#endif

extern int getArgumentCount();
extern char** getArguments();
