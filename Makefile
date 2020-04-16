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
CINCLUDES	+= -I$(SRC)

CLIBS		:= $(patsubst %,-L%, $(LIBDIRS:%/=%))

SOURCESCPP		:= $(shell find $(SRC) -name "*.cpp")
SOURCESHPP		:= $(shell find $(SRC) -name "*.hpp")

OBJECTS		:= $(SOURCESCPP:.cpp=.o)
OBJECTS		+= $(SOURCESHPP:.hpp=.o)

FILENAMESCPP	:= $(SOURCESCPP:.cpp=)
FILENAMESHPP	:= $(SOURCESHPP:.hpp=)

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
	for dir in $(FILENAMESCPP); do \
		echo compile $$dir.cpp; \
		$(CC) -c $(CINCLUDES) $(CLIBS) -o $$dir.o $$dir.cpp; \
	done

	for dir in $(FILENAMESHPP); do \
		echo compile $$dir.hpp; \
		$(CC) -c $(CINCLUDES) $(CLIBS) -o $$dir.o $$dir.hpp; \
	done

	$(CC) $(CFLAGS) $(CINCLUDES) $(CLIBS) $(SRC)/main.o -o $@ $(LIBRARIES)
