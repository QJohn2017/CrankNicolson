#pragma once

#include "observable.h"
#include "simulation.h"

#include <ostream>
#include <memory>

/**
 * @brief The ProperbilityOberservable class Observable which filters the properbility of the wave function for every step
 */
class ProperbilityOberservable : public Observable
{
public:
    /**
     * @brief ProperbilityOberservable construct a new Oberservable to filter the properbility of the wave
     * @param output The stream to write the data into
     */
    ProperbilityOberservable(std::ostream& output)
        : Observable(Observable::Iteration) {
        stream.reset(&output, [] (std::ostream* s) {});
    }

    /**
     * @brief filter Filter the potential
     * @param sim The current simulation step
     */
    virtual void filter(const Simulation& sim) {
        ComplexVector v = sim.getAtoms();
        for (unsigned int i = 0; i < sim.getAtoms().size(); ++i) {
            (*stream.get()) << static_cast<double>(i) / v.size()
                            << " "
                            << std::abs(v(i))
                            << "\n";
        }
        (*stream.get()) << "\n\n";
    }

private:
    std::shared_ptr<std::ostream> stream;
};
