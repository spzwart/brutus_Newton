###################################################################
#ROOT    = /Users/shabaz/Dropbox/2016_projects/mp_libs/
ROOT    = /usr/lib
LOCAL	= /home/spz

#MPRDIR  = $(ROOT)gp.o
#MPRLIB  = $(ROOT)Packages/mpreal_local/lib/
MPRLIB  = $(LOCAL)/src/mpreal

#INCLUDE_DIR = -I/usr/local/Cellar/gmp/6.1.0/include/ -I/usr/local/Cellar/mpfr/3.1.4/include

HOME    = ./
ROOTDIR = ./

LIB     = $(HOME)lib/
MPLIB   = $(HOME)mplib/

DIRTIM  = $(LIB)Timer/
DIRDH   = $(LIB)Data_Handler/
###################################################################
COMP = g++
NVCOMP = nvcc
CFLAGS = -O3 -std=c++11
CC  = $(COMP) $(CFLAGS) -c
NVCC  = $(NVCOMP) $(CFLAGS) -c
CO  = $(COMP) $(CFLAGS) -o
###################################################################
EXE = brutus
all: $(EXE)
###################################################################
brutus: main.o Brutus.o Bulirsch_Stoer.o Cluster.o Star.o Data_Handler.o Timer.o 
	$(CO) brutus main.o Brutus.o Bulirsch_Stoer.o Cluster.o Star.o Data_Handler.o Timer.o -lgmpxx -lgmp -lmpfr 
###################################################################
main.o: main.cpp Brutus.o Bulirsch_Stoer.o Cluster.o Star.o Data_Handler.o Timer.o 
	$(CC) main.cpp -I$(DIRTIM) -I$(DIRDH) -I$(MPRLIB)
###################################################################
Brutus.o: Brutus.h Brutus.cpp Bulirsch_Stoer.o Cluster.o Star.o Timer.o
	$(CC) Brutus.cpp -I$(DIRTIM) -I$(MPRLIB)

Bulirsch_Stoer.o: Bulirsch_Stoer.h Bulirsch_Stoer.cpp Cluster.o Star.o 
	$(CC) Bulirsch_Stoer.cpp -I$(DIRTIM) -I$(MPRLIB)
Cluster.o: Cluster.h Cluster.cpp Star.o 
	$(CC) Cluster.cpp -I$(MPRLIB)
Star.o: Star.h Star.cpp 
	$(CC) Star.cpp -I$(MPRLIB)

Data_Handler.o: $(DIRDH)Data_Handler.h $(DIRDH)Data_Handler.cpp
	$(CC) $(DIRDH)Data_Handler.cpp
Timer.o: $(DIRTIM)Timer.h $(DIRTIM)Timer.cpp
	$(CC) $(DIRTIM)Timer.cpp

###################################################################
clean:
	rm -f *~
	rm -f *.o
	rm -f -r ccache
	rm -f .fuse*
	rm -f brutus



