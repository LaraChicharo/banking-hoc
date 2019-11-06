#pragma once

#include <vector>
#include <cmath>

#include "Solution.hpp"
#include "hungarian-algorithm-cpp/Hungarian.h"

class BipFullGraph {
    private:
        const double MAXERROR = 1e5;
        int nside;
        int debtors_size;
        int creditors_size;
        Solution* solution;

        std::vector<int> debtors;
        std::vector<int> creditors;

        void SetVertices(
            std::vector<int> debtors,
            std::vector<int> creditors
        );
        void SetEdges(); 

    public:
        std::vector<std::vector<double>> edges;

        BipFullGraph(Solution* solution);
};


class BipartiteMatching {
    private:
        Solution* solution;
        BipFullGraph* graph;


    public:
        BipartiteMatching(Solution* solution);
        double Solve();

};

