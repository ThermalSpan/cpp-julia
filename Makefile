# Created By Russell Bentley
# Copyright (c) 2015 Russell Wilhelm Bentley
# Distributed under the MIT License

# Compiler Stuff
CC      = g++
CFLAGS  = -c -std=c++11 -stdlib=libc++ -Wall -I/usr/local/include
LFLAGS  = -L/usr/local/lib -ltiff

# Directories
TEMPDIRS = build bin 

# File/s
FILES = main tiffWrapper AtomicGrid

# Derived File Lists
SRC = $(FILES:%=src/%.cpp)
OBJ = $(FILES:%=build/%.o)

# Targets
all: dirFile bin/mandelbrot

dirFile:
	for dir in $(TEMPDIRS); do \
		mkdir -p $$dir; \
	done
	@touch dirFile

build/%.o : src/%.cpp
	$(CC) $(CFLAGS) -g $< -o $@

bin/mandelbrot : $(OBJ) 
	$(CC) $(LFLAGS) $^ -o bin/mandelbrot

# Phone commands
.PHONY: clean
clean:
	rm -f -r build bin dirFile Tests/buddha Tests/buddha.dSYM
