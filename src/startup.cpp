/*
 * File: startup.cpp
 * -----------------
 * This file implements the wrapper for main that allows for
 * system initialization and error handling.
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

/* Global flag word indicating option for main */

int _mainFlags;

/* Stored arguments */

static int argcMain;
static char** argvMain;

int mainWrapper(int argc, char** argv) {
    extern int Main();
    argcMain = argc;
    argvMain = argv;
    try {
        return Main();
    } catch (ErrorException& ex) {
        std::string msg = "Error: " + ex.getMessage();
        std::cerr << msg << std::endl;
        return EXIT_FAILURE;
    }
}

int getArgumentCount() {
    return argcMain;
}

char** getArguments() {
    return argvMain;
}
