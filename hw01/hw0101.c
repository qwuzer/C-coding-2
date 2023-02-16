#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#define BUFFER_SIZE 10000000

int main()
{
    char *buffer = malloc(sizeof(char) * BUFFER_SIZE);
    fgets(buffer, BUFFER_SIZE, stdin); //"abc.../n <--- newline is scanned"
    int32_t length = strlen(buffer);

    if ((length - 1) % 2)
    {
        printf("Invalid input.\n");
        return 0;
    }

    buffer[length - 1] = 0; //turns /n into /0
    char *string = malloc(sizeof(char) * length);
    strncpy(string, buffer, length);
    printf("%s %d\n", string, length);
    puts(string);

    free(buffer);
    buffer = NULL;


    for (int32_t i = 0  ; i < length - 1 ;  i++)
    {
        printf("str[%d] = %c\n",i,string[i]);
        switch (string[i])
        {
        case '0':
            string[i] = '0';
            break;
        case '1':
            string[i] = '8';
            break;
        case '2':
            string[i] = '4';
            break;
        case '3':
            string[i] = 'C';
            break;
        case '4':
            string[i] = '2';
            break;
        case '5':
            string[i] = 'A';
            break;
        case '6':
            string[i] = '6';
            break;
        case '7':
            string[i] = 'E';
            break;
        case '8':
            string[i] = '1';
            break;
        case '9':
            string[i] = '9';
            break;
        case 'A':
            string[i] = '5';
            break;
        case 'B':
            string[i] = 'D';
            break;
        case 'C':
            string[i] = '3';
            break;
        case 'D':
            string[i] = 'B';
            break;
        case 'E':
            string[i] = '7';
            break;
        case 'F':
            string[i] = 'F';
            break;
        case 'a':
            string[i] = '5';
            break;
        case 'b':
            string[i] = 'D';
            break;
        case 'c':
            string[i] = '3';
            break;
        case 'd':
            string[i] = 'B';
            break;
        case 'e':
            string[i] = '7';
            break;
        case 'f':
            string[i] = 'F';
            break;
        default:
            printf("Invalid input.");
            return 0;
        }
    }
    /*
        puts(binStr2);      
        char substr[9] = {0};
        strncmp( substr , binStr2 , 8 );
        int32_t ans = 0;
        for( int32_t i = 7 ; i >= 0 ; i-- )
        {
            ans += (substr[i] - '0') * pow( 2 , i);
        }
        */

    //printf("\nans = %d\n", ans);
    //puts(string);
    
    for( int32_t i = 0 ; i < length - 2 ; i++ )
    {
        int32_t dec = 0;
        int32_t base = 16;
        for (int32_t j = i + 1; j >=  i ; j-- )
        {
            if (string[j] >= '0' && string[j] <= '9')
            {
                dec += (string[j] - '0') * base;
                base /= 16;
            }
            else if (string[j] >= 'A' && string[j] <= 'F')
            {
                dec += (string[j] - 55) * base;
                base /= 16;
            }
            else
            {
                printf("Invalid input.\n");
                return 0;
            }
        } 

        //printf("dec = %d\n",dec);

        if(dec >= 32 && dec <= 126)
        {
            printf("%c",dec);
        }
        else if( dec == 0 )
        {
            return 0; 
        }
        else
        {
            printf("Invalid input.");
        }

        i++;
    }
    return 0;
}

//puts(binStr2);
/*

    for ( int32_t i = 0; i < length - 2; i++ )
    {
        int32_t dec = 0;
        int32_t base = 16;
        for (int32_t j = i; j < i + 2; j++)
        {
            if (string[j] >= '0' && string[j] <= '9')
            {
                dec += (string[j] - '0') * base;
                base /= 16;
            }
            else if (string[j] >= 'a' && string[j] <= 'f')
            {
                dec += (string[j] - 'a') * base;
                base /= 16;
            }
            else if (string[j] >= 'A' && string[j] <= 'F')
            {
                dec += (string[j] - 'A') * base;
                base /= 16;
            }
            else
            {
                printf("Invalid input.\n");
                return 0;
            }
        }
        i++;
        //printf("\ndec is %d",dec);

    }


*/