#pragma once

#include "Solution.hpp"
#include "BipartiteMatching.hpp"
#include "Constraints.hpp"

/// @brief Given an instance of the problem, it creates a solution
/// using the hungarian algorithm many times
class HungarianSolver {
    private:
        /// solution
        Solution* solution;

    public:
        /// @brief Constructor.
        /// @param solution the inital solution
        HungarianSolver(Solution* solution);
        /// @brief Applies the algorithm.
        void Solve();

};
