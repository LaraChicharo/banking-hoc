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
    FirstBackMove();
}

Solution::Solution(Solution* solution) {
    npeople           = solution->GetNPeople();
    unit              = solution->GetUnit();
    error             = solution->GetError();
    nedges            = solution->GetNEdges();
    back_move         = solution->GetBackMove();
    all_balances      = solution->GetAllBalances();
    debtors_nedges    = solution->GetDebtorsNEdges();
    creditors_current = solution->GetCreditorsCurrent();
    creditors_target  = solution->GetCreditorsTarget();
    debtors           = solution->GetDebtors();
    creditors         = solution->GetCreditors();
    graph             = solution->GetGraph();
    MAXNEDGES         = solution->GetMaxNEdges();
    MINNEDGES         = solution->GetMinNEdges();
    MAXERROR          = solution->GetMaxError();
}

Move* Solution::GetBackMove() {
    return back_move;
}

void Solution::FirstBackMove() {
    Transaction a(0, 0, 0);
    Transaction b(0, 0, 0);
    back_move = new Move(a, b);
}

void Solution::CalculateBounds() {
    MAXNEDGES = creditors.size() * debtors.size(); 
    MINNEDGES = debtors.size();
    MAXERROR = 0;
    long long mincred = 1e18;
    for (int i=0; i<(int)creditors.size(); i++) {
        mincred = min(mincred, creditors_target[i]); 
        MAXERROR += creditors_target[i];
    }
    MAXERROR -= mincred;
    long long debtsum = 0;
    for (int i=0; i<(int)debtors.size(); i++) {
        debtsum += abs(all_balances[debtors[i]]); 
    }
    MAXERROR += abs(mincred - debtsum);
}

long long Solution::GetMaxNEdges() {
    return MAXNEDGES;
}

long long Solution::GetMinNEdges() {
    return MINNEDGES;
}

long long Solution::GetMaxError() {
    return MAXERROR;
}

long long Solution::GetNEdges() {
    return nedges;
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
    CalculateBounds();
    CalculateError();
    CountEdges();
}

void Solution::BuildFirstSolution() {
    for (int i = 0; i<(int)debtors.size(); i++) {
        int j = i % creditors.size();
        graph[i][j] += abs(all_balances[debtors[i]]);
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

void Solution::MorphIntoNeighbour() {
    int debtor = rand() % (int)debtors.size();
    int creditor = rand() % (int)creditors.size();
    int creditor2 = rand() % (int)creditors.size();
    int all = rand() % 4;
    long long amount;
    if (all == 0)
        amount = (rand() % (graph[debtor][creditor]/unit + 1)) * unit;
    else
        amount = graph[debtor][creditor]/unit;
   
    Transaction add(debtor, creditor, amount);
    Transaction substract(debtor, creditor2, amount);

    delete back_move;
    back_move = new Move(substract, add);
    Move move(add, substract);
    ApplyMove(move);
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

void Solution::MorphBack() {
    ApplyMove(*back_move);
}

double Solution::Fitness() {
    double nedges_fitness = NEdgesFitness();    
    double error_fitness = ErrorFitness();
    return error_fitness * pow(npeople, 2) +
        nedges_fitness * pow(npeople, 1.25);
}

double Solution::ErrorFitness() {
    return (double)error / MAXERROR;
}

double Solution::NEdgesFitness() {
    return ((double)nedges - MINNEDGES)/(MAXNEDGES - MINNEDGES);
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

long long Solution::GetError() {
    return error;
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

