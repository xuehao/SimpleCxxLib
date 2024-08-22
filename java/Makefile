# Makefile for the Stanford Portable Library (spl) package
# Last modified on Sat Aug 16 17:30:02 2014 by eroberts
#****************************************************************

PKGNAME = spl
PKGPATH = $(PKGNAME)
JARFILE = $(PKGNAME).jar
TOOLS =

EXPORTJAR = $(HOME)/java/jar
EXPORTBIN = $(HOME)/bin

JAVAC = javac -sourcepath src \
              -d classes \
              -Xlint:-serial

CLASSES = \
    classes/graphics/G3DRect.class \
    classes/graphics/GArc.class \
    classes/graphics/GCanvas.class \
    classes/graphics/GCompound.class \
    classes/graphics/GContainer.class \
    classes/graphics/GDimension.class \
    classes/graphics/GFillable.class \
    classes/graphics/GImage.class \
    classes/graphics/GImageTools.class \
    classes/graphics/GLabel.class \
    classes/graphics/GLine.class \
    classes/graphics/GMath.class \
    classes/graphics/GObject.class \
    classes/graphics/GOval.class \
    classes/graphics/GPoint.class \
    classes/graphics/GPolygon.class \
    classes/graphics/GRect.class \
    classes/graphics/GRectangle.class \
    classes/graphics/GResizable.class \
    classes/graphics/GRoundRect.class \
    classes/graphics/GScalable.class \
    classes/graphics/GWindow.class \
    classes/spl/GButton.class \
    classes/spl/GCheckBox.class \
    classes/spl/GChooser.class \
    classes/spl/GInteractor.class \
    classes/spl/GSlider.class \
    classes/spl/GTextField.class \
    classes/spl/JBECanvas.class \
    classes/spl/JBECommand.class \
    classes/spl/JBEConsole.class \
    classes/spl/JBEFileFilter.class \
    classes/spl/JBELabel.class \
    classes/spl/JBETopCompound.class \
    classes/spl/JBEWindow.class \
    classes/spl/JavaBackEnd.class \
    classes/tokenscanner/TokenScanner.class


# ***************************************************************
# Entry to bring the package up to date
#    The "make all" entry should be the first real entry

all: $(CLASSES) $(JSFILE) jar

always:

jar: $(JARFILE)

# ***************************************************************
# Create the JAR file

$(JARFILE): $(CLASSES) JBEManifest.txt
	@rm -f classes/$(PKGPATH)/package.html
	@(cd classes ; jar cfvm ../$(JARFILE) ../JBEManifest.txt \
                       `find . -type f | sed 's|^[.]/||'`)


# ***************************************************************
# Standard entries to remove files from the directories
#    tidy    -- eliminate unwanted files
#    scratch -- delete derived files in preparation for rebuild

tidy:
	@rm -f `find . -name "*~" -o -name core -o -name "*.tmp"`

