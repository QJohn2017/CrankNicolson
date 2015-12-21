#pragma once

#include <ostream>
#include <memory>

#include "TridiagonalMatrix.h"
#include "observable.h"
#include "simulation.h"


class ExpectationValueObservable : public Observable
{
public:
    /**
     * @brief EnergyEigenvalueObservable construct a new Oberservable to filter the expectation value
     * @param output The stream to write the data into
     */
    ExpectationValueObservable(std::ostream& output)
        : Observable(Observable::Iteration) {
        stream.reset(&output, [] (std::ostream* s) {});
    }

    /**
     * @brief filter Filter the expectation value from the hamiltonian
     * @param sim The current simulation step
     */
    virtual void filter(const Simulation& sim) {
        const ComplexVector atoms = sim.getAtoms();
        (*stream.get()) << sim.getIteration() << " " << sim.getSolver()->getHamiltonianMatrix().getExpectationValue(atoms).real() << "\n";
    }

private:
    std::shared_ptr<std::ostream> stream;
};
