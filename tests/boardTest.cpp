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
#include "board.h"

namespace {
	
	TEST(Board, ctor)
	{
		Board b;
		for (squares s = startSquare; s< squareNumber; ++s) {
			ASSERT_EQ(b.getSquareValue(s), VALUE_NONE);
		}
	}
	
	TEST(Board, setGet)
	{
		Board b;
		
		b.setSquareValue(A4, VALUE_FIVE);
		b.setSquareValue(D7, VALUE_TWO);
		
		ASSERT_EQ(b.getSquareValue(A4), VALUE_FIVE);
		ASSERT_EQ(b.getSquareValue(D7), VALUE_TWO);
		
		for (squares s = startSquare; s< squareNumber; ++s) {
			if (s != A4 && s != D7) {
				ASSERT_EQ(b.getSquareValue(s), VALUE_NONE);
			}
		}
		
		b.setSquareValue(A4, VALUE_NONE);
		ASSERT_EQ(b.getSquareValue(A4), VALUE_NONE);
s
	}
}