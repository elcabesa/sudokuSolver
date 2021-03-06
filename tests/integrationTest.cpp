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
#include "solver.h"

namespace {
	
	TEST(integration, test)
	{
		std::vector<std::string> tests = {
			".6....8217.89234.64.286..79.9.34..8..732.814..24.1796.2.763.51.9..175..4.31...69.",
			".....3...91...28.37...1..2.5.98....2........48.12....94...8..3.28...74.6.....4...",
			"...72.........9.4...9...231.17....2.8.34.16.7.4....81.695...3...7.8.........92...",
			".7..5..9...31.87....9...3..3.8...9.7.4..8..1.1.7...2.4..5...6....65.41...3..2..5.",
			"000400602006000100090500080050300000301206405000007020030002060004000900507009000",
			"005000400020940000900700008003000290100203007079000300400008001000014060006000700",
			"003910700000003400100040006060700000002109600000002010700080003008200000005071900",
			"010037000000000010600008029070049600100000003009350070390200008040000000000790060",
			"000903010004000600750000040000480000200000003000052000040000081005000260090208000",
			"900040000000600031020000090000700020002935600070002000060000073510009000000080009",
			"007000400060070030090203000005047609000000000908130200000705080070020090001000500",
			"600000002208000400000520896030080057000060000720090080574012000002000701800000009",
			"000000001004060208070320400900018000005000600000540009008037040609080300100000000",
			"091700050700801000008469000073000000000396000000000280000684500000902001020007940"
		};
		
		for (auto s: tests) {
			Board b(s);
			Solver so(b, false);
			ASSERT_TRUE(so.solve());
		}
	}
}