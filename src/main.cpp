#include <vector>

#include <cstdio>

#include "Temperature.hpp"
#include "SimulatedAnnealing.hpp"
#include "SimulatedAnnealingSolution.hpp"
#include "Reader.hpp"
#include "Solution.hpp"
#include "HungarianSolver.hpp"

using namespace std;

int main(int argc, char* argv[]) {
    Reader* reader = new Reader(argc, argv);
    int npeople = reader->GetNPeople();
    vector<long long> all_balances = reader->GetAllBalances();
    vector<int> seeds = reader->GetSeeds();
    
    Solution* solution = new Solution(npeople, all_balances);
    
    if (seeds.size() > 0) {
        for (int seed : seeds) {
            printf("seed: %d\n", seed);
            srand(seed);
            SimulatedAnnealingSolution* sasolution =
                new SimulatedAnnealingSolution(solution);
            
            /*printf(
                "First solution, fitness: %f, error: %lld, nedges %lld, ferror: %f, fnedges:%f\n",
                sasolution->Fitness(),
                sasolution->GetError(),
                sasolution->GetNEdges(),
                sasolution->ErrorFitness(),
                sasolution->NEdgesFitness()
            );*/
            Temperature temperature(sasolution);
            SimulatedAnnealing* sa = new SimulatedAnnealing(
                temperature, sasolution
            );
            SimulatedAnnealingSolution* best_sol = sa->TresholdAccepting();
            printf("nedges: %lld\n", best_sol->GetNEdges());
            printf("error: %lld\n", best_sol->GetError());
            printf("ferror: %f\n", best_sol->ErrorFitness());
            printf("fnedges: %f\n", best_sol->NEdgesFitness());
            printf("fitness: %f\n", best_sol->Fitness());

            delete sa; 
            delete best_sol;
        }
    } else {
        printf("Using the hungarian algorithm to approximate a solution\n");
        HungarianSolver* hs = new HungarianSolver(solution);
        hs->Solve();
        vector<Transaction> transactions = solution->GetTransactions();
        printf("transactions: %d\n", (int)transactions.size());
    }
    delete reader;
    delete solution;
}
