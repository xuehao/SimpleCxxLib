# Makefile for the Stanford Portable Library (spl) package
# Last modified on Sat Aug 16 17:30:02 2014 by eroberts
#****************************************************************

PKGNAME = spl
PKGPATH = edu/stanford/cs/java/$(PKGNAME)
JARFILE = $(PKGNAME).jar
TOOLS =

EXPORTJAR = $(HOME)/java/jar
EXPORTBIN = $(HOME)/bin

JAVAC = javac -sourcepath src \
              -d classes \
              -Xlint:-serial

CLASSES = \
    classes/edu/stanford/cs/java/graphics/G3DRect.class \
    classes/edu/stanford/cs/java/graphics/GArc.class \
    classes/edu/stanford/cs/java/graphics/GCanvas.class \
    classes/edu/stanford/cs/java/graphics/GCompound.class \
    classes/edu/stanford/cs/java/graphics/GContainer.class \
    classes/edu/stanford/cs/java/graphics/GDimension.class \
    classes/edu/stanford/cs/java/graphics/GFillable.class \
    classes/edu/stanford/cs/java/graphics/GImage.class \
    classes/edu/stanford/cs/java/graphics/GImageTools.class \
    classes/edu/stanford/cs/java/graphics/GLabel.class \
    classes/edu/stanford/cs/java/graphics/GLine.class \
    classes/edu/stanford/cs/java/graphics/GMath.class \
    classes/edu/stanford/cs/java/graphics/GObject.class \
    classes/edu/stanford/cs/java/graphics/GOval.class \
    classes/edu/stanford/cs/java/graphics/GPoint.class \
    classes/edu/stanford/cs/java/graphics/GPolygon.class \
    classes/edu/stanford/cs/java/graphics/GRect.class \
    classes/edu/stanford/cs/java/graphics/GRectangle.class \
    classes/edu/stanford/cs/java/graphics/GResizable.class \
    classes/edu/stanford/cs/java/graphics/GRoundRect.class \
    classes/edu/stanford/cs/java/graphics/GScalable.class \
    classes/edu/stanford/cs/java/graphics/GWindow.class \
    classes/edu/stanford/cs/java/spl/GButton.class \
    classes/edu/stanford/cs/java/spl/GCheckBox.class \
    classes/edu/stanford/cs/java/spl/GChooser.class \
    classes/edu/stanford/cs/java/spl/GInteractor.class \
    classes/edu/stanford/cs/java/spl/GSlider.class \
    classes/edu/stanford/cs/java/spl/GTextField.class \
    classes/edu/stanford/cs/java/spl/JBECanvas.class \
    classes/edu/stanford/cs/java/spl/JBECommand.class \
    classes/edu/stanford/cs/java/spl/JBEConsole.class \
    classes/edu/stanford/cs/java/spl/JBEFileFilter.class \
    classes/edu/stanford/cs/java/spl/JBELabel.class \
    classes/edu/stanford/cs/java/spl/JBETopCompound.class \
    classes/edu/stanford/cs/java/spl/JBEWindow.class \
    classes/edu/stanford/cs/java/spl/JavaBackEnd.class \
    classes/edu/stanford/cs/java/tokenscanner/TokenScanner.class


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

classes/edu/stanford/cs/java/graphics/G3DRect.class: \
          src/edu/stanford/cs/java/graphics/G3DRect.java \
          src/edu/stanford/cs/java/graphics/GCanvas.java \
          src/edu/stanford/cs/java/graphics/GCompound.java \
          src/edu/stanford/cs/java/graphics/GContainer.java \
          src/edu/stanford/cs/java/graphics/GDimension.java \
          src/edu/stanford/cs/java/graphics/GFillable.java \
          src/edu/stanford/cs/java/graphics/GMath.java \
          src/edu/stanford/cs/java/graphics/GObject.java \
          src/edu/stanford/cs/java/graphics/GPoint.java \
          src/edu/stanford/cs/java/graphics/GRect.java \
          src/edu/stanford/cs/java/graphics/GRectangle.java \
          src/edu/stanford/cs/java/graphics/GResizable.java \
          src/edu/stanford/cs/java/graphics/GScalable.java
	@echo javac src/edu/stanford/cs/java/graphics/G3DRect.java
	@$(JAVAC) src/edu/stanford/cs/java/graphics/G3DRect.java

classes/edu/stanford/cs/java/graphics/GArc.class: \
          src/edu/stanford/cs/java/graphics/GArc.java \
          src/edu/stanford/cs/java/graphics/GCanvas.java \
          src/edu/stanford/cs/java/graphics/GCompound.java \
          src/edu/stanford/cs/java/graphics/GContainer.java \
          src/edu/stanford/cs/java/graphics/GDimension.java \
          src/edu/stanford/cs/java/graphics/GFillable.java \
          src/edu/stanford/cs/java/graphics/GMath.java \
          src/edu/stanford/cs/java/graphics/GObject.java \
          src/edu/stanford/cs/java/graphics/GPoint.java \
          src/edu/stanford/cs/java/graphics/GRectangle.java \
          src/edu/stanford/cs/java/graphics/GResizable.java \
          src/edu/stanford/cs/java/graphics/GScalable.java
	@echo javac src/edu/stanford/cs/java/graphics/GArc.java
	@$(JAVAC) src/edu/stanford/cs/java/graphics/GArc.java

