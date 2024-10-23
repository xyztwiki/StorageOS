#include <stdio.h>
#include <math.h>

int main() {
    double x = 4.0;
    double y = 2.0;

    printf("Math Library Demonstration\n");
    printf("==========================\n");

    // Basic arithmetic functions
    printf("sqrt(%.1f) = %.2f\t\t// Square root\n", x, sqrt(x));
    printf("pow(%.1f, %.1f) = %.2f\t\t// x raised to power y\n", x, y, pow(x, y));
    printf("exp(%.1f) = %.2f\t\t// e raised to power x\n", x, exp(x));
    printf("log(%.1f) = %.2f\t\t// Natural logarithm\n", x, log(x));
    printf("log10(%.1f) = %.2f\t\t// Base-10 logarithm\n", x, log10(x));

    // Rounding and absolute value functions
    printf("ceil(3.6) = %.1f\t\t// Round up to nearest integer\n", ceil(3.6));
    printf("floor(3.6) = %.1f\t\t// Round down to nearest integer\n", floor(3.6));
    printf("round(3.6) = %.1f\t\t// Round to nearest integer\n", round(3.6));
    printf("fabs(-5.2) = %.1f\t\t// Absolute value\n", fabs(-5.2));

    // Trigonometric functions (input in radians)
    printf("sin(PI/4) = %.2f\t\t// Sine\n", sin(M_PI/4));
    printf("cos(PI/4) = %.2f\t\t// Cosine\n", cos(M_PI/4));
    printf("tan(PI/4) = %.2f\t\t// Tangent\n", tan(M_PI/4));

    // Inverse trigonometric functions (return value in radians)
    printf("asin(1.0) = %.2f\t\t// Arc sine\n", asin(1.0));
    printf("acos(0.0) = %.2f\t\t// Arc cosine\n", acos(0.0));
    printf("atan(1.0) = %.2f\t\t// Arc tangent\n", atan(1.0));

    // Hyperbolic functions
    printf("sinh(1.0) = %.2f\t\t// Hyperbolic sine\n", sinh(1.0));
    printf("cosh(1.0) = %.2f\t\t// Hyperbolic cosine\n", cosh(1.0));
    printf("tanh(1.0) = %.2f\t\t// Hyperbolic tangent\n", tanh(1.0));

    // Other useful functions
    printf("fmod(5.0, 2.0) = %.2f\t\t// Floating-point remainder\n", fmod(5.0, 2.0));
    printf("hypot(3.0, 4.0) = %.2f\t// Hypotenuse of right-angled triangle\n", hypot(3.0, 4.0));

    return 0;
}