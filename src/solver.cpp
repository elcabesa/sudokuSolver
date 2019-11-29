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
#include "solvingStrategy.h"

/************************************************************************************
single strategy class
*************************************************************************************/
class singleStrategy : public solvingStrategy {
public:
	singleStrategy(Board& b, Candidates& cand, bool verbose) : solvingStrategy(b, cand, verbose){};
	bool solve();
};

bool singleStrategy::solve() {
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

/************************************************************************************
hidden single strategy class
*************************************************************************************/
template <class IT, class IT2>
class hiddenSingleStrategy: public solvingStrategy {
public:
	hiddenSingleStrategy(Board& b, Candidates& cand, bool verbose, IT it, IT2 it2) : solvingStrategy(b, cand, verbose), _it(it), _it2(it2){};
	bool solve();
private:
	IT _it;
	IT2 _it2;
};

template <class IT, class IT2>
bool hiddenSingleStrategy<IT, IT2>::solve() {
	//std::cout<<"Searching for hidden single in ????"<<std::endl;
	for (const auto r: _it) {
		for (const auto v: squaresIterator::value) {
			unsigned int count = 0;
			tSquares singleSq = squareNumber;
			for( const auto sq: _it2[r]) {
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

/************************************************************************************
naked strategy class
*************************************************************************************/
template <class IT, class IT2>
class nakedStrategy: public solvingStrategy {
public:
	nakedStrategy(Board& b, Candidates& cand, bool verbose, IT it, IT2 it2) : solvingStrategy(b, cand, verbose), _it(it), _it2(it2){};
	bool solve();
private:
	IT _it;
	IT2 _it2;
};

template <class IT, class IT2>
bool nakedStrategy<IT, IT2>::solve() {
	for (const auto b: _it) {
		
		// for all combiantion of 9 squares
		for (unsigned int n = 0; n < 512; ++n) {
			
			//convert bitset to vector of squares
			auto sqList = _getListFromBitset<tSquares>(n, _it2[b]);
			
			//check that the combination doesn't contain solved cells
			if (!_containSolvedCell(sqList)) {
				
				// for the list of cells create the union of values
				auto groupValues = _createUnionOfValuesFromCell(sqList);
				
				// if the number of different values in the group is equal to thee number of squares in the bitset we have found a nake set
				if (sqList.size() == groupValues.size()) {
					// found a nake group. let's try so simplify
					
					// for all the squares outside sqList
					if (_removeCandidatesFromCells(_getComplementaryList(sqList, _it2[b]), groupValues)) {
						_printInfo("naked group", sqList, std::vector<tValues>(groupValues.begin(),groupValues.end()));
						return true;
					}
				}
			}	
		}
	}
	return false;
}

/************************************************************************************
hidden strategy class
*************************************************************************************/
template <class IT, class IT2>
class hiddenStrategy: public solvingStrategy {
public:
	hiddenStrategy(Board& b, Candidates& cand, bool verbose, IT it, IT2 it2) : solvingStrategy(b, cand, verbose), _it(it), _it2(it2){};
	bool solve();
private:
	IT _it;
	IT2 _it2;
};

template <class IT, class IT2>
bool hiddenStrategy<IT, IT2>::solve() {
	// for all the units
	for (const auto b: _it) {
		
		// for all combiantion of 9 values
		for (unsigned int n = 0; n < 512; ++n) {
			
			//convert bitset to vector of values
			std::vector<tValues> temp(squaresIterator::value.begin(), squaresIterator::value.end());
			auto valueList = _getListFromBitset<tValues>(n, temp);
			
			std::vector<tSquares> sqList;
			
			//get squareList not solved and non containing any of the values in candidates
			std::set<tValues> foundValues;
			for (auto sq: _it2[b]) {
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
				if (_removeCandidatesFromCells(sqList, _getComplementaryListOfValues(valueList))) {
					_printInfo("hidden group", sqList, valueList);
					return true;
				}
			}
		}
	}
	return false;
}

/************************************************************************************
pointing pair strategy class
*************************************************************************************/
template <class IT, class IT2>
class pointingPairStrategy: public solvingStrategy {
public:
	pointingPairStrategy(Board& b, Candidates& cand, bool verbose, IT it, IT2 it2) : solvingStrategy(b, cand, verbose), _it(it), _it2(it2){};
	bool solve();
private:
	IT _it;
	IT2 _it2;
};

template <class IT, class IT2>
bool pointingPairStrategy<IT, IT2>::solve() {
	// for all the units
	for (const auto b: _it) {
		// for all the values
		for(auto v: squaresIterator::value) {
			// find all the squares containing value as candidate
			std::vector<tSquares> squareList;
			for(auto sq: _it2[b]) {
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

/************************************************************************************
box line strategy class
*************************************************************************************/
class boxLineForRowStrategy : public solvingStrategy {
public:
	boxLineForRowStrategy(Board& b, Candidates& cand, bool verbose) : solvingStrategy(b, cand, verbose){};
	bool solve();
};

bool boxLineForRowStrategy::solve() {
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

/************************************************************************************
box line strategy class
*************************************************************************************/
// todo unify with box line for row
class boxLineForLineStrategy : public solvingStrategy {
public:
	boxLineForLineStrategy(Board& b, Candidates& cand, bool verbose) : solvingStrategy(b, cand, verbose){};
	bool solve();
};

bool boxLineForLineStrategy::solve() {
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

/************************************************************************************
xwing1 strategy class
*************************************************************************************/

class xWing1Strategy : public solvingStrategy {
public:
	xWing1Strategy(Board& b, Candidates& cand, bool verbose) : solvingStrategy(b, cand, verbose){};
	bool solve();
};

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

/************************************************************************************
xwing2 strategy class
*************************************************************************************/

class xWing2Strategy : public solvingStrategy {
public:
	xWing2Strategy(Board& b, Candidates& cand, bool verbose) : solvingStrategy(b, cand, verbose){};
	bool solve();
};

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

/************************************************************************************
ywing strategy class
*************************************************************************************/

class yWingStrategy : public solvingStrategy {
public:
	yWingStrategy(Board& b, Candidates& cand, bool verbose) : solvingStrategy(b, cand, verbose){};
	bool solve();
};

bool yWingStrategy::solve() {
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

/************************************************************************************
solver private implementation
*************************************************************************************/
class Solver::impl
{
public:
	impl (Board& b, bool verbose): _b(b), _cand(b), _verbose(verbose) {
		
		_solverStrategies.emplace_back(std::make_unique<singleStrategy>(_b, _cand, _verbose));
		
		_solverStrategies.emplace_back(std::make_unique<hiddenSingleStrategy<rowIterator, rowsIterator>>(_b, _cand, _verbose, squaresIterator::row, squaresIterator::rows));
		_solverStrategies.emplace_back(std::make_unique<hiddenSingleStrategy<fileIterator, std::array<std::vector<tSquares>, fileNumber>>>(_b, _cand, _verbose, squaresIterator::file, squaresIterator::files));
		_solverStrategies.emplace_back(std::make_unique<hiddenSingleStrategy<boxIterator, std::array<std::vector<tSquares>, boxNumber>>>(_b, _cand, _verbose, squaresIterator::box, squaresIterator::boxes));
		
		_solverStrategies.emplace_back(std::make_unique<nakedStrategy<rowIterator, rowsIterator>>(_b, _cand, _verbose, squaresIterator::row, squaresIterator::rows));
		_solverStrategies.emplace_back(std::make_unique<nakedStrategy<fileIterator, filesIterator>>(_b, _cand, _verbose, squaresIterator::file, squaresIterator::files));
		_solverStrategies.emplace_back(std::make_unique<nakedStrategy<boxIterator, boxesIterator>>(_b, _cand, _verbose, squaresIterator::box, squaresIterator::boxes));
		
		_solverStrategies.emplace_back(std::make_unique<hiddenStrategy<rowIterator, rowsIterator>>(_b, _cand, _verbose, squaresIterator::row, squaresIterator::rows));
		_solverStrategies.emplace_back(std::make_unique<hiddenStrategy<fileIterator, filesIterator>>(_b, _cand, _verbose, squaresIterator::file, squaresIterator::files));
		_solverStrategies.emplace_back(std::make_unique<hiddenStrategy<boxIterator, boxesIterator>>(_b, _cand, _verbose, squaresIterator::box, squaresIterator::boxes));
		
		_solverStrategies.emplace_back(std::make_unique<pointingPairStrategy<rowIterator, rowsIterator>>(_b, _cand, _verbose, squaresIterator::row, squaresIterator::rows));
		_solverStrategies.emplace_back(std::make_unique<pointingPairStrategy<fileIterator, filesIterator>>(_b, _cand, _verbose, squaresIterator::file, squaresIterator::files));
		
		_solverStrategies.emplace_back(std::make_unique<boxLineForRowStrategy>(_b, _cand, _verbose));
		_solverStrategies.emplace_back(std::make_unique<boxLineForLineStrategy>(_b, _cand, _verbose));
		
		_solverStrategies.emplace_back(std::make_unique<xWing1Strategy>(_b, _cand, _verbose));
		_solverStrategies.emplace_back(std::make_unique<xWing2Strategy>(_b, _cand, _verbose));
		_solverStrategies.emplace_back(std::make_unique<yWingStrategy>(_b, _cand, _verbose));
		
		
	};
	bool solve();
private:
	Board& _b;
	Candidates _cand;
	bool _verbose;	
	
	std::list<std::unique_ptr<solvingStrategy>> _solverStrategies;
	bool _isSolved();
};

bool Solver::impl::solve() {
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
		for (auto& m: _solverStrategies) {
			stepPerformed = m->solve();
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

bool Solver::impl::_isSolved() {
	return !_b.contains(std::vector<tSquares>(squaresIterator::squares.begin(), squaresIterator::squares.end()), VALUE_NONE);
}

/************************************************************************************
Solver implementation
*************************************************************************************/
Solver::Solver (Board& b, bool verbose): _pimpl{std::make_unique<impl>(b,verbose)}{}

bool Solver::solve() {return _pimpl->solve();}

Solver::~Solver() = default;
