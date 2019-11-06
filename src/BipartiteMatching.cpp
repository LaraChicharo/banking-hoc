#include "BipartiteMatching.hpp"

using namespace std;


BipFullGraph::BipFullGraph(Solution* solution): solution(solution) {
    debtors_size = solution->GetDebtors().size();
    creditors_size = solution->GetCreditors().size();
    nside = max(debtors_size, creditors_size);
    SetVertices(solution->GetDebtors(), solution->GetCreditors());
    SetEdges();
}

void BipFullGraph::SetEdges() {
    edges.resize(nside);
    for (int i=0; i < nside; i++) {
        edges[i].resize(nside);
    }
    for (int i=0; i < nside; i++) {
        for (int j=0; j < nside; j++) {
            if (i >= debtors_size || j >= creditors_size) {
                edges[i][j] = MAXERROR;
            } else {
                double credr_balance = solution->GetBalance(creditors[j]); 
                double debtr_balance = solution->GetBalance(debtors[i]); 
                double err = fabs(fabs(credr_balance) - fabs(debtr_balance));
                edges[i][j] = err;
            }
        }
    }
}

void BipFullGraph::SetVertices(
    vector<int> debtors, vector<int> creditors
) {
    this->debtors = debtors;
    this->creditors = creditors;
}


BipartiteMatching::BipartiteMatching(
    Solution* solution): solution(solution
) {
    graph = new BipFullGraph(solution);
}

double BipartiteMatching::Solve() {
    HungarianAlgorithm ha;
    vector<int> pairings;
    double error = ha.Solve(graph->edges, pairings);
    for (int i=0; i<(int)pairings.size(); i++) {
        cout << "(" << solution->GetDebtors()[i] <<
            ", " << solution->GetCreditors()[pairings[i]] << ")";
    }
    return error;
}
