#include <vector>

#include <cstdio>

#include "Temperature.hpp"
#include "SimulatedAnnealing.hpp"
#include "Reader.hpp"
#include "Solution.hpp"
#include "HungarianSolver.hpp"

using namespace std;

int main(int argc, char* argv[]) {
    srand(13);
    Reader* reader = new Reader(argc, argv);
    int npeople = reader->GetNPeople();
    vector<long long> all_balances = reader->GetAllBalances();
    Solution* solution = new Solution(npeople, all_balances);
    printf("debtors: %d\n", (int)solution->GetDebtors().size());
    printf("First solution, fitness: %lld, error: %lld, nedges: %lld\n", solution->Fitness(), solution->GetError(), solution->GetNEdges());
    Temperature temperature(solution);
    printf("After creating temp\n");
    SimulatedAnnealing* sa = new SimulatedAnnealing(
        temperature, solution
    );
    printf("After creating SA\n");
    Solution* best_sol = sa->TresholdAccepting();
    printf("nedges: %lld\n", best_sol->GetNEdges());
    // vector<Transaction> transactions = solution->GetTransactions();
    // printf("transactions: %d\n", (int)transactions.size());
    /*for (Transaction t : transactions) {
        printf("(%d, %d, %lld)\n", t.debtor, t.creditor, t.amount);
    }*/
}
