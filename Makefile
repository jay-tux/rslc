CC=g++
CXXFLAGS=-std=c++17 -Wall -Wextra -pedantic -MMD -g -c -Iinc/
LIBFLAGS=-fPIC
LIBLDFLAGS=-shared
LDFLAGS=-L./bin/ -lrslc

SRCDIRS=$(shell find src/ -mindepth 1 -type d)
OBJDIRS=$(SRCDIRS:src/%=obj/%)

LIBSRCFS=$(shell find src/lib/ -name '*.cpp')
LIBOBJFS=$(LIBSRCFS:src/%.cpp=obj/%.o)
LIBDEPS=$(LIBOBJFS:%.o=%.d)

SRCFILES=src/main.cpp
OBJFILES=$(SRCFILES:src/%.cpp=obj/%.o)
DEPFILES=$(OBJFILES:%.o=%.d)

# Phony targets
all: dirs lib rslc

lib: bin/librslc.so

rslc: bin/rslc

dirs: $(SRCDIRS)
	mkdir -p $(OBJDIRS)

clean:
	rm -rf obj/*
	rm -rf bin/*

# Binaries
bin/rslc: bin/librslc.so $(OBJFILES)
	$(CC) $(OBJFILES) $(LDFLAGS) -o bin/rslc

bin/librslc.so: $(LIBOBJFS)
	$(CC) $(LIBOBJFS) $(LIBLDFLAGS) -o bin/librslc.so

# Include dependencies
-include $(LIBDEPS) $(DEPFILES)

# Objects
obj/lib/%.o: src/lib/%.cpp Makefile
	$(CC) $< $(CXXFLAGS) $(LIBFLAGS) -o $@

obj/%.o: src/%.cpp Makefile
	$(CC) $< $(CXXFLAGS) -o $@

.PHONY: all lib rslc dirs clean
