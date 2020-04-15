CC		:= g++
CFLAGS	:= -std=c++17 -Wall -Wextra -g

BIN		:= bin
SRC		:= src
INCLUDE	:= include
LIB		:= lib

LIBRARIES	:= 

ifeq ($(OS),Windows_NT)
EXECUTABLE	:= main.exe
SOURCEDIRS	:= $(SRC)
INCLUDEDIRS	:= $(INCLUDE)
LIBDIRS		:= $(LIB)
else
EXECUTABLE	:= main
SOURCEDIRS	:= $(shell find $(SRC) -type d)
INCLUDEDIRS	:= $(shell find $(INCLUDE) -type d)
LIBDIRS		:= $(shell find $(LIB) -type d)
endif

CINCLUDES	:= $(patsubst %,-I%, $(INCLUDEDIRS:%/=%))
CLIBS		:= $(patsubst %,-L%, $(LIBDIRS:%/=%))

SOURCES		:= $(wildcard $(patsubst %,%/*.cpp, $(SOURCEDIRS)))
SOURCES		+= $(wildcard $(patsubst %,%/*.hpp, $(SOURCEDIRS)))

OBJECTS		:= $(SOURCES:.cpp=.o)
OBJECTS		+= $(SOURCES:.hpp=.o)

FILENAMES	:= $(SOURCES:.cpp=)
FILENAMES	+= $(SOURCES:.hpp=)

all: $(BIN)/$(EXECUTABLE)

.PHONY: clean
clean:
	-$(RM) $(BIN)/$(EXECUTABLE)
	-$(RM) $(OBJECTS)


run: all
	./$(BIN)/$(EXECUTABLE)

.c.o:
	$(CC) -c $(CFLAGS) $< -o $@

$(BIN)/$(EXECUTABLE): 
	for dir in $(FILENAMES); do \
		$(CC) -c $(CINCLUDES) $(CLIBS) -o $$dir.o $$dir.cpp; \
	done

	$(CC) $(CFLAGS) $(CINCLUDES) $(CLIBS) $(SRC)/main.o -o $@ $(LIBRARIES)