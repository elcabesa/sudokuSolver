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

class squaresIterator {
public:
	static const std::array<rows, rowNumber> row;
	static const std::array<files, fileNumber> file;
	static const std::array<boxes, boxNumber> box;
	
	static const std::array<std::vector<squares>, rowNumber> rows;
	static const std::array<std::vector<squares>, fileNumber> files;
	static const std::array<std::vector<squares>, boxNumber> boxes;
};

#endif
