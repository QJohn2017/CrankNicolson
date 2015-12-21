#pragma once

#include "utilitys.h"

/**
 * @brief The SimulationParamter struct holds the parameter to run the simulation with.
 */
struct SimulationParameter {
    /**
     * @brief SimulationParameter constructor for the default parameters.
     * @param Dx the resolution of the simulation.
     * @param Dt the time step size.
     * @param Iterations the count of the solving equations.
     * @param AtomCount the count of atoms in the sandbox.
     */
    SimulationParameter(const double Dx,
                        const double Dt,
                        const double Mass,
                        const unsigned int Iterations,
                        const unsigned int AtomCount)
        : dx(Dx), dt(Dt), mass(Mass), lambda(dt / (2 * mass * dx * dx)),
          iterations(Iterations), atomCount(AtomCount) {
    }

    const double dx; //! The delta space
    const double dt; //! The delta time
    const double mass; //! The mass of an atom
    const double lambda; //! The computed lambda from the dx, dt and the mass parameter
    const unsigned int iterations; //! The iteration count for the simulation
    const unsigned int atomCount; //! The atom count in the simulation
};
