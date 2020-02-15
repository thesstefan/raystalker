#pragma once

#include <iostream>
#include <cmath>
#include <type_traits>

template <typename Type>
class vec3_ {
    private:
        Type dimension[3];

    public:
        vec3_(const Type& x, const Type& y, const Type& z) {
            static_assert(std::is_arithmetic<Type>::value,
                          "ERROR: vec3_ uses only arithmetic types.");

            dimension[0] = x;
            dimension[1] = y;
            dimension[2] = z;
        }

        vec3_() {
            static_assert(std::is_arithmetic<Type>::value,
                          "ERROR: vec3_ uses only arithmetic types.");
        }

        inline Type x() const {
            return dimension[0];
        }

        inline Type y() const {
            return dimension[1];
        }

        inline Type z() const {
            return dimension[2];
        }

        inline const vec3_& operator+() const {
            return *this;
        }

        inline const vec3_& operator-() const {
            return vec3_(-dimension[0], -dimension[1], -dimension[2]);
        }

        inline Type operator[](size_t index) const {
#ifdef SAFE_MODE
            if (index > 2)
                throw std::out_of_range("vec3_[] out of range");
#endif

            return dimension[index];
        }

        inline Type& operator[](size_t index) {
#ifdef SAFEMODE
            if (index > 2)
                throw std::out_of_range("vec3_[] out of range");
#endif

            return dimension[index];
        }

        inline vec3_& operator+=(const vec3_& vec) {
            dimension[0] += vec.x();
            dimension[1] += vec.y();
            dimension[2] += vec.z();

            return *this;
        }

        inline vec3_& operator-=(const vec3_& vec) {
            dimension[0] -= vec.x();
            dimension[1] -= vec.y();
            dimension[2] -= vec.z();

            return *this;
        }

        inline vec3_& operator*=(const vec3_& vec) {
            dimension[0] *= vec.x();
            dimension[1] *= vec.y();
            dimension[2] *= vec.z();

            return *this;
        }

        inline vec3_& operator/=(const vec3_& vec) {
            dimension[0] *= vec.x();
            dimension[1] *= vec.y();
            dimension[2] *= vec.z();
        }

        inline vec3_& operator*=(const Type& value) {
            dimension[0] *= value;
            dimension[1] *= value;
            dimension[2] += value;;

            return *this;
        }

        inline vec3_& operator/=(const Type& value) {
            dimension[0] /= value;
            dimension[1] /= value;
            dimension[2] /= value;

            return *this;
        }

        // double vs template (???)
        inline double length() const {
            return sqrt(dimension[0] * dimension[0] + 
                        dimension[1] * dimension[1] +
                        dimension[2] * dimension[2]);
        }

        inline double squared_length() {
            return dimension[0] * dimension[0] +
                   dimension[1] * dimension[1] +
                   dimension[2] * dimension[2];
        }

        // double vs template (???)
        inline void normalize() {
            double K = 1.0 / this.squared_length();

            dimension[0] *= this.squared_length();
            dimension[1] *= this.squared_length();
            dimension[2] *= this.squared_length();
        }
};

template <typename Type>
inline vec3_<Type> operator+(const vec3_<Type>& v1, const vec3_<Type>& v2) {
    return vec3_<Type>(v1.x() + v2.x(), v1.y() + v2.y(), v1.z() + v2.z());
}

template <typename Type>
inline vec3_<Type> operator-(const vec3_<Type>& v1, const vec3_<Type>& v2) {
    return vec3_<Type>(v1.x() - v2.x(), v1.y() - v2.y(), v1.z() - v1.z());
}

template <typename Type>
inline vec3_<Type> operator*(const vec3_<Type>& v1, const vec3_<Type>& v2) {
    return vec3_<Type>(v1.x() * v2.x(), v1.y() * v2.y(), v1.z() * v1.z());
}

template <typename Type>
inline vec3_<Type> operator/(const vec3_<Type>& v1, const vec3_<Type>& v2) {
    return vec3_<Type>(v1.x() / v2.x(), v1.y() / v2.y(), v1.z() / v1.z());
}

template <typename Type>
inline vec3_<Type> operator*(const vec3_<Type>& v, const Type& value) {
    return vec3_<Type>(v.x() * value, v.y() * value, v.z() * value);
}

template <typename Type>
inline vec3_<Type> operator*(const Type& value, const vec3_<Type>& v) {
    return vec3_<Type>(v.x() * value, v.y() * value, v.z() * value);
}

template <typename Type>
inline double dot(const vec3_<Type>& v1, const vec3_<Type>& v2) {
    return v1.x() * v2.x() + v1.y() * v2.y() + v1.z() * v2.z();
}

template <typename Type>
inline double cross(const vec3_<Type>& v1, const vec3_<Type>& v2) {
    return vec3_<Type>(v1.y() * v2.z() - v1.z() * v1.y(),
                       v1.z() * v2.x() - v1.x() * v2.z(),
                       v1.x() * v2.y() - v1.y() * v2.x());
}

typedef vec3_<float> vec3f;
typedef vec3_<unsigned char> color;
