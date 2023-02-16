#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include "myvector.h"

/*
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
*/


sVector *myvector_init()
{
    sVector *x = malloc(sizeof(sVector));
    memset(x, 0, sizeof(*x));
    return x;
}

int myvector_set(sVector *pVector, uint8_t type, double a, double b)
{
    if (type == 1)
    {
        (*pVector).type = type;
        (*pVector).data.c.x = a;
        (*pVector).data.c.y = b;
        return 0;
    }
    else if (type == 2)
    {
        if ((*pVector).data.p.distance && ((*pVector).data.p.angle >= 0 || (*pVector).data.p.angle <= 2 * M_PI))
        {
            (*pVector).type = type;
            (*pVector).data.p.distance = a;
            (*pVector).data.p.angle = b;
            return 0;
        }
        else
        {
            return -1;
        }
    }
    else
    {
        return -1;
    }
}

int myvector_print(const sVector *pVector, uint8_t type)
{
    if (type == 1)
    {
        printf("(%lf,%lf)\n", (*pVector).data.c.x, (*pVector).data.c.y);
        return 0;
    }
    else if (type == 2)
    {
        double theta = (*pVector).data.p.angle / M_PI;
        if (theta < 0 || theta > 2)
        {
            return -1;
        }
        else
        {
            printf("(%lf,%lf-pi", (*pVector).data.p.distance, theta);
            return 0;
        }
    }
    else
    {
        return -1;
    }
}

int myvector_add(sVector *pA, const sVector *pB, const sVector *pC)
{
    if ((*pB).type == 1)
    {
        if ((*pC).type == 1)
        {
            (*pA).type = (*pB).type;
            (*pA).data.c.x = (*pB).data.c.x + (*pC).data.c.x;
            (*pA).data.c.y = (*pB).data.c.y + (*pC).data.c.y;
            return 0;
        }
        else if ((*pC).type == 2)
        {
            double x1 = (*pC).data.p.distance * cos((*pC).data.p.angle);
            double y1 = (*pC).data.p.distance * sin((*pC).data.p.angle);
            (*pA).type = (*pB).type;
            (*pA).data.c.x = (*pB).data.c.x + x1;
            (*pA).data.c.y = (*pB).data.c.y + y1;
            return 0;
        }
        else
        {
            return -1;
        }
    }
    else if ((*pB).type == 2)
    {
        if ((*pC).type == 2)
        {
            double a1 = (*pB).data.p.angle;
            double a2 = (*pC).data.p.angle;
            double r1 = (*pB).data.p.distance;
            double r2 = (*pC).data.p.distance;

            (*pA).data.p.angle = a1 + atan2(r2 * sin(a2 - a1), r1 + r2 * cos(a1 - a2));
            (*pA).data.p.distance = sqrt(r1 * r1 + r2 * r2 + 2 * r1 * r2 * cos(a1 - a2));
            return 0;
        }
        else if ((*pC).type == 1)
        {
            double x2 = (*pC).data.c.x;
            double y2 = (*pC).data.c.y;

            double r1 = (*pB).data.p.distance;
            double r2 = sqrt(x2 * x2 + y2 + y2);
            double a1 = (*pB).data.p.angle;
            double a2 = acos(x2 / r2);

            (*pA).data.p.angle = a1 + atan2(r2 * sin(a2 - a1), r1 + r2 * cos(a1 - a2));
            (*pA).data.p.distance = sqrt(r1 * r1 + r2 * r2 + 2 * r1 * r2 * cos(a1 - a2));
            return 0;
        }
        else
        {
            return -1;
        }
    }
    else
    {
        return -1;
    }
}

int myvector_inner_product(double *pA, const sVector *pB, const sVector *pC)
{
    if ((*pB).type == 1)
    {
        if ((*pC).type == 1)
        {
            *pA = (*pB).data.c.x * (*pC).data.c.x + (*pB).data.c.y * (*pC).data.c.y;
            return 0;
        }
        else if ((*pC).type == 2)
        {
            double x2 = (*pC).data.p.distance * cos((*pC).data.p.angle);
            double y2 = (*pC).data.p.distance * sin((*pC).data.p.angle);
            *pA = (*pB).data.c.x * x2 + (*pB).data.c.y * y2;
            return 0;
        }
        else
        {
            return -1;
        }
    }
    else if ((*pB).type == 2)
    {
        if ((*pC).type == 1)
        {
            double x1 = (*pB).data.p.distance * cos((*pB).data.p.angle);
            double y1 = (*pB).data.p.distance * sin((*pB).data.p.angle);
            *pA = x1 * (*pC).data.c.x + y1 * (*pC).data.c.y;
            return 0;
        }
        else if( (*pC).type == 2)
        {
            *pA = (*pB).data.p.distance * (*pC).data.p.distance * cos((*pB).data.p.angle - (*pC).data.p.angle);
        }
        else 
        {
            return -1;
        }
    }
    else
    {
        return -1;
    }
    return -1;
}

int myvector_area(double *pArea, const sVector *pB, const sVector *pC)
{
    if ((*pB).type == 1)
    {
        if ((*pC).type == 1)
        {
            double x1 = (*pB).data.c.x;
            double x2 = (*pC).data.c.x;
            double y1 = (*pB).data.c.y;
            double y2 = (*pC).data.c.y;
            *pArea = fabs( x1 * y2 - x2 * y1 );
            return 0;
        }
        else if ((*pC).type == 2)
        {
            double x1 = (*pB).data.c.x;
            double y1 = (*pB).data.c.y;
            double x2 = (*pC).data.p.distance * cos((*pC).data.p.angle);
            double y2 = (*pC).data.p.distance * sin((*pC).data.p.angle);
            *pArea = fabs( x1 * y2 - x2 * y1 );
            return 0;
        }
        else
        {
            return -1;
        }
    }
    else if ((*pB).type == 2)
    {
        if ((*pC).type == 1)
        {
            double x1 = (*pB).data.p.distance * cos((*pB).data.p.angle);
            double y1 = (*pB).data.p.distance * sin((*pB).data.p.angle);
            double x2 = (*pC).data.c.x;
            double y2 = (*pC).data.c.y;
            *pArea = fabs( x1 * y2 - x2 * y1 );
            return 0;
        }
        else if( (*pC).type == 2)
        {
            double x1 = (*pB).data.p.distance * cos((*pB).data.p.angle);
            double y1 = (*pB).data.p.distance * sin((*pB).data.p.angle);
            double x2 = (*pC).data.p.distance * cos((*pC).data.p.angle);
            double y2 = (*pC).data.p.distance * sin((*pC).data.p.angle);
            *pArea = fabs( x1 * y2 - x2 * y1 );
            return 0;
        }
        else 
        {
            return -1;
        }
    }
    else
    {
        return -1;
    }
}



