#include "BipartiteMatching.hpp"

using namespace std;


BipFullGraph::BipFullGraph(Solution* solution): solution(solution) {
    npeople = solution->GetNPeople();
    ghostid = npeople;
    SetVertices(solution->GetDebtors(), solution->GetCreditors());
    SetEdges();
}

void BipFullGraph::SetEdges() {
    edges.resize(npeople + 1);
    for (int i=0; i<npeople + 1; i++) {
        edges[i].resize(npeople + 1);
    }
    for (int debtorid : debtors) {
        long long debtr_balance = 0;
        if (debtorid != ghostid)
            debtr_balance = solution->GetBalance(debtorid);
        for (int creditorid : creditors) {
            if (creditorid != ghostid && debtorid != ghostid) {
                long long credr_balance = solution->GetBalance(creditorid);
                long long ind_error = abs(credr_balance - debtr_balance);
                edges[debtorid][creditorid] = MAXERROR - ind_error;
            } else {
                edges[debtorid][creditorid] = 0;
            }
        }
    }
}

void BipFullGraph::SetVertices(
    vector<int> debtors, vector<int> creditors
) {
    int sized = debtors.size();
    int sizec = creditors.size();

    if (sized > sizec) {
        for (int i=0; i< sized - sizec; i++)
            creditors.push_back(ghostid);
    } else {
        for (int i=0; i< sizec - sized; i++)
            debtors.push_back(ghostid); 
    }
    this->debtors = debtors;
    this->creditors = creditors;
}

long long BipFullGraph::Get(int debtorid, int creditorid) {
    return edges[debtorid][creditorid];
}


BipartiteMatching::BipartiteMatching(
    Solution* solution): solution(solution
) {
    graph = new BipFullGraph(solution);
}
