#pragma once

#include <vector>
#include <cmath>

#include "Solution.hpp"
#include "hungarian-algorithm-cpp/Hungarian.h"

/// @brief Creates a bipartite graph out of a Solution
class BipFullGraph {
    private:
        /// the bigges error possible
        const double MAXERROR = 1e4;
        /// size of each size of the graph 
        int nside;
        /// nuber of debtors
        int debtors_size;
        /// number of creditors
        int creditors_size;
        /// solution
        Solution* solution;

        /// vector of debtors
        std::vector<int> debtors;
        /// vector of creditors
        std::vector<int> creditors;

        /// @brief Arranges the vertices of the graph
        /// @param debtors   array of debtors
        /// @param creditors array of creditors
        void SetVertices(
            std::vector<int> debtors,
            std::vector<int> creditors
        );

        /// @brief sets the weight of the edges according to the
        /// error it would create if all the debt was to be paid
        /// using that edge
        void SetEdges(); 

    public:
        /// the value of the edges
        std::vector<std::vector<double>> edges;

        /// @brief Constructor
        BipFullGraph(Solution* solution);
        /// @brief builds the bipartite graph
        void BuildGraph();
};


/// @brief Class to create a bipartite matching out of a Solution 
class BipartiteMatching {
    private:
        /// solution
        Solution* solution;
        /// graph
        BipFullGraph* graph;


    public:
        /// @brief Constructor
        BipartiteMatching(Solution* solution);
        /// @brief Creates the matchig
        /// @returns The weight of the matching
        double Solve();
        /// @brief Recreates the graph so a new matching can be calculated 
        void RebuildGraph();

};

