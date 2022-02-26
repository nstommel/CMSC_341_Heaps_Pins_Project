
/******************************************************************************
 * File:    Driver.cpp
 * Project: CMSC 341 Project 4, Fall 2016
 * Author:  Nicholas Stommel
 * Date:    11/22/16
 * Section: 05
 * E-mail:  stommel1@gl.umbc.edu
 * 
 * Description: This is the driver file containing the main() function which accepts
 * two command line arguments, the input filename and the min/max heap flag. Functions
 * implemented in the file include a basic greeting function, a ReadPins function which
 * performs file processing on the input pins file and returns a vector of PinHits,
 * a debugging function to print out the returned vector from ReadPins, and a function
 * to build and return the heap from the ReadPins vector. The Hack function takes the
 * built heap and corresponding PinHits vector and simulates hacking four-digit pin
 * numbers on a user's account. Note: memory leaks fixed, verify with valgrind
 * using make mem-check.
 * 
 ******************************************************************************/

#include <cstdlib>
#include <iostream>
#include <iomanip>
#include <fstream>
#include <cstring>
#include <string>
#include <vector>
#include <time.h>

#include "PinHit.h"
#include "Heap.h"
#include "MinHeap.h"
#include "MaxHeap.h"

// global variable for type of heap
std::string heapType = "--max";

//forward declarations for function definitions below main()

//-------------------------------------------------------
// Name: printGreeting
// PreConditions: none
// PostConditions: prints name and section number
//---------------------------------------------------------
void printGreeting();

//-------------------------------------------------------
// Name: ReadPins
// PreConditions: filename must be valid, check performed
// PostConditions: populates and returns vector of PinHits read from
// a file. 
// Notes: Pins not in the file are set to EMPTY (-1) so they are
// skipped in BuildHeap.
//---------------------------------------------------------
std::vector<PinHit> ReadPins(const char* fileName, int* totalHits);

//-------------------------------------------------------
// Name: dumpPinHitsVec
// PreConditions: none
// PostConditions: prints contents of PinHits vector to console for
// debugging purposes.
//---------------------------------------------------------
// Dump Pin-Hits-Vector to console (debugging function)
void dumpPinHitsVec(const std::vector<PinHit>& PinHits);

//-------------------------------------------------------
// Name: BuildHeap
// PreConditions: none
// PostConditions: inserts to a new heap object data from n slots in
// a passed in PinHits vector, returns a pointer to the constructed heap
// Notes: Pass PinHits vector by const reference to avoid invoking expensive copy 
// constructor on large vector if PinHits is passed by value.
//---------------------------------------------------------
template<class T, int m_size>
Heap<T, m_size>* BuildHeap(const std::vector<T>& PinHits, int slots);

//-------------------------------------------------------
// Name: BuildHeap
// PreConditions: heap pointer must point to valid heap, cannot be null
// PostConditions: inserts to a new heap object data from n slots in
// a passed in PinHits vector, returns a pointer to the constructed heap
// Notes: Pass PinHits vector by const reference to avoid invoking expensive copy 
// constructor on large vector if PinHits is passed by value.
//---------------------------------------------------------
template<class T, int m_size>
int Hack(Heap<T, m_size>* heap, const std::vector<T>& PinHits, int totalHits);


int main(int argc, char* argv[]) {

	printGreeting();
	
	// Test second command line argument for validity
	if(strcmp("--max", argv[2]) == 0) {
		heapType = "--max";
	} else if(strcmp("--min", argv[2]) == 0) {
		heapType = "--min";
	} else {
		throw std::invalid_argument("Invalid second command line argument, must choose --max or --min heap.");
	}
	
	// Create output integer variable to pass to ReadPins function
	int totalHits = 0;
	// Read in pin data from file specified in argv[1]
	std::vector<PinHit> phits = ReadPins(argv[1], &totalHits);
	
	// Uncomment to see contents of PinHits vector returned by ReadPins
	//dumpPinHitsVec(phits);
	
	// Construct heap object using BuildHeap
	Heap<PinHit, PinHit::MAX_PINS>* heap = BuildHeap<PinHit, PinHit::MAX_PINS>(phits, PinHit::MAX_PINS);
	
	// Print out contents of heap and total hits
	std::cout << *heap << std::endl;
	std::cout << "Total Hits: " << totalHits << std::endl;
	
	// Invoke hack function and print successful hacks returned.
	int successfulHacks = Hack(heap, phits, totalHits);
	std::cout << "Successful Hacks: " << successfulHacks << std::endl;
	
	/*
	// Test find and contains methods
	PinHit f(4970, 0);
	std::cout << std::endl << "Found pin: ";
	if(heap->Find(f) != NULL) {
		std::cout << *heap->Find(f) << std::endl;
	} else {
		std::cout << "X (not in heap)" << std::endl;
	}
	std::cout << ((heap->Contains(f)) ? "True" : "False") << std::endl;
	//std::cout << *p << std::endl;
	*/
	
	// Free memory allocated for original heap
	delete heap;
	
	return EXIT_SUCCESS;
}

