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

#ifndef _SINGLE_H
#define _SINGLE_H

#include "solvingStrategy.h"

class singleStrategy : public solvingStrategy {
public:
	singleStrategy(Board& b, Candidates& cand, bool verbose) : solvingStrategy("single", b, cand, verbose){};
	bool solve();
};

#endif