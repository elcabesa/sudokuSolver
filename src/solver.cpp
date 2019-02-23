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

#include <cassert>
#include <iostream>

#include "board.h"
#include "candidates.h"
#include "iterators.h"
#include "solver.h"

Solver::Solver(Board& b): _b(b), _cand(b){}

void Solver::solve() {
	_cand.fillCandidates();
	_b.print();
	do {
		
		_cand.print();
		std::cout<<"Performing STEP..."<<std::endl;
		if (_findSingle()) { _b.print(); continue; }
		if (_findHiddenSingleInRow()) { _b.print(); continue; }
		if (_findHiddenSingleInFile()) { _b.print(); continue; }
		if (_findHiddenSingleInBox()) { _b.print(); continue; }
		if (_findNakedPairInRow()) { _b.print(); continue; }
		if (_findNakedPairInFile()) { _b.print(); continue; }
		if (_findNakedPairInBox()) { _b.print(); continue; }
		
		std::cout<<"Done"<<std::endl;
		break;
	}
	
	while (std::cin.ignore());
	
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
	std::cout<<"Searching for solved cells..."<<std::endl;
	for (auto sq: squaresIterator::squares) {
		if (_cand.getSize(sq) == 1) {
			auto v = _cand.get(sq)[0];
			std::cout<<"...Found at "<< sq <<" value "<< v << std::endl;
			_setSquareValue(sq, v);
			return true;
		}
	}
	return false;
}

bool Solver::_findHiddenSingleInRow() {
	std::cout<<"Searching for hidden single in row..."<<std::endl;
	for (const auto r: squaresIterator::row) {
		for (const auto v: squaresIterator::value) {
			unsigned int count = 0;
			tSquares singleSq = squareNumber;
			for( const auto sq: squaresIterator::rows[r]) {
				if (_cand.contains(sq, v)) {
					++count;
					singleSq = sq;
				}
			}
			if (count == 1) {
				std::cout<<"...Found at "<< singleSq <<" value "<< v << std::endl;
				_setSquareValue(singleSq, v);
				return true;
			}				
		}
	}
	return false;
}

bool Solver::_findHiddenSingleInFile() {
	std::cout<<"Searching for hidden single in file..."<<std::endl;
	for (const auto f: squaresIterator::file) {
		for (const auto v: squaresIterator::value) {
			unsigned int count = 0;
			tSquares singleSq = squareNumber;
			for( const auto sq: squaresIterator::files[f]) {
				if (_cand.contains(sq, v)) {
					++count;
					singleSq = sq;
				}
			}
			if (count == 1) {
				std::cout<<"...Found at "<< singleSq <<" value "<< v << std::endl;
				_setSquareValue(singleSq, v);
				return true;
			}				
		}
	}
	return false;
}

bool Solver::_findHiddenSingleInBox() {
	std::cout<<"Searching for hidden single in box..."<<std::endl;
	for (const auto b: squaresIterator::box) {
		for (const auto v: squaresIterator::value) {
			unsigned int count = 0;
			tSquares singleSq = squareNumber;
			for( const auto sq: squaresIterator::boxes[b]) {
				if (_cand.contains(sq, v)) {
					++count;
					singleSq = sq;
				}
			}
			if (count == 1) {
				std::cout<<"...Found at "<< singleSq <<" value "<< v << std::endl;
				_setSquareValue(singleSq, v);
				return true;	
			}				
		}
	}
	return false;
}

bool Solver::_findNakedPairInRow() {
	for (const auto r: squaresIterator::row) {
		for( const auto sq1: squaresIterator::rows[r]) {
			if (_cand.getSize(sq1) == 2) {
				std::cout<<".found a pair at "<< sq1<<":";
				_cand.print(sq1);
				for( const auto sq2: squaresIterator::rows[r]) {
					if( sq2 != sq1 ) {
						if (_cand.getSize(sq2) == 2) {
							std::cout<<"..check candidate at "<< sq2 <<":";
							_cand.print(sq2);
							if (_cand.get(sq1) == _cand.get(sq2)) {
								std::cout<<"...FOUND naked pair at "<< sq1 <<", "<< sq2 <<std::endl;
								
								auto pair = _cand.get(sq1);
								// removed candidates from other squares in row
								bool candidatesChanged = false;
								for( const auto sq3: squaresIterator::rows[r]) {
									if((sq3 != sq1) && (sq3 != sq2)) {
										//remove candidates from other squares in row
										for (auto v: pair) {
											candidatesChanged |= _cand.remove(sq3, v);
										}
									}
								}
								if(candidatesChanged) {
									return true;
								}
							}
						}
					}
				}
			}
		}
	}
	return false;
}

bool Solver::_findNakedPairInFile() {
	for (const auto f: squaresIterator::file) {
		for( const auto sq1: squaresIterator::files[f]) {
			if (_cand.getSize(sq1) == 2) {
				std::cout<<".found a pair at "<< sq1<<":";
				_cand.print(sq1);
				for( const auto sq2: squaresIterator::files[f]) {
					if( sq2 != sq1 ) {
						if (_cand.getSize(sq2) == 2) {
							std::cout<<"..check candidate at "<< sq2 <<":";
							_cand.print(sq2);
							if (_cand.get(sq1) == _cand.get(sq2)) {
								std::cout<<"...FOUND naked pair at "<< sq1 <<", "<< sq2 <<std::endl;
								
								auto pair = _cand.get(sq1);
								// removed candidates from other squares in file
								bool candidatesChanged = false;
								for( const auto sq3: squaresIterator::files[f]) {
									if((sq3 != sq1) && (sq3 != sq2)) {
										//remove candidates from other squares in row
										for (auto v: pair) {
											candidatesChanged |= _cand.remove(sq3, v);
										}
									}
								}
								if(candidatesChanged) {
									return true;
								}
							}
						}
					}
				}
			}
		}
	}
	return false;
}

bool Solver::_findNakedPairInBox() {
	for (const auto b: squaresIterator::box) {
		for( const auto sq1: squaresIterator::boxes[b]) {
			if (_cand.getSize(sq1) == 2) {
				std::cout<<".found a pair at "<< sq1<<":";
				_cand.print(sq1);
				for( const auto sq2: squaresIterator::boxes[b]) {
					if( sq2 != sq1 ) {
						if (_cand.getSize(sq2) == 2) {
							std::cout<<"..check candidate at "<< sq2 <<":";
							_cand.print(sq2);
							if (_cand.get(sq1) == _cand.get(sq2)) {
								std::cout<<"...FOUND naked pair at "<< sq1 <<", "<< sq2 <<std::endl;
								
								auto pair = _cand.get(sq1);
								// removed candidates from other squares in box
								bool candidatesChanged = false;
								for( const auto sq3: squaresIterator::boxes[b]) {
									if((sq3 != sq1) && (sq3 != sq2)) {
										//remove candidates from other squares in row
										for (auto v: pair) {
											candidatesChanged |= _cand.remove(sq3, v);
										}
									}
								}
								if(candidatesChanged) {
									return true;
								}
							}
						}
					}
				}
			}
		}
	}
	return false;
}