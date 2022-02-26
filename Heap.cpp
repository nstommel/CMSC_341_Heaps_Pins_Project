
/******************************************************************************
 * File:    Heap.cpp
 * Project: CMSC 341 Project 4, Fall 2016
 * Author:  Nicholas Stommel
 * Date:    11/22/16
 * Section: 05
 * E-mail:  stommel1@gl.umbc.edu
 * 
 * Description: This is the source file containing the implementation of 
 * the Heap templated abstract base class.
 * 
 ******************************************************************************/

#ifndef HEAP_CPP_
#define HEAP_CPP_

#include <iostream>
#include <stdexcept>

#define DEBUG false

#include "Heap.h"

template<class T, int m_size>
Heap<T, m_size>::Heap() : m_array(new T[m_size + 1]), m_numElements(0)
{}

template<class T, int m_size>
Heap<T, m_size>::Heap(const Heap<T, m_size>& origHeap) {

	// Note that array must be m_size + 1 in length, because index 0 is
	// not used to make percolating considerably easier. This avoids
	// invalid read/writes (valgrind check passes w/ no leaks or errors).
	m_array = new T[m_size + 1];
	
	// Copy over additional members
	m_numElements = origHeap.m_numElements;		
	for(int i = 1; i <= m_numElements; ++i) {
		m_array[i] = origHeap.m_array[i];
	}
}
	
template<class T, int m_size>
Heap<T, m_size>::~Heap() {
	delete [] m_array;
}

template<class T, int m_size>
bool Heap<T, m_size>::Contains(const T& needle) const {

	return (Find(needle) == NULL) ? false : true;  
}	


template<class T, int m_size>
const T* Heap<T, m_size>::Find(const T& needle) const {

	for(int i = 1; i <= m_numElements; ++i) {
		
		// If the current element is equal in pin number to the needle
		// (uses PinHit equality comparison operator), return the address
		// of that element as a pointer.
		if(m_array[i] == needle) {
			return &m_array[i];
		}
	}
	
	// If needle was not found, return null pointer.
	return NULL;
}

template<class T, int m_size>
T& Heap<T, m_size>::Remove() {

	// Safety check
	if(m_numElements == 0) {
		throw std::out_of_range("Cannot remove from empty heap!");
	}

	if(DEBUG) {
		std::cout << "Remove called on " << m_array[1].GetValue() << std::endl;
	}

	// Save copy of root value
	T temp = m_array[1];

	// Swap root with rightmost leaf at end of array, decrement the current number
	// of elements so PercolateDown functions correctly.
	m_array[1] = m_array[m_numElements--];
	PercolateDown(1);

	// Set now 'empty' slot to equal saved value, to avoid returning a 
	// reference to a local variable.
	m_array[m_numElements + 1] = temp;

	return m_array[m_numElements + 1];
}

template<class T, int m_size>
void Heap<T, m_size>::Insert(const T& insertable) {

	// Safety check
	if(m_numElements == m_size) {
		throw std::out_of_range("Cannot insert to full heap!");
	}

	if(DEBUG) {
		std::cout << "Insert called on " << insertable.GetValue() << std::endl;
	}

	m_array[++m_numElements] = insertable;
	PercolateUp(m_numElements);

}	

template<class T, int m_size>
void Heap<T, m_size>::PercolateUp(int index) {

	// While we haven't reached the root/top of the heap:
	while(index > 1) {

		// Stop if we reach a point where the node is in heap order.
		if(!isSwap(m_array[index], m_array[index / 2])) {

			if(DEBUG) {
				std::cout << "Stop, parent " << m_array[index / 2] 
						<< " lesser/greater than or equal to child " 
						<< m_array[index] << std::endl;
			}
			break;

		// Otherwise, swap parent and child.
		} else {
			if(DEBUG) {
				std::cout << "Swap parent " << m_array[index / 2] << " and child "
						<< m_array[index] << std::endl;
			}

			T temp = m_array[index];
			m_array[index] = m_array[index / 2];
			m_array[index / 2] = temp;

			// Advance to parent node
			index /= 2;
		}
	}
}

template<class T, int m_size>
void Heap<T, m_size>::PercolateDown(int index) {

	// While there are children, i.e. we haven't reached the bottom of the heap:
	while(index * 2 <= m_numElements) {

		// Default swapChild is left child.
		int swapChild = index * 2;

		// Note short-circuit evaluation, comparison not made if right child does not exist.
		if(index * 2 + 1 <= m_numElements && isSwap(m_array[index * 2 + 1], m_array[index * 2])) {

			// If right child exists and is less/greater than left child, assign swapChild to right.
			swapChild = index * 2 + 1;
		}

		// Stop if we reach a point where the node is in heap order
		if(!isSwap(m_array[swapChild], m_array[index])) {
			if(DEBUG) {
				std::cout << "Stop, child " << m_array[swapChild] 
						<< " lesser/greater than or equal to parent " 
						<< m_array[index] << std::endl;
			}
			break;

		// Otherwise, swap child and parent
		} else {
			if(DEBUG) {
				std::cout << "Swap child " << m_array[swapChild] << " and parent " 
						<< m_array[index] << std::endl;
			}

			T temp = m_array[index];
			m_array[index] = m_array[swapChild];
			m_array[swapChild] = temp;

			// Advance to child node
			index = swapChild;
		}
	}
}
	
template<class T, int m_size>
int Heap<T, m_size>::getNumElements() const {
	return m_numElements;
}

template<class T, int m_size>
std::ostream& operator << (std::ostream& os, const Heap<T, m_size>& h) {
	
	std::cout << "[[X (no element here)],";
	for(int i = 1; i <= h.m_numElements; ++i) {
		os << h.m_array[i];
		if(i < h.m_numElements) {
			std::cout << ',';
		}
		
		// Print a line break every 5 pins
		if((i + 1) % 5 == 0 && i < h.m_numElements) {
			std::cout << std::endl;
		}
	}
	std::cout << ']' << std::endl;
	
	return os;
}


#endif /* HEAP_CPP_ */
