#include <stdio.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdlib.h>

/**
 * Library-level functions.
 * You should use them in the main sections.
 */

uint64_t convertToUint64 (double number) {
    return *((uint64_t *)(&number));
}

bool getBit (uint64_t number, const uint8_t index) {
    return ((number >> index) & 1) != 0;
}

/**
 * Simple checkers here
 */

bool checkSign(uint64_t number) {
    return getBit(number, 63);
}

bool checkInf(uint64_t number) {
    return ((number & 0x7FF0000000000000) == 0x7FF0000000000000) &&
           ((number & 0x000FFFFFFFFFFFFF) == 0);
}

bool checkNormal(uint64_t number) {
    return ((number & 0x7FF0000000000000) != 0) &&
           !checkInf(number & 0x7FF0000000000000);
}

bool checkDenormal(uint64_t number) {
    return ((number & 0x7FF0000000000000) == 0) &&
           ((number & 0x000FFFFFFFFFFFFF) != 0);
}

bool checkNaN(uint64_t number) {
    return ((number & 0x7FF0000000000000) == 0x7FF0000000000000);
}

/**
 * Checkers here:
 */

bool checkForPlusZero (uint64_t number) {
    return number == 0x0000000000000000;
}

bool checkForMinusZero (uint64_t number) {
    return number == 0x8000000000000000;
}

bool checkForPlusInf (uint64_t number) {
    return !checkSign(number) && checkInf(number);
}

bool checkForMinusInf (uint64_t number) {
    return checkSign(number) && checkInf(number);
}

bool checkForPlusNormal (uint64_t number) {
    return !checkSign(number) && checkNormal(number);
}

bool checkForMinusNormal (uint64_t number) {
    return checkSign(number) && checkNormal(number);
}

bool checkForPlusDenormal (uint64_t number) {
    return checkSign(number) && checkDenormal(number);
}

bool checkForMinusDenormal (uint64_t number) {
    return !checkSign(number) && checkDenormal(number);
}

bool checkForSignalingNan (uint64_t number) {
    return checkNaN(number) &&
           ((number & 0x0007FFFFFFFFFFFF) != 0) &&
           !getBit(number, 51);
}

bool checkForQuietNan (uint64_t number) {
    return checkNaN(number) &&
           (number & 0x0008000000000000) != 0;
}


void classify (double number) {
    if (checkForPlusZero(convertToUint64(number))) {
        printf("Plus zero\n");
    }

    else if (checkForMinusZero(convertToUint64(number))) {
        printf("Minus zero\n");
    }

    else if (checkForPlusInf(convertToUint64(number))) {
        printf("Plus inf\n");
    }

    else if (checkForMinusInf(convertToUint64(number))) {
        printf("Minus inf\n");
    }

    else if (checkForPlusNormal(convertToUint64(number))) {
        printf("Plus normal\n");
    }

    else if (checkForMinusNormal(convertToUint64(number))) {
        printf("Minus normal\n");
    }

    else if (checkForPlusDenormal(convertToUint64(number))) {
        printf("Plus Denormal\n");
    }

    else if (checkForMinusDenormal(convertToUint64(number))) {
        printf("Minus Denormal\n");
    }

    else if (checkForSignalingNan(convertToUint64(number))) {
        printf("Signailing NaN\n");
    }

    else if (checkForQuietNan(convertToUint64(number))) {
        printf("Quiet NaN\n");
    }

    else {
        printf("Error.\n");
    }
}
