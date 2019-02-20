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

#include "board.h"

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