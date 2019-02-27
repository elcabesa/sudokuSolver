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
#include "solver.h"

Solver::Solver(Board& b): _b(b), _cand(b){}

void Solver::solve() {
	_cand.fillCandidates();
	_cand.print();
	_b.print();
	do {
		
		_cand.print();
		//std::cout<<"Performing STEP..."<<std::endl;
		if (_findSingle()) { /*_b.print();*/ continue; }
		if (_findHiddenSingleInRow()) { /*_b.print();*/ continue; }
		if (_findHiddenSingleInFile()) { /*_b.print();*/ continue; }
		if (_findHiddenSingleInBox()) { /*_b.print();*/ continue; }
		if (_findNakedInRow()) { /*_b.print();*/ continue; }
		if (_findNakedInFile()) { /*_b.print();*/ continue; }
		if (_findNakedInBox()) { /*_b.print();*/ continue; }
		if (_findHiddenInRow()) { /*_b.print();*/ continue; }
		if (_findHiddenInFile()) { /*_b.print();*/ continue; }
		if (_findHiddenInBox()) { /*_b.print();*/ continue; }
		
		std::cout<<"Done"<<std::endl;
		break;
	}
	while (std::cin.ignore());
	_b.print();
	
}

void Solver::_setSquareValue(const tSquares sq, const tValues v) {
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

bool Solver::_findSingle() {
	//std::cout<<"Searching for solved cells..."<<std::endl;
	for (auto sq: squaresIterator::squares) {
		if (_cand.getSize(sq) == 1) {
			auto v = _cand.get(sq)[0];
			std::cout<<"...Found single at "<< sq <<" value "<< v << std::endl;
			_setSquareValue(sq, v);
			return true;
		}
	}
	return false;
}

template <class IT, class IT2>
bool Solver::_findHiddenSingleIn(IT it, IT2 it2) {
	
	for (const auto r: it) {
		for (const auto v: squaresIterator::value) {
			unsigned int count = 0;
			tSquares singleSq = squareNumber;
			for( const auto sq: it2[r]) {
				if (_cand.contains(sq, v)) {
					++count;
					singleSq = sq;
				}
			}
			if (count == 1) {
				std::cout<<"...Found hidden single at "<< singleSq <<" value "<< v << std::endl;
				_setSquareValue(singleSq, v);
				return true;
			}				
		}
	}
	return false;
}

bool Solver::_findHiddenSingleInRow() {
	//std::cout<<"Searching for hidden single in rows"<<std::endl;
	return _findHiddenSingleIn<std::array<tRows, rowNumber>, std::array<std::vector<tSquares>, rowNumber>>(squaresIterator::row, squaresIterator::rows);
}

bool Solver::_findHiddenSingleInFile() {
	//std::cout<<"Searching for hidden single in files"<<std::endl;
	return _findHiddenSingleIn<std::array<tFiles, fileNumber>, std::array<std::vector<tSquares>, fileNumber>>(squaresIterator::file, squaresIterator::files);
}

bool Solver::_findHiddenSingleInBox() {
	//std::cout<<"Searching for hidden single boxes"<<std::endl;
	return _findHiddenSingleIn<std::array<tBoxes, boxNumber>, std::array<std::vector<tSquares>, boxNumber>>(squaresIterator::box, squaresIterator::boxes);
}

template <class type>
std::vector<type> Solver::_getListFromBitset(const unsigned int n, std::vector<type> vec) const {
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

bool Solver::_containSolvedCell(std::vector<tSquares> vec) const {
	bool containsSolvedCells = false;
	for (auto sq: vec) {
		if( _b.getSquareValue(sq) != VALUE_NONE) {containsSolvedCells = true;}
	}
	return containsSolvedCells;
}

std::set<tValues> Solver::_createUnionOfValuesFromCell(std::vector<tSquares> sqList) const {
	std::set<tValues> groupValues;
	for (auto sq: sqList) {
		auto& cand = _cand.get(sq);
		for (auto v: cand ) {
			groupValues.insert(v);
		}
	}
	return groupValues;
}

bool Solver::_removeCandidatesFromCell(const tSquares sq, std::set<tValues> groupValues) {
	bool candidatesChanged = false;
	for (auto v: groupValues) {
		candidatesChanged |= _cand.remove(sq, v);
	}
	return candidatesChanged;
}

template <class IT, class IT2>
bool Solver::_findNakedIn(IT it, IT2 it2) {
	
	for (const auto b: it) {
		
		// for all combiantion of 9 squares
		for (unsigned int n = 0; n < 512; ++n) {
			
			//convert bitset to vector of squares
			auto sqList = _getListFromBitset<tSquares>(n, it2[b]);
			
			//check that the combination doesn't contain solved cells
			if (!_containSolvedCell(sqList)) {
				
				// for the list of cells create the union of values
				auto groupValues = _createUnionOfValuesFromCell(sqList);
				
				// if the number of different values in the group is equal to thee number of squares in the bitset we have found a nake set
				if (sqList.size() == groupValues.size()) {
					// found a nake group. let's try so simplify
					
					bool candidatesChanged = false;
					
					// for all the squares outside sqList
					for ( const auto sq: it2[b]) {
						if (std::find(sqList.begin(), sqList.end(), sq) == sqList.end()) {
							candidatesChanged |= _removeCandidatesFromCell(sq, groupValues);
						}
					}
					if(candidatesChanged) {
						std::cout<<"...FOUND naked group at ";
						for (auto sq:sqList) {
							std::cout<< sq <<", ";
						}
						std::cout<<std::endl;
						std::cout<<"values ";
						for (auto v: groupValues) {
							std::cout<< v <<", ";
						}
						std::cout<<std::endl;
						return true;
					}
				}
			}	
		}
	}
	return false;
}

bool Solver::_findNakedInRow() {
	//std::cout<<"Searching for naked in rows"<<std::endl;
	return _findNakedIn<std::array<tRows, rowNumber>, std::array<std::vector<tSquares>, rowNumber>>(squaresIterator::row, squaresIterator::rows);
}

bool Solver::_findNakedInFile() {
	//std::cout<<"Searching for naked in files"<<std::endl;
	return _findNakedIn<std::array<tFiles, fileNumber>, std::array<std::vector<tSquares>, fileNumber>>(squaresIterator::file, squaresIterator::files);
}

bool Solver::_findNakedInBox() {
	//std::cout<<"Searching for naked in boxes"<<std::endl;
	return _findNakedIn<std::array<tBoxes, boxNumber>, std::array<std::vector<tSquares>, boxNumber>>(squaresIterator::box, squaresIterator::boxes);
}


template <class IT, class IT2>
bool Solver::_findHiddenIn(IT it, IT2 it2) {
	
	// for all the units
	for (const auto b: it) {
		
		// for all combiantion of 9 values
		for (unsigned int n = 0; n < 512; ++n) {
			
			//convert bitset to vector of values
			std::vector<tValues> temp(squaresIterator::value.begin(), squaresIterator::value.end());
			auto valueList = _getListFromBitset<tValues>(n, temp);
			
			std::vector<tSquares> sqList;
			
			//get squareList not solved and non containing any of the values in candidates
			std::set<tValues> foundValues;
			for (auto sq: it2[b]) {
				auto cand = _cand.get(sq);
				bool contain = false;
				for (auto v: valueList) {
					if (std::find(cand.begin(),cand.end(),v) != cand.end()) {
						contain = true;
						foundValues.insert(v);
					}
				}
				if (contain) {
					sqList.push_back(sq);
				}
			}
				
			if (sqList.size() == valueList.size() && sqList.size() != 0 && foundValues.size() == valueList.size()) {
				// found a hidden group. let's try so simplify
				bool modified = false;
				for (auto sq: sqList) {
					for(auto v: squaresIterator::value) {
						if (std::find(valueList.begin(), valueList.end(), v) == valueList.end()) {
							// todo manage cand remo
							modified |= _cand.remove(sq, v);
						}
					}
				}
				if (modified) {
					std::cout<<"...FOUND hidden group at ";
					for (auto sq: sqList) {
						std::cout<< sq <<", ";
					}
					std::cout<<std::endl;
					std::cout<<"values ";
					for (auto v: valueList) {
						std::cout<< v <<", ";
					}
					std::cout<<std::endl;
					return true;
				}
				
			}
		}
	}
	return false;
}

bool Solver::_findHiddenInRow() {
	std::cout<<"Searching for hidden in rows"<<std::endl;
	return _findHiddenIn<std::array<tRows, rowNumber>, std::array<std::vector<tSquares>, rowNumber>>(squaresIterator::row, squaresIterator::rows);
}

bool Solver::_findHiddenInFile() {
	std::cout<<"Searching for hidden in files"<<std::endl;
	return _findHiddenIn<std::array<tFiles, fileNumber>, std::array<std::vector<tSquares>, fileNumber>>(squaresIterator::file, squaresIterator::files);
}

bool Solver::_findHiddenInBox() {
	std::cout<<"Searching for hidden in boxes"<<std::endl;
	return _findHiddenIn<std::array<tBoxes, boxNumber>, std::array<std::vector<tSquares>, boxNumber>>(squaresIterator::box, squaresIterator::boxes);
}