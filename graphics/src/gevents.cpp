/*
 * File: gevents.cpp
 * -----------------
 * This file implements the machine-independent functions for the classes
 * in the gevents.h interface.  The actual functions for receiving events
 * from the environment are implemented in the platform package.
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
 * Implementation notes:
 * ---------------------
 * The classes in this hierarchy are defined in an unusual way
 * for C++ in that all instance variables are part of the top-level
 * class.  The advantage of this design is that the GEvent class
 * then has all of the memory it needs to store an event of any of
 * its subclasses.
 */

#include "gevents.h"

#include <cctype>
#include <iostream>
#include <sstream>
#include <string>

#include "error.h"
#include "gtimer.h"
#include "gtypes.h"
#include "map.h"
#include "platform.h"

/* Implementation of GEvent class */

GEvent::GEvent() {
    eventClass = NULL_EVENT;
    eventType = 0;
    valid = false;
    modifiers = 0;
}

EventClassType GEvent::getEventClass() const {
    return eventClass;
}

EventType GEvent::getEventType() const {
    return EventType(eventType);
}

double GEvent::getEventTime() const {
    return eventTime;
}

int GEvent::getModifiers() const {
    return modifiers;
}

std::string GEvent::toString() const {
    if (eventClass == 0) {
        return "GEvent(NULL)";
    } else if (eventClass == WINDOW_EVENT) {
        GWindowEvent windowEvent(*this);
        return (&windowEvent)->toString();
    } else if (eventClass == ACTION_EVENT) {
        GActionEvent actionEvent(*this);
        return (&actionEvent)->toString();
    } else if (eventClass == MOUSE_EVENT) {
        GMouseEvent mouseEvent(*this);
        return (&mouseEvent)->toString();
    } else if (eventClass == KEY_EVENT) {
        GKeyEvent keyEvent(*this);
        return (&keyEvent)->toString();
    } else if (eventClass == TIMER_EVENT) {
        GTimerEvent timerEvent(*this);
        return (&timerEvent)->toString();
    } else {
        return "GEvent(?)";
    }
}

bool GEvent::isValid() {
    return valid;
}

void GEvent::setEventTime(double time) {
    eventTime = time;
}

void GEvent::setModifiers(int modifiers) {
    this->modifiers = modifiers;
}

GWindowEvent::GWindowEvent() {
    valid = false;
}

GWindowEvent::GWindowEvent(GEvent e) {
    valid = e.valid && e.eventClass == WINDOW_EVENT;
    if (valid) {
        eventClass = e.eventClass;
        eventType = e.eventType;
        modifiers = e.modifiers;
        eventTime = e.eventTime;
        gwd = e.gwd;
    }
}

GWindowEvent::GWindowEvent(EventType type, const GWindow& gw) {
    this->eventClass = WINDOW_EVENT;
    this->eventType = int(type);
    this->gwd = gw.gwd;
    valid = true;
}

GWindow GWindowEvent::getGWindow() const {
    return GWindow(gwd);
}

std::string GWindowEvent::toString() const {
    if (!valid)
        return "GWindowEvent(?)";
    std::ostringstream os;
    os << "GWindowEvent:";
    switch (eventType) {
        case WINDOW_CLOSED:
            os << "WINDOW_CLOSED";
            break;
        case WINDOW_RESIZED:
            os << "WINDOW_RESIZED";
            break;
    }
    os << "()";
    return os.str();
}

GActionEvent::GActionEvent() {
    valid = false;
}

GActionEvent::GActionEvent(GEvent e) {
    valid = e.valid && e.eventClass == ACTION_EVENT;
    if (valid) {
        eventClass = e.eventClass;
        eventType = e.eventType;
        modifiers = e.modifiers;
        eventTime = e.eventTime;
        source = e.source;
        actionCommand = e.actionCommand;
    }
}

GActionEvent::GActionEvent(EventType type, GObject* source, std::string actionCommand) {
    this->eventClass = ACTION_EVENT;
    this->eventType = int(type);
    this->source = source;
    this->actionCommand = actionCommand;
    valid = true;
}

GObject* GActionEvent::getSource() const {
    return source;
}

std::string GActionEvent::getActionCommand() const {
    if (!valid)
        error("getActionCommand: Event is not valid");
    return actionCommand;
}

std::string GActionEvent::toString() const {
    if (!valid)
        return "GActionEvent(?)";
    std::ostringstream os;
    os << "GActionEvent:ACTION_PERFORMED(" << actionCommand << ")";
    return os.str();
}

GMouseEvent::GMouseEvent() {
    valid = false;
}

