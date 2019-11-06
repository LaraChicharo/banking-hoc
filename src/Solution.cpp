#include "Solution.hpp"

#include <cstdio>
using namespace std;


Transaction::Transaction(int debtor, int creditor, int amount):
    debtor(debtor), creditor(creditor), amount(amount) {}


Solution::Solution(
    int npeople, vector<long long> all_balances
): npeople(npeople), error(0), all_balances(all_balances) {
    SelectTypes();
}

void Solution::SelectTypes() {
    for (int i=0; i<npeople; i++) {
        if (all_balances[i] < 0)
            debtors.push_back(i);
        else if (all_balances[i] > 0)
            creditors.push_back(i);
    }

    printf("debtors: %d\n", (int)debtors.size());
    printf("creditors: %d\n", (int)creditors.size());
    printf("debtors: ");
    for (int i=0; i<(int)debtors.size(); i++) {
        printf("%d: %lld, ", debtors[i], all_balances[debtors[i]]);
    }
    printf("\n");
    printf("creditors: ");
    for (int i=0; i<(int)creditors.size(); i++) {
        printf("%d: %lld, ", creditors[i], all_balances[creditors[i]]);
    }
    printf("\n");
}

long long Solution::GetBalance(int i) {
    return all_balances[i];
}

int Solution::GetNPeople() {
    return npeople;
}

void Solution::RestartTypes() {
    debtors.clear();
    creditors.clear();
    SelectTypes();
}

vector<int> Solution::GetDebtors() {
    return debtors;
}

vector<int> Solution::GetCreditors() {
    return creditors;
}

int Solution::GetDebtorAt(int i) {
    return debtors[i];
}

int Solution::GetCreditorAt(int i) {
    return creditors[i];
}

int Solution::GetCreditorsSize() {
    return creditors.size();
}

int Solution::GetDebtorsSize() {
    return debtors.size();
}

void Solution::Pay(int debtor, int creditor, long long amount) {
    Transaction transaction(debtor, creditor, amount);
    transactions.push_back(transaction);
    all_balances[debtor] += amount;
    // printf("debtor balance: %lld\n", all_balances[debtor]);
    all_balances[creditor] -= amount;
}

vector<Transaction> Solution::GetTransactions() {
    return transactions;
}

void Solution::SetError(double error) {
    this->error = error;
}

double Solution::GetError() {
    return error;
}