// prints name and section
void printGreeting() {
	
	std::cout << "Nicholas Stommel, Section 05" << std::endl;
}

std::vector<PinHit> ReadPins(const char* fileName, int* totalHits) {
	
	// Create vector with 10000 slots corresponding to all possible 4-digit pins
	std::vector<PinHit> pinHits(PinHit::MAX_PINS, PinHit());
	
	// Open pin file
	std::ifstream input(fileName);
	if(!input.is_open()) {
		throw std::runtime_error("Could not open file!");
	}

	// Loop through file and read in pin numbers
	std::string line;
	while(!input.eof()) {
		
		getline(input, line);
		
		// Skip empty lines
		if(!line.empty()) {

			// Pin verification is adaptable, MAX_PINS constant can be changed in PinHit class
			// to accommodate larger than four-digit pins
			
			// Verify that every character in pin line is a digit, otherwise throw an exception
			for(int i = 0; i < (int)line.length(); ++i) {
				if (!isdigit(line[i])) {
					throw std::runtime_error("Invalid pin number in file, must be all integers!");
				}
			}

			// Line is an integer, convert to int
			int pin = atoi(line.c_str());

			// If pin number exceeds MAX_PINS constant in PinHit class, throw an exception
			if(pin >= PinHit::MAX_PINS) {
				throw std::runtime_error("Invalid pin number in file, cannot exceed maximum pin number!");
			}

			pinHits[pin].SetKey(pin);
			pinHits[pin].IncrementHits();
			++(*totalHits);
		}
	}
	
	return pinHits;
}

void dumpPinHitsVec(const std::vector<PinHit>& PinHits) {
	
	for(int i = 0; i < (int)PinHits.size(); ++i) {
		std::cout << PinHits[i];
		
		// Print four PinHits per line
		if((i + 1) % 4 == 0) {
			std::cout << std::endl;
		}
	}
	std::cout << std::endl;
}

template<class T, int m_size>
Heap<T, m_size>* BuildHeap(const std::vector<T>& PinHits, int slots) {
	
	Heap<T, m_size>* heap;
	if(heapType == "--min") {
		if(DEBUG) {
			std::cout << "Allocating memory for new MIN Heap..." << std::endl;
		}
		heap = new MinHeap<T, m_size>;
	} else {
		if(DEBUG) {
			std::cout << "Allocating memory for new MAX Heap..." << std::endl;
		}
		heap = new MaxHeap<T, m_size>;
	}
	
	// Loop through x slots in the given vector, inserting if the PinHit was
	// found in the file (it's key is not marked as -1 or EMPTY)
	for(int i = 0; i < slots; ++i) {
		
		// If PinHit was present in file, add it to heap
		if(PinHits[i].GetKey() != PinHit::EMPTY) {
			heap->Insert(PinHits[i]);
		}
	}
	
	return heap;
}

