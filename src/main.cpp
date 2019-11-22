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
        
        vector<int> creditors = solution->GetCreditors();
        vector<int> debtors = solution->GetDebtors();
        
        for (int seed : seeds) {
            printf("seed: %d\n", seed);
            srand(seed);
            SimulatedAnnealingSolution* sasolution =
                new SimulatedAnnealingSolution(solution);
            
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

            best_sol->PrintGraph();

            vector<long long> all_balances_copy(all_balances);
            vector<vector<int>> graph = best_sol->GetSolution()->GetGraph();
            for (int i=0; i < (int)debtors.size(); i++) {
                for (int j=0; j<(int)creditors.size(); j++) {
                    int amount = graph[i][j];
                    all_balances_copy[debtors[i]] += amount;
                    all_balances_copy[creditors[j]] -= amount;
                }
            }

            for (long long balance : all_balances_copy) {
                if (balance != 0) {
                    printf("---Invalid solution, error is not 0---\n");
                    break;
                }
            }

            delete sa; 
            delete best_sol;
        }
    } else {
        printf("Using the hungarian algorithm to approximate a solution\n");
        HungarianSolver* hs = new HungarianSolver(solution);
        hs->Solve();
        vector<Transaction> transactions = solution->GetTransactions();
        printf("transactions: %d\n", (int)transactions.size());
        for (Transaction t : transactions) {
            all_balances[t.debtor] += t.amount;
            all_balances[t.creditor] -= t.amount;
        }

        for (long long balance : all_balances) {
            if (balance != 0) {
                printf("---Invalid solution, error is not 0---\n");
                break;
            }
        }
    }
    delete reader;
    delete solution;
}
