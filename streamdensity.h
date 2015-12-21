#pragma once

#include "observable.h"
#include "simulation.h"

/**
 * @brief The ProperbilityFluxObservable class calculates the proberbility flux for every simulation step.
 */
class ProperbilityFluxObservable : public Observable
{
public:
    /**
     * @brief ProperbilityFluxObservable calculates the proberbility flux for every step.
     * @param output The output stream to write into.
     */
    ProperbilityFluxObservable(std::ostream& output)
        : Observable(CheckTime::Iteration) {
        stream.reset(&output, [] (std::ostream* s) {});
    }

    /**
     * @brief #filter Calculates the properbility flux for every step.
     * @param sim The current simulation step.
     */
    virtual void filter(const Simulation& sim) {
        const ComplexVector atoms = sim.getAtoms();
        const ComplexVector grad = gradient(atoms, sim);
        const double j = 1.0 / sim.getParameter().mass * (atoms.dot(grad)).imag();
        (*stream.get()) << sim.getIteration() << " " << j << "\n";
    }

private:
    ComplexVector gradient(const ComplexVector& vec, const Simulation& sim) {
        ComplexVector v(vec.size());

        v(0) = (vec(1) - vec(0)) / sim.getParameter().dx;
        for (unsigned int i = 1; i < vec.size() - 1; ++i) {
            v(i) = (vec(i + 1) - vec(i - 1)) / (2 * sim.getParameter().dx);
        }
        v(vec.size() - 1) = (vec(vec.size() - 1) - vec(vec.size() - 2)) / sim.getParameter().dx;

        return v;
    }

    std::shared_ptr<std::ostream> stream;
};
