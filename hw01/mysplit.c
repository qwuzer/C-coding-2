#include "mystring.h"
#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <stdlib.h>


int mystrsplit(char ***ppList, int *pCounter, const char *pStr, const char *pSeparator)
{
    int32_t count = 0;//pCounter
    char *pstr = (char*)pStr;
    char *psep = (char*)pSeparator;
    int32_t seplen = strlen( psep );

    if( pstr == NULL )
    {
        ppList = NULL;
        return -1;
    }

    if( pstr == 0 )//empty pstr
    {
        (*ppList)[0] = "";
        *pCounter = 1;
        return 0;
    }

    

    /*
    if( psep == NULL || psep == 0 )//--> ""sep
    {
        printf
    } 
    */

    for( ; *pstr ; )//count the keypstr
    {
        if( strstr(pstr, psep) == pstr )
        {
            count += 1;
            pstr += seplen - 1;
        }
        pstr++;
    }
    if( count )
    {
        *pCounter = count + 1;
    }
    else
    {
        ppList = NULL;
        return -1;
    }

    *ppList = (char**)malloc( sizeof(char*) * count );

    pstr= (char*)pStr;
    int32_t toklen = 1;
    int32_t i = 0;
    for( ; *pstr ;)
    {
        if( strcasestr( pstr , psep) == pstr )
        {
            (*ppList)[i] = (char*)malloc( sizeof( char ) * toklen);
            toklen = 0;
            pstr += seplen;//pstr jumps to next char
            i++;
        } 
        toklen++;
        pstr++;       
    }

    pstr = (char*)pStr;
    i = 0;
    char *p = (*ppList)[i];
    for( ; *pstr ; pstr++ )
    {
        if(strcasestr( pstr , psep) != pstr )//cpys the pstr value to p
        {
            *p = *pstr;
            p++;
        }
        else//when key is found, end the corresponding char pointer with a 0 
        {
            *p = 0;
            i++;
            p = (*ppList)[i];
        }
    }

    return 0;

}
    /*
    if( pstr == NULL )//when the entered pstr is NULL ,return a empty pstr
    {
        (*ppList)[0] = "";
        *pCounter = 1;
        return 0;
    }
    
    for( ; *pstr ; pstr++ )//count the keypstr
    {
        if( strstr(pstr, str) == pstr )
        {
            count += 1;
        }
    }
    if( count )
    {
        *pCounter = count + 1;
    }

    *ppList = (char**)malloc( sizeof(char*) * count );
    if( *ppList == NULL )
    {
        return -1;
    }

    int32_t strLen = strlen(pSeparator);
    pstr = (char*)pStr;
    int32_t toklen = 1;
    int32_t i = 0;
    for( ; *pstr ;)
    {
        if( strcasestr( pstr , str) == pstr )
        {
            (*ppList)[i] = (char*)malloc( sizeof( char ) * toklen);
            toklen = 0;
            pstr += strLen;//pstr jumps to next char
            i++;
        } 
        toklen++;
        pstr++;       
    }

    pstr = (char*)pStr;
    i = 0;
    char *p = (*ppList)[i];
    for( ; *pstr ; pstr++ )
    {
        if(strcasestr( pstr , str) != pstr )//cpys the pstr value to p
        {
            *p = *pstr;
            p++;
        }
        else//when key is found, end the corresponding char pointer with a 0 
        {
            *p = 0;
            i++;
            p = (*ppList)[i];
        }
    }

    */
    
