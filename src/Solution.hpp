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
        std::vector<long long> all_balances;

        std::vector<Transaction> transactions;
        
        std::vector<int> debtors_nedges;
        std::vector<long long> creditors_target;
        std::vector<long long> creditors_current;

        std::vector<int> debtors;
        std::vector<int> creditors;

        std::vector<std::vector<int>> graph;
        
        void SelectTypes();
        void CreateGraph();
        void FirstSolution();
        
        void FillCreditorsInfo();
        void CalculateError();
        void BuildFirstSolution();
        void CountEdges();
        
        std::vector<std::vector<int>> GetGraph();
        std::vector<int> GetDebtorsNEdges();
        std::vector<long long> GetCreditorsCurrent();

    public:
        Solution(int npeople, std::vector<long long> all_balances);
        Solution(Solution* solution);
    
        int GetUnit();
        std::vector<long long> GetCreditorsTarget();
        std::vector<long long> GetAllBalances();
        std::vector<int> GetDebtors();
        std::vector<int> GetCreditors();
        
        int GetCreditorsSize();
        int GetDebtorsSize();
       
        int GetNPeople();
        std::vector<Transaction> GetTransactions(); 
        long long GetNEdges();
        long long GetError();
        int GraphAt(int debtor, int creditor); 
        
        void ApplyMove(Move move);
        
        void PrintGraph();

};