classes/edu/stanford/cs/java/graphics/GCanvas.class: \
          src/edu/stanford/cs/java/graphics/GCanvas.java \
          src/edu/stanford/cs/java/graphics/GCompound.java \
          src/edu/stanford/cs/java/graphics/GContainer.java \
          src/edu/stanford/cs/java/graphics/GDimension.java \
          src/edu/stanford/cs/java/graphics/GFillable.java \
          src/edu/stanford/cs/java/graphics/GMath.java \
          src/edu/stanford/cs/java/graphics/GObject.java \
          src/edu/stanford/cs/java/graphics/GPoint.java \
          src/edu/stanford/cs/java/graphics/GRectangle.java \
          src/edu/stanford/cs/java/graphics/GResizable.java \
          src/edu/stanford/cs/java/graphics/GScalable.java
	@echo javac src/edu/stanford/cs/java/graphics/GCanvas.java
	@$(JAVAC) src/edu/stanford/cs/java/graphics/GCanvas.java

classes/edu/stanford/cs/java/graphics/GCompound.class: \
          src/edu/stanford/cs/java/graphics/GCompound.java \
          src/edu/stanford/cs/java/graphics/GCanvas.java \
          src/edu/stanford/cs/java/graphics/GContainer.java \
          src/edu/stanford/cs/java/graphics/GDimension.java \
          src/edu/stanford/cs/java/graphics/GFillable.java \
          src/edu/stanford/cs/java/graphics/GMath.java \
          src/edu/stanford/cs/java/graphics/GObject.java \
          src/edu/stanford/cs/java/graphics/GPoint.java \
          src/edu/stanford/cs/java/graphics/GRectangle.java \
          src/edu/stanford/cs/java/graphics/GResizable.java \
          src/edu/stanford/cs/java/graphics/GScalable.java
	@echo javac src/edu/stanford/cs/java/graphics/GCompound.java
	@$(JAVAC) src/edu/stanford/cs/java/graphics/GCompound.java

classes/edu/stanford/cs/java/graphics/GContainer.class: \
          src/edu/stanford/cs/java/graphics/GContainer.java \
          src/edu/stanford/cs/java/graphics/GCanvas.java \
          src/edu/stanford/cs/java/graphics/GCompound.java \
          src/edu/stanford/cs/java/graphics/GDimension.java \
          src/edu/stanford/cs/java/graphics/GFillable.java \
          src/edu/stanford/cs/java/graphics/GMath.java \
          src/edu/stanford/cs/java/graphics/GObject.java \
          src/edu/stanford/cs/java/graphics/GPoint.java \
          src/edu/stanford/cs/java/graphics/GRectangle.java \
          src/edu/stanford/cs/java/graphics/GResizable.java \
          src/edu/stanford/cs/java/graphics/GScalable.java
	@echo javac src/edu/stanford/cs/java/graphics/GContainer.java
	@$(JAVAC) src/edu/stanford/cs/java/graphics/GContainer.java

classes/edu/stanford/cs/java/graphics/GDimension.class: \
          src/edu/stanford/cs/java/graphics/GDimension.java
	@echo javac src/edu/stanford/cs/java/graphics/GDimension.java
	@$(JAVAC) src/edu/stanford/cs/java/graphics/GDimension.java

classes/edu/stanford/cs/java/graphics/GFillable.class: \
          src/edu/stanford/cs/java/graphics/GFillable.java
	@echo javac src/edu/stanford/cs/java/graphics/GFillable.java
	@$(JAVAC) src/edu/stanford/cs/java/graphics/GFillable.java

classes/edu/stanford/cs/java/graphics/GImage.class: \
          src/edu/stanford/cs/java/graphics/GImage.java \
          src/edu/stanford/cs/java/graphics/GCanvas.java \
          src/edu/stanford/cs/java/graphics/GCompound.java \
          src/edu/stanford/cs/java/graphics/GContainer.java \
          src/edu/stanford/cs/java/graphics/GDimension.java \
          src/edu/stanford/cs/java/graphics/GFillable.java \
          src/edu/stanford/cs/java/graphics/GImageTools.java \
          src/edu/stanford/cs/java/graphics/GMath.java \
          src/edu/stanford/cs/java/graphics/GObject.java \
          src/edu/stanford/cs/java/graphics/GPoint.java \
          src/edu/stanford/cs/java/graphics/GRectangle.java \
          src/edu/stanford/cs/java/graphics/GResizable.java \
          src/edu/stanford/cs/java/graphics/GScalable.java
	@echo javac src/edu/stanford/cs/java/graphics/GImage.java
	@$(JAVAC) src/edu/stanford/cs/java/graphics/GImage.java

classes/edu/stanford/cs/java/graphics/GImageTools.class: \
          src/edu/stanford/cs/java/graphics/GImageTools.java
	@echo javac src/edu/stanford/cs/java/graphics/GImageTools.java
	@$(JAVAC) src/edu/stanford/cs/java/graphics/GImageTools.java

