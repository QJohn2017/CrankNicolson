#pragma once

#include "utilitys.h"

/**
 * @brief The SimulationParamter struct The parameter to run the simulation with.
 */
struct SimulationParameter {
    /**
     * @brief SimulationParameter constructor for the default parameters
     * @param Dx the resolution of the simulation
     * @param Dt the time step size
     * @param Iterations the count of the solving equations
     * @param AtomCount the count of atoms in the sandbox
     */
    SimulationParameter(const double Dx,
                        const double Dt,
                        const double Mass,
                        const unsigned int Iterations,
                        const unsigned int AtomCount)
        : dx(Dx), dt(Dt), mass(Mass), lambda(dt / (2 * mass * dx * dx)),
          iterations(Iterations), atomCount(AtomCount) {
    }

    const double dx;
    const double dt;
    const double mass;
    const double lambda;
    const unsigned int iterations;
    const unsigned int atomCount;
};
