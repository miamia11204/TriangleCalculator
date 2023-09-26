#define _CRT_SECURE_NO_WARNINGS
#define PI 3.14159265359

#include <stdio.h>
#include <math.h>
#include <stdbool.h>
#include <ctype.h>

//Converting angles to radians for calculating
double toRadians(double input) {
    return input * PI / 180.0;
}

//Express angles in degrees for reports
double toDegrees(double radians) {
    return radians * 180.0 / PI;
}

//Printing triangles
void printTriangle(const char attribute[4], double a, double b, double c, double alpha, double beta, double gamma) {
    if (isnan(alpha) || isnan(beta) || isnan(gamma)) {
        printf("Impossible triangle\n");
    }
    else {
        //Printing length of the three sides (a b c)  in one column, then the three opposite angles in the second column
        printf("\nFormat: %s", attribute);
        printf("\na =  %6.3f      alpha =  %6.3f\n", a, alpha);
        printf("b =  %6.3f      beta  =  %6.3f\n", b, beta);
        printf("c =  %6.3f      gamma =  %6.3f\n", c, gamma);

        //Calculating perimeter, area
        double perimeter = a + b + c;
        double s = perimeter / 2.0;
        double area = sqrt(s * (s - a) * (s - b) * (s - c));

        printf("Perimeter = %.3f\n", perimeter);
        printf("Area      = %.3f\nType      = ", area);

        //Output triangle's types
        if (a == b && b == c) {
            printf("equilateral, ");
        }
        else if (a == b || b == c || c == a) {
            printf("isosceles, ");
        }
        else {
            printf("scalene, ");
        }

        if (alpha > 90 || beta > 90 || gamma > 90) {
            printf("obtuse\n\n");
        }
        else if (alpha == 90 || beta == 90 || gamma == 90) {
            printf("right\n\n");
        }
        else {
            printf("acute\n\n");
        }
    }
}

//Specify for each type of triangle
void calcSSS(const char attribute[4], double a, double b, double c) {
    a = fabs(a);
    b = fabs(b);
    c = fabs(c);

    double cosAlpha = (b * b + c * c - a * a) / (2.0 * b * c);
    double cosBeta = (c * c + a * a - b * b) / (2.0 * c * a);
    double cosGamma = (a * a + b * b - c * c) / (2.0 * a * b);

    double alpha = toDegrees(acos(cosAlpha));
    double beta = toDegrees(acos(cosBeta));
    double gamma = toDegrees(acos(cosGamma));

    printTriangle(attribute, a, b, c, alpha, beta, gamma);
}

void calcSAS(const char attribute[4], double a, double gamma, double b) {
    a = fabs(a);
    gamma = fabs(gamma);
    b = fabs(b);

    double cosAlpha = cos(toRadians(gamma));
    double c = sqrt(a * a + b * b - 2.0 * a * b * cosAlpha);

    double cosBeta = (a * a + c * c - b * b) / (2.0 * a * c);
    double beta = toDegrees(acos(cosBeta));

    double alpha = 180.0 - gamma - beta;

    printTriangle(attribute, a, b, c, alpha, beta, gamma);
}

void calcASA(const char attribute[4], double alpha, double a, double beta) {
    a = fabs(a);
    alpha = fabs(alpha);
    beta = fabs(beta);

    double cosAlpha = cos(toRadians(alpha));
    double cosBeta = cos(toRadians(beta));

    double gamma = 180.0 - alpha - beta;

    double b = a * sin(toRadians(beta)) / sin(toRadians(gamma));
    double c = a * sin(toRadians(alpha)) / sin(toRadians(gamma));

    printTriangle(attribute, a, b, c, alpha, beta, gamma);
}

void calcSSA(const char attribute[4], double b, double c, double beta) {
    b = fabs(b);
    c = fabs(c);
    beta = fabs(beta);
    // Check the conditions
    if (beta >= 90 && b > c) {
        double gamma = asin((c * sin(beta * PI / 180)) / b) * 180 / PI;
        double alpha = 180 - beta - gamma;
        double a = (sin(alpha * PI / 180) * b) / sin(beta * PI / 180);

        printTriangle(attribute, a, b, c, alpha, beta, gamma);
    }
    else if (beta < 90 && b >= c) {
        double gamma = asin((c * sin(beta * PI / 180)) / b) * 180 / PI;
        double alpha = 180 - beta - gamma;
        double a = (sin(alpha * PI / 180) * b) / sin(beta * PI / 180);

        printTriangle(attribute, a, b, c, alpha, beta, gamma);
    }
    else if (sin(beta * PI / 180) < (b / c)) {
        double sinA = b / c;
        double cosA = sqrt(1 - sinA * sinA);
        double solution1_a = c * cosA + sqrt(b * b - c * c * sinA * sinA);
        double solution2_a = c * cosA - sqrt(b * b - c * c * sinA * sinA);

        // Solve for the angles in the first solution
        double alpha1 = acos((solution1_a * solution1_a + c * c - b * b) / (2 * solution1_a * c)) * 180 / PI;
        double gamma1 = 180 - alpha1 - beta;

        // Solve for the angles in the second solution
        double alpha2 = acos((solution2_a * solution2_a + c * c - b * b) / (2 * solution2_a * c)) * 180 / PI;
        double gamma2 = 180 - alpha2 - beta;

        printf("\nFormat: %s", attribute);

        //First solution
        printf("--> gamma");
        printf("\na =  %6.3f      alpha =  %6.3f\n", solution1_a, alpha1);
        printf("b =  %6.3f      beta  =  %6.3f\n", b, beta);
        printf("c =  %6.3f      gamma =  %6.3f\n", c, gamma1);
        //Calculating perimeter, area
        double perimeter = solution1_a + b + c;
        double s = perimeter / 2.0;
        double area = sqrt(s * (s - solution1_a) * (s - b) * (s - c));
        printf("Perimeter = %.3f\n", perimeter);
        printf("Area      = %.3f\nType      = ", area);
        //Output triangle's types
        if (solution1_a == b && b == c) {
            printf("equilateral, ");
        }
        else if (solution1_a == b || b == c || c == solution1_a) {
            printf("isosceles, ");
        }
        else {
            printf("scalene, ");
        }

        if (alpha1 > 90 || beta > 90 || gamma1 > 90) {
            printf("obtuse\n\n");
        }
        else if (alpha1 == 90 || beta == 90 || gamma1 == 90) {
            printf("right\n\n");
        }
        else {
            printf("acute\n\n");
        }

        //Second solution
        printf("--> gamma'");
        printf("\na =  %6.3f      alpha =  %6.3f\n", solution2_a, alpha2);
        printf("b =  %6.3f      beta  =  %6.3f\n", b, beta);
        printf("c =  %6.3f      gamma =  %6.3f\n", c, gamma2);
        //Calculating perimeter, area
        perimeter = solution2_a + b + c;
        s = perimeter / 2.0;
        area = sqrt(s * (s - solution2_a) * (s - b) * (s - c));
        printf("Perimeter = %.3f\n", perimeter);
        printf("Area      = %.3f\nType      = ", area);
        //Output triangle's types
        if (solution2_a == b && b == c) {
            printf("equilateral, ");
        }
        else if (solution2_a == b || b == c || c == solution2_a) {
            printf("isosceles, ");
        }
        else {
            printf("scalene, ");
        }

        if (alpha2 > 90 || beta > 90 || gamma2 > 90) {
            printf("obtuse\n\n");
        }
        else if (alpha2 == 90 || beta == 90 || gamma2 == 90) {
            printf("right\n\n");
        }
        else {
            printf("acute\n\n");
        }
    }
    else {
        printf("Impossible triangle\n");
    }
}

