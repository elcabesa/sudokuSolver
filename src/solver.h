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

#ifndef _SOLVER_H
#define _SOLVER_H

#include <set>

#include "Candidates.h"
#include "value.h"

class Board;

class Solver {
public:
	Solver(Board& b);
	void solve();
private:
	Board& _b;
	Candidates _cand;
	
	bool _findSingle();
	
	bool _findHiddenSingleInRow();
	bool _findHiddenSingleInFile();
	bool _findHiddenSingleInBox();
	
	template <class IT, class IT2>
	bool _findHiddenSingleIn(IT it, IT2 it2);
	
	
	template <class IT, class IT2>
	bool _findNakedIn(IT it, IT2 it2);
	
	bool _findNakedInRow();
	bool _findNakedInFile();
	bool _findNakedInBox();
	
	
	void _setSquareValue(const tSquares t, const tValues v);
	
	template <class type>
	std::vector<type> _getListFromBitset(const unsigned int n, std::vector<type> vec) const;
	
	bool _containSolvedCell(std::vector<tSquares> vec) const;
	
	std::set<tValues> _createUnionOfValuesFromCell(std::vector<tSquares> sqList) const;
	
	bool _removeCandidatesFromCell(const tSquares sq, std::set<tValues> groupValues);
	
	template <class IT, class IT2>
	bool _findHiddenIn(IT it, IT2 it2);
	
	bool _findHiddenInRow();
	bool _findHiddenInFile();
	bool _findHiddenInBox();
	
	template <class IT, class IT2>
	bool _findPointingPairIn(IT it, IT2 it2);
	
	bool _findPointingPairInRow();
	bool _findPointingPairInFile();
	
	
};

#endif