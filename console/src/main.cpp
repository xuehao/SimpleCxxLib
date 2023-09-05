/*
 * File: main.cpp
 * --------------
 * This file defines a default version of the Main function that takes
 * the argc and argv arguments.  This function must be defined in its
 * own module to ensure that it is loaded only if the client doesn't
 * supply one.
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

#include "main.h"

#include <cstdlib>
#include <iostream>

#include "error.h"

/* Stored arguments */

static int argcMain;
static char** argvMain;

/* A default version of the Main function that takes
 * the argc and argv arguments. */
int Main(int argc, char* argv[]) {
    extern int Main();
    return Main();
}

/* A wrapper for main that allows for system initialization
 * and error handling.
 */
int mainWrapper(int argc, char** argv) {
    extern int Main();
    argcMain = argc;
    argvMain = argv;
    try {
        return Main();
    } catch (ErrorException& ex) {
        std::string msg = "Error: " + ex.getMessage();
        error(msg);
        return EXIT_FAILURE;
    }
}

int getArgumentCount() {
    return argcMain;
}

char** getArguments() {
    return argvMain;
}
