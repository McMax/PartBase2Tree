CC	= g++
LD	= g++

CCFLAGS = -g -O0 `root-config --cflags` -lEG -Wall -I$(PEV_INC)
LDFLAGS = -g -O0 `root-config --libs` -lEG -Wall -L$(PEV_SRC)

TOPDIR = .
PEV_DIR = $(TOPDIR)/../Particle_Event_PbPb
PEV_LIB = $(PEV_DIR)/lib
PEV_SRC = $(PEV_DIR)/src
PEV_INC = $(PEV_DIR)/inc

PROGRAM = converter

PEV_OBJECTS = $(PEV_LIB)/Particle.o $(PEV_LIB)/Event.o $(PEV_LIB)/ParticleTree.o $(PEV_LIB)/Dict.o

all: $(PROGRAM)

$(PROGRAM): Convert2Tree.o $(PEV_OBJECTS)
	$(LD) $(LDFLAGS) $^ -o $@ 

Convert2Tree.o:
	$(CC) -c $(CCFLAGS) Convert2Tree.cpp -o Convert2Tree.o

$(PEV_OBJECTS):
	@echo "No base libs. Create them"
	
clean:
	@rm -rf $(PROGRAM) Convert2Tree.o
