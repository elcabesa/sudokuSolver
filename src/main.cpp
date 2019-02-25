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
#include <iostream>

#include "board.h"
#include "candidates.h"
#include "solver.h"

void printStartInfo() {
	std::cout<<"SudokuSolver by Marco Belli"<<std::endl;
}

int main() {
	printStartInfo();
	
	Board b;
	
	b.setSquareValue(B2, VALUE_8);
	b.setSquareValue(B3, VALUE_1);
	b.setSquareValue(B4, VALUE_4);
	b.setSquareValue(B6, VALUE_9);
	b.setSquareValue(B7, VALUE_5);
	b.setSquareValue(B8, VALUE_6);
	
	b.setSquareValue(C1, VALUE_7);
	b.setSquareValue(C3, VALUE_6);
	b.setSquareValue(C4, VALUE_5);
	b.setSquareValue(C6, VALUE_3);
	b.setSquareValue(C7, VALUE_8);
	b.setSquareValue(C9, VALUE_4);
	
	b.setSquareValue(D2, VALUE_4);
	b.setSquareValue(D3, VALUE_2);
	b.setSquareValue(D7, VALUE_7);
	b.setSquareValue(D8, VALUE_1);
	
	b.setSquareValue(E4, VALUE_7);
	b.setSquareValue(E6, VALUE_6);
	
	b.setSquareValue(F3, VALUE_8);
	b.setSquareValue(F7, VALUE_2);
	
	b.setSquareValue(G4, VALUE_3);
	b.setSquareValue(G6, VALUE_7);
	
	b.setSquareValue(H1, VALUE_8);
	b.setSquareValue(H5, VALUE_6);
	b.setSquareValue(H9, VALUE_1);
	
	b.setSquareValue(I2, VALUE_3);
	b.setSquareValue(I8, VALUE_7);
		
	/*b.setSquareValue(A2, VALUE_5);
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
	
	b.setSquareValue(I6, VALUE_1);*/
	Solver s(b);
	s.solve();
	
	return 0;
}