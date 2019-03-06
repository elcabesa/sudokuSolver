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
#include <bitset>
#include <cassert>
#include <list>
#include <iostream>

#include "board.h"
#include "candidates.h"
#include "iterators.h"
#include "solver.h"

Solver::Solver(Board& b, bool verbose): _verbose(verbose), _b(b), _cand(b){
	_methods.push_back(_findSingle);
	_methods.push_back(_findHiddenSingleInRow);
	_methods.push_back(_findHiddenSingleInFile);
	_methods.push_back(_findHiddenSingleInBox);
	_methods.push_back(_findNakedInRow);
	_methods.push_back(_findNakedInFile);
	_methods.push_back(_findNakedInBox);
	_methods.push_back(_findHiddenInRow);
	_methods.push_back(_findHiddenInFile);
	_methods.push_back(_findHiddenInBox);
	_methods.push_back(_findPointingPairInRow);
	_methods.push_back(_findPointingPairInFile);
	_methods.push_back(_findBoxLineForRow);
	_methods.push_back(_findBoxLineForFile);
	_methods.push_back(_findXWing1);
	_methods.push_back(_findXWing2);
	_methods.push_back(_findYWing);
}

bool Solver::solve() {
	bool solved = false;
	_cand.fillCandidates();
	//_cand.print();
	if (_verbose) {
		std::cout<<"INITIAL BOARD"<<std::endl;
		_b.print();
		std::cout<<"---------------------------------------------"<<std::endl;
		std::cout<<"SOLVING"<<std::endl;
	}
	bool stepPerformed = false;
	do {
		//std::cout<<"Performing STEP..."<<std::endl;
		stepPerformed = false;
		for (auto m: _methods) {
			stepPerformed = (this->*m)();
			if (stepPerformed) {
				break;
			}
		}
	}
	while (stepPerformed);
	
	if(_isSolved()) {
		if (_verbose) {
			std::cout<<"SOLVED"<<std::endl;
			std::cout<<"---------------------------------------------"<<std::endl;
		}
		solved = true;
		
	} else {
		if (_verbose) {
			std::cout<<"UNSOLVED"<<std::endl;
			std::cout<<"---------------------------------------------"<<std::endl;
		}
		solved = false;
	}

	
	if (_verbose) {
		std::cout<<"FINAL BOARD"<<std::endl;
		_b.print();
	}
	return solved;
	
}

void Solver::_setSquareValue(const tSquares sq, const tValues v) {
	assert(sq < squareNumber && sq >= startSquare);
	assert(v >= VALUE_1 && v <= VALUE_9);
	_b.setSquareValue(sq, v);
	
	auto c = _cand.get(sq);
	
	for (auto ca: c) {
		_cand.remove(sq, ca);
	}
	
	for (auto s: squaresIterator::files[getFile(sq)]) {
		_cand.remove(s, v);
	}
	
	for (auto s: squaresIterator::rows[getRow(sq)]) {
		_cand.remove(s, v);
	}
	
	for (auto s: squaresIterator::boxes[getBox(sq)]) {
		_cand.remove(s, v);
	}
}

bool Solver::_findSingle() {
	//std::cout<<"Searching for solved cells..."<<std::endl;
	for (auto sq: squaresIterator::squares) {
		if (_cand.getSize(sq) == 1) {
			auto v = _cand.get(sq)[0];
			_printInfo("single", std::vector<tSquares>(1, sq), std::vector<tValues>(1, v));
			_setSquareValue(sq, v);
			return true;
		}
	}
	return false;
}

template <class IT, class IT2>
bool Solver::_findHiddenSingleIn(IT it, IT2 it2) {
	
	for (const auto r: it) {
		for (const auto v: squaresIterator::value) {
			unsigned int count = 0;
			tSquares singleSq = squareNumber;
			for( const auto sq: it2[r]) {
				if (_cand.contains(sq, v)) {
					++count;
					singleSq = sq;
				}
			}
			if (count == 1) {
				_printInfo("hidden single", std::vector<tSquares>(1, singleSq), std::vector<tValues>(1, v));
				_setSquareValue(singleSq, v);
				return true;
			}				
		}
	}
	return false;
}

bool Solver::_findHiddenSingleInRow() {
	//std::cout<<"Searching for hidden single in rows"<<std::endl;
	return _findHiddenSingleIn<std::array<tRows, rowNumber>, std::array<std::vector<tSquares>, rowNumber>>(squaresIterator::row, squaresIterator::rows);
}

bool Solver::_findHiddenSingleInFile() {
	//std::cout<<"Searching for hidden single in files"<<std::endl;
	return _findHiddenSingleIn<std::array<tFiles, fileNumber>, std::array<std::vector<tSquares>, fileNumber>>(squaresIterator::file, squaresIterator::files);
}

