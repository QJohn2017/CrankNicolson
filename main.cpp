#include <iostream>
#include <complex>
#include <fstream>

#include "TridiagonalMatrix.h"
#include "simulation.h"

#include "potentialobservable.h"
#include "properbilityoberservable.h"

#include "linearhamiltonian.h"
#include "nonlinearhamiltonian.h"

#include "gaussianwave.h"

#include "scriptloader.h"

#include "simulationexecutor.h"

using namespace std;

double V(double x) {
    return 0;
    /*if (x < 0.300 || x > 0.700) {
        return 10 * 10^5;
    }
    return 0;

    /*if (x > 0.620 && x < 0.640) {
        return 2.0 * 10e5; //1.8 * 10e5
    }*/

    //return pow(x - 0.5, 2) * 8;
    //Nette Potentiale
    //((x - 520)) * ((x - 520)) * 45;
    //return (pow(x - 0.5, 2) - pow(x - 0.5, 4));
    //return 0;
}

int main() {
    /*const unsigned int iterations = 1000;
    const unsigned int count = 1000;
    const double dx = 0.0005;
    const double dt = 10e-8; //10e-8;*/

    SimulationExecutor exec("/home/tim/Dokumente/Projects/CrankNicolson/build-CrankNicolson-Desktop-Default/simulation.json");    
    //const double lambda = dt / (2 * dx * dx);

    /*SimulationParameter params(dx, dt, iterations, count);
    Simulation sim(params, std::shared_ptr<ComplexHamiltonianSolver>(
                       new NonLinearHamiltonianSolver<std::complex<double>>(params, [] (double x) { return 0; }, 0.01)));
    ScriptExecutor(sim, "/home/tim/Dokumente/Projects/CrankNicolson/build-CrankNicolson-Desktop-Default/scripts");*/
    //sim.addWave(std::shared_ptr<ComplexWave>(new GaussianWave<std::complex<double>>(50, 400, 50000)));
    //sim.addWave(std::shared_ptr<ComplexWave>(new GaussianWave<std::complex<double>>(10, 600, -50000)));
    //sim.addFilter(new PotentialObservable(std::cout, V));
    //sim.addFilter(new ProperbilityOberservable(std::cout));
    return 0;
}

