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

#include <algorithm>

#include "iterators.h"

const std::array<std::vector<tSquares>, rowNumber> squaresIterator::rows = {{
	{A1, A2, A3, A4, A5, A6, A7, A8, A9},
	{B1, B2, B3, B4, B5, B6, B7, B8, B9},
	{C1, C2, C3, C4, C5, C6, C7, C8, C9},
	{D1, D2, D3, D4, D5, D6, D7, D8, D9},
	{E1, E2, E3, E4, E5, E6, E7, E8, E9},
	{F1, F2, F3, F4, F5, F6, F7, F8, F9},
	{G1, G2, G3, G4, G5, G6, G7, G8, G9},
	{H1, H2, H3, H4, H5, H6, H7, H8, H9},
	{I1, I2, I3, I4, I5, I6, I7, I8, I9}
}};

const std::array<std::vector<tSquares>, fileNumber> squaresIterator::files = {{
	{A1, B1, C1, D1, E1, F1, G1, H1, I1},
	{A2, B2, C2, D2, E2, F2, G2, H2, I2},
	{A3, B3, C3, D3, E3, F3, G3, H3, I3},
	{A4, B4, C4, D4, E4, F4, G4, H4, I4},
	{A5, B5, C5, D5, E5, F5, G5, H5, I5},
	{A6, B6, C6, D6, E6, F6, G6, H6, I6},
	{A7, B7, C7, D7, E7, F7, G7, H7, I7},
	{A8, B8, C8, D8, E8, F8, G8, H8, I8},
	{A9, B9, C9, D9, E9, F9, G9, H9, I9},

}};

const std::array<std::vector<tSquares>, boxNumber> squaresIterator::boxes = {{
	{A1, A2, A3, B1, B2, B3, C1, C2, C3},
	{A4, A5, A6, B4, B5, B6, C4, C5, C6},
	{A7, A8, A9, B7, B8, B9, C7, C8, C9},
	{D1, D2, D3, E1, E2, E3, F1, F2, F3},
	{D4, D5, D6, E4, E5, E6, F4, F5, F6},
	{D7, D8, D9, E7, E8, E9, F7, F8, F9},
	{G1, G2, G3, H1, H2, H3, I1, I2, I3},
	{G4, G5, G6, H4, H5, H6, I4, I5, I6},
	{G7, G8, G9, H7, H8, H9, I7, I8, I9},
		

}};

const std::array<tSquares, 81> squaresIterator::squares = {
	A1, A2, A3, A4, A5, A6, A7, A8, A9,
	B1, B2, B3, B4, B5, B6, B7, B8, B9,
	C1, C2, C3, C4, C5, C6, C7, C8, C9,
	D1, D2, D3, D4, D5, D6, D7, D8, D9,
	E1, E2, E3, E4, E5, E6, E7, E8, E9,
	F1, F2, F3, F4, F5, F6, F7, F8, F9,
	G1, G2, G3, G4, G5, G6, G7, G8, G9,
	H1, H2, H3, H4, H5, H6, H7, H8, H9,
	I1, I2, I3, I4, I5, I6, I7, I8, I9
};

const std::array<tRows, rowNumber> squaresIterator::row = {ROW_A, ROW_B, ROW_C, ROW_D, ROW_E, ROW_F, ROW_G, ROW_H, ROW_I};
const std::array<tFiles, fileNumber> squaresIterator::file = {FILE_1, FILE_2, FILE_3, FILE_4, FILE_5, FILE_6, FILE_7, FILE_8, FILE_9};
const std::array<tBoxes, boxNumber> squaresIterator::box = {BOX_1, BOX_2, BOX_3, BOX_4, BOX_5, BOX_6, BOX_7, BOX_8, BOX_9};
const std::array<tValues, 9> squaresIterator::value = {VALUE_1, VALUE_2, VALUE_3, VALUE_4, VALUE_5, VALUE_6, VALUE_7, VALUE_8, VALUE_9};

bool isInRow(const tRows r, const tSquares s) {
	const auto& x = squaresIterator::rows[r];
	return (std::find (x.begin(), x.end(), s)!= x.end());
}

bool isInFile(const tFiles f, const tSquares s) {
	const auto& x = squaresIterator::files[f];
	return (std::find (x.begin(), x.end(), s)!= x.end());
}

bool isInBox(const tBoxes b, const tSquares s) {
	const auto& x = squaresIterator::boxes[b];
	return (std::find (x.begin(), x.end(), s)!= x.end());
}