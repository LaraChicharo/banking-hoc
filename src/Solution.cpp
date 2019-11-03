#include "Solution.hpp"
using namespace std;


Transaction::Transaction(int debtor, int creditor, int amount):
    debtor(debtor), creditor(creditor), amount(amount) {}


Solution::Solution(
    int npeople, vector<long long> all_balances
): npeople(npeople), all_balances(all_balances) {
    for (int i=0; i<npeople; i++) {
        if (all_balances[i] <= 0)
            debtors.push_back(i);
        else
            creditors.push_back(i);
    }
}

vector<int> Solution::GetDebtors() {
    return debtors;
}

vector<int> Solution::GetCreditors() {
    return creditors;
}

void Solution::transaction(int i, long long amount) {
    all_balances[i] += amount;
}

