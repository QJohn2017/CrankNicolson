#ifndef VECTOR_H
#define VECTOR_H


#include <vector>
#include <stdlib.h>
#include <type_traits>

#include "assert.h"
#include "utilitys.h"


/**
 * @brief Vector
 * A simple vector class with any size. The vector type is adjustable by the template parameter
 * and can be a any numeric value type e.g. float, double, complex.
 */
template <typename T>
class Vector {
public:
    /**
     * @brief Vector default constructor with no elements and zero size.
     */
    Vector() : si(0) {
    }

    /**
     * @brief Vector Constructs a new vector of the given size with initial values set to zero.
     * @param Size the dimension of the vector to construct.
     */
    Vector(unsigned int Size) : si(Size) {
        values.resize(size(), T(0.0));
    }

    /**
     * @brief #operator + Addition operator, add another vector to this one
     *                   and return the result as a new vector.
     * @param other The vector to add.
     * @return The current vector added with the other one in a new vector.
     */
    Vector operator + (const Vector& other) {
        assert(size() == other.size());
        return (Vector(*this) += other);
    }

    /**
     * @brief #operator += Addition operator, add another vector to this one.
     *                    This addition happens inplace of the current vector.
     * @param other The vector to add to the current one.
     * @return The current vector added by the other one.
     */
    Vector& operator += (const Vector& other) {
        assert(size() == other.size());
        for (unsigned int i = 0; i < size(); ++i) {
            values[i] += other(i);
        }
        return *this;
    }

    /**
     * @brief #operator - Subtraction operator, subtract another vector to this one
     *                   and return the result as a new vector.
     * @param other The vector to subtract.
     * @return The current vector subtracted with the other one in a new vector.
     */
    Vector operator - (const Vector& other) const {
        assert(size() == other.size());
        Vector ret(size());
        for (unsigned int i = 0; i < size(); ++i) {
            ret(i) = values[i] - other(i);
        }
        return ret;
    }

    /**
     * @brief #operator -= Subtraction operator, subtracts another vector to this one.
     *                    This subtraction happens inplace of the current vector.
     * @param other The vector to subtract to the current one.
     * @return The current vector sutracted by the other one.
     */
    Vector& operator -= (const Vector& other) {
        assert(size() == other.size());
        for (unsigned int i = 0; i < size(); ++i) {
            values[i] -= other(i);
        }
        return *this;
    }

    /**
     * @brief #operator * Multiply operator, multiplies this vector with a factor
     *                   and return the result in a new vector.
     * @param other The factor to multipliy with the vector
     * @return The current vector multiplied by the factor in a new vector object
     */
    Vector operator * (const T& other) {
        Vector ret(*this);
        return (ret *= other);
    }

    /**
     * @brief #operator *= Multiply operator, multiply this vector with a factor
     *                    and modify the values inplace.
     * @param other The factor to multipliy with the vector.
     * @return The current vector multiplied by the factor in the current vector object.
     */
    Vector& operator *= (const T& other) {
        for (unsigned int i = 0; i < size(); ++i) {
            values[i] *= other;
        }
        return *this;
    }

    /**
     * @brief #conjungate Conjungate all elements of the current vector.
     * @return The conjungated vector.
     */
    template <typename U>
    typename std::enable_if<std::is_complex<U>::value, Vector<T>>::type conjungate() const {
        Vector ret(size());
        for (unsigned int i = 0; i < size(); ++i) {
            ret(i) = std::conj((*this)(i));
        }
        return ret;
    }

    /**
     * @brief #conjungate Conjungate all elements of the current vector.
     * @return The conjungated vector.
     */
    template <typename U>
    typename std::enable_if<!std::is_complex<U>::value, Vector<T>>::type conjungate() const {
        return *this;
    }

    /**
     * @brief #dot Compute the dot product of this vector with another one.
     * @param other The other vector to compute the dot product with.
     * @return The computed dot product.
     */
    T dot(const Vector<T>& other) const {
        assert(size() == other.size());
        T ret = T();
        Vector<T> conj = this->conjungate<T>();
        for (unsigned int i = 0; i < size(); ++i) {            
            ret += conj(i) * other(i);
        }
        return ret;
    }

    /**
     * @brief #operator () Index operator to access elements in the vector by index.
     * @param i The index of the element.
     * @return The element at the index.
     */
    T& operator () (unsigned int i) {
        assert(i < size());
        return values[i];
    }

    /**
     * @brief #operator [] Index operator to access elements in the vector by index.
     * @param i The index of the element.
     * @return The element at the index.
     */
    T& operator [] (unsigned int i) {
        assert(i < size());
        return values[i];
    }

    /**
     * @brief #operator () Index operator to access elements in the vector by index.
     * @param i The index of the element.
     * @return The element at the index.
     */
    T operator () (unsigned int i) const {
        assert(i < size());
        return values[i];
    }

    /**
     * @brief #operator [] Index operator to access elements in the vector by index.
     * @param i The index of the element.
     * @return The element at the index.
     */
    T operator [] (unsigned int i) const {
        assert(i < size());
        return values[i];
    }

    /**
     * @brief #length Compute the length of the vector.
     * @return The length of the vector.
     */
    T length() {
        T val = 0;
        for (unsigned int i = 0; i < size(); ++i) {
            val += values[i] * values[i];
        }
        return sqrt(val);
    }

    /**
     * @brief #normalised Compute the normalized vector by euclidian norm.
     * @return the normalized vector.
     */
    Vector normalised() {
        return (*this) * (T(1) / length());
    }

    /**
     * @brief #size return the element count in the vector.
     * @return the element count in the vector.
     */
    unsigned int size() const { return si; }

private:
    std::vector<T> values;
    unsigned int si;
};

#endif // VECTOR_H
