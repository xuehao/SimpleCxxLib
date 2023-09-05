/*
 * File: private/randompatch.h
 * ---------------------------
 * This file patches the implementation of the random number library
 * to avoid some serious bugs in standard implementations of rand,
 * particularly on Mac OS X.  It also includes a hack to set the
 * seed from the RANDOM_SEED environment variable, which makes it
 * possible to produce repeatable figures.
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

/*
 * Implementation notes: rand, srand
 * ---------------------------------
 * To ensure that this package works the same way on all platforms,
 * this file completely reimplements the rand and srand methods.  The
 * algorithm is a conventional linear congruential generator with the
 * parameters used in GNU's gclib.  RAND_MAX for this implementation
 * is 2147483647 (2^31 - 1).
 */

#define MULTIPLIER 1103515245
#define OFFSET     12345

static int _seed = 1;

#undef rand
#define rand() ((_seed = MULTIPLIER * _seed + OFFSET) & 0x7FFFFFFF)

#undef srand
#define srand(seed) (_seed = int(seed), _seed = (_seed <= 0) ? 1 : _seed)

#undef RAND_MAX
#define RAND_MAX 2147483647

/*
 * Implementation notes: Windows patch
 * -----------------------------------
 * On some versions of Windows, the time function is too coarse to use
 * as a random seed.  On those versions, this definition substitutes the
 * GetTickCount function.
 */

#ifdef _WIN32
#include <windows.h>
#define time(dummy) (GetTickCount())
#endif

#ifdef __APPLE__

#include <cstdlib>

static time_t patchedTime(time_t* dummy) {
    char* str = getenv("RANDOM_SEED");
    if (str == nullptr) {
        return time(nullptr);
    } else {
        return atoi(str);
    }
}

#define time(dummy) patchedTime(dummy)

#endif
