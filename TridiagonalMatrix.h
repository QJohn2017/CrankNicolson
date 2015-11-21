#pragma once

#include <assert.h>
#include <stdlib.h>
#include <cmath>

#include <vector>

#include "Vector.h"
#include "utilitys.h"

/**
 * @brief TridiagonalMatrix Tridiagonal matrix storage for compression
 * The matrix has the form
 * \f[
 *      \begin{pmatrix}
 *          a_1    & b_1    & 0      &   0     & \dots     & 0          \\
 *          c_2    & a_2    & b_2    &   0     & \dots     & 0          \\
 *          0      & c_3    & a_3    & b_3     & \dots     & 0          \\
 *          \vdots & \ddots & \ddots & \ddots  & \ddots    & \dots  & 0 \\
 *          0      & \dots  & 0      & c_{n-1} & a_{n - 1} & b_{n-1}    \\
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
    Vector<T> operator * (const Vector<T>& other) {
        Vector<T> r(size);
        r(0) = mat[Diagonal][0] * other(0) + mat[Lower][0] * other(1);
        for (unsigned int i = 1; i < size - 1; ++i) {
            r(i) = mat[Upper][i] * other(i - 1) + mat[Diagonal][i] * other(i) + mat[Lower][i] * other(i + 1);
        }
        r(size - 1) = mat[Upper][size - 1] * other(size - 2) + mat[Diagonal][size - 1] * other(size - 1);
        return r;
    }

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
     * @brief getEigenvalues Return the eigenvalues of the Matrix
     * @return The Eigenvalues organised in a Vector
     * @note This is not implemented jet!
     */
    Vector<T> getEigenvalues() {
        assert(false);
        //static_assert(false, "Not Implemented");
    }

    /**
     * @brief getSize Return the size of the Matrix elements.
     *                This is equal to the number of elements along the main diagonal
     * @return The size of the Matrix
     */
    unsigned int getSize() { return size; }

private:
    std::vector<T> mat[3];
    unsigned int size;
};
