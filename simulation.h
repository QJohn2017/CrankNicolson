#pragma once

#include <vector>
#include <complex>
#include <memory>

#include "Vector.h"
#include "wave.h"
#include "observable.h"
#include "hamiltonian.h"
#include "TridiagonalMatrix.h"
#include "SimulationParameter.h"

typedef TridiagonalMatrix<std::complex<double>> ComplexTridiagonalMatrix;
typedef HamiltonianSolver<std::complex<double>> ComplexHamiltonianSolver;
typedef Vector<std::complex<double>> ComplexVector;
typedef Wave<std::complex<double>> ComplexWave;

/**
 * @brief The Simulation class Main class for the simulation which glue all together.
 *        This class hold the atoms and the equation solver and all filters.
 *        It also does the iteration and calls the filter methods of the Observables.
 *        This class its basicly design to work like a sandbox with bounds.
 */
class Simulation
{
public:
    /**
     * @brief Simulation The constructor of the class which sets the current solver and set the
     *                   simulation parameter
     * @param params The simulation paramter
     * @param hamiltonian The solver which solves the schrödinger equation
     */
    Simulation(SimulationParameter params, std::shared_ptr<ComplexHamiltonianSolver> hamiltonian);
    ~Simulation();

    /**
     * @brief run Runs the simulation and call the filter method of the Observables
     */
    void run();

    /**
     * @brief setSolver Sets the current solver of the simulation
     * @param solver The solver for the schrödinger equation
     */
    void setSolver(ComplexHamiltonianSolver* solver);

    /**
     * @brief getSolver return the solver for the current simulation.
     * @return The solver of the simulation
     */
    ComplexHamiltonianSolver* getSolver() const;

    /**
     * @brief setSolver Sets the current solver of the simulation
     * @param solver The solver for the schrödinger equation
     */
    void setSolver(std::shared_ptr<ComplexHamiltonianSolver> solver);

    /**
     * @brief addWave Add a wave to the
     * @param wave
     */
    void addWave(const ComplexWave* wave);

    /**
     * @brief addFilter Add a Observable to the simulation which gets called in the run method
     * @param filter The Observable to add
     */
    void addFilter(Observable* filter);

    /**
     * @brief addFilter Add a Observable to the simulation which gets called in the run method
     * @param filter The Observable to add
     */
    void addFilter(std::shared_ptr<Observable> filter);

    /**
     * @brief getParameter return the current SimulationParamter of the simulation
     * @return The simulation paramters with timestep and resolution
     */
    SimulationParameter getParameter() const { return parameter; }

    /**
     * @brief getIteration returns the current iteration index
     * @return The iteration index
     */
    int getIteration() const { return currentIteration; }

    /**
     * @brief getAtoms get the atoms in the current simulation in a vector
     * @return The atoms in the simulation in a vector
     */
    ComplexVector getAtoms() const { return atoms; }
protected:
    ComplexVector atoms;
    std::shared_ptr<ComplexHamiltonianSolver> hamiltonian;
    std::vector<std::shared_ptr<Observable>> filter;
    SimulationParameter parameter;
    int currentIteration;
};
