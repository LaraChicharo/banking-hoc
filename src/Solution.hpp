#pragma once

#include <vector>
#include <cmath>
#include <cstdlib>

#include "Constraints.hpp"

struct Transaction {
    int debtor;
    int creditor;
    long long amount;

    Transaction(int debtor, int creditor, int amount);
};

struct Move {
    Transaction substract;
    Transaction add;

    Move(Transaction substact, Transaction add);
};

typedef struct Transaction Transaction;
typedef struct Move Move;

class Solution {
    private:
        int npeople;
        int unit;
        long long error;
        long long nedges;

        Move* back_move;

        std::vector<Transaction> transactions;
        std::vector<long long> all_balances;

        std::vector<int> debtors;
        std::vector<int> creditors;

        std::vector<std::vector<int>> graph;
        std::vector<int> debtors_nedges;
        std::vector<long long> creditors_target;
        std::vector<long long> creditors_current;

        void SelectTypes();
        void CreateGraph();
        void FillCreditorsInfo();
        void FirstSolution();
        void ApplyMove(Move move);
        void CalculateError();
        void BuildFirstSolution();
        void CountEdges();

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

        void MorphIntoNeighbour();
        void MorphBack();

        long long Fitness();
};
