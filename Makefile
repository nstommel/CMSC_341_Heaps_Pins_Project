
# Nick Stommel - Project 4 Makefile

CCFLAGS = -Wall -ansi -ggdb
OBJ_FILES = Driver.o PinHit.o Heap.o MaxHeap.o MinHeap.o
SUBMIT_DIR = /afs/umbc.edu/users/s/l/slupoli/pub/cs341/stommel1/proj4/src

# Makefile constants set to defaults, can be overridden
# by specifying values in command line, or changed here.
INPUT = Input2.txt
FLAG = --max

Driver.out: $(OBJ_FILES)
	g++ $(CCFLAGS) $(OBJ_FILES) -o Driver.out

# All dependencies reliably found using g++ -MM compiler flag
Driver.o: Driver.cpp PinHit.h Heap.h Heap.cpp MinHeap.h MinHeap.cpp MaxHeap.h MaxHeap.cpp
	g++ $(CCFLAGS) -c Driver.cpp

PinHit.o: PinHit.cpp PinHit.h
	g++ $(CCFLAGS) -c PinHit.cpp

Heap.o: Heap.cpp Heap.h
	g++ $(CCFLAGS) -c Heap.cpp

MaxHeap.o: MaxHeap.cpp MaxHeap.h Heap.h Heap.cpp
	g++ $(CCFLAGS) -c MaxHeap.cpp

MinHeap.o: MinHeap.cpp MinHeap.h Heap.h Heap.cpp
	g++ $(CCFLAGS) -c MinHeap.cpp

.PHONY: clean
clean:
	rm -f *.o *~ *.out

.PHONY: run
run: Driver.out
	./Driver.out $(INPUT) $(FLAG)

.PHONY: mem-check
mem-check: Driver.out
	valgrind ./Driver.out $(INPUT) $(FLAG) 

.PHONY: submit
submit:
	cp *.cpp *.h Makefile $(SUBMIT_DIR)
