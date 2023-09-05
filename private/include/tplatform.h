/*
 * File: tplatform.h
 * -----------------
 * This interface defines the platform-specific methods on threads
 * and locks.
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

/* Methods for threads */

int forkForPlatform(void (*fn)(void*), void* arg);
void incThreadRefCountForPlatform(int id);
void decThreadRefCountForPlatform(int id);
void joinForPlatform(int id);
int getCurrentThreadForPlatform();
void yieldForPlatform();

/* Methods for locks */

int initLockForPlatform();
void incLockRefCountForPlatform(int id);
void decLockRefCountForPlatform(int id);
void lockForPlatform(int id);
void unlockForPlatform(int id);
void waitForPlatform(int id);
void signalForPlatform(int id);
