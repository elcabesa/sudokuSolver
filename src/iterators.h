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

#ifndef _ITERATORS_H
#define _ITERATORS_H

#include <array>
#include <vector>

#include "tSquares.h"
#include "value.h"

using rowIterator = std::array<tRows, rowNumber>;
using fileIterator = std::array<tFiles, fileNumber>;
using boxIterator = std::array<tBoxes, boxNumber>;
using valueIterator = std::array<tValues, 9>;
using squareIterator = std::array<tSquares, 81>;

using rowsIterator = std::array<std::vector<tSquares>, rowNumber>;
using filesIterator = std::array<std::vector<tSquares>, fileNumber>;
using boxesIterator = std::array<std::vector<tSquares>, boxNumber>;

class squaresIterator {
public:

	
	static const rowIterator row;
	static const fileIterator file;
	static const boxIterator box;
	static const valueIterator value;
	static const squareIterator squares;
	
	static const rowsIterator rows;
	static const filesIterator files;
	static const boxesIterator boxes;
	
	static bool isInRow(const tRows r, const tSquares s);
	static bool isInFile(const tFiles f, const tSquares s);
	static bool isInBox(const tBoxes b, const tSquares s);
};

#endif
