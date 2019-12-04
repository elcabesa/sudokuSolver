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

#ifndef _SOLVING_STRATEGY_H
#define _SOLVING_STRATEGY_H

#include <set>
#include <string>
#include <vector>

#include "tSquares.h"
#include "value.h"

class Board;
class Candidates;


class solvingStrategy {
public:
	solvingStrategy(const std::string& name,Board& b, Candidates& cand, bool verbose): _name(name), _b(b), _cand(cand), _verbose(verbose){};
	virtual ~solvingStrategy(){};
	virtual bool solve() = 0;
	const std::string& getName() const;
protected:
	const std::string _name;
	Board& _b;
	Candidates& _cand;
	bool _verbose;
	
	void _printInfo(std::string type, std::vector<tSquares> sqList, std::vector<tValues> vList ) const;
	
	void _setSquareValue(const tSquares sq, const tValues v);
	
	template <class type>
	std::vector<type> _getListFromBitset(const unsigned int n, std::vector<type> vec) const;
	
	bool _containSolvedCell(std::vector<tSquares> vec) const;
	
	std::set<tValues> _createUnionOfValuesFromCell(std::vector<tSquares> sqList) const;
	
	bool _removeCandidatesFromCells(const std::vector<tSquares> sqList, std::set<tValues> groupValues);
	
	template <class IT>
	bool _RemoveCandidateFrom(IT sqList, tValues v);
	
	std::set<tValues> _getComplementaryListOfValues(std::vector<tValues> vList) const;
	
	std::vector<tSquares> _getComplementaryList(std::vector<tSquares> sqList, std::vector<tSquares> refList) const;
	
	static bool _isNthBitSet(const int data, const int n);
};

#endif