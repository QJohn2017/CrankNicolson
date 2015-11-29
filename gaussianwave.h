#pragma once

#include <complex>

#include "utilitys.h"
#include "wave.h"

/**
 * @brief GaussianWave Wave which has the form of a gaussian wave.
 * This wave is mathematicly defined as
 * \f[
 *
 * \f]
 */
template <typename T>
class GaussianWave : public Wave<T>
{
public:
    GaussianWave(const double Width, const double Pos, const double K)
        : width(Width), pos(Pos), k(K) {
    }

    virtual T getDisplacement(unsigned int index) const {
        const double ampl = std::pow(1.0 / (2 * PI * width * width), 1.0 / 4.0);
        const double x = static_cast<double>(index);
        const std::complex<double> e1(-(x - pos) * (x - pos) / (width * width));
        const std::complex<double> e2(0, -k * x);
        return ampl * std::exp(e1) * std::exp(e2);
    }
private:
    double width;
    double pos;
    double k;
};
