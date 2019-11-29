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

#ifndef _NAKED_SINGLE_H
#define _NAKED_SINGLE_H

#include "solvingStrategy.h"

template <class IT, class IT2>
class nakedStrategy: public solvingStrategy {
public:
	nakedStrategy(Board& b, Candidates& cand, bool verbose, IT it, IT2 it2) : solvingStrategy("naked", b, cand, verbose), _it(it), _it2(it2){};
	bool solve();
private:
	IT _it;
	IT2 _it2;
};

#endif