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
#include "hidden.h"

template <class IT, class IT2>
bool hiddenStrategy<IT, IT2>::solve() {
	// for all the units
	for (const auto b: _it) {
		
		// for all combiantion of 9 values
		for (unsigned int n = 0; n < 512; ++n) {
			
			//convert bitset to vector of values
			std::vector<tValues> temp(squaresIterator::value.begin(), squaresIterator::value.end());
			auto valueList = _getListFromBitset<tValues>(n, temp);
			
			std::vector<tSquares> sqList;
			
			//get squareList not solved and non containing any of the values in candidates
			std::set<tValues> foundValues;
			for (auto sq: _it2[b]) {
				auto cand = _cand.get(sq);
				bool contain = false;
				for (auto v: valueList) {
					if (std::find(cand.begin(),cand.end(),v) != cand.end()) {
						contain = true;
						foundValues.insert(v);
					}
				}
				if (contain) {
					sqList.push_back(sq);
				}
			}
				
			if (sqList.size() == valueList.size() && sqList.size() != 0 && foundValues.size() == valueList.size()) {
				// found a hidden group. let's try so simplify
				// remove values from complementary value list
				if (_removeCandidatesFromCells(sqList, _getComplementaryListOfValues(valueList))) {
					_printInfo("hidden group", sqList, valueList);
					return true;
				}
			}
		}
	}
	return false;
}

template class hiddenStrategy<rowIterator, rowsIterator>;
template class hiddenStrategy<fileIterator, filesIterator>;
template class hiddenStrategy<boxIterator, boxesIterator>;