scratch clean: tidy
	@rm -fr classes/*
	@echo "[clean succeeded]"


# ***************************************************************
# Compilations for the Java classes

classes/graphics/G3DRect.class: \
          src/graphics/G3DRect.java \
          src/graphics/GCanvas.java \
          src/graphics/GCompound.java \
          src/graphics/GContainer.java \
          src/graphics/GDimension.java \
          src/graphics/GFillable.java \
          src/graphics/GMath.java \
          src/graphics/GObject.java \
          src/graphics/GPoint.java \
          src/graphics/GRect.java \
          src/graphics/GRectangle.java \
          src/graphics/GResizable.java \
          src/graphics/GScalable.java
	@echo javac src/graphics/G3DRect.java
	@$(JAVAC) src/graphics/G3DRect.java

classes/graphics/GArc.class: \
          src/graphics/GArc.java \
          src/graphics/GCanvas.java \
          src/graphics/GCompound.java \
          src/graphics/GContainer.java \
          src/graphics/GDimension.java \
          src/graphics/GFillable.java \
          src/graphics/GMath.java \
          src/graphics/GObject.java \
          src/graphics/GPoint.java \
          src/graphics/GRectangle.java \
          src/graphics/GResizable.java \
          src/graphics/GScalable.java
	@echo javac src/graphics/GArc.java
	@$(JAVAC) src/graphics/GArc.java

classes/graphics/GCanvas.class: \
          src/graphics/GCanvas.java \
          src/graphics/GCompound.java \
          src/graphics/GContainer.java \
          src/graphics/GDimension.java \
          src/graphics/GFillable.java \
          src/graphics/GMath.java \
          src/graphics/GObject.java \
          src/graphics/GPoint.java \
          src/graphics/GRectangle.java \
          src/graphics/GResizable.java \
          src/graphics/GScalable.java
	@echo javac src/graphics/GCanvas.java
	@$(JAVAC) src/graphics/GCanvas.java

classes/graphics/GCompound.class: \
          src/graphics/GCompound.java \
          src/graphics/GCanvas.java \
          src/graphics/GContainer.java \
          src/graphics/GDimension.java \
          src/graphics/GFillable.java \
          src/graphics/GMath.java \
          src/graphics/GObject.java \
          src/graphics/GPoint.java \
          src/graphics/GRectangle.java \
          src/graphics/GResizable.java \
          src/graphics/GScalable.java
	@echo javac src/graphics/GCompound.java
	@$(JAVAC) src/graphics/GCompound.java

classes/graphics/GContainer.class: \
          src/graphics/GContainer.java \
          src/graphics/GCanvas.java \
          src/graphics/GCompound.java \
          src/graphics/GDimension.java \
          src/graphics/GFillable.java \
          src/graphics/GMath.java \
          src/graphics/GObject.java \
          src/graphics/GPoint.java \
          src/graphics/GRectangle.java \
          src/graphics/GResizable.java \
          src/graphics/GScalable.java
	@echo javac src/graphics/GContainer.java
	@$(JAVAC) src/graphics/GContainer.java

classes/graphics/GDimension.class: \
          src/graphics/GDimension.java
	@echo javac src/graphics/GDimension.java
	@$(JAVAC) src/graphics/GDimension.java

classes/graphics/GFillable.class: \
          src/graphics/GFillable.java
	@echo javac src/graphics/GFillable.java
	@$(JAVAC) src/graphics/GFillable.java

classes/graphics/GImage.class: \
          src/graphics/GImage.java \
          src/graphics/GCanvas.java \
          src/graphics/GCompound.java \
          src/graphics/GContainer.java \
          src/graphics/GDimension.java \
          src/graphics/GFillable.java \
          src/graphics/GImageTools.java \
          src/graphics/GMath.java \
          src/graphics/GObject.java \
          src/graphics/GPoint.java \
          src/graphics/GRectangle.java \
          src/graphics/GResizable.java \
          src/graphics/GScalable.java
	@echo javac src/graphics/GImage.java
	@$(JAVAC) src/graphics/GImage.java

classes/graphics/GImageTools.class: \
          src/graphics/GImageTools.java
	@echo javac src/graphics/GImageTools.java
	@$(JAVAC) src/graphics/GImageTools.java

classes/graphics/GLabel.class: \
          src/graphics/GLabel.java \
          src/graphics/GCanvas.java \
          src/graphics/GCompound.java \
          src/graphics/GContainer.java \
          src/graphics/GDimension.java \
          src/graphics/GFillable.java \
          src/graphics/GImageTools.java \
          src/graphics/GMath.java \
          src/graphics/GObject.java \
          src/graphics/GPoint.java \
          src/graphics/GRectangle.java \
          src/graphics/GResizable.java \
          src/graphics/GScalable.java
	@echo javac src/graphics/GLabel.java
	@$(JAVAC) src/graphics/GLabel.java

classes/graphics/GLine.class: \
          src/graphics/GLine.java \
          src/graphics/GCanvas.java \
          src/graphics/GCompound.java \
          src/graphics/GContainer.java \
          src/graphics/GDimension.java \
          src/graphics/GFillable.java \
          src/graphics/GMath.java \
          src/graphics/GObject.java \
          src/graphics/GPoint.java \
          src/graphics/GRectangle.java \
          src/graphics/GResizable.java \
          src/graphics/GScalable.java
	@echo javac src/graphics/GLine.java
	@$(JAVAC) src/graphics/GLine.java

classes/graphics/GMath.class: \
          src/graphics/GMath.java
	@echo javac src/graphics/GMath.java
	@$(JAVAC) src/graphics/GMath.java

classes/graphics/GObject.class: \
          src/graphics/GObject.java \
          src/graphics/GCanvas.java \
          src/graphics/GCompound.java \
          src/graphics/GContainer.java \
          src/graphics/GDimension.java \
          src/graphics/GFillable.java \
          src/graphics/GMath.java \
          src/graphics/GPoint.java \
          src/graphics/GRectangle.java \
          src/graphics/GResizable.java \
          src/graphics/GScalable.java
	@echo javac src/graphics/GObject.java
	@$(JAVAC) src/graphics/GObject.java

classes/graphics/GOval.class: \
          src/graphics/GOval.java \
          src/graphics/GCanvas.java \
          src/graphics/GCompound.java \
          src/graphics/GContainer.java \
          src/graphics/GDimension.java \
          src/graphics/GFillable.java \
          src/graphics/GMath.java \
          src/graphics/GObject.java \
          src/graphics/GPoint.java \
          src/graphics/GRectangle.java \
          src/graphics/GResizable.java \
          src/graphics/GScalable.java
	@echo javac src/graphics/GOval.java
	@$(JAVAC) src/graphics/GOval.java

classes/graphics/GPoint.class: \
          src/graphics/GPoint.java
	@echo javac src/graphics/GPoint.java
	@$(JAVAC) src/graphics/GPoint.java

classes/graphics/GPolygon.class: \
          src/graphics/GPolygon.java \
          src/graphics/GCanvas.java \
          src/graphics/GCompound.java \
          src/graphics/GContainer.java \
          src/graphics/GDimension.java \
          src/graphics/GFillable.java \
          src/graphics/GMath.java \
          src/graphics/GObject.java \
          src/graphics/GPoint.java \
          src/graphics/GRectangle.java \
          src/graphics/GResizable.java \
          src/graphics/GScalable.java
	@echo javac src/graphics/GPolygon.java
	@$(JAVAC) src/graphics/GPolygon.java

classes/graphics/GRect.class: \
          src/graphics/GRect.java \
          src/graphics/GCanvas.java \
          src/graphics/GCompound.java \
          src/graphics/GContainer.java \
          src/graphics/GDimension.java \
          src/graphics/GFillable.java \
          src/graphics/GMath.java \
          src/graphics/GObject.java \
          src/graphics/GPoint.java \
          src/graphics/GRectangle.java \
          src/graphics/GResizable.java \
          src/graphics/GScalable.java
	@echo javac src/graphics/GRect.java
	@$(JAVAC) src/graphics/GRect.java

classes/graphics/GRectangle.class: \
          src/graphics/GRectangle.java \
          src/graphics/GDimension.java \
          src/graphics/GMath.java \
          src/graphics/GPoint.java
	@echo javac src/graphics/GRectangle.java
	@$(JAVAC) src/graphics/GRectangle.java

classes/graphics/GResizable.class: \
          src/graphics/GResizable.java \
          src/graphics/GDimension.java \
          src/graphics/GMath.java \
          src/graphics/GPoint.java \
          src/graphics/GRectangle.java
	@echo javac src/graphics/GResizable.java
	@$(JAVAC) src/graphics/GResizable.java

classes/graphics/GRoundRect.class: \
          src/graphics/GRoundRect.java \
          src/graphics/GCanvas.java \
          src/graphics/GCompound.java \
          src/graphics/GContainer.java \
          src/graphics/GDimension.java \
          src/graphics/GFillable.java \
          src/graphics/GMath.java \
          src/graphics/GObject.java \
          src/graphics/GPoint.java \
          src/graphics/GRect.java \
          src/graphics/GRectangle.java \
          src/graphics/GResizable.java \
          src/graphics/GScalable.java
	@echo javac src/graphics/GRoundRect.java
	@$(JAVAC) src/graphics/GRoundRect.java

classes/graphics/GScalable.class: \
          src/graphics/GScalable.java
	@echo javac src/graphics/GScalable.java
	@$(JAVAC) src/graphics/GScalable.java

classes/graphics/GWindow.class: \
          src/graphics/GWindow.java \
          src/graphics/GCanvas.java \
          src/graphics/GCompound.java \
          src/graphics/GContainer.java \
          src/graphics/GDimension.java \
          src/graphics/GFillable.java \
          src/graphics/GMath.java \
          src/graphics/GObject.java \
          src/graphics/GPoint.java \
          src/graphics/GRectangle.java \
          src/graphics/GResizable.java \
          src/graphics/GScalable.java
	@echo javac src/graphics/GWindow.java
	@$(JAVAC) src/graphics/GWindow.java

classes/spl/GButton.class: \
          src/spl/GButton.java \
          src/graphics/GCanvas.java \
          src/graphics/GCompound.java \
          src/graphics/GContainer.java \
          src/graphics/GDimension.java \
          src/graphics/GFillable.java \
          src/graphics/GMath.java \
          src/graphics/GObject.java \
          src/graphics/GPoint.java \
          src/graphics/GRectangle.java \
          src/graphics/GResizable.java \
          src/graphics/GScalable.java \
          src/spl/GInteractor.java \
          src/spl/JBECanvas.java \
          src/spl/JBETopCompound.java
	@echo javac src/spl/GButton.java
	@$(JAVAC) src/spl/GButton.java

classes/spl/GCheckBox.class: \
          src/spl/GCheckBox.java \
          src/graphics/GCanvas.java \
          src/graphics/GCompound.java \
          src/graphics/GContainer.java \
          src/graphics/GDimension.java \
          src/graphics/GFillable.java \
          src/graphics/GMath.java \
          src/graphics/GObject.java \
          src/graphics/GPoint.java \
          src/graphics/GRectangle.java \
          src/graphics/GResizable.java \
          src/graphics/GScalable.java \
          src/spl/GInteractor.java \
          src/spl/JBECanvas.java \
          src/spl/JBETopCompound.java
	@echo javac src/spl/GCheckBox.java
	@$(JAVAC) src/spl/GCheckBox.java

classes/spl/GChooser.class: \
          src/spl/GChooser.java \
          src/graphics/GCanvas.java \
          src/graphics/GCompound.java \
          src/graphics/GContainer.java \
          src/graphics/GDimension.java \
          src/graphics/GFillable.java \
          src/graphics/GMath.java \
          src/graphics/GObject.java \
          src/graphics/GPoint.java \
          src/graphics/GRectangle.java \
          src/graphics/GResizable.java \
          src/graphics/GScalable.java \
          src/spl/GInteractor.java \
          src/spl/JBECanvas.java \
          src/spl/JBETopCompound.java
	@echo javac src/spl/GChooser.java
	@$(JAVAC) src/spl/GChooser.java

classes/spl/GInteractor.class: \
          src/spl/GInteractor.java \
          src/graphics/GCanvas.java \
          src/graphics/GCompound.java \
          src/graphics/GContainer.java \
          src/graphics/GDimension.java \
          src/graphics/GFillable.java \
          src/graphics/GMath.java \
          src/graphics/GObject.java \
          src/graphics/GPoint.java \
          src/graphics/GRectangle.java \
          src/graphics/GResizable.java \
          src/graphics/GScalable.java \
          src/spl/JBECanvas.java \
          src/spl/JBETopCompound.java
	@echo javac src/spl/GInteractor.java
	@$(JAVAC) src/spl/GInteractor.java

classes/spl/GSlider.class: \
          src/spl/GSlider.java \
          src/graphics/GCanvas.java \
          src/graphics/GCompound.java \
          src/graphics/GContainer.java \
          src/graphics/GDimension.java \
          src/graphics/GFillable.java \
          src/graphics/GMath.java \
          src/graphics/GObject.java \
          src/graphics/GPoint.java \
          src/graphics/GRectangle.java \
          src/graphics/GResizable.java \
          src/graphics/GScalable.java \
          src/spl/GInteractor.java \
          src/spl/JBECanvas.java \
          src/spl/JBETopCompound.java
	@echo javac src/spl/GSlider.java
	@$(JAVAC) src/spl/GSlider.java

classes/spl/GTextField.class: \
          src/spl/GTextField.java \
          src/graphics/GCanvas.java \
          src/graphics/GCompound.java \
          src/graphics/GContainer.java \
          src/graphics/GDimension.java \
          src/graphics/GFillable.java \
          src/graphics/GMath.java \
          src/graphics/GObject.java \
          src/graphics/GPoint.java \
          src/graphics/GRectangle.java \
          src/graphics/GResizable.java \
          src/graphics/GScalable.java \
          src/spl/GInteractor.java \
          src/spl/JBECanvas.java \
          src/spl/JBETopCompound.java
	@echo javac src/spl/GTextField.java
	@$(JAVAC) src/spl/GTextField.java

classes/spl/JBECanvas.class: \
          src/spl/JBECanvas.java \
          src/graphics/GCanvas.java \
          src/graphics/GCompound.java \
          src/graphics/GContainer.java \
          src/graphics/GDimension.java \
          src/graphics/GFillable.java \
          src/graphics/GMath.java \
          src/graphics/GObject.java \
          src/graphics/GPoint.java \
          src/graphics/GRectangle.java \
          src/graphics/GResizable.java \
          src/graphics/GScalable.java \
          src/spl/JBETopCompound.java
	@echo javac src/spl/JBECanvas.java
	@$(JAVAC) src/spl/JBECanvas.java

classes/spl/JBECommand.class: \
          src/spl/JBECommand.java \
          src/graphics/G3DRect.java \
          src/graphics/GArc.java \
          src/graphics/GCanvas.java \
          src/graphics/GCompound.java \
          src/graphics/GContainer.java \
          src/graphics/GDimension.java \
          src/graphics/GFillable.java \
          src/graphics/GImage.java \
          src/graphics/GImageTools.java \
          src/graphics/GLabel.java \
          src/graphics/GLine.java \
          src/graphics/GMath.java \
          src/graphics/GObject.java \
          src/graphics/GOval.java \
          src/graphics/GPoint.java \
          src/graphics/GPolygon.java \
          src/graphics/GRect.java \
          src/graphics/GRectangle.java \
          src/graphics/GResizable.java \
          src/graphics/GRoundRect.java \
          src/graphics/GScalable.java \
          src/spl/GButton.java \
          src/spl/GCheckBox.java \
          src/spl/GChooser.java \
          src/spl/GInteractor.java \
          src/spl/GSlider.java \
          src/spl/GTextField.java \
          src/spl/JBECanvas.java \
          src/spl/JBEConsole.java \
          src/spl/JBEFileFilter.java \
          src/spl/JBELabel.java \
          src/spl/JBETopCompound.java \
          src/spl/JBEWindow.java \
          src/spl/JavaBackEnd.java \
          src/tokenscanner/TokenScanner.java
	@echo javac src/spl/JBECommand.java
	@$(JAVAC) src/spl/JBECommand.java

classes/spl/JBEConsole.class: \
          src/spl/JBEConsole.java
	@echo javac src/spl/JBEConsole.java
	@$(JAVAC) src/spl/JBEConsole.java

classes/spl/JBEFileFilter.class: \
          src/spl/JBEFileFilter.java
	@echo javac src/spl/JBEFileFilter.java
	@$(JAVAC) src/spl/JBEFileFilter.java

classes/spl/JBELabel.class: \
          src/spl/JBELabel.java \
          src/graphics/GCanvas.java \
          src/graphics/GCompound.java \
          src/graphics/GContainer.java \
          src/graphics/GDimension.java \
          src/graphics/GFillable.java \
          src/graphics/GImageTools.java \
          src/graphics/GLabel.java \
          src/graphics/GMath.java \
          src/graphics/GObject.java \
          src/graphics/GPoint.java \
          src/graphics/GRectangle.java \
          src/graphics/GResizable.java \
          src/graphics/GScalable.java
	@echo javac src/spl/JBELabel.java
	@$(JAVAC) src/spl/JBELabel.java

classes/spl/JBETopCompound.class: \
          src/spl/JBETopCompound.java \
          src/graphics/GCanvas.java \
          src/graphics/GCompound.java \
          src/graphics/GContainer.java \
          src/graphics/GDimension.java \
          src/graphics/GFillable.java \
          src/graphics/GMath.java \
          src/graphics/GObject.java \
          src/graphics/GPoint.java \
          src/graphics/GRectangle.java \
          src/graphics/GResizable.java \
          src/graphics/GScalable.java \
          src/spl/JBECanvas.java
	@echo javac src/spl/JBETopCompound.java
	@$(JAVAC) src/spl/JBETopCompound.java

classes/spl/JBEWindow.class: \
          src/spl/JBEWindow.java \
          src/graphics/G3DRect.java \
          src/graphics/GArc.java \
          src/graphics/GCanvas.java \
          src/graphics/GCompound.java \
          src/graphics/GContainer.java \
          src/graphics/GDimension.java \
          src/graphics/GFillable.java \
          src/graphics/GImage.java \
          src/graphics/GImageTools.java \
          src/graphics/GLabel.java \
          src/graphics/GLine.java \
          src/graphics/GMath.java \
          src/graphics/GObject.java \
          src/graphics/GOval.java \
          src/graphics/GPoint.java \
          src/graphics/GPolygon.java \
          src/graphics/GRect.java \
          src/graphics/GRectangle.java \
          src/graphics/GResizable.java \
          src/graphics/GRoundRect.java \
          src/graphics/GScalable.java \
          src/spl/GButton.java \
          src/spl/GCheckBox.java \
          src/spl/GChooser.java \
          src/spl/GInteractor.java \
          src/spl/GSlider.java \
          src/spl/GTextField.java \
          src/spl/JBECanvas.java \
          src/spl/JBECommand.java \
          src/spl/JBEConsole.java \
          src/spl/JBEFileFilter.java \
          src/spl/JBELabel.java \
          src/spl/JBETopCompound.java \
          src/spl/JavaBackEnd.java \
          src/tokenscanner/TokenScanner.java
	@echo javac src/spl/JBEWindow.java
	@$(JAVAC) src/spl/JBEWindow.java

classes/spl/JavaBackEnd.class: \
          src/spl/JavaBackEnd.java \
          src/graphics/G3DRect.java \
          src/graphics/GArc.java \
          src/graphics/GCanvas.java \
          src/graphics/GCompound.java \
          src/graphics/GContainer.java \
          src/graphics/GDimension.java \
          src/graphics/GFillable.java \
          src/graphics/GImage.java \
          src/graphics/GImageTools.java \
          src/graphics/GLabel.java \
          src/graphics/GLine.java \
          src/graphics/GMath.java \
          src/graphics/GObject.java \
          src/graphics/GOval.java \
          src/graphics/GPoint.java \
          src/graphics/GPolygon.java \
          src/graphics/GRect.java \
          src/graphics/GRectangle.java \
          src/graphics/GResizable.java \
          src/graphics/GRoundRect.java \
          src/graphics/GScalable.java \
          src/spl/GButton.java \
          src/spl/GCheckBox.java \
          src/spl/GChooser.java \
          src/spl/GInteractor.java \
          src/spl/GSlider.java \
          src/spl/GTextField.java \
          src/spl/JBECanvas.java \
          src/spl/JBECommand.java \
          src/spl/JBEConsole.java \
          src/spl/JBEFileFilter.java \
          src/spl/JBELabel.java \
          src/spl/JBETopCompound.java \
          src/spl/JBEWindow.java \
          src/tokenscanner/TokenScanner.java
	@echo javac src/spl/JavaBackEnd.java
	@$(JAVAC) src/spl/JavaBackEnd.java

classes/tokenscanner/TokenScanner.class: \
          src/tokenscanner/TokenScanner.java
	@echo javac src/tokenscanner/TokenScanner.java
	@$(JAVAC) src/tokenscanner/TokenScanner.java