bool Solver::_findHiddenSingleInBox() {
	//std::cout<<"Searching for hidden single boxes"<<std::endl;
	return _findHiddenSingleIn<std::array<tBoxes, boxNumber>, std::array<std::vector<tSquares>, boxNumber>>(squaresIterator::box, squaresIterator::boxes);
}

template <class type>
std::vector<type> Solver::_getListFromBitset(const unsigned int n, std::vector<type> vec) const {
	//convert in a list of index
	std::bitset<9> bs(n);
	//get list of squares
	std::vector<type> sqList;
			
	for (std::size_t idx = 0; idx < bs.size(); ++idx) {
		if (bs[idx] != 0) {
			sqList.push_back(vec[idx]);
		}
	}
	return sqList;
}

bool Solver::_containSolvedCell(std::vector<tSquares> vec) const {
	bool containsSolvedCells = false;
	for (auto sq: vec) {
		if( _b.getSquareValue(sq) != VALUE_NONE) {containsSolvedCells = true;}
	}
	return containsSolvedCells;
}

std::set<tValues> Solver::_createUnionOfValuesFromCell(std::vector<tSquares> sqList) const {
	std::set<tValues> groupValues;
	for (auto sq: sqList) {
		auto& cand = _cand.get(sq);
		for (auto v: cand ) {
			groupValues.insert(v);
		}
	}
	return groupValues;
}

bool Solver::_removeCandidatesFromCells(const std::vector<tSquares> sqList, std::set<tValues> groupValues) {
	bool candidatesChanged = false;
	for (auto v: groupValues) {
		candidatesChanged |= _RemoveCandidateFrom(sqList, v);
	}
	return candidatesChanged;
}

template <class IT, class IT2>
bool Solver::_findNakedIn(IT it, IT2 it2) {
	
	for (const auto b: it) {
		
		// for all combiantion of 9 squares
		for (unsigned int n = 0; n < 512; ++n) {
			
			//convert bitset to vector of squares
			auto sqList = _getListFromBitset<tSquares>(n, it2[b]);
			
			//check that the combination doesn't contain solved cells
			if (!_containSolvedCell(sqList)) {
				
				// for the list of cells create the union of values
				auto groupValues = _createUnionOfValuesFromCell(sqList);
				
				// if the number of different values in the group is equal to thee number of squares in the bitset we have found a nake set
				if (sqList.size() == groupValues.size()) {
					// found a nake group. let's try so simplify
					
					// for all the squares outside sqList
					if (_removeCandidatesFromCells(_getComplementaryList(sqList, it2[b]), groupValues)) {
						_printInfo("naked group", sqList, std::vector<tValues>(groupValues.begin(),groupValues.end()));
						return true;
					}
				}
			}	
		}
	}
	return false;
}

bool Solver::_findNakedInRow() {
	//std::cout<<"Searching for naked in rows"<<std::endl;
	return _findNakedIn<std::array<tRows, rowNumber>, std::array<std::vector<tSquares>, rowNumber>>(squaresIterator::row, squaresIterator::rows);
}

bool Solver::_findNakedInFile() {
	//std::cout<<"Searching for naked in files"<<std::endl;
	return _findNakedIn<std::array<tFiles, fileNumber>, std::array<std::vector<tSquares>, fileNumber>>(squaresIterator::file, squaresIterator::files);
}

bool Solver::_findNakedInBox() {
	//std::cout<<"Searching for naked in boxes"<<std::endl;
	return _findNakedIn<std::array<tBoxes, boxNumber>, std::array<std::vector<tSquares>, boxNumber>>(squaresIterator::box, squaresIterator::boxes);
}


template <class IT, class IT2>
bool Solver::_findHiddenIn(IT it, IT2 it2) {
	
	// for all the units
	for (const auto b: it) {
		
		// for all combiantion of 9 values
		for (unsigned int n = 0; n < 512; ++n) {
			
			//convert bitset to vector of values
			std::vector<tValues> temp(squaresIterator::value.begin(), squaresIterator::value.end());
			auto valueList = _getListFromBitset<tValues>(n, temp);
			
			std::vector<tSquares> sqList;
			
			//get squareList not solved and non containing any of the values in candidates
			std::set<tValues> foundValues;
			for (auto sq: it2[b]) {
				auto cand = _cand.get(sq);
				bool contain = false;
				for (auto v: valueList) {
					if (std::find(cand.begin(),cand.end(),v) != cand.end()) {
						contain = true;
						foundValues.insert(v);
					}
				}
				if (contain) {
					sqList.push_back(sq);
				}
			}
				
			if (sqList.size() == valueList.size() && sqList.size() != 0 && foundValues.size() == valueList.size()) {
				// found a hidden group. let's try so simplify
				// remove values from complementary value list
				if (_removeCandidatesFromCells(sqList, _getComplementaryList(valueList))) {
					_printInfo("hidden group", sqList, valueList);
					return true;
				}
			}
		}
	}
	return false;
}

