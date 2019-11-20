#pragma once

#include <vector>
#include <cmath>
#include <cstdlib>

#include "Constraints.hpp"
#include "Solution.hpp"


class SimulatedAnnealingSolution {
    private:
        Solution* solution;

        long long MAXNEDGES;
        long long MINNEDGES;
        long long MAXERROR;

        Move* back_move;

        void CalculateBounds();
        void FirstBackMove();
        long long GetMaxNEdges();
        long long GetMinNEdges();
        long long GetMaxError();

        Move* GetBackMove();
    public:
        SimulatedAnnealingSolution(Solution* solution);
        SimulatedAnnealingSolution(SimulatedAnnealingSolution* sasolution);
    
        Solution* GetSolution();

        void MorphIntoNeighbour();
        void MorphBack();

        double Fitness();
        int GetNPeople();
        long long GetNEdges();
        long long GetError();
        double ErrorFitness();
        double NEdgesFitness();
        
        void PrintGraph();

};
