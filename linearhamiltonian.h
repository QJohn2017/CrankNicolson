#pragma once

#include <complex>
#include <functional>
#include "hamiltonian.h"

#include "SimulationParameter.h"
#include "utilitys.h"

/**
 * @brief Basic linear Schrödinger equation solver which solves the Crank Nicolson algorithm.
 * The LinearHamiltonianSolver solves the Schrödinger equation with the form
 * \f[
 *      (\frac{P^2}{2m} + V(r))|x(r, t)\rangle = i\hbar \frac{\delta}{\delta t}|x(r,t)\rangle
 * \f]
 * with the \f$V(r)\f$ potential at the position \f$r\f$.
 * The default solver used a left and a right matrix to solve the equation with:
 * \f[
 *      (1 + \frac{it}{2h} H)|x(r,t)\rangle^{n+1} = (1 - \frac{it}{2h} H)|x(r,t)\rangle^{n}
 * \f]
 * with
 * \f[
 *      Left := 1 + \frac{i\Delta t}{2h} H
 * \f]
 * and
 * \f[
 *      Right := 1 - \frac{i\Delta t}{2h} H
 * \f]
 */
template <typename T>
class LinearHamiltonianSolver : public HamiltonianSolver<T>
{
public:
    /**
     * @brief LinearHamiltonianSolver construct the Hamiltonian matrix from the SimulationParamter and a PotentialFunction
     * @param Parameter The Parameter with time step and resolution
     * @param PotentialFunction The potential function which must be a function of the form:
     *                          \f$ f:[0,1]\rightarrow\mathbb{R} \f$
     */
    LinearHamiltonianSolver(SimulationParameter Parameter,
                            std::function<double (double)> PotentialFunction)
        : parameter(Parameter), potentialFunction(PotentialFunction) {

        hamiltonian = TridiagonalMatrix<T>(parameter.atomCount);
        for (unsigned int i = 0; i < parameter.atomCount; ++i) {
            hamiltonian(TridiagonalMatrix<T>::Lower, i) = std::complex<double>(-1.0, 0);
            hamiltonian(TridiagonalMatrix<T>::Diagonal, i) = std::complex<double>( 2.0 + 2.0 * potentialFunction(static_cast<double>(i) / parameter.atomCount), 0);
            hamiltonian(TridiagonalMatrix<T>::Upper, i) = std::complex<double>(-1.0, 0);
        }

        left = TridiagonalMatrix<T>::identity(parameter.atomCount, std::complex<double>(1.0, 0)) +
                hamiltonian * std::complex<double>(0, parameter.lambda);
        right = TridiagonalMatrix<T>::identity(parameter.atomCount, std::complex<double>(1.0, 0)) -
                hamiltonian * std::complex<double>(0, parameter.lambda);
    }

    /**
     * @brief #solve Solve the equation for the wave function for the computed hamiltonian.
     * @param current The current wave vector of the simulation.
     * @return The new wave in the next timestep of the simulation.
     */
    virtual Vector<T> solve(const Vector<T>& current) override {
        return getLeftMatrix().solve(getRightMatrix() * current);
    }

    /**
     * @brief #getHamiltonianMatrix Return the used hamilton matrix.
     * @return The Hamilton Matrix.
     */
    virtual TridiagonalMatrix<T> getHamiltonianMatrix() override {
        return hamiltonian;
    }

    /**
     * @brief #getLeftMatrix The left assigned matrix which may be used in the simulation.
     * @return The left assigned Matrix.
     */
    virtual TridiagonalMatrix<T> getLeftMatrix() override {
        return left;
    }

    /**
     * @brief #getRightMatrix The right assigned matrix which may be used in the simulation.
     * @return The right assigned matrix.
     */
    virtual TridiagonalMatrix<T> getRightMatrix() override {
        return right;
    }

private:
    TridiagonalMatrix<T> hamiltonian;
    TridiagonalMatrix<T> left;
    TridiagonalMatrix<T> right;

    std::function<double (double)> potentialFunction;
    SimulationParameter parameter;
};
