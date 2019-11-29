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

#include "board.h"
#include "candidates.h"
#include "iterators.h"
#include "yWing.h"



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