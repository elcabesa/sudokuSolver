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

#ifndef _TSQUARES_H
#define _TSQUARES_H

enum tRows {
	ROW_A,
	ROW_B,
	ROW_C,
	ROW_D,
	ROW_E,
	ROW_F,
	ROW_G,
	ROW_H,
	ROW_I,
	rowNumber,
	startRow = 0
};

enum tFiles {
	FILE_1,
	FILE_2,
	FILE_3,
	FILE_4,
	FILE_5,
	FILE_6,
	FILE_7,
	FILE_8,
	FILE_9,
	fileNumber,
	startFile = 0
};

enum tBoxes {
	BOX_1,
	BOX_2,
	BOX_3,
	BOX_4,
	BOX_5,
	BOX_6,
	BOX_7,
	BOX_8,
	BOX_9,
	boxNumber,
	startBox = 0
};

enum tSquares {
	A1,A2,A3,A4,A5,A6,A7,A8,A9,
	B1,B2,B3,B4,B5,B6,B7,B8,B9,
	C1,C2,C3,C4,C5,C6,C7,C8,C9,
	D1,D2,D3,D4,D5,D6,D7,D8,D9,
	E1,E2,E3,E4,E5,E6,E7,E8,E9,
	F1,F2,F3,F4,F5,F6,F7,F8,F9,
	G1,G2,G3,G4,G5,G6,G7,G8,G9,
	H1,H2,H3,H4,H5,H6,H7,H8,H9,
	I1,I2,I3,I4,I5,I6,I7,I8,I9,
	squareNumber,
	startSquare = 0
};

inline tSquares& operator++(tSquares& d) { d = static_cast<tSquares>(static_cast<int>(d) + 1); return d; }
inline tSquares& operator--(tSquares& d) { d = static_cast<tSquares>(static_cast<int>(d) - 1); return d; }

tSquares getSquare(const tRows r, const tFiles f);

tFiles getFile(const tSquares sq);
tRows getRow(const tSquares sq);
tBoxes getBox(const tSquares sq);

//TODO add print for squares, file, row, box

#endif