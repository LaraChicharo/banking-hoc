#pragma once

#include "Constraints.hpp"
#include "Solution.hpp"
#include <cmath>


/// @brief Represents a temperature.
class Temperature {
    private:
        /// actual numerical value
        double temperature;
        /// zero. Used to check if the temperature is small enough
        double virtual_zero;
        /// number of cities involved in the problem
        int instance_size;
        /// rate in which the temperature is going to decrease
        double decrease_rate;
        
        /// @brief Binary search to check wether or not a temperature is 
        /// good or not.
        /// @param solution the solution to work with
        /// @param T1 lowest temperature on the range of search
        /// @param T2 highest temperature on the range of search
        /// @param P  Treshold of accepted percentage of solutions
        double BinarySearch(Solution* solution, double T1, double T2, double P);
        /// @brief Given a numerical temperature and a solution, it calculates
        /// whats the percentage of accepted solutions under this conditions.
        /// @param solution the solution to work with
        /// @param temp the numerical temperature to test
        double AcceptedPercentage(Solution* solution, double temp);
        double InitialTemperature(
            Solution* solution,
            double initial_temp,
            double P
        );

    public:
        /// @brief Constructor.
        /// @param solution initial solution
        Temperature(Solution* solution);

        /// @brief Returns the numerical temperature.
        double GetTemperature();
        /// @brief Checks if the temperature is higher than the virtual zero.
        /// @return true if its bigger than zero, false otherwise.
        bool BiggerThanZero();
        /// @brief Decreases the temperature by decrease_rate.
        void Decrease();
};
