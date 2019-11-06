#include "HungarianSolver.hpp"

#include <cstdio>


using namespace std;

HungarianSolver::HungarianSolver(Solution* solution): solution(solution) {

}

void HungarianSolver::Solve() {
    double error = 1;
    BipartiteMatching bm(solution);
    while (error > VIRTUAL_ZERO) {
        error = bm.Solve();
        bm.RebuildGraph();
        // printf("error: %f\n", error);
        solution->SetError(error);
    }
}
