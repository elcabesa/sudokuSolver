/*
	This file is part of SudokuSolver.

    SudokuSolver is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    SudokuSolver is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with SudokuSolver.  If not, see <http://www.gnu.org/licenses/>
*/

#include <bitset>
#include <cassert>
#include <iostream>

#include "board.h"
#include "candidates.h"
#include "iterators.h"
#include "solvingStrategy.h"


void solvingStrategy::_printInfo(std::string type, std::vector<tSquares> sqList, std::vector<tValues> vList ) const {
	if (_verbose) {
		std::cout<<"...FOUND "<<type<<" at ";
		for (auto & sq: sqList) {
			std::cout<< sq;
			if (&sq != &sqList.back()) {
				std::cout<<", ";
			}
		}
		std::cout<<" values: (";
		for (auto& v: vList) {
			std::cout<< v;
			if (&v != &vList.back()) {
				std::cout<<", ";
			}
		}
		std::cout<<")"<<std::endl;
	}
}

void solvingStrategy::_setSquareValue(const tSquares sq, const tValues v) {
	assert(sq < squareNumber && sq >= startSquare);
	assert(v >= VALUE_1 && v <= VALUE_9);
	_b.setSquareValue(sq, v);
	
	auto c = _cand.get(sq);
	
	for (auto ca: c) {
		_cand.remove(sq, ca);
	}
	
	for (auto s: squaresIterator::files[getFile(sq)]) {
		_cand.remove(s, v);
	}
	
	for (auto s: squaresIterator::rows[getRow(sq)]) {
		_cand.remove(s, v);
	}
	
	for (auto s: squaresIterator::boxes[getBox(sq)]) {
		_cand.remove(s, v);
	}
}

template <class type>
std::vector<type> solvingStrategy::_getListFromBitset(const unsigned int n, std::vector<type> vec) const {
	//convert in a list of index
	std::bitset<9> bs(n);
	//get list of squares
	std::vector<type> sqList;
			
	for (std::size_t idx = 0; idx < bs.size(); ++idx) {
		if (bs[idx] != 0) {
			sqList.push_back(vec[idx]);
		}
	}
	return sqList;
}

template std::vector<tSquares> solvingStrategy::_getListFromBitset<tSquares>(const unsigned int n, std::vector<tSquares> vec) const;
template std::vector<tValues> solvingStrategy::_getListFromBitset<tValues>(const unsigned int n, std::vector<tValues> vec) const;

bool solvingStrategy::_containSolvedCell(std::vector<tSquares> vec) const {
	bool containsSolvedCells = false;
	for (auto sq: vec) {
		if( _b.getSquareValue(sq) != VALUE_NONE) {containsSolvedCells = true;}
	}
	return containsSolvedCells;
}

std::set<tValues> solvingStrategy::_createUnionOfValuesFromCell(std::vector<tSquares> sqList) const {
	std::set<tValues> groupValues;
	for (auto sq: sqList) {
		auto& cand = _cand.get(sq);
		for (auto v: cand ) {
			groupValues.insert(v);
		}
	}
	return groupValues;
}

bool solvingStrategy::_removeCandidatesFromCells(const std::vector<tSquares> sqList, std::set<tValues> groupValues) {
	bool candidatesChanged = false;
	for (auto v: groupValues) {
		candidatesChanged |= _RemoveCandidateFrom(sqList, v);
	}
	return candidatesChanged;
}

template <class IT>
bool solvingStrategy::_RemoveCandidateFrom(IT sqList, tValues v) {
	bool modified = false;
	for (auto sq: sqList) { 
		auto x =  _cand.remove(sq, v);
		modified |= x;
		/*if(x)std::cout<<"removed "<<C<<" from "<<sq<<std::endl;*/
	}
	return modified;
}

template bool solvingStrategy::_RemoveCandidateFrom<std::vector<tSquares>>(std::vector<tSquares> sqList, tValues v);
	
std::set<tValues> solvingStrategy::_getComplementaryListOfValues(std::vector<tValues> vList) const {
	std::set<tValues> complementaryValueList;
	for(auto v: squaresIterator::value) {
		if (std::find(vList.begin(), vList.end(), v) == vList.end()) {
			complementaryValueList.insert(v);
		}
	}
	return complementaryValueList;
}

std::vector<tSquares> solvingStrategy::_getComplementaryList(std::vector<tSquares> sqList, std::vector<tSquares> refList) const {
	std::vector<tSquares> complSquares;
	for (auto sq: refList) { 
		if (std::find(sqList.begin(), sqList.end(), sq) == sqList.end()) {
			complSquares.push_back(sq);
		}
	}
	return complSquares;
}