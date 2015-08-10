#ifndef SEE_H
#define SEE_H

#include "types.h"
#include "board.h"
#include "move.h"

#include <functional>

namespace SEE
{

static const Score SEE_MAT[14] = {
	1500, // WK
	975, // WQ
	500, // WR
	325, // WN
	325, // WB
	100, // WP

	0,
	0,

	1500, // BK
	975, // BQ
	500, // BR
	325, // BN
	325, // BB
	100 // BP
};

// returns how good this capture is for the moving side
Score StaticExchangeEvaluation(Board &board, Move mv);

// returns the value of the largest piece the opponent can place on the square
Score SEEMap(Board &board, Square sq);

Score StaticExchangeEvaluationSq(Board &board, Square sq, bool forced = false);

// this is essentially QSearch, but using SEE evaluation instead of the actual eval function
// the goal is to discover a reasonable PV quickly
// scores are biased to 0 at the start position of the search
Score GlobalExchangeEvaluation(Board &board, std::vector<Move> &pv, Score currentEval = 0, Score lowerBound = -SEE_MAT[WK], Score upperBound = SEE_MAT[WK]);

// this is a wrapper for GEE that simply runs the supplied function on the leaf of GEE, and undo all the moves
void GEERunFunc(Board &board, std::function<void(Board &b)> func);

bool RunSeeTest(std::string fen, std::string move, Score expectedScore);

void DebugRunSeeTests();

}

#endif // SEE_H
