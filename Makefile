UNAME		 = $(shell uname)
CXX          = g++
LDFLAGS      = -Iinclude
ifeq ($(UNAME), Darwin)
	CXXFLAGS = -pedantic -Wall -march=native -Xpreprocessor -fopenmp -lomp
else
	CXXFLAGS = -pedantic -Wall -march=native -fopenmp 
endif
DEBUGFLAGS   = -O0 -ggdb3 -Wextra
RELEASEFLAGS = -O3 -DNDEBUG
PROFILEFLAGS = $(RELEASFLAGS) -pg

TARGET       = vlg.out
SOURCEDIR    = src/
SOURCES      = $(shell find $(SOURCEDIR) -name '*.cpp')
INCLUDEDIR   = src/
HEADERS      = $(shell find $(INCLUDEDIR) -name '*.h')
COMMON       = README.md Makefile .gitignore data/
OBJECTS      = $(SOURCES:.cpp=.o)

PREFIX       = $(DESTDIR)/usr/local
BINDIR       = $(PREFIX)/bin

all: debug

release: CXXFLAGS += $(RELEASEFLAGS)
release: $(TARGET)

debug: CXXFLAGS += $(DEBUGFLAGS)
debug: $(TARGET)

clean:
	rm -f $(OBJECTS) gmon.out $(TARGET)

tarball:
	tar -cvzf $(TARGET).tar.gz $(HEADERS) $(SOURCES) $(COMMON) Makefile

$(TARGET): $(OBJECTS)
	$(CXX) $(LDFLAGS) $(CXXFLAGS) -o $(TARGET) $(OBJECTS)

%.o: %.cpp
	$(CXX) $(LDFLAGS) $(CXXFLAGS) -o $@ -c $<

.PHONY: all release debug clean tarball