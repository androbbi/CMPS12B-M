# $Id: Makefile,v 1.6 2014-01-17 17:40:59-08 - - $

JAVASRC    = jroff.java commands.java linkedqueue.java auxlib.java
SOURCES    = ${JAVASRC} Makefile README
MAINCLASS  = jroff
CLASSES    = jroff.class commands.class linkedqueue.class auxlib.class
JARCLASSES = ${CLASSES} linkedqueue\$$node.class
JARFILE    = jroff
LISTING    = Listing.ps
SUBMITDIR  = cmps012b-wm.w14 asg2

all : ${JARFILE}

${JARFILE} : ${CLASSES} Makefile
	echo Main-class: ${MAINCLASS} >Manifest
	jar cvfm ${JARFILE} Manifest ${JARCLASSES}
	- rm Manifest
	chmod +x ${JARFILE}

%.class : %.java
	- checksource $<
	- cid + $<
	javac $<

clean :
	- rm ${JARCLASSES} Manifest

spotless : clean
	- rm ${JARFILE}

ci : ${SOURCES}
	- checksource ${SOURCES}
	cid + ${SOURCES}

lis : ${SOURCES}
	mkpspdf ${LISTING} ${SOURCES}

submit : ${SOURCES}
	submit ${SUBMITDIR} ${SOURCES}
	testsubmit ${SUBMITDIR} ${SOURCES}
	
again:
	gmake --no-print-directory spotless ci all lis

