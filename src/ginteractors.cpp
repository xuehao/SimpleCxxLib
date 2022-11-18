/*
 * File: gobjects.cpp
 * ------------------
 * This file implements the ginteractors.h interface.
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

#include "ginteractors.h"
#include <iostream>
#include <sstream>
#include "gevents.h"
#include "gobjects.h"
#include "gtypes.h"
#include "gwindow.h"
#include "platform.h"

static Platform* pp = getPlatform();

/*
 * Implementation notes: GInteractor class
 * ---------------------------------------
 */

GInteractor::GInteractor() {
    actionCommand = "";
}

void GInteractor::setActionCommand(std::string cmd) {
    actionCommand = cmd;
    pp->setActionCommand(this, cmd);
}

std::string GInteractor::getActionCommand() {
    return actionCommand;
}

void GInteractor::setSize(const GDimension& size) {
    setSize(size.getWidth(), size.getHeight());
}

void GInteractor::setSize(double width, double height) {
    pp->setSize(this, width, height);
}

void GInteractor::setBounds(const GRectangle& rect) {
    setLocation(rect.getX(), rect.getY());
    setSize(rect.getWidth(), rect.getHeight());
}

void GInteractor::setBounds(double x, double y, double width, double height) {
    setLocation(x, y);
    setSize(width, height);
}

GRectangle GInteractor::getBounds() const {
    GDimension size = pp->getSize((GObject*)this);
    return GRectangle(x, y, size.getWidth(), size.getHeight());
}

/*
 * Implementation notes: GButton class
 * -----------------------------------
 */

GButton::GButton(std::string label) {
    this->label = label;
    pp->createGButton(this, label);
}

std::string GButton::getType() const {
    return "GButton";
}

std::string GButton::toString() const {
    std::ostringstream oss;
    oss << "GButton(\"" << label << "\")";
    return oss.str();
}

/*
 * Implementation notes: GCheckBox class
 * -------------------------------------
 */

GCheckBox::GCheckBox(std::string label) {
    this->label = label;
    pp->createGCheckBox(this, label);
}

bool GCheckBox::isSelected() {
    return pp->isSelected(this);
}

void GCheckBox::setSelected(bool state) {
    pp->setSelected(this, state);
}

std::string GCheckBox::getType() const {
    return "GCheckBox";
}

std::string GCheckBox::toString() const {
    std::ostringstream oss;
    oss << "GCheckBox(\"" << label << "\")";
    return oss.str();
}

/*
 * Implementation notes: GSlider class
 * -----------------------------------
 */

GSlider::GSlider() {
    create(0, 100, 50);
}

GSlider::GSlider(int min, int max, int value) {
    create(min, max, value);
}

int GSlider::getValue() {
    return pp->getValue(this);
}

void GSlider::setValue(int value) {
    pp->setValue(this, value);
}

std::string GSlider::getType() const {
    return "GSlider";
}

std::string GSlider::toString() const {
    std::ostringstream oss;
    oss << "GSlider()";
    return oss.str();
}

void GSlider::create(int min, int max, int value) {
    this->min = min;
    this->max = max;
    pp->createGSlider(this, min, max, value);
}

/*
 * Implementation notes: GTextField class
 * --------------------------------------
 */

GTextField::GTextField() {
    pp->createGTextField(this, 10);
}

GTextField::GTextField(int nChars) {
    pp->createGTextField(this, nChars);
}

std::string GTextField::getText() {
    return pp->getText(this);
}

void GTextField::setText(std::string str) {
    pp->setText(this, str);
}

std::string GTextField::getType() const {
    return "GTextField";
}

std::string GTextField::toString() const {
    std::ostringstream oss;
    oss << "GTextField()";
    return oss.str();
}

/*
 * Implementation notes: GChooser class
 * ------------------------------------
 */

GChooser::GChooser() {
    pp->createGChooser(this);
}

void GChooser::addItem(std::string item) {
    pp->addItem(this, item);
}

std::string GChooser::getSelectedItem() {
    return pp->getSelectedItem(this);
}

void GChooser::setSelectedItem(std::string item) {
    pp->setSelectedItem(this, item);
}

std::string GChooser::getType() const {
    return "GChooser";
}

std::string GChooser::toString() const {
    std::ostringstream oss;
    oss << "GChooser()";
    return oss.str();
}
