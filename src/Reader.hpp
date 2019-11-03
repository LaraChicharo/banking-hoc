#pragma once

#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <iostream>

#include "Constraints.hpp"


class Reader {
    private:
        std::vector<long long> all_balances;
        int npeople;
        
        int argc;
        std::vector<std::string> input_strings;
        
        std::string sourcefile;

        void BuildInput(int argc, char* argv[]);
        void ParseInput();
        void CheckInput();
        void OpenFile();

    public:
        Reader(int argc, char* argv[]);
        
        std::vector<long long> GetAllBalances(); 
        int GetNPeople();
};
