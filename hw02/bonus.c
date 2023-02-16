#include <stdio.h> 
#include <stdint.h>
int main()
{
    int32_t number = 0;
    scanf("%d", &number);
    int32_t bit = 1;
    bit = bit << 30;
    printf("bit = %d\n",bit);
    for (int i = 0; i < 32; i++)
    {
        if (bit & number)
        {
            printf("1");
            printf("  bit = %d " , bit );
        }
        else
        {
            printf("0");
        }
        bit = bit >> 1;
    }
    return 0;
}