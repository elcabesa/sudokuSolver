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
#include "naked.h"

template <class IT, class IT2>
bool nakedStrategy<IT, IT2>::solve() {
	for (const auto b: _it) {
		
		// for all combiantion of 9 squares
		for (unsigned int n = 0; n < 512; ++n) {
			
			//convert bitset to vector of squares
			auto sqList = _getListFromBitset<tSquares>(n, _it2[b]);
			
			//check that the combination doesn't contain solved cells
			if (!_containSolvedCell(sqList)) {
				
				// for the list of cells create the union of values
				auto groupValues = _createUnionOfValuesFromCell(sqList);
				
				// if the number of different values in the group is equal to thee number of squares in the bitset we have found a nake set
				if (sqList.size() == groupValues.size()) {
					// found a nake group. let's try so simplify
					
					// for all the squares outside sqList
					if (_removeCandidatesFromCells(_getComplementaryList(sqList, _it2[b]), groupValues)) {
						_printInfo("naked group", sqList, std::vector<tValues>(groupValues.begin(),groupValues.end()));
						return true;
					}
				}
			}	
		}
	}
	return false;
}

template class nakedStrategy<rowIterator, rowsIterator>;
template class nakedStrategy<fileIterator, filesIterator>;
template class nakedStrategy<boxIterator, boxesIterator>;