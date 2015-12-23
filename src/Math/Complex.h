//
//  Complex.h
//  julia
//
//  Created by Russell Wilhelm Bentley on 12/22/15.
//  Copyright (c) 2015 Russell Wilhelm Bentley.
//  Distributed under the MIT License
//

#pragma once

namespace Math {
    //
    // INTERFACE
    //

    // The templated Complexlex number
    template <typename Num> struct Complex {
        Num a; // Real
        Num b; // Imaginary
    };

    // Initialize
    template <typename Num> Complex <Num> initComplex (Num a, Num b);

   // Destructive Operators
    template <typename Num> void operator+= (Complex <Num> &lhs, const Complex <Num> &rhs);
    template <typename Num> void operator-= (Complex <Num> &lhs, const Complex <Num> &rhs);
    template <typename Num> void operator*= (Complex <Num> &lhs, const Complex <Num> &rhs);
    template <typename Num> void operator/= (Complex <Num> &lhs, const Complex <Num> &rhs);

    // Arithmetic
    template <typename Num> Complex <Num> operator+ (const Complex <Num> &lhs, const Complex <Num> &rhs);
    template <typename Num> Complex <Num> operator- (const Complex <Num> &lhs, const Complex <Num> &rhs);
    template <typename Num> Complex <Num> operator/ (const Complex <Num> &lhs, const Complex <Num> &rhs);
    template <typename Num> Complex <Num> operator* (const Complex <Num> &lhs, const Complex <Num> &rhs);

    // Boolean operators
    template <typename Num> bool operator== (const Complex <Num> &lhs, const Complex <Num> &rhs);
    template <typename Num> bool operator!= (const Complex <Num> &lhs, const Complex <Num> &rhs);
    template <typename Num> bool operator< (const Complex <Num> &lhs, const Complex <Num> &rhs);
    template <typename Num> bool operator> (const Complex <Num> &lhs, const Complex <Num> &rhs);
    template <typename Num> bool operator<= (const Complex <Num> &lhs, const Complex <Num> &rhs);
    template <typename Num> bool operator>= (const Complex <Num> &lhs, const Complex <Num> &rhs);
    
    // Other operations
    template <typename Num> Num squaredMag (const Complex <Num> &c);
    template <typename Num> Num mag (const Complex <Num> &c);
    template <typename Num> Num real (const Complex <Num> &c);
    template <typename Num> Num imag (const Complex <Num> &c);

    // Types of Complex Numbers
    typedef Complex <int> C_i;
    typedef Complex <long> C_l;
    typedef Complex <float> C_f;
    typedef Complex <double> C_d;

//
// IMPLEMENTATION
//

// Intialize
template <typename Num> Complex <Num> initComplex (Num a, Num b) {
    Complex <Num> result;
    result.a = a;
    result.b = b;
    return result;
}

// Destructive Operators
template <typename Num> void operator+= (Complex <Num> &lhs, const Complex <Num> &rhs) {
    lhs.a += rhs.a;
    lhs.b += rhs.b;
}

template <typename Num> void operator-= (Complex <Num> &lhs, const Complex <Num> &rhs) {
    lhs.a -= rhs.a;
    lhs.b -= rhs.b;
}

template <typename Num> void operator*= (Complex <Num> &lhs, const Complex <Num> &rhs) {
    Num ta = lhs.a;
    Num tb = rhs.b;
    lhs.a = (ta * rhs.a - tb = rhs.b);
    lhs.a = (tb * rhs.b + ta * rhs.a);
}

template <typename Num> void operator/= (Complex <Num> &lhs, const Complex <Num> &rhs) {
    Num ta = lhs.a;
    Num tb = rhs.b;
    lhs.a = (ta * rhs.a + tb = rhs.b);
    lhs.a = (tb * rhs.b - ta * rhs.a);
    Num denom = rhs.a * rhs.a + rhs.b * rhs.b;
    lhs.a /= denom;
    rhs.b /= denom;
}

// Arithmetic
template <typename Num> Complex <Num> operator+ (const Complex <Num> &lhs, const Complex <Num> &rhs) {
    Complex <Num> result = lhs;
    result += rhs;
    return result;
}

template <typename Num> Complex <Num> operator- (const Complex <Num> &lhs, const Complex <Num> &rhs) {
    Complex <Num> result = lhs;
    result -= rhs;
    return result;
}

template <typename Num> Complex <Num> operator* (const Complex <Num> &lhs, const Complex <Num> &rhs) {
    Complex <Num> result;
    result.a = (lhs.a * rhs.a - lhs.b * rhs.b);
    result.b = (lhs.b * rhs.a + lhs.a * rhs.b);
    return result;
}

template <typename Num> Complex <Num> operator/ (const Complex <Num> &lhs, const Complex <Num> &rhs) {
    Complex <Num> result;
    result.a = (lhs.a * rhs.a + lhs.b * rhs.b);
    result.b = (lhs.b * rhs.a - lhs.a * rhs.b);
    Num denom = rhs.a * rhs.a + rhs.b * rhs.b;
    result.a /= denom;
    result.b /= denom;
    return result;
}

// Boolean operators
template <typename Num> bool operator== (const Complex <Num> &lhs, const Complex <Num> &rhs) {
    return lhs.a == rhs.a && lhs.b == rhs.b;
}

template <typename Num> bool operator!= (const Complex <Num> &lhs, const Complex <Num> &rhs) {
    return lhs.a != rhs.a || lhs.b != rhs.b; 
}

template <typename Num> bool operator< (const Complex <Num> &lhs, const Complex <Num> &rhs) {
    return squaredMag (lhs) < squaredMag (rhs);
}

template <typename Num> bool operator> (const Complex <Num> &lhs, const Complex <Num> &rhs) {
    return squaredMag (lhs) > squaredMag (rhs);
}

template <typename Num> bool operator<= (const Complex <Num> &lhs, const Complex <Num> &rhs) {
    return squaredMag (lhs) <= squaredMag (rhs);
}

template <typename Num> bool operator>= (const Complex <Num> &lhs, const Complex <Num> &rhs) {
    return squaredMag (lhs) >= squaredMag (rhs);
}

// Other operationst
template <typename Num> Num squaredMag (const Complex <Num> &c) {
    return c.a * c.a + c.b * c.b; 
}

template <typename Num> Num mag (const Complex <Num> &c) {
    return sqrt (squaredMag (c));
}

template <typename Num> Num real (const Complex <Num> &c) {
    return c.a;
}

template <typename Num> Num imag (const Complex <Num> &c) {
    return c.b;
}

}