classes/edu/stanford/cs/java/graphics/GLabel.class: \
          src/edu/stanford/cs/java/graphics/GLabel.java \
          src/edu/stanford/cs/java/graphics/GCanvas.java \
          src/edu/stanford/cs/java/graphics/GCompound.java \
          src/edu/stanford/cs/java/graphics/GContainer.java \
          src/edu/stanford/cs/java/graphics/GDimension.java \
          src/edu/stanford/cs/java/graphics/GFillable.java \
          src/edu/stanford/cs/java/graphics/GImageTools.java \
          src/edu/stanford/cs/java/graphics/GMath.java \
          src/edu/stanford/cs/java/graphics/GObject.java \
          src/edu/stanford/cs/java/graphics/GPoint.java \
          src/edu/stanford/cs/java/graphics/GRectangle.java \
          src/edu/stanford/cs/java/graphics/GResizable.java \
          src/edu/stanford/cs/java/graphics/GScalable.java
	@echo javac src/edu/stanford/cs/java/graphics/GLabel.java
	@$(JAVAC) src/edu/stanford/cs/java/graphics/GLabel.java

classes/edu/stanford/cs/java/graphics/GLine.class: \
          src/edu/stanford/cs/java/graphics/GLine.java \
          src/edu/stanford/cs/java/graphics/GCanvas.java \
          src/edu/stanford/cs/java/graphics/GCompound.java \
          src/edu/stanford/cs/java/graphics/GContainer.java \
          src/edu/stanford/cs/java/graphics/GDimension.java \
          src/edu/stanford/cs/java/graphics/GFillable.java \
          src/edu/stanford/cs/java/graphics/GMath.java \
          src/edu/stanford/cs/java/graphics/GObject.java \
          src/edu/stanford/cs/java/graphics/GPoint.java \
          src/edu/stanford/cs/java/graphics/GRectangle.java \
          src/edu/stanford/cs/java/graphics/GResizable.java \
          src/edu/stanford/cs/java/graphics/GScalable.java
	@echo javac src/edu/stanford/cs/java/graphics/GLine.java
	@$(JAVAC) src/edu/stanford/cs/java/graphics/GLine.java

classes/edu/stanford/cs/java/graphics/GMath.class: \
          src/edu/stanford/cs/java/graphics/GMath.java
	@echo javac src/edu/stanford/cs/java/graphics/GMath.java
	@$(JAVAC) src/edu/stanford/cs/java/graphics/GMath.java

classes/edu/stanford/cs/java/graphics/GObject.class: \
          src/edu/stanford/cs/java/graphics/GObject.java \
          src/edu/stanford/cs/java/graphics/GCanvas.java \
          src/edu/stanford/cs/java/graphics/GCompound.java \
          src/edu/stanford/cs/java/graphics/GContainer.java \
          src/edu/stanford/cs/java/graphics/GDimension.java \
          src/edu/stanford/cs/java/graphics/GFillable.java \
          src/edu/stanford/cs/java/graphics/GMath.java \
          src/edu/stanford/cs/java/graphics/GPoint.java \
          src/edu/stanford/cs/java/graphics/GRectangle.java \
          src/edu/stanford/cs/java/graphics/GResizable.java \
          src/edu/stanford/cs/java/graphics/GScalable.java
	@echo javac src/edu/stanford/cs/java/graphics/GObject.java
	@$(JAVAC) src/edu/stanford/cs/java/graphics/GObject.java

classes/edu/stanford/cs/java/graphics/GOval.class: \
          src/edu/stanford/cs/java/graphics/GOval.java \
          src/edu/stanford/cs/java/graphics/GCanvas.java \
          src/edu/stanford/cs/java/graphics/GCompound.java \
          src/edu/stanford/cs/java/graphics/GContainer.java \
          src/edu/stanford/cs/java/graphics/GDimension.java \
          src/edu/stanford/cs/java/graphics/GFillable.java \
          src/edu/stanford/cs/java/graphics/GMath.java \
          src/edu/stanford/cs/java/graphics/GObject.java \
          src/edu/stanford/cs/java/graphics/GPoint.java \
          src/edu/stanford/cs/java/graphics/GRectangle.java \
          src/edu/stanford/cs/java/graphics/GResizable.java \
          src/edu/stanford/cs/java/graphics/GScalable.java
	@echo javac src/edu/stanford/cs/java/graphics/GOval.java
	@$(JAVAC) src/edu/stanford/cs/java/graphics/GOval.java

classes/edu/stanford/cs/java/graphics/GPoint.class: \
          src/edu/stanford/cs/java/graphics/GPoint.java
	@echo javac src/edu/stanford/cs/java/graphics/GPoint.java
	@$(JAVAC) src/edu/stanford/cs/java/graphics/GPoint.java

