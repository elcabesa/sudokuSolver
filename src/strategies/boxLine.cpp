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

#include "board.h"
#include "candidates.h"
#include "iterators.h"
#include "boxLine.h"



bool boxLineForRowStrategy::solve() {
	// for all boxes
	for (const auto b: squaresIterator::box) {
		// for all the values
		for(auto v: squaresIterator::value) {
			// find all the squares containing value as candidate
			std::vector<tSquares> squareList;
			for(auto sq: squaresIterator::boxes[b]) {
				if (_cand.contains(sq, v)) {
					squareList.push_back(sq);
				}
			}
			
			if (auto b = areOnTheSameRow(squareList); b != ROW_NONE ) {
				// you can remove the value from all other squares in the row
				if (_RemoveCandidateFrom(_getComplementaryList(squareList, squaresIterator::rows[b]), v)) {
					_printInfo("box line reduction", squareList, std::vector<tValues>(1, v));
					return true;
				}
			}
		}
	}
	return false;
}




bool boxLineForLineStrategy::solve() {
	// for all boxes
	for (const auto b: squaresIterator::box) {
		// for all the values
		for(auto v: squaresIterator::value) {
			// find all the squares containing value as candidate
			std::vector<tSquares> squareList;
			for(auto sq: squaresIterator::boxes[b]) {
				if (_cand.contains(sq, v)) {
					squareList.push_back(sq);
				}
			}
			
			if (auto b = areOnTheSameFile(squareList); b != FILE_NONE ) {
				// you can remove the value from all other squares in the file
				if (_RemoveCandidateFrom(_getComplementaryList(squareList, squaresIterator::files[b]), v)) {
					_printInfo("box line reduction", squareList, std::vector<tValues>(1, v));
					return true;
				}
			}
		}
	}
	return false;
}