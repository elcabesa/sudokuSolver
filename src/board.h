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

#ifndef _BOARD_H
#define _BOARD_H

#include <algorithm>
#include <array>
#include <string>
#include <vector>

#include "tSquares.h"
#include "value.h"

class Board {
public:
	explicit Board();
	explicit Board(std::string input);
	tValues getSquareValue(const tSquares sn) const;
	void setSquareValue(const tSquares sn, const tValues v);
	tValues getSquareValue(const tRows r, const tFiles f) const;
	void setSquareValue(const tRows r, const tFiles f, const tValues v);
	
	bool checkBoard() const;
	
	bool contains(const std::vector<tSquares>& in, const tValues v) const;
	void print() const;
private:
	std::array<tValues, squareNumber> _squares;
	static bool _areEqualValues(const tValues i, const tValues j);
	bool _checkForDuplicate( std::vector<tSquares> in) const;
	void _clear();
	
};

#endif