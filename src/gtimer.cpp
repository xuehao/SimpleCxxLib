/*
 * File: gtimer.cpp
 * ----------------
 * This file implements the gtimer.h interface.
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

#include <iostream>
#include <sstream>
#include <string>
#include "platform.h"

/* Global variables */

static Platform* pp = getPlatform();

/* Implementation of the GTimer class */

GTimer::GTimer(double milliseconds) {
    gtd = new GTimerData();
    gtd->refCount = 1;
    pp->createTimer(*this, milliseconds);
}

GTimer::~GTimer() {
    if (--gtd->refCount == 0)
        delete gtd;
}

void GTimer::start() {
    pp->startTimer(*this);
}

void GTimer::stop() {
    pp->stopTimer(*this);
}

bool GTimer::operator==(GTimer t2) {
    return gtd == t2.gtd;
}

bool GTimer::operator!=(GTimer t2) {
    return gtd != t2.gtd;
}

GTimer::GTimer(GTimerData* gtd) {
    this->gtd = gtd;
    gtd->refCount++;
}

GTimer::GTimer(const GTimer& src) {
    this->gtd = src.gtd;
    this->gtd->refCount++;
}

GTimer& GTimer::operator=(const GTimer& src) {
    if (this != &src) {
        if (--gtd->refCount == 0)
            delete gtd;
        this->gtd = src.gtd;
        this->gtd->refCount++;
    }
    return *this;
}
