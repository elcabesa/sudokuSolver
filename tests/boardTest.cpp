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
		for (tSquares s = startSquare; s< squareNumber; ++s) {
			ASSERT_EQ(b.getSquareValue(s), VALUE_NONE);
		}
	}
	
	TEST(Board, setGet)
	{
		Board b;
		
		b.setSquareValue(A4, VALUE_5);
		b.setSquareValue(D7, VALUE_2);
		
		ASSERT_EQ(b.getSquareValue(A4), VALUE_5);
		ASSERT_EQ(b.getSquareValue(D7), VALUE_2);
		
		for (tSquares s = startSquare; s< squareNumber; ++s) {
			if (s != A4 && s != D7) {
				ASSERT_EQ(b.getSquareValue(s), VALUE_NONE);
			}
		}
		
		b.setSquareValue(A4, VALUE_NONE);
		ASSERT_EQ(b.getSquareValue(A4), VALUE_NONE);
	}
	
	TEST(Board, setGet2)
	{
		Board b;
		
		b.setSquareValue(ROW_A, FILE_4, VALUE_5);
		ASSERT_EQ(b.getSquareValue(A4), VALUE_5);
		
		b.setSquareValue(D7, VALUE_2);
	
		ASSERT_EQ(b.getSquareValue(ROW_D, FILE_7), VALUE_2);
		
	}
	
	TEST(Board, checkBoard)
	{
		Board b;
		//ASSERT_TRUE(b.checkBoard());
		
		b.setSquareValue(A2, VALUE_5);
		b.setSquareValue(A3, VALUE_8);
		b.setSquareValue(A4, VALUE_1);
		b.setSquareValue(A8, VALUE_4);
		
		b.setSquareValue(B1, VALUE_3);
		b.setSquareValue(B6, VALUE_4);
		b.setSquareValue(B7, VALUE_8);
		
		b.setSquareValue(C1, VALUE_1);
		b.setSquareValue(C4, VALUE_6);
		
		b.setSquareValue(D1, VALUE_7);
		b.setSquareValue(D3, VALUE_4);
		b.setSquareValue(D7, VALUE_3);
		
		b.setSquareValue(E6, VALUE_3);
		b.setSquareValue(E7, VALUE_2);
		b.setSquareValue(E8, VALUE_7);
		
		b.setSquareValue(F2, VALUE_6);
		b.setSquareValue(F5, VALUE_1);
		b.setSquareValue(F7, VALUE_4);
		b.setSquareValue(F8, VALUE_9);
		b.setSquareValue(F9, VALUE_8);
		
		b.setSquareValue(G2, VALUE_7);
		b.setSquareValue(G4, VALUE_5);
		b.setSquareValue(G5, VALUE_9);
		b.setSquareValue(G6, VALUE_2);
		b.setSquareValue(G8, VALUE_8);
		
		b.setSquareValue(H1, VALUE_8);
		b.setSquareValue(H5, VALUE_4);
		b.setSquareValue(H6, VALUE_6);
		b.setSquareValue(H7, VALUE_1);
		
		b.setSquareValue(I6, VALUE_1);
		
		//ASSERT_TRUE(b.checkBoard());
		
		/*b.setSquareValue(I3, VALUE_1);
		ASSERT_FALSE(b.checkBoard());
		b.setSquareValue(I3, VALUE_NONE);
		
		b.setSquareValue(E4, VALUE_6);
		ASSERT_FALSE(b.checkBoard());
		b.setSquareValue(E4, VALUE_NONE);*/
		
		b.setSquareValue(C8, VALUE_4);
		ASSERT_FALSE(b.checkBoard());
		b.setSquareValue(C8, VALUE_NONE);
		
	}
}