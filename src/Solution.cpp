#include "Solution.hpp"

#include <cstdio>
using namespace std;


Transaction::Transaction(int debtor, int creditor, int amount):
    debtor(debtor), creditor(creditor), amount(amount)
{}

Move::Move(Transaction substract, Transaction add):
    substract(substract), add(add) 
{}

Solution::Solution(int npeople, vector<long long> all_balances): 
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

void Solution::CreateGraph() {
    debtors_nedges.resize(debtors.size());
    graph.resize(debtors.size());
    for (int i=0; i<(int)debtors.size(); i++) {
        graph.resize(creditors.size());
    } 
}

void Solution::FirstSolution() {
    BuildFirstSolution();
    CalculateError();
    CountEdges();
}

void Solution::BuildFirstSolution() {
    int div = creditors.size() / debtors.size();
    for (int i = 0; i<(int)debtors.size(); i++) {
        int j = div * i;
        int money = all_balances[debtors[i]];
        while (money > 0) {
            graph[i][j] += unit;
            creditors_current[j] += unit;
            debtors_nedges[i]++;
            money -= unit;
            j++;
            j %= creditors.size();
        }
        all_balances[debtors[i]] = 0;
    }
}

void Solution::CalculateError() {
    error = 0;
    for (int i=0; i<(int)creditors.size(); i++) {
       error += abs(creditors_target[i] - creditors_current[i]);
    } 
}

void Solution::CountEdges() {
    nedges = 0; 
    for (int i=0; i<(int)debtors.size(); i++) {
        nedges += debtors_nedges[i]; 
    }
}

void Solution::MorphIntoNeighbour() {
    int debtor = rand() % (int)debtors.size();
    int creditor = rand() % (int)creditors.size();
    int creditor2 = rand() % (int)creditors.size();
    long long amount = (rand() % (graph[debtor][creditor] / unit + 1)) * unit;
    while (creditor == creditor2)
        creditor2 = rand() % (int)creditors.size();
    while (amount == 0) 
        amount = (rand() % ((graph[debtor][creditor] / unit) + 1)) * unit;
   
    Transaction add(debtor, creditor, amount);
    Transaction substract(debtor, creditor2, amount);
   
    back_move = new Move(substract, add);
    Move move(add, substract);
    ApplyMove(move);
}

void Solution::ApplyMove(Move move) {
    int debtor = move.substract.debtor;
    int creditor = move.substract.creditor;
    int creditor2 = move.add.creditor;
    long long amount = move.add.amount;
    bool creditor2_edge = (graph[debtor][creditor2] > 0);
    error -= abs(creditors_target[creditor] - creditors_current[creditor]);
    graph[debtor][creditor] -= amount;
    graph[debtor][creditor2] += amount;
    error += abs(creditors_target[creditor2] - creditors_current[creditor2]);
    
    if (graph[debtor][creditor] == 0)
        debtors_nedges[debtor]--;
    if (!creditor2_edge)
        debtors_nedges[debtor]++; 
}

void Solution::MorphBack() {
    ApplyMove(*back_move);
}

long long Solution::Fitness() {
    return nedges + error * pow((long long)npeople, 2);
}

void Solution::FillCreditorsInfo() {
    creditors_target.resize(creditors.size());
    creditors_current.resize(creditors.size());
    for (int i = 0; i < (int)creditors.size(); i++) {
        creditors_target[i] = all_balances[creditors[i]];
        creditors_current[i] = 0;
    }
}

void Solution::SelectTypes() {
    for (int i=0; i<npeople; i++) {
        if (all_balances[i] < 0)
            debtors.push_back(i);
        else if (all_balances[i] > 0)
            creditors.push_back(i);
    }
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
