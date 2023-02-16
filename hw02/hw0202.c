#include <stdio.h>
#include <stdint.h>

int8_t frac[52] = {0};

union _dcast
{
    double d;
    struct
    {
        uint64_t fraction : 52;
        uint64_t exponent : 11;
        uint64_t sign : 1;
    } parts;
}dcast;

void printBinary(int64_t n, int64_t i)
{
    int64_t k;
    int32_t j = 0;
    for( int32_t m = 0 ; m < 52 ; m++)
    {
        frac[m] = 0;
    }
    for (k = i - 1; k >= 0; k--) 
    {
        if ((n >> k) & 1)
        {
            printf("1");
            frac[j] = 1;
            j++;
        }
        else
        {
            printf("0");
            j++;
        }
    }
}

int main()
{
    printf("Please enter a floating-point number (double precision):");
    
    scanf("%lf",&dcast.d);

    printf("Sign: %d\n",dcast.parts.sign);
    printf("Exponent: ");
    printBinary(dcast.parts.exponent, 11);
    printf("\n");
    printf("Fraction: ");
    printBinary(dcast.parts.fraction, 52);
    printf("\n");

    printf("%lf = (-1)^%d * (1",dcast.d,dcast.parts.sign);
    for( int32_t k = 0 ; k < 52 ; k++ )
    {
        if(frac[k] == 1)
        {
            printf(" + ");
            printf("2^-%d",k+1);
        }
    }
    printf(") * 2^(%d - 1023)",dcast.parts.exponent);

    return 0;
}
