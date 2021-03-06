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

#include <memory>
#include <set>
#include <string>

#include "candidates.h"
#include "value.h"

class Board;

class Solver {
public:
	Solver (Board& b, bool verbose = true);
	~Solver();
	
	Solver( const Solver& other ) = delete;
	Solver& operator=(const Solver& other) = delete;
	Solver(Solver&&) =delete;
	Solver& operator=(Solver&&) = delete;
	
	bool solve();
private:
	class impl;
	std::unique_ptr<impl> _pimpl;
};


#endif