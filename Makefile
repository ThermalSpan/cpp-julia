# Created By Russell Bentley
# Copyright (c) 2015 Russell Wilhelm Bentley
# Distributed under the MIT License

# Compiler Stuff
CC      = g++
CFLAGS  = -c -std=c++11 -stdlib=libc++ -Wall -I/usr/local/include
LFLAGS  = -L/usr/local/lib -ltiff

# Directories
TEMPDIRS = build bin build/buddha

# File/s
BUDDHAFILES = main

# Derived File Lists
BUDDHASRC = $(BUDDHAFILES:%=src/buddha/%.cpp)
BUDDHAOBJ = $(BUDDHAFILES:%=build/buddha/%.o)

# Targets
all: dirFile bin/buddha

dirFile:
	for dir in $(TEMPDIRS); do \
		mkdir -p $$dir; \
	done
	@touch dirFile

build/%.o : src/%.cpp
	$(CC) $(CFLAGS) -g $< -o $@

bin/buddha : $(BUDDHAOBJ)
	$(CC) $(LFLAGS) $^ -o bin/buddha

# Phone commands
.PHONY: install
install: bin/buddha
	cp bin/buddha Tests/buddha

.PHONY: clean
clean:
	rm -f -r build bin dirFile Tests/buddha Tests/buddha.dSYM
