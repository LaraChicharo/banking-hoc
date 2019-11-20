#include "Solution.hpp"

#include <cstdio>


using namespace std;


Transaction::Transaction(int debtor, int creditor, int amount):
    debtor(debtor), creditor(creditor), amount(amount)
{}


Move::Move(Transaction substract, Transaction add):
    substract(substract), add(add) 
{}


Solution::Solution(
    int npeople, vector<long long> all_balances
): 
    npeople(npeople),
    unit(1),
    error(0), 
    nedges(0),
    all_balances(all_balances)
{
    SelectTypes();
    CreateGraph();
    FirstSolution();
}

Solution::Solution(
    Solution* solution
) {
    npeople           = solution->GetNPeople();
    unit              = solution->GetUnit();
    error             = solution->GetError();
    nedges            = solution->GetNEdges();
    all_balances      = solution->GetAllBalances();
    transactions      = solution->GetTransactions();
    debtors_nedges    = solution->GetDebtorsNEdges();
    creditors_target  = solution->GetCreditorsTarget();
    creditors_current = solution->GetCreditorsCurrent();
    debtors           = solution->GetDebtors();
    creditors         = solution->GetCreditors();
    graph             = solution->GetGraph();
}

void Solution::SelectTypes() {
    for (int i=0; i<npeople; i++) {
        if (all_balances[i] < 0)
            debtors.push_back(i);
        else if (all_balances[i] > 0)
            creditors.push_back(i);
    }
}

void Solution::CreateGraph() {
    debtors_nedges.resize(debtors.size());
    graph.resize(debtors.size());
    for (int i=0; i<(int)debtors.size(); i++) {
        graph[i].resize(creditors.size());
        for (int j=0; j<(int)creditors.size(); j++)
            graph[i][j] = 0;
    } 
}

void Solution::FirstSolution() {
    BuildFirstSolution();
    FillCreditorsInfo();
    CalculateError();
    CountEdges();
}

void Solution::BuildFirstSolution() {
    for (int i = 0; i<(int)debtors.size(); i++) {
        int j = i % creditors.size();
        graph[i][j] += abs(all_balances[debtors[i]]);
    }
}

void Solution::FillCreditorsInfo() {
    creditors_target.resize(creditors.size());
    creditors_current.resize(creditors.size());
    
    for (int j=0; j < (int)graph[0].size(); j++) {
        for (int i=0; i < (int)graph.size(); i++) {
            creditors_current[j] += graph[i][j];  
        } 
    }
    for (int i = 0; i < (int)creditors.size(); i++) {
        creditors_target[i] = all_balances[creditors[i]];
    }
}

void Solution::CalculateError() {
    error = 0;
    for (int i=0; i<(int)creditors.size(); i++) {
       error += abs(creditors_target[i] - creditors_current[i]);
    } 
}

void Solution::CountEdges() {
    for (int i=0; i<(int)graph.size(); i++) {
        for (int j=0; j<(int)graph[i].size(); j++) {
            if (graph[i][j] > 0) 
                debtors_nedges[i]++;
        } 
    }
    nedges = 0; 
    for (int i=0; i<(int)debtors.size(); i++) {
        nedges += debtors_nedges[i]; 
    }
}

int Solution::GetUnit() {
    return unit;
}

vector<long long> Solution::GetAllBalances() {
    return all_balances;
}

vector<vector<int>> Solution::GetGraph() {
    return graph;
}

vector<int> Solution::GetDebtorsNEdges() {
    return debtors_nedges;
}

vector<long long> Solution::GetCreditorsTarget() {
    return creditors_target;
}

vector<long long> Solution::GetCreditorsCurrent() {
    return creditors_current;
}

vector<int> Solution::GetDebtors() {
    return debtors;
}

vector<int> Solution::GetCreditors() {
    return creditors;
}

int Solution::GetCreditorsSize() {
    return creditors.size();
}

int Solution::GetDebtorsSize() {
    return debtors.size();
}

int Solution::GetNPeople() {
    return npeople;
}

vector<Transaction> Solution::GetTransactions() {
    return transactions;
}

long long Solution::GetNEdges() {
    return nedges;
}

long long Solution::GetError() {
    return error;
}

int Solution::GraphAt(int debtor, int creditor) {
    return graph[debtor][creditor];
}

void Solution::ApplyMove(Move move) {
    int debtor = move.substract.debtor;
    int creditor = move.substract.creditor;
    int creditor2 = move.add.creditor;
    long long amount = move.add.amount;
    if (creditor == creditor2 || amount == 0)
        return;
    bool creditor2_edge = (graph[debtor][creditor2] > 0);
    error -= abs(creditors_target[creditor] - creditors_current[creditor]);
    creditors_current[creditor] -= amount;
    error += abs(creditors_target[creditor] - creditors_current[creditor]);
    graph[debtor][creditor] -= amount;
    graph[debtor][creditor2] += amount;
    error -= abs(creditors_target[creditor2] - creditors_current[creditor2]);
    creditors_current[creditor2] += amount;
    error += abs(creditors_target[creditor2] - creditors_current[creditor2]);
    
    if (graph[debtor][creditor] == 0) {
        nedges--;
        debtors_nedges[debtor]--;
    }
    if (!creditor2_edge) {
        nedges++;
        debtors_nedges[debtor]++; 
    }
}

void Solution::PrintGraph() {
    printf("X :");
    for (int j=0; j<(int)creditors.size(); j++)
        printf(", %d", creditors[j]);
    printf("\n");
   
    for (int i=0; i<(int)graph.size(); i++) {
        printf("%d :", debtors[i]);
        for (int j=0; j<(int)graph[i].size(); j++) {
            printf(", %d", graph[i][j]);
        }
        printf("\n");
    }
}