classes/edu/stanford/cs/java/graphics/GPolygon.class: \
          src/edu/stanford/cs/java/graphics/GPolygon.java \
          src/edu/stanford/cs/java/graphics/GCanvas.java \
          src/edu/stanford/cs/java/graphics/GCompound.java \
          src/edu/stanford/cs/java/graphics/GContainer.java \
          src/edu/stanford/cs/java/graphics/GDimension.java \
          src/edu/stanford/cs/java/graphics/GFillable.java \
          src/edu/stanford/cs/java/graphics/GMath.java \
          src/edu/stanford/cs/java/graphics/GObject.java \
          src/edu/stanford/cs/java/graphics/GPoint.java \
          src/edu/stanford/cs/java/graphics/GRectangle.java \
          src/edu/stanford/cs/java/graphics/GResizable.java \
          src/edu/stanford/cs/java/graphics/GScalable.java
	@echo javac src/edu/stanford/cs/java/graphics/GPolygon.java
	@$(JAVAC) src/edu/stanford/cs/java/graphics/GPolygon.java

classes/edu/stanford/cs/java/graphics/GRect.class: \
          src/edu/stanford/cs/java/graphics/GRect.java \
          src/edu/stanford/cs/java/graphics/GCanvas.java \
          src/edu/stanford/cs/java/graphics/GCompound.java \
          src/edu/stanford/cs/java/graphics/GContainer.java \
          src/edu/stanford/cs/java/graphics/GDimension.java \
          src/edu/stanford/cs/java/graphics/GFillable.java \
          src/edu/stanford/cs/java/graphics/GMath.java \
          src/edu/stanford/cs/java/graphics/GObject.java \
          src/edu/stanford/cs/java/graphics/GPoint.java \
          src/edu/stanford/cs/java/graphics/GRectangle.java \
          src/edu/stanford/cs/java/graphics/GResizable.java \
          src/edu/stanford/cs/java/graphics/GScalable.java
	@echo javac src/edu/stanford/cs/java/graphics/GRect.java
	@$(JAVAC) src/edu/stanford/cs/java/graphics/GRect.java

classes/edu/stanford/cs/java/graphics/GRectangle.class: \
          src/edu/stanford/cs/java/graphics/GRectangle.java \
          src/edu/stanford/cs/java/graphics/GDimension.java \
          src/edu/stanford/cs/java/graphics/GMath.java \
          src/edu/stanford/cs/java/graphics/GPoint.java
	@echo javac src/edu/stanford/cs/java/graphics/GRectangle.java
	@$(JAVAC) src/edu/stanford/cs/java/graphics/GRectangle.java

classes/edu/stanford/cs/java/graphics/GResizable.class: \
          src/edu/stanford/cs/java/graphics/GResizable.java \
          src/edu/stanford/cs/java/graphics/GDimension.java \
          src/edu/stanford/cs/java/graphics/GMath.java \
          src/edu/stanford/cs/java/graphics/GPoint.java \
          src/edu/stanford/cs/java/graphics/GRectangle.java
	@echo javac src/edu/stanford/cs/java/graphics/GResizable.java
	@$(JAVAC) src/edu/stanford/cs/java/graphics/GResizable.java

classes/edu/stanford/cs/java/graphics/GRoundRect.class: \
          src/edu/stanford/cs/java/graphics/GRoundRect.java \
          src/edu/stanford/cs/java/graphics/GCanvas.java \
          src/edu/stanford/cs/java/graphics/GCompound.java \
          src/edu/stanford/cs/java/graphics/GContainer.java \
          src/edu/stanford/cs/java/graphics/GDimension.java \
          src/edu/stanford/cs/java/graphics/GFillable.java \
          src/edu/stanford/cs/java/graphics/GMath.java \
          src/edu/stanford/cs/java/graphics/GObject.java \
          src/edu/stanford/cs/java/graphics/GPoint.java \
          src/edu/stanford/cs/java/graphics/GRect.java \
          src/edu/stanford/cs/java/graphics/GRectangle.java \
          src/edu/stanford/cs/java/graphics/GResizable.java \
          src/edu/stanford/cs/java/graphics/GScalable.java
	@echo javac src/edu/stanford/cs/java/graphics/GRoundRect.java
	@$(JAVAC) src/edu/stanford/cs/java/graphics/GRoundRect.java

classes/edu/stanford/cs/java/graphics/GScalable.class: \
          src/edu/stanford/cs/java/graphics/GScalable.java
	@echo javac src/edu/stanford/cs/java/graphics/GScalable.java
	@$(JAVAC) src/edu/stanford/cs/java/graphics/GScalable.java

classes/edu/stanford/cs/java/graphics/GWindow.class: \
          src/edu/stanford/cs/java/graphics/GWindow.java \
          src/edu/stanford/cs/java/graphics/GCanvas.java \
          src/edu/stanford/cs/java/graphics/GCompound.java \
          src/edu/stanford/cs/java/graphics/GContainer.java \
          src/edu/stanford/cs/java/graphics/GDimension.java \
          src/edu/stanford/cs/java/graphics/GFillable.java \
          src/edu/stanford/cs/java/graphics/GMath.java \
          src/edu/stanford/cs/java/graphics/GObject.java \
          src/edu/stanford/cs/java/graphics/GPoint.java \
          src/edu/stanford/cs/java/graphics/GRectangle.java \
          src/edu/stanford/cs/java/graphics/GResizable.java \
          src/edu/stanford/cs/java/graphics/GScalable.java
	@echo javac src/edu/stanford/cs/java/graphics/GWindow.java
	@$(JAVAC) src/edu/stanford/cs/java/graphics/GWindow.java

