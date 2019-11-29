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
#include "hiddenSingle.h"

template <class IT, class IT2>
bool hiddenSingleStrategy<IT, IT2>::solve() {
	//std::cout<<"Searching for hidden single in ????"<<std::endl;
	for (const auto r: _it) {
		for (const auto v: squaresIterator::value) {
			unsigned int count = 0;
			tSquares singleSq = squareNumber;
			for( const auto sq: _it2[r]) {
				if (_cand.contains(sq, v)) {
					++count;
					singleSq = sq;
				}
			}
			if (count == 1) {
				_printInfo("hidden single", std::vector<tSquares>(1, singleSq), std::vector<tValues>(1, v));
				_setSquareValue(singleSq, v);
				return true;
			}				
		}
	}
	return false;
}

template class hiddenSingleStrategy<rowIterator, rowsIterator>;
template class hiddenSingleStrategy<fileIterator, std::array<std::vector<tSquares>, fileNumber>>;
template class hiddenSingleStrategy<boxIterator, std::array<std::vector<tSquares>, boxNumber>>;