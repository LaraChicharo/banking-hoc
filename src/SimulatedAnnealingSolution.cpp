#include "SimulatedAnnealingSolution.hpp"

#include <cstdio>


using namespace std;


SimulatedAnnealingSolution::SimulatedAnnealingSolution(
    Solution* solution
): 
    solution(solution)
{
    FirstBackMove();
    CalculateBounds();
}

SimulatedAnnealingSolution::SimulatedAnnealingSolution(
    SimulatedAnnealingSolution* sasolution
) {
    solution  = sasolution->GetSolution();
    MAXNEDGES = sasolution->GetMaxNEdges();
    MINNEDGES = sasolution->GetMinNEdges();
    MAXERROR  = sasolution->GetMaxError();
    ERRORMULTIPLIER = sasolution->GetErrorMultiplier();
    EDGESMULTIPLIER = sasolution->GetEdgesMultiplier();
    back_move = sasolution->GetBackMove();
}

void SimulatedAnnealingSolution::CalculateBounds() {
    int npeople = solution->GetNPeople();
    ERRORMULTIPLIER = pow(npeople, 2);
    EDGESMULTIPLIER = pow(npeople, 1.25);
    int creditors_size = solution->GetCreditorsSize();
    int debtors_size = solution->GetDebtorsSize();
    MAXNEDGES = creditors_size * debtors_size; 
    MINNEDGES = max(debtors_size, creditors_size);
    MAXERROR = 0;
    long long mincred = 1e18;
    vector<long long> creditors_target = solution->GetCreditorsTarget();
    for (int i = 0; i < creditors_size; i++) {
        mincred = min(mincred, creditors_target[i]); 
        MAXERROR += creditors_target[i];
    }
    MAXERROR -= mincred;
    long long debtsum = 0;
    vector<long long> all_balances = solution->GetAllBalances();
    vector<int> debtors = solution->GetDebtors();
    for (int i=0; i<(int)debtors.size(); i++) {
        debtsum += abs(all_balances[debtors[i]]); 
    }
    MAXERROR += abs(mincred - debtsum);
}

void SimulatedAnnealingSolution::FirstBackMove() {
    Transaction a(0, 0, 0);
    Transaction b(0, 0, 0);
    back_move = new Move(a, b);
}

long long SimulatedAnnealingSolution::GetErrorMultiplier() {
    return ERRORMULTIPLIER;
}

long long SimulatedAnnealingSolution::GetEdgesMultiplier() {
    return EDGESMULTIPLIER;
}

long long SimulatedAnnealingSolution::GetMaxNEdges() {
    return MAXNEDGES;
}

long long SimulatedAnnealingSolution::GetMinNEdges() {
    return MINNEDGES;
}

long long SimulatedAnnealingSolution::GetMaxError() {
    return MAXERROR;
}

Move* SimulatedAnnealingSolution::GetBackMove() {
    return back_move;
}

Solution* SimulatedAnnealingSolution::GetSolution() {
    return solution;
}

int SimulatedAnnealingSolution::GetNPeople() {
    return solution->GetNPeople();
}

void SimulatedAnnealingSolution::MorphIntoNeighbour() {
    int creditors_size = solution->GetCreditorsSize();
    int debtors_size = solution->GetDebtorsSize();
    int debtor = rand() % debtors_size;
    int creditor = rand() % creditors_size;
    int creditor2 = rand() % creditors_size;
    int unit = solution->GetUnit();
    
    int all = rand() % 4;
    long long amount;
    if (all == 0) {
        amount =
            (rand() %
                (solution->GraphAt(debtor, creditor)/unit + 1)
            ) * unit;
    } else
        amount = solution->GraphAt(debtor, creditor)/unit;
   
    Transaction add(debtor, creditor, amount);
    Transaction substract(debtor, creditor2, amount);

    delete back_move;
    back_move = new Move(substract, add);
    Move move(add, substract);
    solution->ApplyMove(move);
}

void SimulatedAnnealingSolution::MorphBack() {
    solution->ApplyMove(*back_move);
}

double SimulatedAnnealingSolution::Fitness() {
    double nedges_fitness = NEdgesFitness();    
    double error_fitness = ErrorFitness();
    return error_fitness * ERRORMULTIPLIER +
        nedges_fitness * EDGESMULTIPLIER;
}

double SimulatedAnnealingSolution::ErrorFitness() {
    return (double)solution->GetError() / MAXERROR;
}

double SimulatedAnnealingSolution::NEdgesFitness() {
    return (
        (double)solution->GetNEdges() - 
        MINNEDGES)/(MAXNEDGES - MINNEDGES
    );
}

long long SimulatedAnnealingSolution::GetNEdges() {
    return solution->GetNEdges();
}

long long SimulatedAnnealingSolution::GetError() {
    return solution->GetError();
}

void SimulatedAnnealingSolution::PrintGraph() {
    solution->PrintGraph();
}

