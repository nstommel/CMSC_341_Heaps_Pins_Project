
/******************************************************************************
 * File:    PinHit.cpp
 * Project: CMSC 341 Project 4, Fall 2016
 * Author:  Nicholas Stommel
 * Date:    11/22/16
 * Section: 05
 * E-mail:  stommel1@gl.umbc.edu
 * 
 * Description: This is the source file containing the implementation of 
 * the basic PinHit class.
 * 
 ******************************************************************************/

#include "PinHit.h"

#include <iostream>
#include <iomanip>

// Default key is set to 'available'
PinHit::PinHit() : m_pin(EMPTY), m_hits(0)
{}

PinHit::PinHit(int key, int value) : m_pin(key), m_hits(value)
{}

void PinHit::SetKey(int pin) {
	m_pin = pin;
}

int PinHit::GetKey() const {
	return m_pin;
}

int PinHit::GetValue() const {
	return m_hits;
}

void PinHit::IncrementHits() {
	++m_hits;
}

int PinHit::CompareTo(const PinHit& other) const {
	return m_hits - other.m_hits;
}

bool PinHit::operator==(const PinHit& other) {
	return m_pin == other.m_pin;
}

std::ostream& operator<<(std::ostream& os, const PinHit& ph) {
	
	os << "[Pin: ";
	if(ph.GetKey() == PinHit::EMPTY) {
		// If pin wasn't in file, indicate the number is irrelevant. 
		os << "N/A ";
	} else {
		// Print pin in 4 digits with leading zeroes
		os << std::setw(4) << std::setfill('0') << ph.GetKey();
	}
	os << " Hits: ";
	// Print hits in 4 digits with leading zeroes
	os << std::setw(4) << std::setfill('0') << ph.GetValue();
	os << ']';

	return os;
}


