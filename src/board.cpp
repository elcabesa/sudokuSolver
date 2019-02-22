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
#include "iterators.h"

Board::Board() { std::fill(_squares.begin(), _squares.end(), VALUE_NONE);}

tValues Board::getSquareValue(const tSquares sn) const {
	assert(sn >= startSquare && sn <= squareNumber);
	return _squares[sn];
}

void Board::setSquareValue(const tSquares sn, const tValues v) {
	assert(sn >= startSquare && sn <= squareNumber);
	assert(v == VALUE_NONE || (v >= VALUE_1  && v  <= VALUE_9));
	_squares[sn] = v;
}

tValues Board::getSquareValue(const tRows r, const tFiles f) const {
	return getSquareValue(getSquare(r, f));
}
void Board::setSquareValue(const tRows r, const tFiles f, const tValues v) {
	setSquareValue(getSquare(r, f), v);
}

bool Board::_areEqualValues(const tValues i, const tValues j) {
	return ((i == j) && (i != VALUE_NONE));
}

bool Board::checkBoard() const {
	//print();
	bool duplicate = false;
	for (auto r: squaresIterator::row) {
		//std::cerr<<"---- check row "<< r + 1 <<std::endl;
		duplicate |= _checkForDuplicate(squaresIterator::rows[r]);
	}
	
	for (auto f: squaresIterator::file) {
		//std::cerr<<"---- check file "<< f + 1 <<std::endl;
		duplicate |= _checkForDuplicate(squaresIterator::files[f]);
	}
	
	for (auto b: squaresIterator::box) {
		//std::cerr<<"---- check box "<< b + 1 <<std::endl;
		duplicate |= _checkForDuplicate(squaresIterator::boxes[b]);
	}
	return !duplicate;
	
}

// return true duplicate are found, false otherwise
bool Board::_checkForDuplicate( std::vector<tSquares> in) const
{
	std::vector<tValues> res;
	//std::cerr<<"testing squares: ";
	for (const auto s: in) {
		//std::cerr<< getSquareValue(s) << ", ";
		res.push_back(getSquareValue(s));
	}
	//std::cerr<< std::endl;
	std::sort(res.begin(), res.end());

	auto it = std::unique(res.begin(), res.end(), _areEqualValues);
	if (res.end() == it) {
		//duplicate not found
		return false;
	} else {
		return true;
	}
}

void Board::print() const {
	std::cerr<<"BOARD"<<std::endl;
	
	for (auto r: squaresIterator::row) {
		for (auto f: squaresIterator::file) {
			auto v = getSquareValue(r, f);
			if (v == VALUE_NONE) { std::cerr<<"x"; }
			else { std::cerr << v; }
		}
		std::cerr<<std::endl;
	}
}

bool Board::contains(const std::vector<tSquares>& in, const tValues v) const {
	std::vector<tValues> res;

	for (const auto s: in) {
		res.push_back(getSquareValue(s));
	}
	
	return std::find(res.begin(), res.end(), v) != res.end();
}