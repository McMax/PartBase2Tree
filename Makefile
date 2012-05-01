CC	= g++
LD	= g++

CCFLAGS = -g -O0 `root-config --cflags` -lEG -Wall -I./inc
LDFLAGS = -g -O0 `root-config --libs` -lEG -Wall -L./lib

TOPDIR = .
SRC_DIR = $(TOPDIR)/src
OBJ_DIR = $(TOPDIR)/lib
INC_DIR = $(TOPDIR)/inc

PROGRAM = converter

SOURCES := $(shell find $(SRC_DIR) -type f -name "*.cpp")
OBJECTS := $(patsubst $(SRC_DIR)/%.cpp, $(OBJ_DIR)/%.o, $(SOURCES))
INCLUDES := $(addprefix -I,$(SRC_DIR))
INCLUDES += inc/linkdef.h

all: $(PROGRAM)

$(PROGRAM): $(OBJECTS)
	$(warning $(OBJECTS))
	$(LD) $(LDFLAGS) $^ -o $@ 

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp
	$(CC) -c $(CCFLAGS) $< -o $@ 

Dict.cpp: $(INCLUDES) $(INC_DIR)/linkdef.h
	@echo "Generating dictionary..."
	@rootcint -f src/Dict.cpp -c -P -I$ROOTSYS -I/usr/local/include $(INCLUDES)

lib/Particle.o: src/Particle.cpp
	g++ -c -o $@ $< $(CCFLAGS)

lib/Event.o: src/Event.cpp
	g++ -c -o $@ $< $(CCFLAGS)

clean:; @rm $(PROGRAM) ./lib/*.o	
