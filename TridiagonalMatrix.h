#pragma once

#include <assert.h>
#include <stdlib.h>
#include <cmath>
#include <vector>
#include <limits>
#include <tuple>
#include <algorithm>
#include <type_traits>

#include "Vector.h"
#include "utilitys.h"

/**
 * @brief TridiagonalMatrix Tridiagonal matrix storage for compression
 * The matrix has the form
 * \f[
 *      \begin{pmatrix}
 *          a_1    & b_1    & 0      &   0     & \dots     & 0          \\
 *          c_2    & a_2    & b_2    &   0     & \dots     & 0          \\
 *          0      & c_3    & a_3    & b_3     & \ddots    & 0          \\
 *          \vdots & \ddots & \ddots  & \ddots & \ddots    & 0          \\
 *          0      & \ddots & 0      & c_{n-1} & a_{n - 1} & b_{n-1}    \\
 *          0      & \dots  & 0      & 0       & c_n       & a_n        \\
 *      \end{pmatrix}
 * \f]
 * but only the diagonals are stored to simplify computation and reduce the memory usage.
 * Its posible to store every numerical value supports all mathematical field operations
 */
template <typename T>
class TridiagonalMatrix
{
public:
    /**
     * @brief The Line enum
     */
    enum Line {
        Upper = 2,    //! The upper diagonal
        Diagonal = 1, //! The main diagonal
        Lower = 0     //! The lower diagonal
    };

    /**
     * @brief TridiagonalMatrix default constructor for the TridiagonalMatrix
     *        construct an empty matrix with no elements
     */
    TridiagonalMatrix() : size(0) {
    }

    /**
     * @brief TridiagonalMatrix construct a new matrix with the given size and default constructed elements
     * @param Size The number of elements along the main diagonal
     */
    TridiagonalMatrix(unsigned int Size) : size(Size) {
        for (int i = 0; i < 3; ++i) {
            mat[i].resize(size, T());
        }
    }

    /**
     * @brief identity Construct a identity matrix with defaultValue elements a the main diagonal
     *                 and zero at the other elements
     * @param size The size of the Matrix to construct, this is equal to the number of elements along the main diagonal
     * @param defaultValue The value which should be set at the main diagonal
     * @return The constructed Matrix
     */
    static TridiagonalMatrix<T> identity(unsigned int size, T defaultValue) {
        TridiagonalMatrix<T> mat(size);
        for (unsigned int i = 0; i < size; ++i) {
            mat(Line::Diagonal, i) = defaultValue;
        }
        return mat;
    }

    /**
     * @brief operator + Addition operator, which adds another TridiagonalMatrix to the current current one.
     *                   This returns a new TridiagonalMatrix with the added elements
     * @param other The TridiagonalMatrix to add
     * @require The other TridiagonalMatrix must have the same size as the current one
     * @return The added TridiagonalMatrix in a new object
     */
    TridiagonalMatrix operator + (TridiagonalMatrix other) {
        assert (size == other.size);
        TridiagonalMatrix m(*this);
        for (unsigned int i = 0; i < size; ++i) {
            m.mat[0][i] += other.mat[0][i];
            m.mat[1][i] += other.mat[1][i];
            m.mat[2][i] += other.mat[2][i];
        }
        return m;
    }

    /**
     * @brief operator += Addition operator, which adds another TridiagonalMatrix to the current current one.
     *                   This returns this matrix with inplace added elements
     * @param other The TridiagonalMatrix to add
     * @require The other TridiagonalMatrix must have the same size as the current one
     * @return The current Matrix with inplace added Elements
     */
    TridiagonalMatrix operator += (TridiagonalMatrix other) {
        assert (size == other.size);
        for (unsigned int i = 0; i < size; ++i) {
            mat[0][i] += other.mat[0][i];
            mat[1][i] += other.mat[1][i];
            mat[2][i] += other.mat[2][i];
        }
        return *this;
    }

    /**
     * @brief operator - Subtraction operator, which subtracts another TridiagonalMatrix to the current current one.
     *                   This returns a new TridiagonalMatrix with the subtracted elements
     * @param other The TridiagonalMatrix to subtract
     * @require The other TridiagonalMatrix must have the same size as the current one
     * @return The subtracted TridiagonalMatrix in a new object
     */
    TridiagonalMatrix operator - (TridiagonalMatrix other) {
        assert (size == other.size);
        TridiagonalMatrix m(*this);
        for (unsigned int i = 0; i < size; ++i) {
            m.mat[0][i] -= other.mat[0][i];
            m.mat[1][i] -= other.mat[1][i];
            m.mat[2][i] -= other.mat[2][i];
        }
        return m;
    }

