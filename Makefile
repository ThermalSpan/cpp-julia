# Created By Russell Bentley
# Copyright (c) 2015 Russell Wilhelm Bentley
# Distributed under the MIT License

# Compiler Stuff
CC      = g++
CFLAGS  = -c -std=c++11 -stdlib=libc++ -Wall -I/usr/local/include
LFLAGS  = -L/usr/local/lib -ltiff

# Directories
TEMPDIRS = build bin build/buddha build/Math build/fractal build/Tiff

# File/s
FRACTALFILES = main
MATHFILES = 
TIFFILES = tiffWrapper

# Derived File Lists
MATHSRC = $(MATHFILES:%=src/Math/%.cpp)
MATHOBJ = $(MATHFILES:%=build/Math/%.o)

FRACTALSRC = $(FRACTALFILES:%=src/fractal/%.cpp)
FRACTALOBJ = $(FRACTALFILES:%=build/fractal/%.o)

TIFFSRC = $(TIFFILES:%=src/Tiff/%.cpp)
TIFFOBJ = $(TIFFILES:%=build/Tiff/%.o)

# Targets
all: dirFile bin/mandelbrot

dirFile:
	for dir in $(TEMPDIRS); do \
		mkdir -p $$dir; \
	done
	@touch dirFile

build/%.o : src/%.cpp
	$(CC) $(CFLAGS) -g $< -o $@

bin/mandelbrot : $(FRACTALOBJ) $(TIFFOBJ)
	$(CC) $(LFLAGS) $^ -o bin/mandelbrot

# Phone commands
.PHONY: install
install: bin/buddha
	cp bin/buddha Tests/buddha

.PHONY: clean
clean:
	rm -f -r build bin dirFile Tests/buddha Tests/buddha.dSYM
