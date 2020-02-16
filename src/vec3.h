/** @file vec3.h */

#pragma once

#include <iostream>
#include <cmath>
#include <type_traits>
#include <exception>

/**
 * @class vec3_
 * @brief Implements vec3 module.
 *
 * @warning Every case of component overflowing / underflowing results
 *          in undefined behaviour.
 *
 * @tparam Type The vector component type. Must be arithmetic. 
 *              A static assertion halts the program otherwise.
 *
 *              unsigned char (color) and float (vec3f) are the tested 
 *              and supported types, but any arithmetic type should
 *              work.
 */
template <typename Type>
class vec3_ {
    private:
        Type dimension[3];

    public:
        /**
         * @brief Default constructs the vector and the internal components.
         *
         * @warning If Type is not arithmetic, a static assertion 
         *          halts the program.
         */
        vec3_() {
            dimension[0] = Type();
            dimension[1] = Type();
            dimension[2] = Type();

            static_assert(std::is_arithmetic<Type>::value,
                          "ERROR: vec3_ uses only arithmetic types.");
        }

        /**
         * @brief Constructs the vector with specified component values.
         *
         * @param x -> The x-component value
         * @param y -> The y-component value
         * @param z -> The z-component value
         *
         * @warning If Type is not arithmetic, a static assertion 
         *          halts the program.
         */
        vec3_(const Type& x, const Type& y, const Type& z) {
            static_assert(std::is_arithmetic<Type>::value,
                          "ERROR: vec3_ uses only arithmetic types.");

            dimension[0] = x;
            dimension[1] = y;
            dimension[2] = z;
        }

        /**
         * @brief Copy-constructs the vector.
         *
         * @param vec -> The vector to copy
         *
         * The internal component values of vec are assigned to the vec3
         * on which this is called.
         *
         * @warning If Type is not arithmetic, a static assertion 
         *          halts the program.
         */
        vec3_(const vec3_& vec) {
            static_assert(std::is_arithmetic<Type>::value,
                          "ERROR: vec3_ uses only arithmetic types.");

            dimension[0] = vec.x();
            dimension[1] = vec.y();
            dimension[2] = vec.z();
        }

        /** @brief Returns the x-component value. */
        inline Type x() const {
            return dimension[0];
        }

        /** @brief Returns the y-component value. */
        inline Type y() const {
            return dimension[1];
        }

        /** @brief Returns the z-component value. */
        inline Type z() const {
            return dimension[2];
        }

        /**
         * @brief Copy-assignment operator.
         *
         * @param vec -> The vector to copy.
         *
         * The internal component values of vec are assigned to the vec3
         * on which this is called.
         */
        inline vec3_& operator=(const vec3_& vec) {
            dimension[0] = vec.x();
            dimension[1] = vec.y();
            dimension[2] = vec.z();

            return *this;
        }

        /**
         * @brief Equality operator.
         *
         * @param vec -> The vec3 to check equality with.
         *
         * @returns true if all the component values of the vectors are equal,
         *          false otherwise
         */
        inline const bool operator==(const vec3_& vec) const {
            if (this->x() != vec.x() ||
                this->y() != vec.y() || 
                this->z() != vec.z())
                return false;

            return true;
        }

        /**
         * @brief Inequality operator.
         *
         * @param vec -> The vec3 to check inequality with.
         *
         * @returns true if all the component values of the vectors are 
         *          not equal, false otherwise
         */
        inline const bool operator!=(const vec3_& vec) const {
            return !(*this == vec);
        }

        /** 
         * @brief Addition operator.
         *
         * @warning Overflow / underflow of component values
         *          results in undefined behaviour.
         */
        inline const vec3_& operator+() const {
            return *this;
        }

        /**
         * @brief Subtraction operator.
         *
         * @warning Overflow / underflow of component values 
         *          result in undefined behaviour.
         */
        inline const vec3_& operator-() const {
            return vec3_(-dimension[0], -dimension[1], -dimension[2]);
        }

        /**
         * @brief Direct access operator (const).
         *
         * @param index -> The index of the component
         *
         * @returns x, y, z component values for the 0, 1, 2 index values.
         *
         * @warning If index is out of bounds (negative or bigger than 2),
         *          std::out_of_range is thrown.
         */
        inline Type operator[](size_t index) const {
            if (index > 2)
                throw std::out_of_range("vec3_[] out of range");

            return dimension[index];
        }

