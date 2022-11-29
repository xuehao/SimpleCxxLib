/*
 * File: error.cpp
 * ---------------
 * Implementation of the error function.
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

#include "error.h"
#include <exception>
#include <iostream>
#include <string>

/* Definitions for the ErrorException class */

ErrorException::ErrorException(std::string msg) {
    this->msg = msg;
}

ErrorException::~ErrorException() throw() {
    /* Empty */
}

std::string ErrorException::getMessage() const {
    return msg;
}

const char* ErrorException::what() const throw() {
    return msg.c_str();
}

/*
 * Implementation notes: error
 * ---------------------------
 * Earlier implementations of error made it possible, at least on the
 * Macintosh, to help the debugger generate a backtrace at the point
 * of the error.  Unfortunately, doing so is no longer possible if
 * the errors are catchable.
 */

void error(std::string msg) {
    throw ErrorException(msg);
}
