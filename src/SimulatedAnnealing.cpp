#include "SimulatedAnnealing.hpp"

#include <cstdio>

using namespace std;


SimulatedAnnealing::SimulatedAnnealing(
    Temperature temperature,
    Solution* initial_solution
):
    temperature(temperature),
    initial_solution(initial_solution),
    // journal(journal),
    accepted_global(0)
{}

SimulatedAnnealing::~SimulatedAnnealing() {
    // delete journal;
    delete initial_solution;
}

Solution* SimulatedAnnealing::TresholdAccepting() {
    double p = 0;
    Solution* best_solution = new Solution(initial_solution);
    Solution* solution = initial_solution;
    printf("temperature: %f\n", temperature.GetTemperature());
    while (temperature.BiggerThanZero()) {
        double q = DBL_MAX;
        while (p < q) {
            q = p;
            p = ComputeBatch(solution, &best_solution);
        }
        temperature.Decrease();
        // printf("solution accepted, fitness: %lld, error: %lld, nedges: %lld\n", solution->Fitness(), solution->GetError(), solution->GetNEdges());
    }
    return best_solution;
}

double SimulatedAnnealing::ComputeBatch(
    Solution* solution, Solution** best_solution
) {
    int iteration_batch = 0;
    int c = 0;
    long long r = 0;
    double temp = temperature.GetTemperature();
    while (c < L*solution->GetNPeople() && iteration_batch++ < STOP) {
        long long fitness = solution->Fitness();
        solution->MorphIntoNeighbour();
        
        if (solution->Fitness() < (*best_solution)->Fitness()) {
            delete *best_solution;
            *best_solution = new Solution(solution);
        }
            
        if (solution->Fitness() <= fitness + temp) {  // Solution gets accepted
            c++;
            accepted_global++;
            r += solution->Fitness();
        } else
            solution->MorphBack();
    }
    return (double)r / c;
}