    /**
     * @brief operator -= Subtraction operator, which subtracts another TridiagonalMatrix to the current current one.
     *                    This returns this matrix with inplace subtracted elements
     * @param other The TridiagonalMatrix to subtract
     * @require The other TridiagonalMatrix must have the same size as the current one
     * @return The current Matrix with inplace subtracted Elements
     */
    TridiagonalMatrix operator -= (TridiagonalMatrix other) {
        assert (size == other.size);
        for (unsigned int i = 0; i < size; ++i) {
            mat[0][i] -= other.mat[0][i];
            mat[1][i] -= other.mat[1][i];
            mat[2][i] -= other.mat[2][i];
        }
        return *this;
    }

    /**
     * @brief operator * Multiplication operator, which multiplies a factor to the current current TridiagonalMatrix.
     *                   This returns a new TridiagonalMatrix with the multiplied factor
     * @param other The factor to multiply the matrix with
     * @return The resulting TridiagonalMatrix in a new object
     */
    TridiagonalMatrix operator * (const T& other) {
        TridiagonalMatrix m(*this);
        for (unsigned int i = 0; i < size; ++i) {
            m.mat[0][i] *= other;
            m.mat[1][i] *= other;
            m.mat[2][i] *= other;
        }
        return m;
    }

    /**
     * @brief operator * Multiplication operator, which multiplies a Vector with current current TridiagonalMatrix.
     *                   This returns a new Vector results form the Matrix multiplication
     * @param other The Vector to multiply the matrix with
     * @return The resulting Vector in a new object
     */
    template <typename U>
    friend Vector<U> operator * (const TridiagonalMatrix<U>& mat, const Vector<U>& other);

    /**
     * @brief operator * Multiplication operator, which multiplies a Vector with current current TridiagonalMatrix.
     *                   This returns a new Vector results form the Matrix multiplication
     * @param other The Vector to multiply the matrix with
     * @return The resulting Vector in a new object
     */
    template <typename U>
    friend Vector<U> operator * (const Vector<U>& other, const TridiagonalMatrix<U>& mat);

    /**
     * @brief operator () The index operator to access elements by the diagonal and the index
     * @param line The diagonal of the element
     * @param j The index at the diagonal
     * @require The index must be smaller than the size of the matrix
     * @return The element at the diagonal with the given index
     */
    T& operator () (Line line, unsigned int j) {
        assert(line < 3 && j < size);
        return mat[line][j];
    }

    /**
     * @brief operator () The index operator to access elements by the diagonal and the index
     * @param line The diagonal of the element
     * @param j The index at the diagonal
     * @require The index must be smaller than the size of the matrix
     * @return The element at the diagonal with the given index
     */
    T operator () (Line line, unsigned int j) const {
        assert(line < 3 && j < size);
        return mat[line][j];
    }

    /**
     * @brief solve Solve a linear equation system with the given matrix and the resulting vector.
     *              This has the mathematical form
     *              \f[
     *                  Ax = b
     *              \f]
     * @param vec The resulting vector. In this case the b vector
     * @require The vector must have the same size as the matrix
     * @return The x vector of the system
     */
    Vector<T> solve(const Vector<T>& vec) {
        assert(size == vec.size());
        Vector<T> d(vec);
        auto c = mat[Lower];
        auto b = mat[Diagonal];
        auto a = mat[Upper];


        c[0] /= c[0];
        d[0] /= b[0];
        for (unsigned int i = 1; i < size - 1; ++i) {
            c[i] /= b[i] - a[i] * c[i - 1];
            d[i] = (d[i] - a[i] * d[i - 1]) / (b[i] - a[i] * c[i - 1]);
        }

        d[size - 1] = (d[size - 1] - a[size - 1] * d[size - 2]) / (b[size - 1] - a[size - 1] * c[size - 2]);
        for (unsigned int i = size - 1; i-- > 0;) {
            d[i] -= c[i] * d[i + 1];
        }
        return d;
    }

    /**
     * @brief getEigenvalues Return the eigenvalues of the Matrix in accending order
     * @param error The error value for the non diagonal elements. For smaller errors use a smaller error value.
     * @return The Eigenvalues organised in a std::vector
     * @note The used algorithm is the qr algorithm for symmetric tridiagonal matrices so be carefull if your not using symmetric matrices
     */
    template <typename U>
    typename std::enable_if<!std::is_complex<U>::value, Vector<U>>::type getEigenvalues(U error = 0.00001) {
        TridiagonalMatrix<U> step(*this);
        step.qrStep(std::sqrt(step.getSize()));

        std::vector<U> eigenvalues;
        eigenvalues.resize(size);
        for (unsigned int i = 0; i < size; ++i) {
            eigenvalues[i] = step(Diagonal, i);
        }
        std::sort(eigenvalues.begin(), eigenvalues.end());
        Vector<U> result(eigenvalues.size());
        for (unsigned int i = 0; i < eigenvalues.size(); ++i) {
            result(i) = eigenvalues[i];
        }

        return result;
    }

