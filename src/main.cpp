#include <vector>

#include "Reader.hpp"
#include "Solution.hpp"

using namespace std;

int main(int argc, char* argv[]) {
    Reader* reader = new Reader(argc, argv);
    int npeople = reader->GetNPeople();
    vector<long long> all_balances = reader->GetAllBalances();
    int ss = 0;
    for (int i=0; i<npeople; i++) {
        cout << "i: " << all_balances[i] << " ";
        ss += all_balances[i];
    }
    cout << endl;
    cout << "ss: " << ss << endl;

    Solution* solution = new Solution(npeople, all_balances);
}
