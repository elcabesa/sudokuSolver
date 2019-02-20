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
#include "iterators.h"

namespace {
	
	TEST(Iterator, row)
	{
		unsigned int c = 0;
		for (auto r: squaresIterator::row) {		
			ASSERT_EQ(r, c);
			++c;
		}
		ASSERT_EQ(c, 9);
		
	}
	
	TEST(Iterator, file)
	{
		unsigned int c = 0;
		for (auto f: squaresIterator::file) {		
			ASSERT_EQ(f, c);
			++c;
		}
		ASSERT_EQ(c, 9);
	}
	
	TEST(Iterator, box)
	{
		unsigned int c = 0;
		for (auto b: squaresIterator::box) {		
			ASSERT_EQ(b, c);
			++c;
		}
		ASSERT_EQ(c, 9);
	}
	
	TEST(Iterator, value)
	{
		unsigned int c = 0;
		for (auto v: squaresIterator::value) {		
			ASSERT_EQ(v, c);
			++c;
		}
		ASSERT_EQ(c, 9);
	}
}