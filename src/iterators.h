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

class squaresIterator {
public:
	static const std::array<tRows, rowNumber> row;
	static const std::array<tFiles, fileNumber> file;
	static const std::array<tBoxes, boxNumber> box;
	static const std::array<tValues, 9> value;
	
	static const std::array<std::vector<tSquares>, rowNumber> rows;
	static const std::array<std::vector<tSquares>, fileNumber> files;
	static const std::array<std::vector<tSquares>, boxNumber> boxes;
	
	static bool isInRow(const tRows r, const tSquares s);
	static bool isInFile(const tFiles f, const tSquares s);
	static bool isInBox(const tBoxes b, const tSquares s);
};

#endif
