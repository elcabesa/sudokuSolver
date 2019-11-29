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

#ifndef _BOX_LINE_H
#define _BOX_LINE_H

#include "solvingStrategy.h"
// todo unify
class boxLineForRowStrategy : public solvingStrategy {
public:
	boxLineForRowStrategy(Board& b, Candidates& cand, bool verbose) : solvingStrategy("boxLineRow", b, cand, verbose){};
	bool solve();
};

class boxLineForLineStrategy : public solvingStrategy {
public:
	boxLineForLineStrategy(Board& b, Candidates& cand, bool verbose) : solvingStrategy("boxLineFile", b, cand, verbose){};
	bool solve();
};

#endif