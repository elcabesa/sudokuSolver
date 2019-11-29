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

#include <chrono>
#include <list>
#include <iostream>
#include <map>

#include "board.h"
#include "candidates.h"
#include "iterators.h"
#include "solver.h"

#include "solvingStrategy.h"

#include "single.h"
#include "hiddenSingle.h"
#include "naked.h"
#include "hidden.h"
#include "pointingPair.h"
#include "boxLine.h"
#include "xWing.h"
#include "yWing.h"



/************************************************************************************
solver private implementation
*************************************************************************************/

struct statt{
	unsigned long long int time = 0;
	unsigned long long int calls = 0;
};

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
	std::map<std::string, statt> _stats;

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
	bool stepPerformed = true;
	while(!_isSolved() && stepPerformed) {
		//std::cout<<"Performing STEP..."<<std::endl;
		stepPerformed = false;
		for (auto& m: _solverStrategies) {
			if (_verbose) std::cout << m->getName() <<std::endl;
			std::chrono::steady_clock::time_point begin = std::chrono::steady_clock::now();
			stepPerformed = m->solve();
			std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();
			_stats[m->getName()].time += std::chrono::duration_cast<std::chrono::nanoseconds> (end - begin).count();
			_stats[m->getName()].calls ++;
			if (stepPerformed) {
				break;
			}
		}
	}
	
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
	
		std::cout << "**************time report****************" << std::endl;
		unsigned long long int tot = 0;
		for (const auto& s: _stats) {
			tot += s.second.time;
		}
		for (const auto& s: _stats) {
			std::cout << s.first << " " << s.second.time/ 1.0e9 << "s [" << s.second.time * 100.0 / tot << "%], " << s.second.calls <<std::endl;
		}
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
