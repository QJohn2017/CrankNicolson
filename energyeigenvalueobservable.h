#pragma once

#include <ostream>
#include <memory>

#include "observable.h"
#include "TridiagonalMatrix.h"
#include "simulation.h"

/**
 * @brief The EnergyEigenvalueObservable class
 */
class EnergyEigenvalueObservable : public Observable
{
public:
    /**
     * @brief EnergyEigenvalueObservable construct a new Oberservable to filter the energy eigenvalues from the hamiltonian
     * @param output The stream to write the data into
     */
    EnergyEigenvalueObservable(std::ostream& output)
        : Observable(Observable::Startup) {
        stream.reset(&output, [] (std::ostream* s) {});
    }

    /**
     * @brief filter Filter the energy eigenvalues from the hamiltonian
     * @param sim The current simulation step
     */
    virtual void filter(const Simulation& sim) {
        const ComplexTridiagonalMatrix ham = sim.getSolver()->getHamiltonianMatrix();
        TridiagonalMatrix<double> mat(ham.getSize());
        for (unsigned int i = 0; i < mat.getSize(); ++i) {
            mat(TridiagonalMatrix<double>::Diagonal, i) = ham(ComplexTridiagonalMatrix::Diagonal, i).real();
            mat(TridiagonalMatrix<double>::Upper, i) = ham(ComplexTridiagonalMatrix::Upper, i).real();
            mat(TridiagonalMatrix<double>::Lower, i) = ham(ComplexTridiagonalMatrix::Lower, i).real();
        }

        const Vector<double> eigenvalues = mat.getEigenvalues<double>();
        for (unsigned int i = 0; i < eigenvalues.size(); ++i) {
            (*stream.get()) << i
                            << " "
                            << eigenvalues(i)
                            << "\n";
        }

        (*stream.get()) << "\n\n";
    }

private:
    std::shared_ptr<std::ostream> stream;
};
