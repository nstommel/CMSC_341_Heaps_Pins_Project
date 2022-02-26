
/******************************************************************************
 * File:    MaxHeap.cpp
 * Project: CMSC 341 Project 4, Fall 2016
 * Author:  Nicholas Stommel
 * Date:    11/22/16
 * Section: 05
 * E-mail:  stommel1@gl.umbc.edu
 * 
 * Description: This is the source file containing the implementation of 
 * the templated derived class MaxHeap.
 * 
 ******************************************************************************/

#ifndef MAXVALUEHEAP_CPP_
#define MAXVALUEHEAP_CPP_

#include "MaxHeap.h"

template<class T, int m_size>
MaxHeap<T, m_size>::MaxHeap() : Heap<T, m_size>()
{}

template<class T, int m_size>
MaxHeap<T, m_size>::MaxHeap(const Heap<T, m_size>& origHeap) : Heap<T, m_size>(origHeap)
{}

template<class T, int m_size>
bool MaxHeap<T, m_size>::isSwap(const T& first, const T& second) {
	return (first.CompareTo(second) > 0) ? true : false;
}

#endif