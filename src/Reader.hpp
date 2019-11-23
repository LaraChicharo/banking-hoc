#pragma once

#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <iostream>

#include "Constraints.hpp"

/// @brief Reads the data from the user
class Reader {
    private:
        /// vector containing all the balances of all the people
        std::vector<long long> all_balances;
        /// number of people in the system
        int npeople;
        
        /// number of arguments in the input
        int argc;

        /// input strings
        std::vector<std::string> input_strings;
        /// seeds to run 
        std::vector<int> seeds;
        
        /// path to the file containing the instance of the problem
        std::string sourcefile;
        /// path to the file containing the seeds
        std::string seedsfile;

        /// @brief Reads the input and parses it.
        /// @param argc number of arguments
        /// @param argv the arguments per se
        void BuildInput(int argc, char* argv[]);
        /// @brief parses the input.
        void ParseInput();
        /// @brief Checks wether the input is correct or not.
        void CheckInput();
        /// @brief Reads the file containing the instance of the problem.
        void ReadSourceFile();
        /// @brief Reads the file containing the seeds.
        void ReadSeedsFile();

    public:
        /// @brief Constructor.
        /// @param argc number of arguments.
        /// @param argv arguments per se.
        Reader(int argc, char* argv[]);
        
        /// @brief Returns all the balances of all the people.
        std::vector<long long> GetAllBalances(); 
        /// @brief Returns the number of people in the instance.
        int GetNPeople();
        /// @brief Returns the seeds.
        std::vector<int> GetSeeds();
};
