
/******************************************************************************
 * File:    MaxHeap.h
 * Project: CMSC 341 Project 4, Fall 2016
 * Author:  Nicholas Stommel
 * Date:    11/22/16
 * Section: 05
 * E-mail:  stommel1@gl.umbc.edu
 * 
 * Description: This is the header file containing the declaration of 
 * the templated derived class MaxHeap. This class is very minimally extended,
 * only the isSwap function is changed by a single comparison operator. In a 
 * MaxHeap, every child node is less than or equal to its parent node, and every
 * parent node is greater than or equal to its children.
 * 
 ******************************************************************************/

#ifndef MAXVALUEHEAP_H_
#define MAXVALUEHEAP_H_

#include "Heap.h"

template<class T, int m_size>
class MaxHeap : public Heap<T, m_size> {

public:
	
	//-------------------------------------------------------
	// Name: MaxHeap default constructor
	// PreConditions: none
	// PostConditions: allocates memory for element storage and sets 
	// number of elements to 0 by invoking base class Heap constructor
	//---------------------------------------------------------
	MaxHeap();
	
	//-------------------------------------------------------
	// Name: MaxHeap copy constructor
	// PreConditions: passed in heap must be valid
	// PostConditions: allocates memory for element storage, copies original
	// heap data to m_array, and sets number of elements accordingly, invokes
	// base class Heap copy constructor
	//---------------------------------------------------------
	MaxHeap(const Heap<T, m_size>& origHeap);

	//-------------------------------------------------------
	// Name: isSwap
	// PreConditions: none
	// PostConditions: returns true if first and second T objects are swappable
	// Notes: overrides abstract base class method,
	// uses PinHit CompareTo function, used to compare values of two elements in the heap.
	// Utilized in PercolateUp(...) and PercolateDown(...). Differs by single comparison
	// operator '>' from the implementation in MinHeap.
	//---------------------------------------------------------
	bool isSwap(const T& first, const T& second);
};

#include "MaxHeap.cpp"

#endif