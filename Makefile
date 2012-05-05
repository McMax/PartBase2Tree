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
INCLUDES := $(shell find $(INC_DIR) -type f -name "*.h")

all: $(PROGRAM)

$(PROGRAM): $(OBJECTS)
	$(LD) $(LDFLAGS) $^ -o $@ 

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp
	mkdir -p $(OBJ_DIR)
	$(CC) -c $(CCFLAGS) $< -o $@ 

Dict.cpp: $(INCLUDES)
	@echo "Generating dictionary..."
	@rootcint -f src/Dict.cpp -c -P -I$(ROOTSYS) -I/usr/local/include $(INCLUDES)

clean:
	@rm $(PROGRAM) -r ./lib	

