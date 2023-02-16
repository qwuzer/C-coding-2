#include "mymatch.h"
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

int mymatch(char ***pppList, const char *pStr, const char *pPattern)
{   
    pppList = malloc( sizeof( char* ) );
    *pppList = calloc( 1024 , sizeof( char* ) );

    char *str = strdup(pStr);//turning const char string into char array
    int32_t strLen = strlen(str);//since strtok modifies the element
    char str1[strLen + 1 ];
    strcpy( str1 , str ); 

    char *token = strtok( str1 , " " );
    int32_t plen = strlen( pPattern );

    int32_t i = 0;
    int32_t count = 0;

    while( token != NULL )
    {

        const char *pattern = pPattern;//resets pPattern 

        int32_t toklen = strlen(token);
        //printf("%d: %s , len = %d\n",i,token,toklen);


        bool T[toklen+1][plen+1];//lookup table
        memset( T , false , sizeof(T) );


        T[0][0] = true;//empty string to empty pattern

        for( int32_t j = 1 ; j <= plen ; j++ )//starts from 1 since T[0][0] is reserved ( both are empty string
        {
            if( pattern[j-1] == '*' )
            {
                T[0][j] = T[0][j-1];
            }
        }

        for( int32_t i = 1 ; i <= toklen ; i++ )
        {
            for( int32_t j = 1 ; j <= plen ; j++ )
            {
                if( pattern[j-1] == '?' || pattern[j-1] == token[i-1] )
                {
                    T[i][j] = T[i-1][j-1];
                }
                else if( pattern[j-1] == '*' )
                {
                    T[i][j] = T[i-1][j] || T[i][j-1];// * is any char || * is empty sequence
                }
                else
                {
                    T[i][j] = false;
                }
            }
        }

        if( T[toklen][plen] )
        {
            (*pppList)[count] = (char*)malloc( sizeof( char ) * (toklen + 1));
            strcpy( (*pppList)[count] , token );
            count++;
        }

        token = strtok( NULL , " " );
        i++;   
    }
    /*
    for( int32_t i = 0 ; i < count ; i++ )
    {
        printf("%s\n",(*pppList)[i]);
    }
    */

    return count;
}