        /**
         * @brief Direct access operator.
         *
         * @param index -> The index of the component
         *
         * @returns x, y, z component values for the 0, 1, 2 index values.
         *
         * @warning If index is out of bounds (bigger than 2),
         *          std::out_of_range is thrown.
         */
        inline Type& operator[](size_t index) {
            if (index > 2)
                throw std::out_of_range("vec3_[] out of range");

            return dimension[index];
        }

        /**
         * @brief Addition-assignment operator.
         *
         * Increases itself by another vec3.
         *
         * @param vec -> The vec3 to add with
         *
         * @warning Overflow / underflow of component values
         *          result in undefined behaviour.
         */
        inline vec3_& operator+=(const vec3_& vec) {
            dimension[0] += vec.x();
            dimension[1] += vec.y();
            dimension[2] += vec.z();

            return *this;
        }

        /**
         * @brief Subtraction-assignment operator.
         *
         * Subtracts itself by another vec3.
         *
         * @param vec -> The vec3 to subtract by
         *
         * @warning Overflow / underflow of component values
         *          result in undefined behaviour.
         */
        inline vec3_& operator-=(const vec3_& vec) {
            dimension[0] -= vec.x();
            dimension[1] -= vec.y();
            dimension[2] -= vec.z();

            return *this;
        }

        /**
         * @brief Multipication-assignment operator by vec3.
         *
         * Multiply itself by another vec3.
         *
         * @param vec -> The vec3 to multiply by.
         *
         * @warning Overflow / underflow of component values
         *          result in undefined behaviour.
         */
        inline vec3_& operator*=(const vec3_& vec) {
            dimension[0] *= vec.x();
            dimension[1] *= vec.y();
            dimension[2] *= vec.z();

            return *this;
        }

        /**
         * @brief Division-assignment operator by vec3.
         *
         * Divides itself by another vec3.
         *
         * @param vec -> The vec3 to divide by.
         *
         * @warning Overflow / underflow of component values
         *          result in undefined behaviour.
         */
        inline vec3_& operator/=(const vec3_& vec) {
            dimension[0] /= vec.x();
            dimension[1] /= vec.y();
            dimension[2] /= vec.z();

            return *this;
        }

        /**
         * @brief Multiplication-assignment operator by scalar.
         *
         * Increases itself by a scalar.
         *
         * @param value -> The scalar to multiply by. 
         *                 (same type as the vec3 components)
         *
         * @warning Overflow / underflow of component values
         *          result in undefined behaviour.
         */
        inline vec3_& operator*=(const Type& value) {
            dimension[0] *= value;
            dimension[1] *= value;
            dimension[2] *= value;

            return *this;
        }

        /**
         * @brief Division-assignment operator by scalar.
         *
         * Divides itself by a scalar.
         *
         * @param value -> The scalar to divide by. 
         *                 (same type as the vec3 components)
         *
         * @warning Overflow / underflow of component values
         *          result in undefined behaviour.
         */
        inline vec3_& operator/=(const Type& value) {
            dimension[0] /= value;
            dimension[1] /= value;
            dimension[2] /= value;

            return *this;
        }

        /**
         * @returns The length of the vector.
         */
        inline double length() const {
            return sqrt(dimension[0] * dimension[0] + 
                        dimension[1] * dimension[1] +
                        dimension[2] * dimension[2]);
        }

        /**
         * @returns The squared length of the vector.
         */
        inline double squared_length() const {
            return dimension[0] * dimension[0] +
                   dimension[1] * dimension[1] +
                   dimension[2] * dimension[2];
        }

        /**
         * @brief Normalizes the vector.
         *
         * @warning Currently, the multiplication operators
         *          are defined for scalars/vectors of the same type as the
         *          vector components. That means that normalizing
         *          a non-floating point type vector doesn't work very
         *          well, so using @ref vec3_convert is recommended.
         */
        inline void normalize() {
            double K = 1.0 / this.squared_length();

            dimension[0] *= this.squared_length();
            dimension[1] *= this.squared_length();
            dimension[2] *= this.squared_length();
        }
};

