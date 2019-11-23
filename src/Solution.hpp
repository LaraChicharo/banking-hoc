#pragma once

#include <vector>
#include <cmath>
#include <cstdlib>

#include "Constraints.hpp"

/// @brief Represents a transaction
struct Transaction {
    /// debtor
    int debtor;
    /// creditor
    int creditor;
    /// amount of money
    long long amount;

    /// @brief Constructor.
    Transaction(int debtor, int creditor, int amount);
};

/// @brief a pair of transactions from the same debtor
struct Move {
    /// transaction of substraction
    Transaction substract;
    /// transaction of adddition
    Transaction add;

    /// @brief Constructor.
    Move(Transaction substact, Transaction add);
};

typedef struct Transaction Transaction;
typedef struct Move Move;

/// @brief Represents a solution to an instance of the problem.
class Solution {
    private:
        /// number of people involved
        int npeople;
        /// minimum amount of money that can be transfered
        int unit;
        /// error raw
        long long error;
        /// number of edges
        long long nedges;
        /// the balances of all the people involved
        std::vector<long long> all_balances;

        /// transactions that make the current solution
        std::vector<Transaction> transactions;
        
        /// the amount of edges each debtor has
        std::vector<int> debtors_nedges;
        /// the target amount of money each creditor has
        std::vector<long long> creditors_target;
        /// the amount of money each creditor currently has
        std::vector<long long> creditors_current;

        /// ids of the debtors
        std::vector<int> debtors;
        /// ids of the creditors
        std::vector<int> creditors;

        /// graph representing the transactions
        std::vector<std::vector<int>> graph;
        
        /// @brief Selects wether each person is debtor or creditor.
        void SelectTypes();
        /// @brief Creates the graph.
        void CreateGraph();
        /// @brief Creates the first solution.
        void FirstSolution();
        
        /// @brief Fills the information necesary for the operations.
        /// of the creditors
        void FillCreditorsInfo();
        /// @brief Calculates the total error of the solution.
        void CalculateError();
        /// @brief Builds the first solution.
        void BuildFirstSolution();
        /// @brief Counts the total edges of the solution.
        void CountEdges();
       
        /// @brief Returns the number of debtors of each debtor.
        std::vector<int> GetDebtorsNEdges();
        /// @brief Returns the current amount of money of each creditor.
        std::vector<long long> GetCreditorsCurrent();

    public:
        /// @brief Constructor.
        Solution(int npeople, std::vector<long long> all_balances);
        /// @brief Copy Constructor.
        Solution(Solution* solution);
    
        /// @brief Returns the unit of this instance.
        int GetUnit();
        /// @brief Returns the graph of transactions.
        std::vector<std::vector<int>> GetGraph();
        /// @brief Returns the target money of each creditor.
        std::vector<long long> GetCreditorsTarget();
        /// @brief Returns the balances of all the people.
        std::vector<long long> GetAllBalances();
        /// @brief Returns the debtors.
        std::vector<int> GetDebtors();
        /// @brief Returns the creditors.
        std::vector<int> GetCreditors();
       
        /// @brief Returns the number of creditors.
        int GetCreditorsSize();
        /// @brief Returns the number of debtors.
        int GetDebtorsSize();
      
        /// @brief Returns the number of people involved in the instance.
        int GetNPeople();
        /// @brief Returns the transactions.
        std::vector<Transaction> GetTransactions();
        /// @brief Returns the number of edges in the solution.
        long long GetNEdges();
        /// @brief Returns the raw error.
        long long GetError();
        /// @brief Returns graph[debtor][creditor].
        /// @param debtor   the position of the debtor to consult.
        /// @param creditor the position of the creditor to consult.
        int GraphAt(int debtor, int creditor);
        /// @brief Returns the current balace of a person.
        long long GetBalance(int id);
       
        /// @brief Sets the error of the solution.
        /// @brief error the error of the solution.
        void SetError(long long error);
        /// @brief The debtor debtori pays to the creditor creditori
        /// all of its debt.
        /// @param debtori   the id of the debtor that is going to pay.
        /// @param creditori the id of the creditor that is going to receive.
        void Pay(int debtori, int creditori);
        /// @brief Selects who is creditor and who is debtor.
        void RestartTypes();
        
        /// @brief Makes all of the necesary changes to make the two
        /// transactions that a move implies.
        /// @param move The move to apply.
        void ApplyMove(Move move);
        
        /// @brief Prints the graph of the solution.
        void PrintGraph();

};