bool Solver::_findHiddenInRow() {
	//std::cout<<"Searching for hidden in rows"<<std::endl;
	return _findHiddenIn<std::array<tRows, rowNumber>, std::array<std::vector<tSquares>, rowNumber>>(squaresIterator::row, squaresIterator::rows);
}

bool Solver::_findHiddenInFile() {
	//std::cout<<"Searching for hidden in files"<<std::endl;
	return _findHiddenIn<std::array<tFiles, fileNumber>, std::array<std::vector<tSquares>, fileNumber>>(squaresIterator::file, squaresIterator::files);
}

bool Solver::_findHiddenInBox() {
	//std::cout<<"Searching for hidden in boxes"<<std::endl;
	return _findHiddenIn<std::array<tBoxes, boxNumber>, std::array<std::vector<tSquares>, boxNumber>>(squaresIterator::box, squaresIterator::boxes);
}

template <class IT, class IT2>
bool Solver::_findPointingPairIn(IT it, IT2 it2) {
	// for all the units
	for (const auto b: it) {
		// for all the values
		for(auto v: squaresIterator::value) {
			// find all the squares containing value as candidate
			std::vector<tSquares> squareList;
			for(auto sq: it2[b]) {
				if (_cand.contains(sq, v)) {
					squareList.push_back(sq);
				}
			}
			
			if (auto b = areOnTheSameBox(squareList); b != BOX_NONE ) {
				// you can remove the value from all other squares in the box
				if (_RemoveCandidateFrom(_getComplementaryList(squareList, squaresIterator::boxes[b]), v)) {
					_printInfo("pointing pair", squareList, std::vector<tValues>(1, v));
					return true;
				}

			}
		}
	}
	return false;
		
}

bool Solver::_findPointingPairInRow() {
	return _findPointingPairIn<std::array<tRows, rowNumber>, std::array<std::vector<tSquares>, rowNumber>>(squaresIterator::row, squaresIterator::rows);
}
bool Solver::_findPointingPairInFile() {
	return _findPointingPairIn<std::array<tFiles, fileNumber>, std::array<std::vector<tSquares>, fileNumber>>(squaresIterator::file, squaresIterator::files);
}


bool Solver::_findBoxLineForRow() {
	// for all boxes
	for (const auto b: squaresIterator::box) {
		// for all the values
		for(auto v: squaresIterator::value) {
			// find all the squares containing value as candidate
			std::vector<tSquares> squareList;
			for(auto sq: squaresIterator::boxes[b]) {
				if (_cand.contains(sq, v)) {
					squareList.push_back(sq);
				}
			}
			
			if (auto b = areOnTheSameRow(squareList); b != ROW_NONE ) {
				// you can remove the value from all other squares in the row
				if (_RemoveCandidateFrom(_getComplementaryList(squareList, squaresIterator::rows[b]), v)) {
					_printInfo("box line reduction", squareList, std::vector<tValues>(1, v));
					return true;
				}
			}
		}
	}
	return false;
}
bool Solver::_findBoxLineForFile() {
	// for all boxes
	for (const auto b: squaresIterator::box) {
		// for all the values
		for(auto v: squaresIterator::value) {
			// find all the squares containing value as candidate
			std::vector<tSquares> squareList;
			for(auto sq: squaresIterator::boxes[b]) {
				if (_cand.contains(sq, v)) {
					squareList.push_back(sq);
				}
			}
			
			if (auto b = areOnTheSameFile(squareList); b != FILE_NONE ) {
				// you can remove the value from all other squares in the file
				if (_RemoveCandidateFrom(_getComplementaryList(squareList, squaresIterator::files[b]), v)) {
					_printInfo("box line reduction", squareList, std::vector<tValues>(1, v));
					return true;
				}
			}
		}
	}
	return false;
}

void Solver::_printInfo(std::string type, std::vector<tSquares> sqList, std::vector<tValues> vList ) const {
	if (_verbose) {
		std::cout<<"...FOUND "<<type<<" at ";
		for (auto & sq: sqList) {
			std::cout<< sq;
			if (&sq != &sqList.back()) {
				std::cout<<", ";
			}
		}
		std::cout<<" values: (";
		for (auto& v: vList) {
			std::cout<< v;
			if (&v != &vList.back()) {
				std::cout<<", ";
			}
		}
		std::cout<<")"<<std::endl;
	}
}

bool Solver::_isSolved() {
	return !_b.contains(std::vector<tSquares>(squaresIterator::squares.begin(), squaresIterator::squares.end()), VALUE_NONE);
}

