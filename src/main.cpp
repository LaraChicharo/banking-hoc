#include <vector>

#include <cstdio>

#include "Temperature.hpp"
#include "SimulatedAnnealing.hpp"
#include "Reader.hpp"
#include "Solution.hpp"
#include "HungarianSolver.hpp"

using namespace std;

int main(int argc, char* argv[]) {
    Reader* reader = new Reader(argc, argv);
    int npeople = reader->GetNPeople();
    vector<long long> all_balances = reader->GetAllBalances();
    vector<int> seeds = reader->GetSeeds();
    
    for (int seed : seeds) {
        srand(seed);
        Solution* solution = new Solution(npeople, all_balances);
        vector<int>creditors = solution->GetCreditors();
        vector<int>debtors = solution->GetDebtors();
        
        printf("debtors: %d\n", (int)solution->GetDebtors().size());
        /*for (int debtor : debtors)
            printf("%d: %lld,  ", debtor, all_balances[debtor]);
        printf("\n");
        for (int creditor : creditors)
            printf("%d: %lld, ", creditor, all_balances[creditor]);
        printf("\n");
        */

        printf("First solution, fitness: %f, error: %lld, nedges %lld, ferror: %f, fnedges:%f\n", solution->Fitness(), solution->GetError(), solution->GetNEdges(), solution->ErrorFitness(), solution->NEdgesFitness());
        Temperature temperature(solution);
        SimulatedAnnealing* sa = new SimulatedAnnealing(
            temperature, solution
        );
        Solution* best_sol = sa->TresholdAccepting();
        printf("nedges: %lld\n", best_sol->GetNEdges());
        printf("error: %lld\n", best_sol->GetError());
        printf("ferror: %f\n", best_sol->ErrorFitness());
        printf("fnedges: %f\n", best_sol->NEdgesFitness());
        printf("fitness: %f\n", best_sol->Fitness());

        delete sa; 
        delete best_sol;
    }
    delete reader;
    // best_sol->PrintGraph();
    // vector<Transaction> transactions = solution->GetTransactions();
    // printf("transactions: %d\n", (int)transactions.size());
    /*for (Transaction t : transactions) {
        printf("(%d, %d, %lld)\n", t.debtor, t.creditor, t.amount);
    }*/
}
