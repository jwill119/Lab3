// Lab03.cpp
// Jacob Williams
// COSC 2030 Lab 3
//
// Numerical errors that pop up in computer arithmetic

#include <iostream>
using std::cin;
using std::cout;
using std::endl;

#include<climits>   // For my numeric limits
#include<cmath>     // For the isinf() function

// Function declarations
short calcSumShort(short);
long calcSumLong(long);
float calcFactFloat(long);
double calcFactDouble(long);
float recipSumFloat(long);
double recipSumDouble(long);

int main() {
    // Let's display our maximum values.
    cout << endl << endl;
    cout << "The maximum short on my machine: " << SHRT_MAX << "." << endl;
    cout << "The maximum long on my machine: " << LONG_MAX << "." << endl << endl;
    // My shorts are 16-bit and my longs are 64-bit.

    // Begin with sum-of-shorts and the testing thereof.
    // As these are signed, we will notice an overflow as soon as we jump into a negative number.
    // For unsigned shorts, overflow would be when calcSumShort(i+1) < calcSumShort(i).

    // Basic test
    short twenty = 20;
    short sumtwenty = calcSumShort(twenty);
    cout << "Basic test of shorts: " << endl;
    cout << "n = " << twenty << "; calcSumShort(n) = " << sumtwenty << endl << endl;

    // Let's find overflow! We'll run a loop and report when the overflow occurs.  

    // Store the last and current sum
    short prevSumShort = 0;
    short currSumShort = 1;
    for (short upperLimShort = 1; upperLimShort < 5000; upperLimShort++) {
        currSumShort = calcSumShort(upperLimShort);
        if (currSumShort < prevSumShort) {
            cout << "For short, overflow occurs just before n = " << upperLimShort << "." << endl;
            cout << "calcSumShort(" << upperLimShort-1 << ") = " << prevSumShort << ";" << endl;
            cout << "calcSumShort(" << upperLimShort << ") = " << currSumShort << "." << endl << endl;
            break;
        }
        prevSumShort = currSumShort;
    }

    // We'll do it again for longs. Basic test:
    long twentythousand = 20000;
    long sumtwentythousand = calcSumLong(twentythousand);
    cout << "Basic test of longs: " << endl;
    cout << "n = " << twentythousand << "; calcSumLong(n) = " << sumtwentythousand << endl << endl;

    // Loop to find the overflow, yo
    // Store the last and current sum
    long prevSumLong = 0;
    long currSumLong = 1;

    // Start with coarse-grained search: from 1 to 5000000000, skip by 100000
    //     gives: 3037100001
    // Finer grain: from 3037000000 to 3037100000, step by 100
    //     overflows at 3037000600
    // Yet finer grain: from 3037000500 to 3037000600, step by 1
    for (long upperLimLong = 3037000500; upperLimLong < 3037000600; upperLimLong++) {
        currSumLong = calcSumLong(upperLimLong);
        if (currSumLong < prevSumLong) {
            cout << "For long, overflow occurs just before n = " << upperLimLong << "." << endl;
            cout << "calcSumLong(" << upperLimLong-1 << ") = " << prevSumLong << ";" << endl;
            cout << "calcSumLong(" << upperLimLong << ") = " << currSumLong << "." << endl << endl;
            break;
        }
        prevSumLong = currSumLong;
    }

    // Let's run some factorials.

    float prevFactFloat = 0;
    float currFactFloat = 1;
    cout << endl;
    for (long upperLimLong = 1; upperLimLong < 1000; upperLimLong++) {
        currFactFloat = calcFactFloat(upperLimLong);
        if (isinf(currFactFloat)) {
            cout << "For floats, factorial overflows just before n = " << upperLimLong << "." << endl;
            cout << "calcFactFloat(" << upperLimLong-1 << ") = " << prevFactFloat << ";" << endl;
            cout << "calcFactFloat(" << upperLimLong << ") = " << currFactFloat << "." << endl << endl;
            break;
        }
        prevFactFloat = currFactFloat;
    }


    // Double-precision factorial
    double prevFactDouble = 0;
    double currFactDouble = 1;
    for (long upperLimLong = 1; upperLimLong < 1000; upperLimLong++) {
        currFactDouble = calcFactDouble(upperLimLong);
        if (isinf(currFactDouble)) {
            cout << "For doubles, factorial overflows just before n = " << upperLimLong << "." << endl;
            cout << "calcFactDouble(" << upperLimLong-1 << ") = " << prevFactDouble << ";" << endl;
            cout << "calcFactDouble(" << upperLimLong << ") = " << currFactDouble << "." << endl << endl;
            break;
        }
        prevFactDouble = currFactDouble;
    }

    // Let's look at this weird reciprocal thing

    long recipLim = 2;
    float recipFloat = recipSumFloat(recipLim);
    cout << "Test of float recip: n = " << recipLim << ", sumRecipFloat(n) = " << recipFloat << endl;

    double recipDouble = recipSumDouble(recipLim);
    cout << "Test of double recip: n = " << recipLim << ", sumRecipDouble(n) = " << recipDouble << endl << endl;

    // Final section: Strangeness in for loop
    cout << "i is a float." << endl;
    for (float i = 3.4; i < 4.4; i+= 0.2) {
        cout << "i = " << i << endl;
    }
    cout << endl;

    cout << "i is a double." << endl;
    for (double i = 3.4; i < 4.4; i+= 0.2) {
        cout << "i = " << i << endl;
    }
    cout << endl;

    return 0;
}

// Function definitions

// Summation function (short int, signed)
short calcSumShort(short upperLim) {
    short theSum = 0;
    for (short i = 0; i < upperLim; i++) {
        theSum += i;
    }
    return theSum;
}

// Summation function (long int, signed)
long calcSumLong(long upperLim) {
   /*
   long theSum = 0;
   for (long i = 0; i < upperLim; i++) {
        theSum += i;
    }
   */
    // Way too slow for big, big numbers. We'll use Gauss's formula.
    return (upperLim*(upperLim-1))/2;
}

// Factorial function (long int/float, signed)
float calcFactFloat(long upperLim) {
    float theFact = 1;
    for (long i = 1; i <= upperLim; i++) {
        theFact *= i;
    }
    return theFact;
}

// Factorial function (long int/double, signed)
double calcFactDouble(long upperLim) {
    double theFact = 1;
    for (long i = 1; i <= upperLim; i++) {
        theFact *= i;
    }
    return theFact;
}

// Sum of reciprocals to illustrate floating-point pathology
// Float version
float recipSumFloat(long upperLim) {
    float theRecip = static_cast<float> (1.0/upperLim);
    for (long i = 1; i < upperLim; i++) {
        theRecip += theRecip;
    }
    return theRecip--;
}

// Double verion of sum of reciprocals
double recipSumDouble(long upperLim) {
    double theRecip = static_cast<double> (1.0/upperLim);
    for (long i = 1; i < upperLim; i++) {
        theRecip += theRecip;
    }
    return theRecip--;
}