classes/edu/stanford/cs/java/spl/GButton.class: \
          src/edu/stanford/cs/java/spl/GButton.java \
          src/edu/stanford/cs/java/graphics/GCanvas.java \
          src/edu/stanford/cs/java/graphics/GCompound.java \
          src/edu/stanford/cs/java/graphics/GContainer.java \
          src/edu/stanford/cs/java/graphics/GDimension.java \
          src/edu/stanford/cs/java/graphics/GFillable.java \
          src/edu/stanford/cs/java/graphics/GMath.java \
          src/edu/stanford/cs/java/graphics/GObject.java \
          src/edu/stanford/cs/java/graphics/GPoint.java \
          src/edu/stanford/cs/java/graphics/GRectangle.java \
          src/edu/stanford/cs/java/graphics/GResizable.java \
          src/edu/stanford/cs/java/graphics/GScalable.java \
          src/edu/stanford/cs/java/spl/GInteractor.java \
          src/edu/stanford/cs/java/spl/JBECanvas.java \
          src/edu/stanford/cs/java/spl/JBETopCompound.java
	@echo javac src/edu/stanford/cs/java/spl/GButton.java
	@$(JAVAC) src/edu/stanford/cs/java/spl/GButton.java

classes/edu/stanford/cs/java/spl/GCheckBox.class: \
          src/edu/stanford/cs/java/spl/GCheckBox.java \
          src/edu/stanford/cs/java/graphics/GCanvas.java \
          src/edu/stanford/cs/java/graphics/GCompound.java \
          src/edu/stanford/cs/java/graphics/GContainer.java \
          src/edu/stanford/cs/java/graphics/GDimension.java \
          src/edu/stanford/cs/java/graphics/GFillable.java \
          src/edu/stanford/cs/java/graphics/GMath.java \
          src/edu/stanford/cs/java/graphics/GObject.java \
          src/edu/stanford/cs/java/graphics/GPoint.java \
          src/edu/stanford/cs/java/graphics/GRectangle.java \
          src/edu/stanford/cs/java/graphics/GResizable.java \
          src/edu/stanford/cs/java/graphics/GScalable.java \
          src/edu/stanford/cs/java/spl/GInteractor.java \
          src/edu/stanford/cs/java/spl/JBECanvas.java \
          src/edu/stanford/cs/java/spl/JBETopCompound.java
	@echo javac src/edu/stanford/cs/java/spl/GCheckBox.java
	@$(JAVAC) src/edu/stanford/cs/java/spl/GCheckBox.java

classes/edu/stanford/cs/java/spl/GChooser.class: \
          src/edu/stanford/cs/java/spl/GChooser.java \
          src/edu/stanford/cs/java/graphics/GCanvas.java \
          src/edu/stanford/cs/java/graphics/GCompound.java \
          src/edu/stanford/cs/java/graphics/GContainer.java \
          src/edu/stanford/cs/java/graphics/GDimension.java \
          src/edu/stanford/cs/java/graphics/GFillable.java \
          src/edu/stanford/cs/java/graphics/GMath.java \
          src/edu/stanford/cs/java/graphics/GObject.java \
          src/edu/stanford/cs/java/graphics/GPoint.java \
          src/edu/stanford/cs/java/graphics/GRectangle.java \
          src/edu/stanford/cs/java/graphics/GResizable.java \
          src/edu/stanford/cs/java/graphics/GScalable.java \
          src/edu/stanford/cs/java/spl/GInteractor.java \
          src/edu/stanford/cs/java/spl/JBECanvas.java \
          src/edu/stanford/cs/java/spl/JBETopCompound.java
	@echo javac src/edu/stanford/cs/java/spl/GChooser.java
	@$(JAVAC) src/edu/stanford/cs/java/spl/GChooser.java

classes/edu/stanford/cs/java/spl/GInteractor.class: \
          src/edu/stanford/cs/java/spl/GInteractor.java \
          src/edu/stanford/cs/java/graphics/GCanvas.java \
          src/edu/stanford/cs/java/graphics/GCompound.java \
          src/edu/stanford/cs/java/graphics/GContainer.java \
          src/edu/stanford/cs/java/graphics/GDimension.java \
          src/edu/stanford/cs/java/graphics/GFillable.java \
          src/edu/stanford/cs/java/graphics/GMath.java \
          src/edu/stanford/cs/java/graphics/GObject.java \
          src/edu/stanford/cs/java/graphics/GPoint.java \
          src/edu/stanford/cs/java/graphics/GRectangle.java \
          src/edu/stanford/cs/java/graphics/GResizable.java \
          src/edu/stanford/cs/java/graphics/GScalable.java \
          src/edu/stanford/cs/java/spl/JBECanvas.java \
          src/edu/stanford/cs/java/spl/JBETopCompound.java
	@echo javac src/edu/stanford/cs/java/spl/GInteractor.java
	@$(JAVAC) src/edu/stanford/cs/java/spl/GInteractor.java

