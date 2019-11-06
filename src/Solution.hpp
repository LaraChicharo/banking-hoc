#pragma once

#include <vector>

#include "Constraints.hpp"

struct Transaction {
    int debtor;
    int creditor;
    long long amount;

    Transaction(int debtor, int creditor, int amount);
};

typedef struct Transaction Transaction;

class Solution {
    private:
        int npeople;
        std::vector<Transaction> transactions;
        std::vector<long long> all_balances;

        std::vector<int> debtors;
        std::vector<int> creditors;

        void SelectTypes();

    public:
        Solution(int npeople, std::vector<long long> all_balances);
    
        std::vector<int> GetDebtors();
        std::vector<int> GetCreditors();

        void Pay(int debtor, int creditor, long long amount);
        long long GetBalance(int id);
        int GetNPeople();
        void RestartTypes();
        std::vector<Transaction> GetTransactions();
};
