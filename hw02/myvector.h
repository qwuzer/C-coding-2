#include <stdio.h>
#include <stdint.h>
#pragma once

typedef struct _sVector
{
    uint8_t type; // 1: Cartesian coordinates; 2: polar coordinates
    union Component
    {
        struct _sCartesian
        {
            double x;
            double y;
        } c;
        struct _sPolar
        {
            double distance;
            double angle;
        } p;
    } data;
} sVector;

sVector *myvector_init();

int myvector_set(sVector *pVector, uint8_t type, double a, double b);

int myvector_print(const sVector *pVector, uint8_t type);

int myvector_add(sVector *pA, const sVector *pB, const sVector *pC);

int myvector_inner_product(double *pA, const sVector *pB, const sVector *pC);

int myvector_area(double *pArea, const sVector *pB, const sVector *pC);

int myvector_cvp(double *pX, double *pY, const double *pTx, const double *pTy, const sVector *pA, const sVector *pB);