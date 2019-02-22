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
#include "tSquares.h"

tSquares getSquare(const tRows r, const tFiles f) {
	assert(f >= FILE_1 && f <= FILE_9);
	assert(r >= ROW_A && r <= ROW_I);
	return static_cast<tSquares>(f + r * fileNumber);
}

tFiles getFile(const tSquares sq) {
	return static_cast<tFiles>(sq % fileNumber);
}

tRows getRow(const tSquares sq) {
	return static_cast<tRows>(sq / fileNumber);
}

tBoxes getBox(const tSquares sq) {
	return static_cast<tBoxes>((3 * (getRow(sq) / 3)) + (getFile(sq) / 3));
}

bool areOnTheSameFile(std::vector<tSquares> s) {
	if (s.empty()) {
		return false;
	}
	const auto ref = getFile(s[0]);
	for (auto sq: s) {
		if (getFile(sq) != ref) {
			return false;
		}
	}
	return true;
}
bool areOnTheSameRow(std::vector<tSquares> s) {
	if (s.empty()) {
		return false;
	}
	const auto ref = getRow(s[0]);
	for (auto sq: s) {
		if (getRow(sq) != ref) {
			return false;
		}
	}
	return true;
}
bool areOnTheSameBox(std::vector<tSquares> s) {
	if (s.empty()) {
		return false;
	}
	const auto ref = getBox(s[0]);
	for (auto sq: s) {
		if (getBox(sq) != ref) {
			return false;
		}
	}
	return true;
}