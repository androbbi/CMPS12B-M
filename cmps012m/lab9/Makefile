#Antony Robbins androbbi@ucsc.edu
#Brandon Gomez brlgomez@ucsc.edu
MKFILE    = Makefile
NOINCLUDE = ci
NEEDINCL  = ${filter ${NOINCLUDE}, ${MAKECMDGOALS}}

GCC       = gcc -g -O0 -Wall -Wextra -std=gnu99
MKDEPS    = gcc -MM
GRIND     = valgrind --leak-check=full
NUMSOURCE = numsort.c inssort.c
LINESOURCE= linesort.c inssort.c
CHEADER   = inssort.h
NUMOBJ    = ${NUMSOURCE:.c=.o}
LINOBJ    = ${LINESOURCE:.c=.o}
EXECBIN   = numsort
EXECBIN2  = linesort
SOURCES   = ${CHEADER} ${NUMSOURCE} ${LINESOURCE} ${MKFILE}
LISTSRC   = ${SOURCES}
LISTING   = Listing.sort.ps
OUTPUT    = output*.lis

all : ${EXECBIN} ${EXECBIN2}

${EXECBIN} : ${NUMOBJ}
	${GCC} -o $@ ${NUMOBJ}
	
${EXECBIN2} : ${LINOBJ}
	${GCC} -o $@ ${LINOBJ}

%.o : %.c
	cid + $<
	${GCC} -c $<

ci : ${SOURCES}
	cid + ${SOURCES} test*.data

again :
	gmake ci all

ifeq "${NEEDINCL}" ""
endif

