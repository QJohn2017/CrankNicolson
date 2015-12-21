#pragma once

#include "observable.h"
#include "simulation.h"


class StreamDensity : public Observable
{
public:
    StreamDensity(std::ostream& output)
        : Observable(CheckTime::Iteration) {
        stream.reset(&output, [] (std::ostream* s) {});
    }

    /**
     * @brief filter
     * @param sim
     *
     * j = h/m * Im(p* d/dx p)
     * grad (p) = (p(x + dx) - p(x)) / dx
     * p(x)* (A p(x) - p(x)) / dx
     * (p(x)* A p(x) - p(x)*p(x)) / d
     *
     * => (<p|A|p> - <p|p>) / d
     * => j = h/(d*m) * Im(<p|A|p> - <p|p>)
     * A = (1 - l*H)^(-1) * (1 + l*H)
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
