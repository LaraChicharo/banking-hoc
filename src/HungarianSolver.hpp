#pragma once

#include "Solution.hpp"
#include "BipartiteMatching.hpp"
#include "Constraints.hpp"

class HungarianSolver {
    private:
        Solution* solution;

    public:
        HungarianSolver(Solution* solution);
        void Solve();

};
