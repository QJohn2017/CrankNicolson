#pragma once

#include "observable.h"
#include "simulation.h"

#include <ostream>
#include <memory>

/**
 * @brief The ProperbilityOberservable class is an observable, which filters the properbility of the wave function for every step.
 */
class ProperbilityOberservable : public Observable
{
public:
    /**
     * @brief ProperbilityOberservable Construct a new Oberservable to filter the properbility of the wave.
     * @param output The stream to write the data into.
     */
    ProperbilityOberservable(std::ostream& output)
        : Observable(Observable::Iteration) {
        stream.reset(&output, [] (std::ostream* s) {});
    }

    /**
     * @brief #filter Filter the potential.
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
    std::complex<double> greenFunction(const Simulation& sim, double energy) {
        ComplexTridiagonalMatrix mat = sim.getSolver()->getHamiltonianMatrix();
        std::complex<double> x = energy - mat(ComplexTridiagonalMatrix::Diagonal, mat.getSize() - 1);

        for (unsigned int i = mat.getSize() - 2; i > 0; --i) {
            x = energy - mat(ComplexTridiagonalMatrix::Diagonal, i) -  mat(ComplexTridiagonalMatrix::Upper, i) *  mat(ComplexTridiagonalMatrix::Upper, i) / x;
        }
        return std::complex<double>(1.0, 0) / x;
    }

    std::shared_ptr<std::ostream> stream;
};


/**
 * @brief The RealProperbilityOberservable class is an observable, which filters
 *        the real part of the properbility from the wave function for every step.
 */class RealProperbilityOberservable : public Observable
{
public:
    /**
     * @brief RealProperbilityOberservable construct a new oberservable to filter
     *        the real part of the properbility from the wave.
     * @param output The stream to write the data into.
     */
    RealProperbilityOberservable(std::ostream& output)
        : Observable(Observable::Iteration) {
        stream.reset(&output, [] (std::ostream* s) {});
    }

    /**
     * @brief #filter Filter the real part of the proberbility from the wave.
     * @param sim The current simulation step.
     */
    virtual void filter(const Simulation& sim) {
        ComplexVector v = sim.getAtoms();
        for (unsigned int i = 0; i < sim.getAtoms().size(); ++i) {
            (*stream.get()) << static_cast<double>(i) / v.size()
                            << " "
                            << v(i).real()
                            << "\n";
        }

        (*stream.get()) << "\n\n";
    }

private:
    std::shared_ptr<std::ostream> stream;
};


/**
 * @brief The ImaginaryProperbilityOberservable class is an observable, which filters
 *        the imaginary part of the properbility from the wave function for every step.
 */
class ImaginaryProperbilityOberservable : public Observable
{
public:
    /**
     * @brief ImaginaryProperbilityOberservable construct a new oberservable to filter
     *        the imaginary part of the properbility from the wave.
     * @param output The stream to write the data into.
     */
    ImaginaryProperbilityOberservable(std::ostream& output)
        : Observable(Observable::Iteration) {
        stream.reset(&output, [] (std::ostream* s) {});
    }

    /**
     * @brief #filter Filter the imaginary part of the properbility of the wave.
     * @param sim The current simulation step.
     */
    virtual void filter(const Simulation& sim) {
        ComplexVector v = sim.getAtoms();
        for (unsigned int i = 0; i < sim.getAtoms().size(); ++i) {
            (*stream.get()) << static_cast<double>(i) / v.size()
                            << " "
                            << v(i).imag()
                            << "\n";
        }

        (*stream.get()) << "\n\n";
    }

private:
    std::shared_ptr<std::ostream> stream;
};