GMouseEvent::GMouseEvent(GEvent e) {
    valid = e.valid && e.eventClass == MOUSE_EVENT;
    if (valid) {
        eventClass = e.eventClass;
        eventType = e.eventType;
        modifiers = e.modifiers;
        eventTime = e.eventTime;
        x = e.x;
        y = e.y;
    }
}

GMouseEvent::GMouseEvent(EventType type, const GWindow& gw, double x, double y) {
    this->eventClass = MOUSE_EVENT;
    this->eventType = int(type);
    this->gwd = gw.gwd;
    this->x = x;
    this->y = y;
    valid = true;
}

GWindow GMouseEvent::getGWindow() const {
    return GWindow(gwd);
}

double GMouseEvent::getX() const {
    if (!valid)
        error("getX: Event is not valid");
    return x;
}

double GMouseEvent::getY() const {
    if (!valid)
        error("getY: Event is not valid");
    return y;
}

std::string GMouseEvent::toString() const {
    if (!valid)
        return "GMouseEvent(?)";
    std::ostringstream os;
    os << "GMouseEvent:";
    switch (eventType) {
        case MOUSE_PRESSED:
            os << "MOUSE_PRESSED";
            break;
        case MOUSE_RELEASED:
            os << "MOUSE_RELEASED";
            break;
        case MOUSE_CLICKED:
            os << "MOUSE_CLICKED";
            break;
        case MOUSE_MOVED:
            os << "MOUSE_MOVED";
            break;
        case MOUSE_DRAGGED:
            os << "MOUSE_DRAGGED";
            break;
    }
    os << "(" << x << ", " << y << ")";
    return os.str();
}

GKeyEvent::GKeyEvent() {
    valid = false;
}

GKeyEvent::GKeyEvent(GEvent e) {
    this->eventClass = KEY_EVENT;
    valid = e.valid && e.eventClass == KEY_EVENT;
    if (valid) {
        eventClass = e.eventClass;
        eventType = e.eventType;
        modifiers = e.modifiers;
        eventTime = e.eventTime;
        keyChar = e.keyChar;
        keyCode = e.keyCode;
    }
}

GKeyEvent::GKeyEvent(EventType type, const GWindow& gw, int keyChar, int keyCode) {
    this->eventClass = KEY_EVENT;
    this->eventType = int(type);
    this->gwd = gw.gwd;
    this->keyChar = keyChar;
    this->keyCode = keyCode;
    valid = true;
}

GWindow GKeyEvent::getGWindow() const {
    return GWindow(gwd);
}

char GKeyEvent::getKeyChar() const {
    if (!valid)
        error("getKey: Event is not valid");
    return char(keyChar);
    // Think about wide characters at some point
}

int GKeyEvent::getKeyCode() const {
    if (!valid)
        error("getKey: Event is not valid");
    return keyCode;
}

std::string GKeyEvent::toString() const {
    if (!valid)
        return "GKeyEvent(?)";
    std::ostringstream os;
    os << "GKeyEvent:";
    int ch = '\0';
    switch (eventType) {
        case KEY_PRESSED:
            os << "KEY_PRESSED";
            ch = keyCode;
            break;
        case KEY_RELEASED:
            os << "KEY_RELEASED";
            ch = keyCode;
            break;
        case KEY_TYPED:
            os << "KEY_TYPED";
            ch = keyChar;
            break;
    }
    if (isprint(ch)) {
        os << "('" << char(ch) << "')";
    } else {
        os << std::oct << "('\\" << ch << "')";
    }
    return os.str();
}

/* Timer events */

GTimerEvent::GTimerEvent() {
    valid = false;
}

GTimerEvent::GTimerEvent(GEvent e) {
    valid = e.valid && e.eventClass == TIMER_EVENT;
    if (valid) {
        eventClass = e.eventClass;
        eventType = e.eventType;
        modifiers = e.modifiers;
        eventTime = e.eventTime;
        gtd = e.gtd;
    }
}

GTimerEvent::GTimerEvent(EventType type, const GTimer& timer) {
    this->eventClass = TIMER_EVENT;
    this->eventType = int(type);
    this->gtd = timer.gtd;
    valid = true;
}

GTimer GTimerEvent::getGTimer() const {
    return GTimer(gtd);
}

std::string GTimerEvent::toString() const {
    if (!valid)
        return "GTimerEvent(?)";
    return "GTimerEvent:TIMER_TICKED()";
}

/* Global event handlers */

void waitForClick() {
    waitForEvent(CLICK_EVENT);
}

GEvent waitForEvent(int mask) {
    return getPlatform()->waitForEvent(mask);
}

GEvent getNextEvent(int mask) {
    return getPlatform()->getNextEvent(mask);
}