int main() {
    printf("TriCalculator (c) 2023, Mia Nguyen\n\n");

    //Read String and followed by three real nums
    //Declaration
    char input[30];
    char attribute[4];
    int count;
    double a = 0.000;
    double b = 0.000;
    double c = 0.000;
    double alpha = 0.000;
    double beta = 0.000;
    double gamma = 0.000;
    char remaining[100];
    do {
        printf("-> ");
        fgets(input, sizeof(input), stdin);

        // Convert the input string to uppercase
        for (int i = 0; i < strlen(input); i++) {
            input[i] = toupper(input[i]);
        }

        // Exit case
        if (strcmp(input, "QUIT") == 0 || strcmp(input, "EXIT") == 0 || strcmp(input, "BYE") == 0) {
            break;
        }

        if (sscanf(input, "%3s %lf %lf %lf %[^\n]", attribute, &a, &b, &c, remaining) != 4) {
            printf("Bad command: Format # # # \nWhere Format = SSS|SAS|ASA|SSA \n      # = a real number\n\n");
            continue;
        }

        if (strcmp(attribute, "SSS") != 0 && strcmp(attribute, "SAS") != 0 && strcmp(attribute, "ASA") != 0 && strcmp(attribute, "SSA") != 0) {
            printf("Unknown command triangle format '%s'\n", attribute);
            continue;
        }


        if (strcmp(attribute, "SSS") == 0) {
            // Side-Side-Side (SSS) triangle
            count = sscanf(input, "%s %lf %lf %lf", attribute, &a, &b, &c);
            if (count != 4) //if inputs are not correct
            {
                printf("Bad command: Format # # # \nWhere Format = SSS|SAS|ASA|SSA \n      # = a real number\n\n");
                continue;
            }
            if ((a + b > c) || (b + c > a) || (c + a > b)) {
                calcSSS(attribute, a, b, c);
            }
            else {
                printf("Impossible triangle\n");
                continue;
            }
        }
        else if (strcmp(attribute, "SAS") == 0) {
            // Side-Angle-Side (SAS) triangle
            count = sscanf(input, "%s %lf %lf %lf", attribute, &a, &alpha, &b);
            if (count != 4) //if inputs are not correct
            {
                printf("Bad command: Format # # # \nWhere Format = SSS|SAS|ASA|SSA \n      # = a real number\n\n");
                continue;
            }
            if ((a + b > c) || (b + c > a) || (c + a > b)) {
                calcSAS(attribute, a, alpha, b);
            }
            else {
                printf("Impossible triangle\n");
                continue;
            }
        }
        else if (strcmp(attribute, "ASA") == 0) {
            // Angle-Side-Angle (ASA)
            count = sscanf(input, "%s %lf %lf %lf", attribute, &alpha, &a, &beta);
            if (count != 4) //if inputs are not correct
            {
                printf("Bad command: Format # # # \nWhere Format = SSS|SAS|ASA|SSA \n     # = a real number\n\n");
                continue;
            }
            if ((a + b > c) || (b + c > a) || (c + a > b)) {
                calcASA(attribute, alpha, a, beta);
            }
            else {
                printf("Impossible triangle\n");
                continue;
            }

        }
        else if (strcmp(attribute, "SSA") == 0) {
            // Side-Side-Angle (SSA)
            count = sscanf(input, "%s %lf %lf %lf", attribute, &b, &c, &beta);
            if (count != 4) //if inputs are not correct
            {
                printf("Bad command: Format # # # \nWhere Format = SSS|SAS|ASA|SSA \n      # = a real number\n\n");
                continue;
            }
            if ((a + b > c) || (b + c > a) || (c + a > b)) {
                calcSSA(attribute, b, c, beta);
            }
            else {
                printf("Impossible triangle\n");
                continue;
            }
        }
    } while (1);
    return 0;
}