classes/edu/stanford/cs/java/spl/GSlider.class: \
          src/edu/stanford/cs/java/spl/GSlider.java \
          src/edu/stanford/cs/java/graphics/GCanvas.java \
          src/edu/stanford/cs/java/graphics/GCompound.java \
          src/edu/stanford/cs/java/graphics/GContainer.java \
          src/edu/stanford/cs/java/graphics/GDimension.java \
          src/edu/stanford/cs/java/graphics/GFillable.java \
          src/edu/stanford/cs/java/graphics/GMath.java \
          src/edu/stanford/cs/java/graphics/GObject.java \
          src/edu/stanford/cs/java/graphics/GPoint.java \
          src/edu/stanford/cs/java/graphics/GRectangle.java \
          src/edu/stanford/cs/java/graphics/GResizable.java \
          src/edu/stanford/cs/java/graphics/GScalable.java \
          src/edu/stanford/cs/java/spl/GInteractor.java \
          src/edu/stanford/cs/java/spl/JBECanvas.java \
          src/edu/stanford/cs/java/spl/JBETopCompound.java
	@echo javac src/edu/stanford/cs/java/spl/GSlider.java
	@$(JAVAC) src/edu/stanford/cs/java/spl/GSlider.java

classes/edu/stanford/cs/java/spl/GTextField.class: \
          src/edu/stanford/cs/java/spl/GTextField.java \
          src/edu/stanford/cs/java/graphics/GCanvas.java \
          src/edu/stanford/cs/java/graphics/GCompound.java \
          src/edu/stanford/cs/java/graphics/GContainer.java \
          src/edu/stanford/cs/java/graphics/GDimension.java \
          src/edu/stanford/cs/java/graphics/GFillable.java \
          src/edu/stanford/cs/java/graphics/GMath.java \
          src/edu/stanford/cs/java/graphics/GObject.java \
          src/edu/stanford/cs/java/graphics/GPoint.java \
          src/edu/stanford/cs/java/graphics/GRectangle.java \
          src/edu/stanford/cs/java/graphics/GResizable.java \
          src/edu/stanford/cs/java/graphics/GScalable.java \
          src/edu/stanford/cs/java/spl/GInteractor.java \
          src/edu/stanford/cs/java/spl/JBECanvas.java \
          src/edu/stanford/cs/java/spl/JBETopCompound.java
	@echo javac src/edu/stanford/cs/java/spl/GTextField.java
	@$(JAVAC) src/edu/stanford/cs/java/spl/GTextField.java

classes/edu/stanford/cs/java/spl/JBECanvas.class: \
          src/edu/stanford/cs/java/spl/JBECanvas.java \
          src/edu/stanford/cs/java/graphics/GCanvas.java \
          src/edu/stanford/cs/java/graphics/GCompound.java \
          src/edu/stanford/cs/java/graphics/GContainer.java \
          src/edu/stanford/cs/java/graphics/GDimension.java \
          src/edu/stanford/cs/java/graphics/GFillable.java \
          src/edu/stanford/cs/java/graphics/GMath.java \
          src/edu/stanford/cs/java/graphics/GObject.java \
          src/edu/stanford/cs/java/graphics/GPoint.java \
          src/edu/stanford/cs/java/graphics/GRectangle.java \
          src/edu/stanford/cs/java/graphics/GResizable.java \
          src/edu/stanford/cs/java/graphics/GScalable.java \
          src/edu/stanford/cs/java/spl/JBETopCompound.java
	@echo javac src/edu/stanford/cs/java/spl/JBECanvas.java
	@$(JAVAC) src/edu/stanford/cs/java/spl/JBECanvas.java

