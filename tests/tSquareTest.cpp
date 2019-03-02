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
	
	TEST(tSquare, getFile)
	{
		ASSERT_EQ(getFile(D3), FILE_3);
		ASSERT_EQ(getFile(I2), FILE_2);
		ASSERT_EQ(getFile(A7), FILE_7);
	}
	
	TEST(tSquare, getRow)
	{
		ASSERT_EQ(getRow(D3), ROW_D);
		ASSERT_EQ(getRow(I2), ROW_I);
		ASSERT_EQ(getRow(A7), ROW_A);
	}
	
	TEST(tSquare, getBox)
	{
		ASSERT_EQ(getBox(D3), BOX_4);
		ASSERT_EQ(getBox(I2), BOX_7);
		ASSERT_EQ(getBox(A7), BOX_3);
	}
}