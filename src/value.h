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

#ifndef _VALUES_H
#define _VALUES_H

#include <ostream>

enum tValues {
	VALUE_1,
	VALUE_2,
	VALUE_3,
	VALUE_4,
	VALUE_5,
	VALUE_6,
	VALUE_7,
	VALUE_8,
	VALUE_9,
	VALUE_NONE = -1
};

std::ostream& operator <<(std::ostream& stream, const tValues& v);

#endif