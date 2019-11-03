#include "Reader.hpp"


using namespace std;


Reader::Reader(int argc, char* argv[]): argc(argc) {
    all_balances.resize(MAXPEOPLE);
    BuildInput(argc, argv);
    CheckInput();
    ParseInput();
    OpenFile();
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
    npeople = 0;
    while (getline(filestream, line)) {
        npeople++;

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

vector<long long> Reader::GetAllBalances() {
    return all_balances;
}

int Reader::GetNPeople() {
    return npeople;
}
