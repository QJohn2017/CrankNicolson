#include "simulation.h"

#include <iostream>

Simulation::Simulation(SimulationParameter params, std::shared_ptr<ComplexHamiltonianSolver> ham)
    : atoms(params.atomCount), hamiltonian(ham), parameter(params) {
}

Simulation::~Simulation() {
}

void Simulation::run() {
    for (auto& it : filter) {
        if (it->check(Observable::Startup))
            it->filter(*this);
    }

    for (unsigned int i = 0; i < parameter.iterations; ++i) {
        atoms = hamiltonian->solve(atoms);
        atoms(0) = atoms(atoms.size() - 1) = 0;

        for (auto& it : filter) {
            if (it->check(Observable::Iteration))
                it->filter(*this);
        }
    }

    for (auto& it : filter) {
        if (it->check(Observable::Cooldown))
            it->filter(*this);
    }
}

void Simulation::setSolver(ComplexHamiltonianSolver* solver) {
    hamiltonian.reset(solver);
}

void Simulation::setSolver(std::shared_ptr<ComplexHamiltonianSolver> solver) {
    hamiltonian = solver;
}

void Simulation::addWave(const ComplexWave* wave) {
    for (unsigned int i = 1; i < atoms.size() - 1; ++i) {
        atoms[i] += wave->getDisplacement(i);
    }
}

void Simulation::addFilter(Observable* fil) {
    filter.push_back(std::shared_ptr<Observable>(fil));
}

void Simulation::addFilter(std::shared_ptr<Observable> fil) {
    filter.push_back(fil);
}
