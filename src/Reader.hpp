#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <iostream>

#include "Constraints.hpp"



class Reader {
    private:
        std::vector<long long> negatives;
        std::vector<long long> positives;
        long long all_balances[MAXPEOPLE];
        int size;
        
        int argc;
        std::vector<std::string> input_strings;
        
        std::string sourcefile;

        void BuildInput(int argc, char* argv[]);
        void ParseInput();
        void CheckInput();
        void OpenFile();
        void BuildNegativesPositives();

    public:
        Reader(int argc, char* argv[]);

        std::vector<long long> GetNegatives();
        std::vector<long long> GetPositives();
};
