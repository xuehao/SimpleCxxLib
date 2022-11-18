# Makefile for pictures/ClassHierarchies
# Last modified on Sat Dec 15 17:59:26 2012 by eroberts
#****************************************************************

PICTURES = \
    GObjectHierarchy.pdf \
    GObjectHierarchy-h.pdf \
    GInteractorHierarchy.pdf \
    GInteractorHierarchy-h.pdf \
    GEventHierarchy.pdf \
    GEventHierarchy-h.pdf


# ***************************************************************
# Entry to bring the package up to date
#    The "make all" entry should be the first real entry

all: $(PICTURES)

GObjectHierarchy.pdf: GObjectHierarchy.ps hierarchy.ps Makefile
	makepdf -png -pad GObjectHierarchy.ps

GObjectHierarchy-h.pdf: GObjectHierarchy-h.ps hierarchy.ps Makefile
	makepdf -png -pad GObjectHierarchy-h.ps

GInteractorHierarchy.pdf: GInteractorHierarchy.ps hierarchy.ps Makefile
	makepdf -png -pad GInteractorHierarchy.ps

GInteractorHierarchy-h.pdf: GInteractorHierarchy-h.ps hierarchy.ps Makefile
	makepdf -png -pad GInteractorHierarchy-h.ps

GEventHierarchy.pdf: GEventHierarchy.ps hierarchy.ps Makefile
	makepdf -png -pad GEventHierarchy.ps

GEventHierarchy-h.pdf: GEventHierarchy-h.ps hierarchy.ps Makefile
	makepdf -png -pad GEventHierarchy-h.ps


# ***************************************************************
# Standard entries to remove files from the directories
#    tidy    -- eliminate unwanted files
#    scratch -- delete derived files in preparation for rebuild

tidy:
	rm -f ,* .,* *~ core a.out *.err

scratch clean: tidy
	rm -f *.o *.a *.html $(PICTURES)
