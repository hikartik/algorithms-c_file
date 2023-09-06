#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Function to add two large integers represented as strings
char* add(char* num1, char* num2) {
    int len1 = strlen(num1);
    int len2 = strlen(num2);
    int maxLen = (len1 > len2) ? len1 : len2;
    char* result = (char*)malloc((maxLen + 2) * sizeof(char)); // +1 for potential carry, +1 for null terminator
    result[maxLen + 1] = '\0';

    int carry = 0;
    for (int i = 0; i < maxLen; i++) {
        int digit1 = (i < len1) ? (num1[len1 - i - 1] - '0') : 0;
        int digit2 = (i < len2) ? (num2[len2 - i - 1] - '0') : 0;

        int sum = digit1 + digit2 + carry;
        result[maxLen - i] = (sum % 10) + '0';
        carry = sum / 10;
    }

    if (carry > 0) {
        result[0] = carry + '0';
        return result;
    } else {
        return result + 1; // Skip leading zero if there is no carry
    }
}

// Function to multiply two large integers using Karatsuba's algorithm
char* karatsuba(char* X, char* Y) {
    int lenX = strlen(X);
    int lenY = strlen(Y);

    // Base case: If either X or Y is a single digit, perform simple multiplication
    if (lenX == 1 || lenY == 1) {
        int result = atoi(X) * atoi(Y);
        char* res = (char*)malloc(20 * sizeof(char)); // Allocate enough space for the result
        snprintf(res, 20, "%d", result); // Convert the result to a string
        return res;
    }

    // Find the middle point of X and Y
    int mid = (lenX < lenY) ? lenX / 2 : lenY / 2;

    // Split X and Y into two parts
    char* Xl = strndup(X, mid);
    char* Xr = X + mid;
    char* Yl = strndup(Y, mid);
    char* Yr = Y + mid;

    // Recursive calls
    char* P1 = karatsuba(Xl, Yl);
    char* P2 = karatsuba(Xr, Yr);

    char* XlXr = add(Xl, Xr);
    char* YlYr = add(Yl, Yr);
    char* P3 = karatsuba(XlXr, YlYr);

    char* temp1 = add(P1, P2);
    char* temp2 = add(temp1, P3);

    // Calculate the result
    int maxLen = (lenX > lenY) ? lenX : lenY;
    char* result = (char*)malloc((2 * maxLen + 1) * sizeof(char));
    snprintf(result, 2 * maxLen + 1, "%s", P1);
    snprintf(result + maxLen, 2 * maxLen + 1 - maxLen, "%s", P2);

    char* temp = (char*)malloc((2 * maxLen + 1) * sizeof(char));
    snprintf(temp, 2 * maxLen + 1, "%s", P1);
    snprintf(temp + mid, 2 * maxLen + 1 - mid, "%s", P2);

    for (int i = 0; i < mid; i++) {
        result[maxLen + i] += (temp2[i] - '0') - (temp[i] - '0');
    }

    free(Xl);
    free(Yl);
    free(XlXr);
    free(YlYr);
    free(temp1);
    free(temp2);
    free(P1);
    free(P2);
    free(temp);

    return result;
}

int main() {
    char X[] = "3141592653589793238462643383279502884197169399375105820974944592";
    char Y[] = "2718281828459045235360287471352662497757247093699959574966967627";

    char* result = karatsuba(X, Y);

    printf("Result: %s\n", result);

    free(result);

    return 0;
}
