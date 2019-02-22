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
	_b.print();
	_cand.fillCandidates();
	
	do {
		_b.print();
		_cand.print();
		std::cout<<"Performing STEP..."<<std::endl;
		if (_findSingle()) continue;
		if (_findHiddenSingleInRow()) continue;
		if (_findHiddenSingleInFile()) continue;
		if (_findHiddenSingleInBox()) continue;
		
		std::cout<<"Done"<<std::endl;
		break;
	}
	while (std::cin.ignore());
	
}

void Solver::_setSquareValue(const tSquares sq, const tValues v) {
	assert(sq < squareNumber && sq > startSquare);
	assert(v >= VALUE_1 && v <= VALUE_9);
	_b.setSquareValue(sq, v);
	
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
	std::cout<<"Seraching for solved cells..."<<std::endl;
	for (auto sq: squaresIterator::squares) {
		if (_cand.getSize(sq) == 1) {
			auto v = _cand.get(sq)[0];
			std::cout<<"...Found at "<<(sq + 1)<<" value "<< (v + 1) << std::endl;
			_setSquareValue(sq, v);
			return true;
		}
	}
	return false;
}

bool Solver::_findHiddenSingleInRow() {
	std::cout<<"Seraching for hidden single in row..."<<std::endl;
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
				std::cout<<"...Found at "<<(singleSq + 1)<<" value "<< (v + 1) << std::endl;
				_setSquareValue(singleSq, v);
				return true;
			}				
		}
	}
	return false;
}

bool Solver::_findHiddenSingleInFile() {
	std::cout<<"Seraching for hidden single in file..."<<std::endl;
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
				std::cout<<"...Found at "<<(singleSq + 1)<<" value "<< (v + 1) << std::endl;
				_setSquareValue(singleSq, v);
				return true;
			}				
		}
	}
	return false;
}

bool Solver::_findHiddenSingleInBox() {
	std::cout<<"Seraching for hidden single in box..."<<std::endl;
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
				std::cout<<"...Found at "<<(singleSq + 1)<<" value "<< (v + 1) << std::endl;
				_setSquareValue(singleSq, v);
				return true;	
			}				
		}
	}
	return false;
}