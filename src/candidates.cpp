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

#include <algorithm>
#include <cassert>
#include <iostream>


#include "candidates.h"
#include "iterators.h"

Candidates::Candidates(const Board& b): _b(b) {
	clear();
}

void Candidates::clear() {
	for (auto s: _squares) {
		s.clear();
	}
}

void Candidates::add(const tSquares sq, tValues v) {
	assert(sq < squareNumber && sq > startSquare);
	assert(v >= VALUE_1 && v <= VALUE_9);
	
	auto & s = _squares[sq];
	
	if (std::find(s.begin(), s.end(), v) == s.end()) {
		_squares[sq].push_back(v);
	} else {
		std::cout<<"warning candidate already contain "<<v<<std::endl;
	}
}

void Candidates::remove(const tSquares sq, tValues v) {
	assert(sq < squareNumber && sq > startSquare);
	assert(v >= VALUE_1 && v <= VALUE_9);
	
	auto & s = _squares[sq];
	
	auto it = std::find(s.begin(), s.end(), v);
	if ( it != s.end()) {
		_squares[sq].erase(it);
	} else {
		std::cout<<"warning candidate oesn't contain "<<v<<std::endl;
	}
}

const std::vector<tValues>& Candidates::getCandidates(const tSquares sq) const {
	assert(sq < squareNumber && sq > startSquare);
	assert(v >= VALUE_1 && v <= VALUE_9);
	
	return _squares[sq];
}