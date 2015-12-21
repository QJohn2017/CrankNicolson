#pragma once

#include <complex>
#include <type_traits>

//! PI Define Pi for the appliation
#define PI 3.141592653

//! Hbar Define the reduced planck constant in Joule * second
#define HBAR 6.626070040e-34

namespace std {
     /**
     * @brief is_complex Utility class for the application for
     * [sfinae](https://de.wikipedia.org/wiki/Substitution_failure_is_not_an_error)
     */
    template<class T> struct is_complex : std::false_type {};

    /**
    * @brief is_complex Utility class for the application for
    * [sfinae](https://de.wikipedia.org/wiki/Substitution_failure_is_not_an_error)
    */
    template<class T> struct is_complex<std::complex<T>> : std::true_type {};
}
