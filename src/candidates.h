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

#ifndef _CANDIDATES_H
#define _CANDIDATES_H


#include <array>
#include <vector>

#include "tSquares.h"
#include "value.h"

class Board;

class Candidates {
public:
	Candidates(const Board& b);
	void clear();
	void add(const tSquares sq, tValues v);
	bool remove(const tSquares sq, tValues v);
	const std::vector<tValues>& get(const tSquares sq) const;
	size_t getSize(const tSquares sq) const;
	void fillCandidates();
	void print() const;
	void print(const tSquares sq) const;
	bool contains(const tSquares sq, tValues v) const;
private:
	const Board& _b;
	std::array<std::vector<tValues>, squareNumber> _squares;
};

#endif