    /**
     * @brief getEigenvalues Return the eigenvalues of the Matrix in accending order
     * @param error The error value for the non diagonal elements. For smaller errors use a smaller error value.
     * @return The Eigenvalues organised in a std::vector
     * @note The used algorithm is the qr algorithm for symmetric tridiagonal matrices so be carefull if your not using symmetric matrices
     */
    template <typename U>
    typename std::enable_if<std::is_complex<U>::value, Vector<typename U::value_type>>::type getEigenvalues(typename U::value_type error = typename U::value_type(0.00001)) {
        TridiagonalMatrix<U> step(*this);
        step.qrStep(std::sqrt(step.getSize()));

        std::vector<typename U::value_type> eigenvalues;
        eigenvalues.resize(size);
        for (unsigned int i = 0; i < size; ++i) {
            eigenvalues[i] = step(Diagonal, i).real();
        }
        std::sort(eigenvalues.begin(), eigenvalues.end());
        Vector<typename U::value_type> result(eigenvalues.size());
        for (unsigned int i = 0; i < eigenvalues.size(); ++i) {
            result(i) = eigenvalues[i];
        }

        return result;
    }

    /**
     * @brief getExpectationValue computes the expectation value of an operator
     *        \f[
     *          <A>_{\phi} =
     *        \f]
     * @param vec The state to be expected
     * @return The properbility of the expected state
     */
    T getExpectationValue(const Vector<T>& vec) const {
        Vector<T> result = (*this) * vec;
        return vec.dot(result);
    }

    /**
     * @brief getSize Return the size of the Matrix elements.
     *                This is equal to the number of elements along the main diagonal
     * @return The size of the Matrix
     */
    unsigned int getSize() const { return size; }

private:
    template <typename U>
    typename std::enable_if<!std::is_complex<U>::value, U>::type sign (U x) {
        U value;
        if (x < 0.0) {
            value = -1.0;
        }
        else {
            value = 1.0;
        }
        return value;
    }

    template <typename U>
    typename std::enable_if<std::is_complex<T>::value, U>::type sign (U x) {
        U value;
        if (x.real() < 0.0) {
            value = -1.0;
        }
        else {
            value = 1.0;
        }
        return value;
    }

    inline std::tuple<T, T, T> givens(T a, T b) {
        std::tuple<T, T, T> result;
        if (std::abs(b) <= std::abs(std::numeric_limits<T>::epsilon())) {
            std::get<0>(result) = sign(a); //std::copysign(1.0, a); // c
            std::get<1>(result) = 0;                  // s
            std::get<2>(result) = std::abs(a);        // r
        } else if (std::abs(a) <= std::abs(std::numeric_limits<T>::epsilon())) {
            std::get<0>(result) = 0;
            std::get<1>(result) = sign(b); //std::copysign(1.0, b);
            std::get<2>(result) = std::abs(b);
        } else if (std::abs(b) > std::abs(a)) {
            const T t = a / b;
            const T u = sign(b) * std::sqrt(T(1) + t * t); //std::copysign(std::sqrt(1.0 + t*t), b);
            std::get<1>(result) = -1.0 / u;
            std::get<0>(result) = -std::get<1>(result) * t;
            std::get<2>(result) = b * u;
        } else {
            const T t = b / a;
            const T u = sign(a) * std::sqrt(T(1) + t * t); //std::copysign(std::sqrt(T(1) + t*t), a);
            std::get<0>(result) = 1.0 / u;
            std::get<1>(result) = -std::get<0>(result) * t;
            std::get<2>(result) = a * u;
        }
        return result;
    }

    void qrStep(unsigned int iterations) {
        unsigned int m = (*this).getSize() - 1;
        unsigned int k = iterations;
        while (m > 1) {
            T shift = (*this)(Diagonal, m);
            const T u = ((*this)(Diagonal, m - 1) - (*this)(Diagonal, m)) / 2.0;
            if (std::abs(u) <= std::abs(std::numeric_limits<T>::epsilon())) {
                shift = (*this)(Diagonal, m) - std::abs((*this)(Upper, m));
            } else {
                T b = (*this)(Upper, m - 1);
                shift = (*this)(Diagonal, m) - sign(u) * b * b / (std::abs(u) + std::sqrt(u * u + b * b));
            }

            T x = (*this)(Diagonal, 0) - shift;
            T y = (*this)(Upper, 0);
            for (unsigned int k = 0; k < m; ++k) {
                std::tuple<T, T, T> giv = givens(x, y);
                const T c = std::get<0>(giv);
                const T s = std::get<1>(giv);

                const T w = c * x - s * y;
                const T d = (*this)(Diagonal, k) - (*this)(Diagonal, k + 1);
                const T z = (2 * c * (*this)(Upper, k) + d * s) * s;
                (*this)(Diagonal, k) -= z;
                (*this)(Diagonal, k + 1) += z;
                (*this)(Upper, k) = d * c * s + (c * c - s * s) * (*this)(Upper, k);
                x = (*this)(Upper, k);
                if (k > 0) {
                    (*this)(Upper, k - 1) = w;
                }
                if (k < m - 1) {
                    y = -s * (*this)(Upper, k + 1);
                    (*this)(Upper, k + 1) *= c;
                }
            }

            k--;
            if (k == 0) {
                m--;
                k = iterations;
            }
        }

    }

