#include <vector>

#include <cstdio>

#include "Reader.hpp"
#include "Solution.hpp"
#include "BipartiteMatching.hpp"

using namespace std;

int main(int argc, char* argv[]) {
    Reader* reader = new Reader(argc, argv);
    int npeople = reader->GetNPeople();
    vector<long long> all_balances = reader->GetAllBalances();
    Solution* solution = new Solution(npeople, all_balances);
    BipartiteMatching* bpm = new BipartiteMatching(solution);
    double error = bpm->Solve();
    vector<Transaction> transactions = solution->GetTransactions();
    printf(" error: %f\n", error);
    printf("transactions: %d\n", (int)transactions.size());
    for (Transaction t : transactions) {
        printf("(%d, %d, %lld)\n", t.debtor, t.creditor, t.amount);
    }
}
