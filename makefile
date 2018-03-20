IDIR=include
SDIR=src
ODIR=bin

CC=clang++
CFLAGS=-I $(IDIR) -std=c++11 -Wall -Wextra -pedantic -g

_DEPS = Cluster.hpp Processor.hpp TaskGraph.hpp read_write.hpp Scheduler.hpp
DEPS = $(patsubst %, $(IDIR)/%, $(_DEPS))

SOURCES = Cluster.cpp Processor.cpp read_write.cpp Scheduler.cpp
_OBJ = $(SOURCES:.cpp=.o)
OBJ = $(patsubst %, $(ODIR)/%, $(_OBJ))

$(ODIR)/%.o: $(SDIR)/%.cpp $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)
	
all: $(OBJ)
	$(CC) -o $(ODIR)/main.o $(SDIR)/main.cpp $(OBJ) $(CFLAGS)

.PHONY: clean

clean:
	rm -f $(ODIR)/*.o core