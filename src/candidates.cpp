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


#include "board.h"
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
	assert(sq < squareNumber && sq >= startSquare);
	assert(v >= VALUE_1 && v <= VALUE_9);
	
	if( !contains(sq, v) ) {
		_squares[sq].push_back(v);
	} else {
		std::cout<<"warning candidate already contain "<<v<<std::endl;
	}
}

bool Candidates::remove(const tSquares sq, tValues v) {
	assert(sq < squareNumber && sq >= startSquare);
	assert(v >= VALUE_1 && v <= VALUE_9);
	
	auto & s = _squares[sq];
	
	auto it = std::find(s.begin(), s.end(), v);
	if ( it != s.end()) {
		_squares[sq].erase(it);
		return true;
	}/* else {
		std::cout<<"warning candidate oesn't contain "<<v<<std::endl;
	}*/
	return false;
}

const std::vector<tValues>& Candidates::get(const tSquares sq) const {
	assert(sq < squareNumber && sq >= startSquare);
	return _squares[sq];
}

void Candidates::fillCandidates() {
	for (auto r: squaresIterator::row) {
		for (auto f: squaresIterator::file) { 
			auto sq = getSquare(r, f);
			for (auto v: squaresIterator::value) {
				if( _b.getSquareValue(sq) == VALUE_NONE &&
					!_b.contains(squaresIterator::rows[r], v) &&
					!_b.contains(squaresIterator::files[f], v) &&
					!_b.contains(squaresIterator::boxes[getBox(sq)], v)
				) {
					add(sq, v);
				}
			}	
		}
	}
}

void Candidates::print() const {
	std::cout<<"INITIAL CANDIDITATES"<<std::endl;
	
	for (auto sq: squaresIterator::squares) {
		if( sq <=9 )
		if( _squares[sq].size() != 0 )
		{
			std::cout<<"candidates for square "<< (sq + 1)<<":";
			print(sq);
		}
	}
}

void Candidates::print(const tSquares sq) const {
	
	for( auto v: _squares[sq] ) {
		std::cout<<(v + 1)<<", ";
	}
	std::cout<<std::endl;
}

size_t Candidates::getSize(const tSquares sq) const {
	return get(sq).size();
}

bool Candidates::contains(const tSquares sq, tValues v) const {
	const auto& values = get(sq);
	return std::find(values.begin(), values.end(), v) != values.end();	
}