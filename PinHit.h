
/******************************************************************************
 * File:    PinHit.h
 * Project: CMSC 341 Project 4, Fall 2016
 * Author:  Nicholas Stommel
 * Date:    11/22/16
 * Section: 05
 * E-mail:  stommel1@gl.umbc.edu
 * 
 * Description: This is the header file containing the declaration of 
 * the basic PinHit class. PinHits have two attributes: the key m_pin and the
 * value m_hits. An overloaded insertion operator is created to conveniently print
 * out PinHit objects, and two constants are created. EMPTY represents a pin that
 * has not been found in the file, and MAX_PINS is the total number of possible pins.
 * PinHits are heap-ordered by value (m_hits) in a heap object.
 * 
 ******************************************************************************/

#ifndef PINHIT_H_
#define PINHIT_H_

#include <iostream>

class PinHit {
	
	public:
		
		//-------------------------------------------------------
		// Name: PinHit default constructor
		// PreConditions: none
		// PostConditions: sets key m_pin to default 'empty' -1,
		// sets value m_hits to 0
		//---------------------------------------------------------
		PinHit();
		
		//-------------------------------------------------------
		// Name: PinHit non-default constructor
		// PreConditions: none
		// PostConditions: sets key and value based on input arguments
		//---------------------------------------------------------
		PinHit(int key, int value);
		
		//-------------------------------------------------------
		// Name: SetKey
		// PreConditions: none
		// PostConditions: sets key m_pin to pin value, 
		// Notes: used in Driver.cpp ReadPins function
		//---------------------------------------------------------
		void SetKey(int pin);
		
		//-------------------------------------------------------
		// Name: GetKey
		// PreConditions: none
		// PostConditions: returns copy of m_pin key
		//---------------------------------------------------------
		int GetKey() const;
		
		//-------------------------------------------------------
		// Name: GetValue
		// PreConditions: none
		// PostConditions: returns copy of m_hits value
		//---------------------------------------------------------
		int GetValue() const;
		
		//-------------------------------------------------------
		// Name: IncrementHits
		// PreConditions: none
		// PostConditions: increments m_hits value by one, 
		// Notes: used in Driver.cpp ReadPins function
		//---------------------------------------------------------
		void IncrementHits();
		
		//-------------------------------------------------------
		// Name: CompareTo
		// PreConditions: none
		// PostConditions: returns the difference between the PinHit's
		// value m_hits and the other PinHit's value m_hits.
		// Notes: used in Heap isSwap method
		//---------------------------------------------------------
		int CompareTo(const PinHit& other) const;
		
		//-------------------------------------------------------
		// Name: equality comparison operator
		// PreConditions: none
		// PostConditions: returns true if m_pin key is equal to passed in
		// other m_pin key, false otherwise
		// Notes: used in Heap Find method
		//---------------------------------------------------------
		bool operator==(const PinHit& other);

		//-------------------------------------------------------
		// Name: PinHit overloaded insertion operator
		// PreConditions: none
		// PostConditions: prints out a PinHit object in the following format:
		// [Pin: ---- Hits: ----]
		//---------------------------------------------------------
		friend std::ostream& operator << (std::ostream& os, const PinHit& ph);
		
		
		static const int EMPTY = -1;
		
		// Set constant int max pins
		static const int MAX_PINS = 10000;
		
	private:

		int m_pin, m_hits;
};

#endif /* PinHit_H_ */