classes/edu/stanford/cs/java/spl/JBECommand.class: \
          src/edu/stanford/cs/java/spl/JBECommand.java \
          src/edu/stanford/cs/java/graphics/G3DRect.java \
          src/edu/stanford/cs/java/graphics/GArc.java \
          src/edu/stanford/cs/java/graphics/GCanvas.java \
          src/edu/stanford/cs/java/graphics/GCompound.java \
          src/edu/stanford/cs/java/graphics/GContainer.java \
          src/edu/stanford/cs/java/graphics/GDimension.java \
          src/edu/stanford/cs/java/graphics/GFillable.java \
          src/edu/stanford/cs/java/graphics/GImage.java \
          src/edu/stanford/cs/java/graphics/GImageTools.java \
          src/edu/stanford/cs/java/graphics/GLabel.java \
          src/edu/stanford/cs/java/graphics/GLine.java \
          src/edu/stanford/cs/java/graphics/GMath.java \
          src/edu/stanford/cs/java/graphics/GObject.java \
          src/edu/stanford/cs/java/graphics/GOval.java \
          src/edu/stanford/cs/java/graphics/GPoint.java \
          src/edu/stanford/cs/java/graphics/GPolygon.java \
          src/edu/stanford/cs/java/graphics/GRect.java \
          src/edu/stanford/cs/java/graphics/GRectangle.java \
          src/edu/stanford/cs/java/graphics/GResizable.java \
          src/edu/stanford/cs/java/graphics/GRoundRect.java \
          src/edu/stanford/cs/java/graphics/GScalable.java \
          src/edu/stanford/cs/java/spl/GButton.java \
          src/edu/stanford/cs/java/spl/GCheckBox.java \
          src/edu/stanford/cs/java/spl/GChooser.java \
          src/edu/stanford/cs/java/spl/GInteractor.java \
          src/edu/stanford/cs/java/spl/GSlider.java \
          src/edu/stanford/cs/java/spl/GTextField.java \
          src/edu/stanford/cs/java/spl/JBECanvas.java \
          src/edu/stanford/cs/java/spl/JBEConsole.java \
          src/edu/stanford/cs/java/spl/JBEFileFilter.java \
          src/edu/stanford/cs/java/spl/JBELabel.java \
          src/edu/stanford/cs/java/spl/JBETopCompound.java \
          src/edu/stanford/cs/java/spl/JBEWindow.java \
          src/edu/stanford/cs/java/spl/JavaBackEnd.java \
          src/edu/stanford/cs/java/tokenscanner/TokenScanner.java
	@echo javac src/edu/stanford/cs/java/spl/JBECommand.java
	@$(JAVAC) src/edu/stanford/cs/java/spl/JBECommand.java

classes/edu/stanford/cs/java/spl/JBEConsole.class: \
          src/edu/stanford/cs/java/spl/JBEConsole.java
	@echo javac src/edu/stanford/cs/java/spl/JBEConsole.java
	@$(JAVAC) src/edu/stanford/cs/java/spl/JBEConsole.java

classes/edu/stanford/cs/java/spl/JBEFileFilter.class: \
          src/edu/stanford/cs/java/spl/JBEFileFilter.java
	@echo javac src/edu/stanford/cs/java/spl/JBEFileFilter.java
	@$(JAVAC) src/edu/stanford/cs/java/spl/JBEFileFilter.java

classes/edu/stanford/cs/java/spl/JBELabel.class: \
          src/edu/stanford/cs/java/spl/JBELabel.java \
          src/edu/stanford/cs/java/graphics/GCanvas.java \
          src/edu/stanford/cs/java/graphics/GCompound.java \
          src/edu/stanford/cs/java/graphics/GContainer.java \
          src/edu/stanford/cs/java/graphics/GDimension.java \
          src/edu/stanford/cs/java/graphics/GFillable.java \
          src/edu/stanford/cs/java/graphics/GImageTools.java \
          src/edu/stanford/cs/java/graphics/GLabel.java \
          src/edu/stanford/cs/java/graphics/GMath.java \
          src/edu/stanford/cs/java/graphics/GObject.java \
          src/edu/stanford/cs/java/graphics/GPoint.java \
          src/edu/stanford/cs/java/graphics/GRectangle.java \
          src/edu/stanford/cs/java/graphics/GResizable.java \
          src/edu/stanford/cs/java/graphics/GScalable.java
	@echo javac src/edu/stanford/cs/java/spl/JBELabel.java
	@$(JAVAC) src/edu/stanford/cs/java/spl/JBELabel.java

classes/edu/stanford/cs/java/spl/JBETopCompound.class: \
          src/edu/stanford/cs/java/spl/JBETopCompound.java \
          src/edu/stanford/cs/java/graphics/GCanvas.java \
          src/edu/stanford/cs/java/graphics/GCompound.java \
          src/edu/stanford/cs/java/graphics/GContainer.java \
          src/edu/stanford/cs/java/graphics/GDimension.java \
          src/edu/stanford/cs/java/graphics/GFillable.java \
          src/edu/stanford/cs/java/graphics/GMath.java \
          src/edu/stanford/cs/java/graphics/GObject.java \
          src/edu/stanford/cs/java/graphics/GPoint.java \
          src/edu/stanford/cs/java/graphics/GRectangle.java \
          src/edu/stanford/cs/java/graphics/GResizable.java \
          src/edu/stanford/cs/java/graphics/GScalable.java \
          src/edu/stanford/cs/java/spl/JBECanvas.java
	@echo javac src/edu/stanford/cs/java/spl/JBETopCompound.java
	@$(JAVAC) src/edu/stanford/cs/java/spl/JBETopCompound.java

