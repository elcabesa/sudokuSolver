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

#include <cmath>
#include <iostream>
#include <set>

#include "board.h"
#include "candidates.h"
#include "iterators.h"
#include "swordfish.h"


bool swordFishStrategyRow::solve() {
	// for all the values
	for(auto v: squaresIterator::value) {
		// find all the squares with v as candidate
		// save the squares in a vector, grouped by row
		std::vector<std::vector<tSquares>> list;
		for (auto row: squaresIterator::row) {
			std::vector<tSquares> tempList;
			for (auto sq: squaresIterator::rows[row]) {
				if (_cand.contains(sq, v)) {
					tempList.push_back(sq);
				}
			}
			// we are interested in non hidden singles (>1) with no more than 3 squares
			if (tempList.size() > 1 && tempList.size() <=3) {
				list.push_back(tempList);
			}
		}
		
		// we can proceed only if we have found at least 3 groups
		if(list.size() >= 3) {
			for( int i = 0; i < pow(2, list.size());++i) {
				if(__builtin_popcount(i) == 3) {

					// calc union of column
					std::set<tFiles> t;
					for(unsigned int n = 0; n<list.size(); ++n){
						if(_isNthBitSet(i, n)) {
							for(auto x: list[n]) {
								t.insert(getFile(x));
							}
						}
					}
					if(t.size() == 3) {
						
						// create list of swordfish squares
						std::vector<tSquares> sw;
						for(unsigned int n = 0; n<list.size(); ++n){
							if(_isNthBitSet(i, n)) {
								auto it = list.begin();
								std::advance(it,n);
								for(auto x: *it) {
									sw.push_back(x);
								}
							}
						}

						std::vector<tSquares> sqList;
						// create list of squares on which remove V as candidate
						for(auto f: t) {
							for(auto x: squaresIterator::files[f]){
								if(std::find(sw.begin(),sw.end(), x) == sw.end()) {
									sqList.push_back(x);
								}
							}
						}
						
						if (_RemoveCandidateFrom(sqList, v)) {
							_printInfo("swordfish", sw, std::vector<tValues>(1, v));
							return true;
						}	
					}
				}
			}
		}
	}
	return false;
}


bool swordFishStrategyFile::solve() {
	// for all the values
	for(auto v: squaresIterator::value) {
		// find all the squares with v as candidate
		// save the squares in a vector, grouped by file
		std::vector<std::vector<tSquares>> list;
		for (auto file: squaresIterator::file) {
			std::vector<tSquares> tempList;
			for (auto sq: squaresIterator::files[file]) {
				if (_cand.contains(sq, v)) {
					tempList.push_back(sq);
				}
			}
			// we are interested in non hidden singles (>1) with no more than 3 squares
			if (tempList.size() > 1 && tempList.size() <=3) {
				list.push_back(tempList);
			}
		}
		
		// we can proceed only if we have found at least 3 groups
		if(list.size() >= 3) {
			for( int i = 0; i < pow(2, list.size());++i) {
				if(__builtin_popcount(i) == 3) {
					// calc union of column
					std::set<tRows> t;
					for(unsigned int n = 0; n<list.size(); ++n){
						if(_isNthBitSet(i, n)) {
							for(auto x: list[n]) {
								t.insert(getRow(x));
							}
						}
					}
					if(t.size() == 3) {
						
						// create list of swordfish squares
						std::vector<tSquares> sw;
						for(unsigned int n = 0; n<list.size(); ++n){
							if(_isNthBitSet(i, n)) {
								auto it = list.begin();
								std::advance(it,n);
								for(auto x: *it) {
									sw.push_back(x);
								}
							}
						}
						
						std::vector<tSquares> sqList;
						// create list of squares on which remove V as candidate
						for(auto f: t) {
							for(auto x: squaresIterator::rows[f]){
								if(std::find(sw.begin(),sw.end(), x) == sw.end()) {
									sqList.push_back(x);
								}
							}
						}
						
						if (_RemoveCandidateFrom(sqList, v)) {
							_printInfo("swordfish", sw, std::vector<tValues>(1, v));
							return true;
						}	
					}
				}
			}
		}
	}
	return false;
}