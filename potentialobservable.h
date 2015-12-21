#pragma once

#include <memory>
#include <ostream>

#include "observable.h"
#include "simulation.h"

/**
 * @brief The PotentialObservable class Observable which filter the Potential and write it to the given outputstream.
 */
class PotentialObservable : public Observable
{
public:
    /**
     * @brief PotentialObservable Constructs a new observable which filters the potential from the simulation at startup.
     * @param output The stream to write the potential into.
     * @param PotentialFunction The potential of the Schrödinger equation.
     */
    PotentialObservable(std::ostream& output, std::function<double (double)> PotentialFunction)
        : Observable(Observable::Startup), func(PotentialFunction) {
         stream.reset(&output, [] (std::ostream* s) {});
    }

    /**
     * @brief #filter Filter the potential.
     * @param sim The current simulation step.
     */
    virtual void filter(const Simulation& sim) {
        for (unsigned int i = 0; i < sim.getAtoms().size(); ++i) {
            (*stream.get()) << static_cast<double>(i) / sim.getAtoms().size()
                            << " "
                            << func(static_cast<double>(i) / sim.getAtoms().size())
                            << "\n";
        }
        (*stream.get()) << "\n\n";
    }

private:
    std::shared_ptr<std::ostream> stream;
    std::function<double (double)> func;
};