/** 
 * @returns the addition result of the two vectors.
 *
 * @warning Overflow / underflow of component values
 *          results in undefined behaviour.
 */
template <typename Type>
inline vec3_<Type> operator+(const vec3_<Type>& v1, const vec3_<Type>& v2) {
    return vec3_<Type>(v1.x() + v2.x(), v1.y() + v2.y(), v1.z() + v2.z());
}

/** 
 * @returns the subtraction result of the two vectors. (v1 - v2)
 *
 * @warning Overflow / underflow of component values
 *          results in undefined behaviour.
 */
template <typename Type>
inline vec3_<Type> operator-(const vec3_<Type>& v1, const vec3_<Type>& v2) {
    return vec3_<Type>(v1.x() - v2.x(), v1.y() - v2.y(), v1.z() - v2.z());
}

/** 
 * @returns the multiplication result of the two vectors.
 *
 * @warning Overflow / underflow of component values
 *          results in undefined behaviour.
 */
template <typename Type>
inline vec3_<Type> operator*(const vec3_<Type>& v1, const vec3_<Type>& v2) {
    return vec3_<Type>(v1.x() * v2.x(), v1.y() * v2.y(), v1.z() * v2.z());
}

/** 
 * @returns the division result of the two vectors. (v1 / v2)
 *
 * @warning Overflow / underflow of component values
 *          results in undefined behaviour.
 */
template <typename Type>
inline vec3_<Type> operator/(const vec3_<Type>& v1, const vec3_<Type>& v2) {
    return vec3_<Type>(v1.x() / v2.x(), v1.y() / v2.y(), v1.z() / v2.z());
}

/**
 * @returns the division of the vector by the scalar
 *
 * @warning Overflow / underflow of component values
 *          results in undefined behaviour.
 */
template <typename Type>
inline vec3_<Type> operator/(const vec3_<Type>& v, const Type& value) {
    return vec3_<Type>(v.x() / value, v.y() / value, v.z() / value);
}

/**
 * @returns the multiplication of the vector by the scalar (vec3 * scalar)
 *
 * @warning Overflow / underflow of component values
 *          results in undefined behaviour.
 */
template <typename Type>
inline vec3_<Type> operator*(const vec3_<Type>& v, const Type& value) {
    return vec3_<Type>(v.x() * value, v.y() * value, v.z() * value);
}

/**
 * @returns the multiplication of the vector by the scalar (scalar * vec)
 *
 * @warning Overflow / underflow of component values
 *          results in undefined behaviour.
 */
template <typename Type>
inline vec3_<Type> operator*(const Type& value, const vec3_<Type>& v) {
    return vec3_<Type>(v.x() * value, v.y() * value, v.z() * value);
}

/**
 * @returns the dot product of the two vectors
 */
template <typename Type>
inline double dot(const vec3_<Type>& v1, const vec3_<Type>& v2) {
    return v1.x() * v2.x() + v1.y() * v2.y() + v1.z() * v2.z();
}

/**
 * @returns the cross product of the two vectors
 *
 * @warning Overflow / underflow of component values
 *          results in undefined behaviour.
 */
template <typename Type>
inline vec3_<Type> cross(const vec3_<Type>& v1, const vec3_<Type>& v2) {
    return vec3_<Type>(v1.y() * v2.z() - v1.z() * v2.y(),
                       v1.z() * v2.x() - v1.x() * v2.z(),
                       v1.x() * v2.y() - v1.y() * v2.x());
}

/**
 * @brief Converts a vec3 to another type.
 *
 * Converts by calling static_cast<outType> on components.
 *
 * @tparam inType -> The type of the vec3 to convert from
 * @tparam outType -> The type of the vec3 to convert to
 *
 * @param vec -> The vector to convert
 */
template <typename inType, typename outType>
inline vec3_<outType> vec3_convert(const vec3_<inType>& vec) {
    return vec3_<outType>(static_cast<outType>(vec.x()),
                          static_cast<outType>(vec.y()),
                          static_cast<outType>(vec.z()));
}

typedef vec3_<float> vec3f;

typedef vec3_<unsigned char> color;
typedef vec3_<float> colorf;
