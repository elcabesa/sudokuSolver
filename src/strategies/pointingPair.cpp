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
#include "pointingPair.h"



template <class IT, class IT2>
bool pointingPairStrategy<IT, IT2>::solve() {
	// for all the units
	for (const auto b: _it) {
		// for all the values
		for(auto v: squaresIterator::value) {
			// find all the squares containing value as candidate
			std::vector<tSquares> squareList;
			for(auto sq: _it2[b]) {
				if (_cand.contains(sq, v)) {
					squareList.push_back(sq);
				}
			}
			
			if (auto b = areOnTheSameBox(squareList); b != BOX_NONE ) {
				// you can remove the value from all other squares in the box
				if (_RemoveCandidateFrom(_getComplementaryList(squareList, squaresIterator::boxes[b]), v)) {
					_printInfo("pointing pair", squareList, std::vector<tValues>(1, v));
					return true;
				}

			}
		}
	}
	return false;
}

template class pointingPairStrategy<rowIterator, rowsIterator>;
template class pointingPairStrategy<fileIterator, filesIterator>;