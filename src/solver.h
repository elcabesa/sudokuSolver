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
#include <string>

#include "candidates.h"
#include "value.h"

class Board;

class Solver {
public:
	Solver(Board& b, bool verbose = true);
	bool solve();
private:
	std::vector<bool(Solver::*)()> _methods;
	bool _verbose;
	Board& _b;
	Candidates _cand;
	
	void _setSquareValue(const tSquares t, const tValues v);
	void _printInfo(std::string type, std::vector<tSquares> sqList, std::vector<tValues> vList ) const;
	bool _isSolved();
	template <class type>
	std::vector<type> _getListFromBitset(const unsigned int n, std::vector<type> vec) const;
	bool _containSolvedCell(std::vector<tSquares> vec) const;
	std::set<tValues> _createUnionOfValuesFromCell(std::vector<tSquares> sqList) const;
	std::set<tValues> _getComplementaryList(std::vector<tValues> vList) const;
	std::vector<tSquares> _getComplementaryList(std::vector<tSquares> sqList, std::vector<tSquares> refList) const;
	bool _removeCandidatesFromCells(const std::vector<tSquares> sqList, std::set<tValues> groupValues);
	template <class IT>
	bool _RemoveCandidateFrom(IT sqList, tValues v);


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

	template <class IT, class IT2>
	bool _findHiddenIn(IT it, IT2 it2);
	
	bool _findHiddenInRow();
	bool _findHiddenInFile();
	bool _findHiddenInBox();
	
	template <class IT, class IT2>
	bool _findPointingPairIn(IT it, IT2 it2);
	bool _findPointingPairInRow();
	bool _findPointingPairInFile();

	bool _findBoxLineForRow();
	bool _findBoxLineForFile();
	
	bool _findXWing1();
	bool _findXWing2();
	
	bool _findYWing();
};

#endif