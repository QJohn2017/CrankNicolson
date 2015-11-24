#pragma once

#include "TridiagonalMatrix.h"

/**
 * @brief HamiltonianSolver Base class for the equation solver.
 *                          If you want to implement a custom solver inherit from this class
 * The HamiltonSolver solves the Schrödinger equation with the form
 * \f[
 *      H|x(r, t)\rangle = i\hbar \frac{\delta}{\delta t}|x(r,t)\rangle
 * \f]
 * The default solver used a left and a right matrix to solve the equation with
 * \f[
 *      (1 + \frac{it}{2} H)|x(r,t)\rangle^{n+1} = (1 - \frac{it}{2} H)|x(r,t)\rangle^{n}
 * \f]
 * with
 * \f[
 *      Left := 1 + \frac{i\Delta t}{2} H
 * \f]
 * and
 * \f[
 *      Right := 1 - \frac{i\Delta t}{2} H
 * \f]
 */
template <typename T>
class HamiltonianSolver
{
public:
    /**
     * @brief HamiltonianSolver Default constructor does nothing
     */
    HamiltonianSolver() {
    }

    /**
     * @brief solve Solve the Equation for the wave function for the computed Hamiltonian
     * @param current The current Wave vector of the simulation
     * @return The new Wave in the next timestep of the Simulation
     */
    virtual Vector<T> solve(const Vector<T>& current) = 0;

    /**
     * @brief getHamiltonianMatrix Return the used Hamilton Matrix
     * @return The Hamilton Matrix
     */
    virtual TridiagonalMatrix<T> getHamiltonianMatrix() = 0;

    /**
     * @brief getLeftMatrix The left assigned Matrix which may be used in the simulation
     * @return The left assigned Matrix
     */
    virtual TridiagonalMatrix<T> getLeftMatrix() = 0;

    /**
     * @brief getRightMatrix The right assigned Matrix which may be used in the simulation
     * @return The right assigned Matrix
     */
    virtual TridiagonalMatrix<T> getRightMatrix() = 0;
};
