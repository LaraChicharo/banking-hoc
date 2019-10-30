#include "Reader.hpp"


using namespace std;


Reader::Reader(int argc, char* argv[]): argc(argc) {
    BuildInput(argc, argv);
    CheckInput();
    ParseInput();
    OpenFile();
    BuildNegativesPositives();
}


void Reader::BuildInput(int argc, char* argv[]) {
    for (int i = 0; i < argc; i++) {
        string stringi = "";
        int j = 0;
        while(argv[i][j] != '\0') {
            stringi.push_back(argv[i][j]);
            j++;
        }
        cout << stringi << endl;
        input_strings.push_back(stringi);
    }
}

void Reader::ParseInput() {
    sourcefile = input_strings[1];
}

void Reader::CheckInput() {
   // Nothing as of now
   return;
}

void Reader::OpenFile() {
    ifstream filestream(sourcefile);
    if (filestream.fail()) {
        // trows
        printf("Cant open file\n");
        exit(1);
    }
    
    string line;
    size = 0;
    while (getline(filestream, line)) {
        size++;

        for (int i=0; i<(int)line.size(); i++) {
            if (line[i] == ':' || line[i] == ',')
                line[i] = ' ';
        }
        
        stringstream linestream;
        linestream << line;

        int debtor;
        linestream >> debtor;
    
        int creditor;
        while (linestream >> creditor) {
            int money;
            linestream >> money;

            cout << debtor << " owes " << money << " to " << creditor << endl;

            all_balances[debtor] -= money;
            all_balances[creditor] += money;
        }
    }
}

void Reader::BuildNegativesPositives() {
    for (int i=0; i<size; i++) {
        if (all_balances[i] < 0) {
            negatives.push_back(all_balances[i]);
        } else if (all_balances > 0) {
            positives.push_back(all_balances[i]);
        }
    }
}

vector<long long> Reader::GetNegatives() {
    return negatives;
}

vector<long long> Reader::GetPositives() {
    return positives;
}
