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
        double error;
        std::vector<Transaction> transactions;
        std::vector<long long> all_balances;

        std::vector<int> debtors;
        std::vector<int> creditors;

        void SelectTypes();

    public:
        Solution(int npeople, std::vector<long long> all_balances);
    
        std::vector<int> GetDebtors();
        std::vector<int> GetCreditors();

        int GetDebtorAt(int i);
        int GetCreditorAt(int i);

        int GetCreditorsSize();
        int GetDebtorsSize();

        void Pay(int debtor, int creditor, long long amount);
        long long GetBalance(int id);
        int GetNPeople();
        void RestartTypes();
        std::vector<Transaction> GetTransactions();
        void SetError(double error);
        double GetError();
};