bool Solver::_findXWing1() {
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

bool Solver::_findXWing2() {
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

bool Solver::_findYWing() {
	/*std::cout<<"testing ywing"<<std::endl;*/
	std::vector<tSquares> sqList;
	for( auto sq: squaresIterator::squares)
	{
		if (_cand.getSize(sq) == 2) {
			sqList.push_back(sq);
		}
	}
	/*std::cout<<"list of candidate squares: ";
	for (auto sq: sqList) {
		std::cout<<sq<<",";
	}
	std::cout<<std::endl;*/
	
	// search for y-wing in candidates
	for (auto sq1: sqList) {
		auto AB = _cand.get(sq1);
		for (auto sq2: sqList) {
			auto BC = _cand.get(sq2);
			for (auto sq3: sqList) {
				// todo questo if alla fine controlla che esista una sfera di influenza non vuota..... posso provare ad approfondire il concetto 
				if (
					(areOnTheSameFile({sq1,sq2}) != FILE_NONE || areOnTheSameRow({sq1,sq2}) != ROW_NONE || areOnTheSameBox({sq1,sq2}) != BOX_NONE)
				    && (areOnTheSameFile({sq1,sq3}) != FILE_NONE || areOnTheSameRow({sq1,sq3}) != ROW_NONE || areOnTheSameBox({sq1,sq3}) != BOX_NONE)
				){
					auto AC = _cand.get(sq3);
					if( 
						   std::find(BC.begin(), BC.end(), AB[0]) != BC.end()
						&& std::find(AC.begin(), AC.end(), AB[1]) != AC.end()
					) {
						// check if the last value is C in BC and AC
						// find C
						tValues C =VALUE_NONE;
						for (auto val: BC) {
							if( std::find(AB.begin(), AB.end(), val) == AB.end()) {
								C = val;
							}
						}
						if ( C != VALUE_NONE && std::find(AC.begin(), AC.end(), C) != AC.end()) {
							
							/*std::cout<<" found probable ywing at "<<sq1<<", "<<sq2<<", "<<sq3<<std::endl;*/
							
							// todo calcolare sfera di influenza di una casa.... e fare intersezione fra sq2 e sq3 per trovare le case in cui rimuovere i C dai candidati :)
							//calc sq2 influence area.						
							std::set<tSquares> set1;
							for (auto sq: squaresIterator::files[getFile(sq2)]) {set1.insert(sq);}
							for (auto sq: squaresIterator::rows[getRow(sq2)]) {set1.insert(sq);}
							for (auto sq: squaresIterator::boxes[getBox(sq2)]) {set1.insert(sq);}
							//calc sq3 influence area.						
							std::set<tSquares> set2;
							for (auto sq: squaresIterator::files[getFile(sq3)]) {set2.insert(sq);}
							for (auto sq: squaresIterator::rows[getRow(sq3)]) {set2.insert(sq);}
							for (auto sq: squaresIterator::boxes[getBox(sq3)]) {set2.insert(sq);}
							
							std::vector<tSquares> res;
							// calc intersection
							for (auto sq: set1) {
								if (std::find(set2.begin(), set2.end(), sq) != set2.end()) {
									res.push_back(sq);
								}
							}
							/*std::cout<<"intersection squares ";
							for (auto sq: res) {
								std::cout<<sq<<",";
							}
							std::cout<<std::endl;*/
							if (_RemoveCandidateFrom(_getComplementaryList({sq1, sq2, sq3}, res), C)) {
								_printInfo("yWing", {sq1, sq2, sq3}, std::vector<tValues>(1, C));
								return true;
							}
						}
					}
				}
			}
		}
	}
	return false;
}

template <class IT>
bool Solver::_RemoveCandidateFrom(IT sqList, tValues v) {
	bool modified = false;
	for (auto sq: sqList) { 
		auto x =  _cand.remove(sq, v);
		modified |= x;
		/*if(x)std::cout<<"removed "<<C<<" from "<<sq<<std::endl;*/
	}
	return modified;
}

std::set<tValues> Solver::_getComplementaryList(std::vector<tValues> vList) const {
	std::set<tValues> complementaryValueList;
	for(auto v: squaresIterator::value) {
		if (std::find(vList.begin(), vList.end(), v) == vList.end()) {
			complementaryValueList.insert(v);
		}
	}
	return complementaryValueList;
}

std::vector<tSquares> Solver::_getComplementaryList(std::vector<tSquares> sqList, std::vector<tSquares> refList) const {
	std::vector<tSquares> complSquares;
	for (auto sq: refList) { 
		if (std::find(sqList.begin(), sqList.end(), sq) == sqList.end()) {
			complSquares.push_back(sq);
		}
	}
	return complSquares;
}