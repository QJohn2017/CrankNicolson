#pragma once

#include <complex>

#include "utilitys.h"
#include "wave.h"

/**
 * @brief GaussianWave which has the form of a gaussian wave.
 * This wave is mathematicly defined as
 * \f[
 *      (\frac{1}{2\cdot\pi\cdot\sigma^2})^{\frac{1}{4}}\cdot e^{-\frac{(x-x_0)^2}{\sigma^2}}\cdot e^{-k_0\cdot x}
 * \f]
 */
template <typename T>
class GaussianWave : public Wave<T>
{
public:
    /**
     * @brief GaussianWave construct a new wave at the given position, width and the with the wavevector k
     * @param Width The wave width this equals to \f$\sigma\f$ in the equation
     * @param Pos the position of the wave equals to \f$x_0\f$ in the equation
     * @param K the wavevector of the wave equals to \f$k_0\f$ in the equation
     * @see GaussianWave
     */
    GaussianWave(const double Width, const double Pos, const double K)
        : width(Width), pos(Pos), k(K) {
    }

    /**
     * @brief #getDisplacement Return the displacement for an atom
     * @param index The index of the atom
     * @return the displacement for the atom at the given index
     */
    virtual T getDisplacement(unsigned int index) const {
        /*const double ampl = std::pow(1.0 / (2 * PI * width * width), 1.0 / 4.0);
        const double x = static_cast<double>(index);
        const std::complex<double> e1(-(x - pos) * (x - pos) / (width * width));
        const std::complex<double> e2(0, -k * x);
        return ampl * std::exp(e1) * std::exp(e2);*/

        return getPsiK(static_cast<double>(index) / 1000.0);
    }

private:
    std::complex<double> getPsiK(double x, double x0 = 0, double a = 5e-3, double l = 50, double vk = 1e-2) const
    {
        //double n0 = 1 / (4 * M_PI * a * l * l); // und das?
        //double cs = pow(4 * M_PI * a * n0, 0.5); // wo für ist das?

        std::complex<double> psi = 0;
        if (x > -0.785398 && x < 0.785398) {
            psi = std::cos(2 * x) *
                            std::pow(20, 0.5) *
                           (std::complex<double>(0, vk) +
                            std::pow(1 - (vk * vk), 0.5) *
                            std::tanh(((x - x0) * l) *
                                      std::pow(1 - ((vk * vk)), 0.5)));
        }
        else {
            psi = 0;
        }
        if (x > 0)
            psi = std::complex<double>(-1,0) * psi;

        return psi;
    }

    double width;
    double pos;
    double k;
};
