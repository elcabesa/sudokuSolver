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

#include "gtest/gtest.h"
#include "tSquares.h"

namespace {
	
	TEST(tSquare, getSquare)
	{
		ASSERT_EQ(getSquare(ROW_D, FILE_3), D3);
		ASSERT_EQ(getSquare(ROW_I, FILE_2), I2);
		ASSERT_EQ(getSquare(ROW_A, FILE_7), A7);
	}
}