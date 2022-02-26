
/******************************************************************************
 * File:    MinHeap.cpp
 * Project: CMSC 341 Project 4, Fall 2016
 * Author:  Nicholas Stommel
 * Date:    11/22/16
 * Section: 05
 * E-mail:  stommel1@gl.umbc.edu
 * 
 * Description: This is the source file containing the implementation of 
 * the templated derived class MinHeap.
 * 
 ******************************************************************************/

#ifndef MINVALUEHEAP_CPP_
#define MINVALUEHEAP_CPP_

#include "MinHeap.h"

template<class T, int m_size>
MinHeap<T, m_size>::MinHeap() : Heap<T, m_size>()
{}

template<class T, int m_size>
MinHeap<T, m_size>::MinHeap(const Heap<T, m_size>& origHeap) : Heap<T, m_size>(origHeap)
{}

template<class T, int m_size>
bool MinHeap<T, m_size>::isSwap(const T& first, const T& second) {
	return (first.CompareTo(second) < 0) ? true : false;
}

#endif