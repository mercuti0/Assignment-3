/**
 * File: warmup.cpp
 * ----------------
 * @author Julie Zelenski, Spring 2020
 * This code is provided as part of an exercise to practice using a
 * debugger. This program has buggy use of recursion.
 */

#include <iostream>    // for cout, endl
#include "error.h"
#include "random.h"
#include "testing/SimpleTest.h"
using namespace std;


/* This is a recursive implementation of a function to calculate
 * factorials. This function works correctly for positive values
 * of n whose computed factorial value does not overflow the int
 * data type (n <= 12).
 *
 * As currently written, this function does not correctly handle
 * negative inputs.
 */
int factorial(int n) {
    if (n < 0) {
        error ("Factorial of a negative number cannot be calculated.");
    }
    if (n == 0) {
        return 1;
    } else {
        return n * factorial(n-1);
    }
}


/* This is an iterative implementation of a function that calculates
 * the exponentiation operation to raise a base to an exponent.
 *
 * This function works correctly for both positive and negative
 * exponents. This function has return type double to correctly return
 * floating point values instead of integer values for better precision.
 */
double iterativePower(int base, int exp) {
    double result = 1;
    if (base == 0) {
      return 0;
    }
    for (int i = 0; i < abs(exp); i++) {
        result *= base;
    }
    if (exp < 0) {
        result = 1/result; // calculate the reciprocal for negative exponent
    }
    return result;
}

/* This is an iterative implementation of a function that calculates
 * the exponentiation operation to raise a base to an exponent while
 * base and exp do not simultaneously equal to 0.
 */
double power(int base, int exp) {
    if (base == 0 && exp == 0)
        error("Answer is undefined.");
    if (base == 0) {
        return 0;
    } else if (exp == 0) {
        return 1;
    } else if (exp < 0) {
        return 1/power(base, -exp);
    } else {
        return base*power(base, exp-1);
    }
}


/* * * * * * Test Cases * * * * * */

PROVIDED_TEST("Test factorial function on simple input") {
    EXPECT_EQUAL(factorial(7), 7*6*5*4*3*2);
}

PROVIDED_TEST("Test recursive power against iterative power, random inputs") {
    for (int i = 0; i < 25; i++) {
        int base = randomInteger(1, 20);
        int exp = randomInteger(0, 10);
        EXPECT_EQUAL(power(base, exp), iterativePower(base, exp));
    }
}

STUDENT_TEST("Test factorial function on negatives") {
    EXPECT_ERROR(factorial(-7));
    EXPECT_ERROR(factorial(-1));
}

STUDENT_TEST("Test recursive power against iterative power, random inputs") {
    for (int i = 0; i < 25; i++) {
        int base = randomInteger(-20, -1);
        int exp = randomInteger(0, 10);
        EXPECT_EQUAL(power(base, exp), iterativePower(base, exp));
    }
}

STUDENT_TEST("Test recursive power against iterative power, random inputs") {
    for (int i = 0; i < 25; i++) {
        int base = randomInteger(1, 20);
        int exp = randomInteger(-10, -1);
        cout << base << " , " << exp << endl;
        EXPECT_EQUAL(power(base, exp), iterativePower(base, exp));
    }
}

STUDENT_TEST("Test recursive power against iterative power, random inputs") {
    for (int i = 0; i < 25; i++) {
        int base = randomInteger(1, 20);
        int exp = -1;
        EXPECT_EQUAL(power(base, exp), iterativePower(base, exp));
    }
}
STUDENT_TEST("Test recursive power against iterative power, random inputs") {
        int base = 0;
        int exp = 0;
        EXPECT_ERROR(power(base, exp));
}