// provided
template<class T, int m_size>
int Hack(Heap<T, m_size>* heap, const std::vector<T>& PinHits, int totalHits) {

	int UPPER_BOUND = totalHits; // used for failsafes

	/*
	* His fictional bank with fictional cards and 
	* "normal pins" will allow you to incorrectly attempt 
	* to access his card 3 times per hour. You have from 
	* the start of the assignment to the end to hack as 
	* many accounts as possible (14 days * 24 hr/day * 3 
	* attempts/hr = 1008 attempts per card)
	*/
	int MAX_ATTEMPTS = 1008;

	int hackAttemptsLeft = MAX_ATTEMPTS;
	int successfulHacks = 0;

  	srand (time(NULL)); // seeds our random generator with the current time  	
	int randomNumHits = rand() % totalHits; // generates a random hit between 0 and total hits	
	//randomNumHits = 0; // change this if you want to hardcode in your hits for a specific pin
	int curHits = 0; // our variable for crawling
	int randomIndex = -1; // the index where our new random pinhit lives
	int newHits = 0; // number of hits in new "random" pin
	int failSafe = 0; // always good to have one of these in what could be an infinite loop

	/* 
	* Linearly searches through PinHits until
	* we've accrued enough hits to reach our random hits
	* which will then determine the next pin to try to hack.
	* We use newHits to make sure we don't pick a random pin
	* that's not in our heap. 
	*/
	PinHit curPinHit;
	while (newHits == 0 && failSafe < UPPER_BOUND) {

		for (unsigned int i = 0; i < PinHits.size() && curHits <= randomNumHits; i++) {
			curHits += PinHits[i].GetValue();
			randomIndex = i;
		}
		// should have found the random pin by now
		curPinHit = PinHits[randomIndex];
		newHits = curPinHit.GetValue(); // make sure it's actually in our heap
		std::cout << "Random Pin: [" << curPinHit.GetKey() << ", " << curPinHit.GetValue() << "] found!" << std::endl;
		failSafe++;
	}

	// let's make a copy of the heap so we don't modify the original.
	Heap<T, m_size>* heapCopy;

	if (heapType == "--min") {
		heapCopy = new MinHeap<T, m_size>(*heap);
	} else if (heapType == "--max") {
		heapCopy = new MaxHeap<T, m_size>(*heap);
	}
	// Cannot instantiate abstract base class Heap
	//} else {
	//	heapCopy = new Heap<T, m_size>(*heap);
	//}
	
	failSafe = 0;

	PinHit defaultPin;

	// exit once hacking 10000 accounts, either a hacking prodigy or something is wrong
	int MAX_NUM_HACKS = 10000;

	while (0 < hackAttemptsLeft && successfulHacks < MAX_NUM_HACKS) {

		// grabs our root
		PinHit topOfHeap = heapCopy->Remove();
		if (topOfHeap == defaultPin)
			break;

		std::cout << topOfHeap.GetKey() << ", " << topOfHeap.GetValue() << std::endl;

		if (hackAttemptsLeft == 1)
		std::cout << topOfHeap.GetKey() << ", " << topOfHeap.GetValue() << " our last attempt" << std::endl;

		hackAttemptsLeft--;

		// account was hacked!
		if (topOfHeap == curPinHit) {
			std::cout << "We got them!" << std::endl;
			successfulHacks++;

			// Clean up memory
			delete heapCopy;
			
			// reset our heap
			if (heapType == "--min") {
				heapCopy = new MinHeap<T, m_size>(*heap);
			} else if (heapType == "--max") {
				heapCopy = new MaxHeap<T, m_size>(*heap);
			} 
			// Cannot instantiate abstract base class Heap
			//} else {
			//	heapCopy = new Heap<T, m_size>(*heap);
			//}

			// reset
			hackAttemptsLeft = MAX_ATTEMPTS;
			randomNumHits = rand() % totalHits;
			curHits = 0;
			randomIndex = -1;
			newHits = 0;
			failSafe = 0;
			while (newHits == 0 && failSafe < UPPER_BOUND) {

				for (unsigned int i = 0; i < PinHits.size() && curHits <= randomNumHits; i++) {
					curHits += PinHits[i].GetValue();
					randomIndex = i;
				}
				// should have found the random pin by now
				curPinHit = PinHits[randomIndex];
				newHits = curPinHit.GetValue(); // make sure it's actually in our heap
				std::cout << "Random Pin: [" << curPinHit.GetKey() << ", " << curPinHit.GetValue() << "] found!" << std::endl;
				failSafe++;
			}

			std::cout << "Valid Random Pin: " << curPinHit.GetKey() << " found!" << std::endl;
		}
	}
	
	// Clean up memory
	delete heapCopy;

	return successfulHacks;

}
