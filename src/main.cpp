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

#include <fstream>
#include <iostream>
#include <string>

#include "board.h"
#include "candidates.h"
#include "solver.h"

void printStartInfo() {
	std::cout<<"SudokuSolver V1.2.0 by Marco Belli"<<std::endl;
}

int main(int argc, char* argv[]) {
	printStartInfo();
	
	std::cout<<"------------------------------------------------------------------------------------------------------"<<std::endl;
	if(argc == 1) {
		std::ifstream myfile;
		std::string s;
		myfile.open("sudokus.txt");
		unsigned int solved = 0;
		unsigned int tested = 0;
		while (myfile.good()) {
			std::getline(myfile, s);
			std::cout<<"testing: "<<s;
			++tested;
			Board b(s);
			Solver slv(b, false);
			if (slv.solve()) {
				++solved;
				std::cout<<" [SOLVED]"<<std::endl;
			} else {
				std::cout<<" [UNSOLVED]"<<std::endl;
			}
		}
		myfile.close();
		std::cout<<"------------------------------------------------------------------------------------------------------"<<std::endl;
		std::cout<<"Solved "<<solved<<"/"<<tested<<std::endl;
		
	} else if (argc == 2) {
		Board b(argv[1]);
		Solver s(b);
		s.solve();
		return 0;
	}
	return -1;
}