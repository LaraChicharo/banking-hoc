#pragma once

#include <vector>
#include <cmath>

#include "Solution.hpp"

class BipFullGraph {
    private:
        const long long MAXERROR = 1e18;
        int ghostid;
        int npeople;
        Solution* solution;

        std::vector<std::vector<long long>> edges;
        std::vector<int> debtors;
        std::vector<int> creditors;

        void SetVertices(
            std::vector<int> debtors,
            std::vector<int> creditors
        );
        void SetEdges(); 

    public:
        BipFullGraph(Solution* solution);
        long long Get(int debtorid, int creditorid);
};


class BipartiteMatching {
    private:
        Solution* solution;
        BipFullGraph* graph;


    public:
        BipartiteMatching(Solution* solution);

};

