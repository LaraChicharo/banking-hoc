#include "Temperature.hpp"

#include <cstdio>

using namespace std;


Temperature::Temperature(Solution* solution):
    virtual_zero(VIRTUAL_ZERO),
    decrease_rate(TEMPERATURE_DECAY)
{
    instance_size = solution->GetNPeople() * 2;
    Solution* tempsol = new Solution(solution);
    // temperature = InitialTemperature(tempsol, INITIAL_TEMPERATURE, P);
    temperature = solution->GetNPeople() * 500;
    delete tempsol;
}

double Temperature::InitialTemperature(
    Solution* solution,
    double initial_temp,
    double P
) {
    double p = AcceptedPercentage(solution, initial_temp);
    double T1;
    double T2;
    if (abs(P - p) <= virtual_zero) {
        return initial_temp;
    } else if (p < P) {
        while (p < P) {
            initial_temp *= 2;
            p = AcceptedPercentage(solution, initial_temp);
        }
        T1 = initial_temp / 2;
        T2 = initial_temp;
    } else {
        while (p > P && initial_temp > 0) {
            initial_temp /= 2;
            p = AcceptedPercentage(solution, initial_temp);
        }
        T1 = initial_temp;
        T2 = 2 * initial_temp;
    }
    return BinarySearch(solution, T1, T2, P);
}

double Temperature::BinarySearch(
    Solution* solution, double T1, double T2, double P
) {
    double Tm = (T1 + T2)/2;
    if (T2 - T1 < virtual_zero)
        return Tm;
    double p = AcceptedPercentage(solution, Tm);
    if (abs(P - p) < virtual_zero) {
        return Tm;
    }
    if (p > P)
        return BinarySearch(solution, T1, Tm, P);
    else
        return BinarySearch(solution, Tm, T2, P);
}

double Temperature::AcceptedPercentage(Solution* solution, double temp) {
    int c = 0;
    for (int i = 1; i <= instance_size; i++) {
        double fitness = solution->Fitness();
        solution->MorphIntoNeighbour();
        double new_fitness = solution->Fitness();
        if (new_fitness <= fitness + temp)
            c++;
        else
            solution->MorphBack();
    }
    return ((double)c / instance_size);
}

double Temperature::GetTemperature() {
    return temperature;
}

bool Temperature::BiggerThanZero() {
    return temperature > virtual_zero;
}

void Temperature::Decrease() {
    this->temperature *= decrease_rate;
}