classes/edu/stanford/cs/java/spl/JBEWindow.class: \
          src/edu/stanford/cs/java/spl/JBEWindow.java \
          src/edu/stanford/cs/java/graphics/G3DRect.java \
          src/edu/stanford/cs/java/graphics/GArc.java \
          src/edu/stanford/cs/java/graphics/GCanvas.java \
          src/edu/stanford/cs/java/graphics/GCompound.java \
          src/edu/stanford/cs/java/graphics/GContainer.java \
          src/edu/stanford/cs/java/graphics/GDimension.java \
          src/edu/stanford/cs/java/graphics/GFillable.java \
          src/edu/stanford/cs/java/graphics/GImage.java \
          src/edu/stanford/cs/java/graphics/GImageTools.java \
          src/edu/stanford/cs/java/graphics/GLabel.java \
          src/edu/stanford/cs/java/graphics/GLine.java \
          src/edu/stanford/cs/java/graphics/GMath.java \
          src/edu/stanford/cs/java/graphics/GObject.java \
          src/edu/stanford/cs/java/graphics/GOval.java \
          src/edu/stanford/cs/java/graphics/GPoint.java \
          src/edu/stanford/cs/java/graphics/GPolygon.java \
          src/edu/stanford/cs/java/graphics/GRect.java \
          src/edu/stanford/cs/java/graphics/GRectangle.java \
          src/edu/stanford/cs/java/graphics/GResizable.java \
          src/edu/stanford/cs/java/graphics/GRoundRect.java \
          src/edu/stanford/cs/java/graphics/GScalable.java \
          src/edu/stanford/cs/java/spl/GButton.java \
          src/edu/stanford/cs/java/spl/GCheckBox.java \
          src/edu/stanford/cs/java/spl/GChooser.java \
          src/edu/stanford/cs/java/spl/GInteractor.java \
          src/edu/stanford/cs/java/spl/GSlider.java \
          src/edu/stanford/cs/java/spl/GTextField.java \
          src/edu/stanford/cs/java/spl/JBECanvas.java \
          src/edu/stanford/cs/java/spl/JBECommand.java \
          src/edu/stanford/cs/java/spl/JBEConsole.java \
          src/edu/stanford/cs/java/spl/JBEFileFilter.java \
          src/edu/stanford/cs/java/spl/JBELabel.java \
          src/edu/stanford/cs/java/spl/JBETopCompound.java \
          src/edu/stanford/cs/java/spl/JavaBackEnd.java \
          src/edu/stanford/cs/java/tokenscanner/TokenScanner.java
	@echo javac src/edu/stanford/cs/java/spl/JBEWindow.java
	@$(JAVAC) src/edu/stanford/cs/java/spl/JBEWindow.java

classes/edu/stanford/cs/java/spl/JavaBackEnd.class: \
          src/edu/stanford/cs/java/spl/JavaBackEnd.java \
          src/edu/stanford/cs/java/graphics/G3DRect.java \
          src/edu/stanford/cs/java/graphics/GArc.java \
          src/edu/stanford/cs/java/graphics/GCanvas.java \
          src/edu/stanford/cs/java/graphics/GCompound.java \
          src/edu/stanford/cs/java/graphics/GContainer.java \
          src/edu/stanford/cs/java/graphics/GDimension.java \
          src/edu/stanford/cs/java/graphics/GFillable.java \
          src/edu/stanford/cs/java/graphics/GImage.java \
          src/edu/stanford/cs/java/graphics/GImageTools.java \
          src/edu/stanford/cs/java/graphics/GLabel.java \
          src/edu/stanford/cs/java/graphics/GLine.java \
          src/edu/stanford/cs/java/graphics/GMath.java \
          src/edu/stanford/cs/java/graphics/GObject.java \
          src/edu/stanford/cs/java/graphics/GOval.java \
          src/edu/stanford/cs/java/graphics/GPoint.java \
          src/edu/stanford/cs/java/graphics/GPolygon.java \
          src/edu/stanford/cs/java/graphics/GRect.java \
          src/edu/stanford/cs/java/graphics/GRectangle.java \
          src/edu/stanford/cs/java/graphics/GResizable.java \
          src/edu/stanford/cs/java/graphics/GRoundRect.java \
          src/edu/stanford/cs/java/graphics/GScalable.java \
          src/edu/stanford/cs/java/spl/GButton.java \
          src/edu/stanford/cs/java/spl/GCheckBox.java \
          src/edu/stanford/cs/java/spl/GChooser.java \
          src/edu/stanford/cs/java/spl/GInteractor.java \
          src/edu/stanford/cs/java/spl/GSlider.java \
          src/edu/stanford/cs/java/spl/GTextField.java \
          src/edu/stanford/cs/java/spl/JBECanvas.java \
          src/edu/stanford/cs/java/spl/JBECommand.java \
          src/edu/stanford/cs/java/spl/JBEConsole.java \
          src/edu/stanford/cs/java/spl/JBEFileFilter.java \
          src/edu/stanford/cs/java/spl/JBELabel.java \
          src/edu/stanford/cs/java/spl/JBETopCompound.java \
          src/edu/stanford/cs/java/spl/JBEWindow.java \
          src/edu/stanford/cs/java/tokenscanner/TokenScanner.java
	@echo javac src/edu/stanford/cs/java/spl/JavaBackEnd.java
	@$(JAVAC) src/edu/stanford/cs/java/spl/JavaBackEnd.java

classes/edu/stanford/cs/java/tokenscanner/TokenScanner.class: \
          src/edu/stanford/cs/java/tokenscanner/TokenScanner.java
	@echo javac src/edu/stanford/cs/java/tokenscanner/TokenScanner.java
	@$(JAVAC) src/edu/stanford/cs/java/tokenscanner/TokenScanner.java
