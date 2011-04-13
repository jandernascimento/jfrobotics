#######################################
# Makefile PBM                        #
#                                     #
# E.B.                                #
#######################################


PROG = wave  #pxmtopxm pgmtopgm

all : $(PROG)

# Variables pour la compilation des fichiers
CC        =  gcc
CFLAGS    =  -g -Wall -std=c99
CPPFLAGS  =  -DDEBUG
LDFLAGS   =  -g -lm

wave : wave.o  

clean : 
	@rm -f *.o
	@rm wave

.PHONY: clean

cleanall : clean
	@rm -f $(PROG)

