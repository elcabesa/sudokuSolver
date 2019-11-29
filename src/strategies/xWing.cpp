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

#include <list>

#include "board.h"
#include "candidates.h"
#include "iterators.h"
#include "xWing.h"


bool xWing1Strategy::solve() {
	// for all the values
	//std::cout<<"testing xwing"<<std::endl;
	for(auto v: squaresIterator::value) {
		//std::cout<<"value "<<v<<std::endl;
		// find all the squares with v as candidate
		std::vector<tSquares> tempList;
		std::list<std::vector<tSquares>> list;
		for (auto row: squaresIterator::row) {
			//std::cout<<" testing row "<<row<<std::endl;
			tempList.clear();
			for (auto sq: squaresIterator::rows[row]) {
				if (_cand.contains(sq, v)) {
					tempList.push_back(sq);
					//std::cout<<" found in square "<<sq<<std::endl;
				}
			}
			if (tempList.size() == 2) {
				//std::cout<<"found locked pair"<<std::endl;
				list.push_back(tempList);
			}
		}
		
		/*std::cout<<"locked pairs list:"<<std::endl;
		for (auto x: list) {
			std::cout<<x[0]<<", "<<x[1]<<std::endl;
		}*/
		
		// try to find an xwing in the list of locked pairs
		for (auto x1: list) {
			for (auto x2: list) {
				if (
					getRow(x2[0]) > getRow(x1[0])
					&& getFile(x1[0]) == getFile(x2[0])
					&& getFile(x1[1]) == getFile(x2[1])
				) {
					//std::cout<<"FOUND xwing at "<< x1[0]<<", "<<x1[1] <<"; "<< x2[0]<<", "<<x2[1]<<std::endl;
					tFiles f1 = getFile(x1[0]); 
					tFiles f2 = getFile(x1[1]); 
					tRows  r1 = getRow(x1[0]); 
					tRows  r2 = getRow(x2[0]); 
					
					std::vector<tSquares> sqList;
					// create list of squares on which remove V as candidate
					for (auto sq: squaresIterator::files[f1]) {
						if (getRow(sq) != r1 &&  getRow(sq) != r2) {
							sqList.push_back(sq);
						}
					}
					for (auto sq: squaresIterator::files[f2]) {
						if (getRow(sq) != r1 &&  getRow(sq) != r2) {
							sqList.push_back(sq);
						}
					}
					
					if (_RemoveCandidateFrom(sqList, v)) {
						_printInfo("xwing", {x1[0], x1[1], x2[0], x2[1]}, std::vector<tValues>(1, v));
						return true;
					}	
				}
			}
		}
	}
	return false;
}




bool xWing2Strategy::solve() {
	// for all the values
	//std::cout<<"testing xwing"<<std::endl;
	for(auto v: squaresIterator::value) {
		//std::cout<<"value "<<v<<std::endl;
		// find all the squares with v as candidate
		std::vector<tSquares> tempList;
		std::list<std::vector<tSquares>> list;
		for (auto file: squaresIterator::file) {
			//std::cout<<" testing file "<<row<<std::endl;
			tempList.clear();
			for (auto sq: squaresIterator::files[file]) {
				if (_cand.contains(sq, v)) {
					tempList.push_back(sq);
					//std::cout<<" found in square "<<sq<<std::endl;
				}
			}
			if (tempList.size() == 2) {
				//std::cout<<"found locked pair"<<std::endl;
				list.push_back(tempList);
			}
		}
		
		/*std::cout<<"locked pairs list:"<<std::endl;
		for (auto x: list) {
			std::cout<<x[0]<<", "<<x[1]<<std::endl;
		}*/
		
		// try to find an xwing in the list of locked pairs
		for (auto x1: list) {
			for (auto x2: list) {
				if (
					getFile(x2[0]) > getFile(x1[0])
					&& getRow(x1[0]) == getRow(x2[0])
					&& getRow(x1[1]) == getRow(x2[1])
				) {
					//std::cout<<"FOUND xwing at "<< x1[0]<<", "<<x1[1] <<"; "<< x2[0]<<", "<<x2[1]<<std::endl;
					tRows  r1 = getRow(x1[0]); 
					tRows  r2 = getRow(x1[1]); 
					tFiles f1 = getFile(x1[0]); 
					tFiles f2 = getFile(x2[0]); 
					
					std::vector<tSquares> sqList;
					// create list of squares on which remove V as candidate
					for (auto sq: squaresIterator::rows[r1]) {
						if (getFile(sq) != f1 &&  getFile(sq) != f2) {
							sqList.push_back(sq);
						}
					}
					for (auto sq: squaresIterator::rows[r2]) {
						if (getFile(sq) != f1 &&  getFile(sq) != f2) {
							sqList.push_back(sq);
						}
					}
					
					if (_RemoveCandidateFrom(sqList, v)) {
						_printInfo("xwing", {x1[0], x1[1], x2[0], x2[1]}, std::vector<tValues>(1, v));
						return true;
					}	
				}
			}
		}
	}
	return false;
}