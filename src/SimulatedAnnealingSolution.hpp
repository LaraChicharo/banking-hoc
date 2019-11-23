#pragma once

#include <vector>
#include <cmath>
#include <cstdlib>

#include "Constraints.hpp"
#include "Solution.hpp"

/// @brief Wrapper to the Solution class to perform simulated annealing
/// on it.
class SimulatedAnnealingSolution {
    private:
        /// solution
        Solution* solution;

        /// constant containing the max number of edges possible for the
        /// instance
        long long MAXNEDGES;
        /// minimum number of edges possible in the solution
        long long MINNEDGES;
        /// maximum error possible in the instance
        long long MAXERROR;
        /// multiplier to the current error in the fitness function
        long long ERRORMULTIPLIER;
        /// multiplier to the current number of edges in the fitness
        /// function
        long long EDGESMULTIPLIER;

        /// Move to return the solution to its parent solution
        Move* back_move;

        /// @brief Calculates variables such as MAXNEDGES, MINNEDGES, etc.
        void CalculateBounds();
        /// @brief Fills the back move of the first solution.
        void FirstBackMove();
        /// @brief Returns MAXNEDGES.
        long long GetMaxNEdges();
        /// @brief Returns MINNEDGES.
        long long GetMinNEdges();
        /// @brief Returns MAXERROR.
        long long GetMaxError();

        /// @brief Returns ERRORMULTIPLIER.
        long long GetErrorMultiplier();
        /// @brief Returns EDGESMULTIPLIER.
        long long GetEdgesMultiplier();

        /// Returns the back move of the solution.
        Move* GetBackMove();
    public:
        /// Constructor.
        SimulatedAnnealingSolution(Solution* solution);
        /// Copy constructor.
        SimulatedAnnealingSolution(SimulatedAnnealingSolution* sasolution);
    
        /// @brief Gets the underlying solution.
        Solution* GetSolution();

        /// @brief Transforms itself into a random neighbour.
        void MorphIntoNeighbour();
        /// @brief Transforms itself into its parent solution.
        void MorphBack();

        /// @brief Returns the fitness value of the solution.
        double Fitness();
        /// @brief Returns the number of people in the problem.
        int GetNPeople();
        /// @brief Returns the number of edges in the current solution.
        long long GetNEdges();
        /// @brief Returns the raw error.
        long long GetError();
        /// @brief Returns the error normalized.
        double ErrorFitness();
        /// @brief Returns the number of edges normalized.
        double NEdgesFitness();
        
        /// @brief Prints the graph of transactions
        void PrintGraph();

};
