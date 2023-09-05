/*
 * File: TestRandomLibrary.cpp
 * ---------------------------
 * This file tests to see if the distribution of random values
 * seems reasonable.
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

#include <limits.h>

#include <cmath>
#include <iostream>
#include <string>

#include "random.h"
#include "unittest.h"
using namespace std;

const int N_RANGES = 20;
const int N_TRIALS = 10000;

static bool randomIntegerSeemsReasonable(int low, int high);
static bool randomRealSeemsReasonable(double low, double high);
static bool randomChanceSeemsReasonable(double p = 0.5);
static bool hugeRangeSeemsReasonable();

void testRandomLibrary() {
    test(randomIntegerSeemsReasonable(0, 9), true);
    test(randomIntegerSeemsReasonable(-10, 10), true);
    test(randomRealSeemsReasonable(0.0, 10.0), true);
    test(randomRealSeemsReasonable(-100.0, 100.0), true);
    test(randomChanceSeemsReasonable(), true);
    test(randomChanceSeemsReasonable(0), true);
    test(randomChanceSeemsReasonable(1), true);
    test(randomChanceSeemsReasonable(0.9), true);
    test(hugeRangeSeemsReasonable(), true);
    reportResult("random.h library");
}

static bool randomIntegerSeemsReasonable(int low, int high) {
    int rangeSize = high - low + 1;
    int* counts = new int[rangeSize];
    for (int i = 0; i < rangeSize; i++) {
        counts[i] = 0;
    }
    for (int i = 0; i < N_TRIALS; i++) {
        int k = randomInteger(low, high);
        if (k < low || k > high) {
            cerr << "randomInteger returned out of range value " << k << endl;
            return false;
        }
        counts[k - low]++;
    }
    double expected = double(N_TRIALS) / rangeSize;
    bool ok = true;
    for (int i = 0; i < rangeSize; i++) {
        int outcome = low + i;
        if (counts[i] < 0.5 * expected) {
            cerr << "Low count for outcome " << outcome << endl;
            ok = false;
        } else if (counts[i] > 1.5 * expected) {
            cerr << "High count for outcome " << outcome << endl;
            ok = false;
        }
    }
    delete[] counts;
    return ok;
}

static bool randomRealSeemsReasonable(double low, double high) {
    double range = high - low;
    int counts[N_RANGES];
    for (int i = 0; i < N_RANGES; i++) {
        counts[i] = 0;
    }
    for (int i = 0; i < N_TRIALS; i++) {
        double d = randomReal(low, high);
        if (d < low || d >= high) {
            cerr << "randomReal returned out of range value " << d << endl;
            return false;
        }
        counts[int(N_RANGES * (d - low) / range)]++;
    }
    double expected = double(N_TRIALS) / N_RANGES;
    bool ok = true;
    for (int i = 0; i < N_RANGES; i++) {
        if (counts[i] < 0.5 * expected) {
            cerr << "Low count for outcome " << i << endl;
            ok = false;
        } else if (counts[i] > 1.5 * expected) {
            cerr << "High count for outcome " << i << endl;
            ok = false;
        }
    }
    return ok;
}

static bool randomChanceSeemsReasonable(double p) {
    int hits = 0;
    for (int i = 0; i < N_TRIALS; i++) {
        if (randomChance(p))
            hits++;
    }
    double expected = p * N_TRIALS;
    if (hits < 0.5 * expected || (p == 1.0 && hits != N_TRIALS)) {
        cerr << "Hit count low" << endl;
        return false;
    } else if (hits > 1.5 * expected || (p == 0.0 && hits != 0)) {
        cerr << "Hit count high" << endl;
        return false;
    }
    return true;
}

static bool hugeRangeSeemsReasonable() {
    unsigned maskHigh = ((unsigned)INT_MAX + 1) >> 1;
    int rangesLeft = 0xF;
    for (int i = 0; i < N_TRIALS && rangesLeft; i++) {
        int k = randomInteger(INT_MIN, INT_MAX);
        int rangeBit;
        if (k < 0) {
            rangeBit = (k & maskHigh) ? 1 : 2;
        } else {
            rangeBit = (k & maskHigh) ? 8 : 4;
        }
        rangesLeft &= ~rangeBit;
    }
    if (rangesLeft & 1) {
        cerr << "No large negative values generated" << endl;
    }
    if (rangesLeft & 2) {
        cerr << "No small negative values generated" << endl;
    }
    if (rangesLeft & 4) {
        cerr << "No small positive values generated" << endl;
    }
    if (rangesLeft & 8) {
        cerr << "No large positive values generated" << endl;
    }
    return rangesLeft == 0;
}
