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

#ifndef _X_WING_H
#define _X_WING_H

#include "solvingStrategy.h"

class xWing1Strategy : public solvingStrategy {
public:
	xWing1Strategy(Board& b, Candidates& cand, bool verbose) : solvingStrategy(b, cand, verbose){};
	bool solve();
};

class xWing2Strategy : public solvingStrategy {
public:
	xWing2Strategy(Board& b, Candidates& cand, bool verbose) : solvingStrategy(b, cand, verbose){};
	bool solve();
};

#endif