
/******************************************************************************
 * File:    Heap.h
 * Project: CMSC 341 Project 4, Fall 2016
 * Author:  Nicholas Stommel
 * Date:    11/22/16
 * Section: 05
 * E-mail:  stommel1@gl.umbc.edu
 * 
 * Description: This is the header file containing the declaration of 
 * the Heap templated abstract base class. This implementation of a heap
 * uses a basic array of T objects. A heap supports insert, remove-from-root, 
 * find, and contains operations. The destructor is made virtual
 * so that derived classes can deallocate memory for the array appropriately.
 * 
 ******************************************************************************/

#ifndef HEAP_H_
#define HEAP_H_

#include <iostream>

// Forward declaration necessary for overloaded templated insertion operator
// for printing out heap (useful for debugging and checking contents of heap).
template<class T, int m_size> class Heap;
template<class T, int m_size> std::ostream& operator << (std::ostream& os, const Heap<T, m_size>& h);

template<class T, int m_size> 
class Heap {

public:

	//-------------------------------------------------------
	// Name: Heap default constructor
	// PreConditions: none
	// PostConditions: allocates memory for data storage, sets
	// number of elements to 0
	//---------------------------------------------------------
	Heap();
	
	//-------------------------------------------------------
	// Name: Heap copy constructor
	// PreConditions: passed in heap must be valid
	// PostConditions: allocates memory for data storage and
	// copies over data of passed in original heap
	//---------------------------------------------------------
	Heap(const Heap<T, m_size>& origHeap);
	
	//-------------------------------------------------------
	// Name: Heap destructor
	// PreConditions: none
	// PostConditions: deallocates memory for m_array
	// Notes: Destructor made virtual so that derived classes utilize Heap destructor 
	//---------------------------------------------------------
	virtual ~Heap();
	
	//-------------------------------------------------------
	// Name: Contains
	// PreConditions: none
	// PostConditions: returns true if needle was found in heap, false otherwise
	// Notes: uses Find function
	//---------------------------------------------------------
	bool Contains(const T& needle) const;
	
	//-------------------------------------------------------
	// Name: Find
	// PreConditions: none
	// PostConditions: returns pointer to PinHit in array if pin is in heap, NULL otherwise
	//---------------------------------------------------------
	const T* Find(const T& needle) const;
	
	//-------------------------------------------------------
	// Name: Remove
	// PreConditions: there must be at least one element in the heap to remove from root
	// PostConditions: returns reference to root object T, removes root and re-establishes
	// heap order.
	// Notes: uses PercolateDown function to re-establish heap order
	//---------------------------------------------------------
	T& Remove();
	
	//-------------------------------------------------------
	// Name: Insert
	// PreConditions: there must be enough storage space in the array to insert
	// PostConditions: inserts a T element to the heap, re-establishes heap order
	// Notes: uses PercolateUp function to re-establish heap order,
	// insertable made const parameter because inserted T object will not be
	// changed (also fixes compiler error so that vector can be passed by
	// const ref in BuildHeap function from Driver.cpp)
	//---------------------------------------------------------
	void Insert(const T& insertable);

	//-------------------------------------------------------
	// Name: getNumElements
	// PreConditions: none
	// PostConditions: returns current number of elements in heap
	//---------------------------------------------------------
	int getNumElements() const;
	
	//-------------------------------------------------------
	// Name: overloaded insertion operator (for printing contents of heap)
	// PreConditions: none
	// PostConditions: prints out entire contents of heap in rows to console
	// Notes: uses PinHit overloaded insertion operator, prints heap in level-order
	// by looping through the array
	//---------------------------------------------------------
	friend std::ostream& operator << <T, m_size>(std::ostream& os, const Heap<T,m_size>& h);

protected:

	//-------------------------------------------------------
	// Name: PercolateUp
	// PreConditions: none
	// PostConditions: re-establishes heap order from index to root
	//---------------------------------------------------------
	void PercolateUp(int index);
	
	//-------------------------------------------------------
	// Name: PercolateDown
	// PreConditions: none
	// PostConditions: re-establishes heap order from index to 
	// bottom of tree.
	//---------------------------------------------------------
	void PercolateDown(int index);
	
	//-------------------------------------------------------
	// Name: isSwap
	// PreConditions: none
	// PostConditions: returns true if first and second T objects are swappable
	// Notes: uses PinHit CompareTo function, used to compare values of two elements in the heap. 
	// Utilized in PercolateUp(...) and PercolateDown(...). Pure virtual, implemented in
	// MinHeap and MaxHeap classes. Makes Heap an abstract base class.
	//---------------------------------------------------------
	virtual bool isSwap(const T& first, const T& second) = 0;
	
	// The storage array for the heap elements.
	T* m_array;
	
	// The current number of T elements in the heap, is changed on insert and remove
	int m_numElements;

};

#include "Heap.cpp"
#endif /* HEAP_H_ */