    /*void qrStep(unsigned int M, unsigned int s) {
        assert (s > 1 && s <= size);

        T shift = (*this)(Diagonal, M); //0.0;
        //Wilkinson shift
        const T u = ((*this)(Diagonal, M - 1) - (*this)(Diagonal, M)) / 2.0;
        if (std::abs(u) <= std::abs(std::numeric_limits<T>::epsilon())) {
            shift = (*this)(Diagonal, M) - std::abs((*this)(Upper, M));
        } else {
            T b = (*this)(Upper, M - 1);
            shift = (*this)(Diagonal, M) - sign(u) * b * b / (std::abs(u) + std::sqrt(u * u + b * b));
        }

        const unsigned int size = s; //(*this).getSize();
        T a = (*this)(Diagonal, 0) - shift;
        T b = (*this)(Upper, 0);
        T x = (*this)(Diagonal, 0);
        T y = (*this)(Upper, 0);
        for (unsigned int i = 0; i < size - 1; ++i) {
            std::tuple<T, T, T> giv = givens(a, b);
            const T c = std::get<0>(giv);
            const T s = std::get<1>(giv);
            const T r = std::get<2>(giv);
            (*this)(Diagonal, i) = c * c * x + T(2) * c * s * y + s * s * (*this)(Diagonal, i + 1);
            a = (c * c - s * s) * y + c * s * ((*this)(Diagonal, i + 1) - x);
            x = s * s * x - T(2) * c * s * y + c * c * (*this)(Diagonal, i + 1);

            if (i > 0) {
                (*this)(Upper, i - 1) = r;
            }
            if (i < size - 1) {
                b = s * (*this)(Upper, i + 1);
                y = c * (*this)(Upper, i + 1);
            }
        }
        (*this)(Upper, size - 2) = a;
        (*this)(Diagonal, size - 1) = x;
    }*/

    std::vector<T> mat[3];
    unsigned int size;
};


template <typename T>
inline Vector<T> operator * (const TridiagonalMatrix<T>& mat, const Vector<T>& other) {
    Vector<T> r(mat.size);
    r(0) = mat.mat[TridiagonalMatrix<T>::Diagonal][0] * other(0) + mat.mat[TridiagonalMatrix<T>::Lower][0] * other(1);
    for (unsigned int i = 1; i < mat.size - 1; ++i) {
        r(i) = mat.mat[TridiagonalMatrix<T>::Upper][i] * other(i - 1) +
               mat.mat[TridiagonalMatrix<T>::Diagonal][i] * other(i)  +
               mat.mat[TridiagonalMatrix<T>::Lower][i] * other(i + 1);
    }
    r(mat.size - 1) = mat.mat[TridiagonalMatrix<T>::Upper][mat.size - 1] * other(mat.size - 2) +
                      mat.mat[TridiagonalMatrix<T>::Diagonal][mat.size - 1] * other(mat.size - 1);
    return r;
}

template <typename T>
inline Vector<T> operator * (const Vector<T>& other, const TridiagonalMatrix<T>& mat) {
    Vector<T> r(mat.size);
    r(0) = mat.mat[TridiagonalMatrix<T>::Diagonal][0] * other(0) + mat.mat[TridiagonalMatrix<T>::Lower][0] * other(1);
    for (unsigned int i = 1; i < mat.size - 1; ++i) {
        r(i) = mat.mat[TridiagonalMatrix<T>::Upper][i - 1] * other(i - 1) +
               mat.mat[TridiagonalMatrix<T>::Diagonal][i] * other(i)      +
               mat.mat[TridiagonalMatrix<T>::Lower][i - 1] * other(i + 1);
    }
    r(mat.size - 1) = mat.mat[TridiagonalMatrix<T>::Upper][mat.size - 1] * other(mat.size - 2) +
                      mat.mat[TridiagonalMatrix<T>::Diagonal][mat.size - 1] * other(mat.size - 1);
    return r;
}
