
/******************************************************************************
 * File:    MinHeap.h
 * Project: CMSC 341 Project 4, Fall 2016
 * Author:  Nicholas Stommel
 * Date:    11/22/16
 * Section: 05
 * E-mail:  stommel1@gl.umbc.edu
 * 
 * Description: This is the header file containing the declaration of 
 * the templated derived class MinHeap. This class is very minimally extended,
 * only the isSwap function is changed by a single comparison operator. In a
 * MinHeap, every child node is greater than or equal to its parent, and every
 * parent node is less than or equal to its children.
 * 
 ******************************************************************************/

#ifndef MINVALUEHEAP_H_
#define MINVALUEHEAP_H_

#include "Heap.h"

template<class T, int m_size>
class MinHeap : public Heap<T, m_size> {
	
public:
	
	//-------------------------------------------------------
	// Name: MinHeap default constructor
	// PreConditions: none
	// PostConditions: allocates memory for element storage and sets 
	// number of elements to 0 by invoking base class Heap constructor
	//---------------------------------------------------------
	MinHeap();

	//-------------------------------------------------------
	// Name: MinHeap copy constructor
	// PreConditions: passed in heap must be valid
	// PostConditions: allocates memory for element storage, copies original
	// heap data to m_array, and sets number of elements accordingly, invokes
	// base class Heap copy constructor
	//---------------------------------------------------------
	MinHeap(const Heap<T, m_size>& origHeap);
	
	//-------------------------------------------------------
	// Name: isSwap
	// PreConditions: none
	// PostConditions: returns true if first and second T objects are swappable
	// Notes: overrides abstract base class method,
	// uses PinHit CompareTo function, used to compare values of two elements in the heap.
	// Utilized in PercolateUp(...) and PercolateDown(...). Differs by single comparison
	// operator '<' from the implementation in MaxHeap.
	//---------------------------------------------------------
	bool isSwap(const T& first, const T& second);
};

#include "MinHeap.cpp"

#endif