#include "mystring.h"
#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <ctype.h>
#include <errno.h>
#include <limits.h>

long int mystrtol(const char *nptr, char **endptr, int base)
{
    char *ptr1 = (char *)nptr;
    char c1;
    int8_t sign = 1;

    c1 = *ptr1;
    while (isspace(c1))
    {
        c1 = *ptr1++; // note that ptr1 is ahead by one byte of c1
    }
    if (c1 == '-')
    {
        sign = -1;
        c1 = *ptr1++;
    }
    if (c1 == '+')
    {
        c1 = *ptr1++;
    }

    if (base == 0 || base == 16)
    {
        if (c1 == '0' && (*ptr1 == 'x' || *ptr1 == 'X'))
        {
            c1 = ptr1[1];
            ptr1 += 2;
            base = 16;
        }
    }

    if (base == 0)
    {
        if (c1 == '0')
        {
            base = 8;
        }
        else
        {
            base = 10;
        }
    }

    if ((base < 2 || base > 36) && base != 0)
    {
        errno = EINVAL;
        return 0;
    }

    int32_t any, cutlim;
    long acc, cutoff;
    cutoff = sign ? LONG_MAX : LONG_MIN;
    cutlim = cutoff % base;
    cutoff /= base;

    if (sign == -1)
    {
        if (cutlim > 0)
        {
            cutlim -= base;
            cutoff += 1;
        }
        cutlim = -cutlim;
    }
    for (acc = 0, any = 0;; c1 = (unsigned char)*ptr1++)
    {
        if (isdigit(c1))
            c1 -= '0';
        else if (isalpha(c1))
            c1 -= isupper(c1) ? 'A' - 10 : 'a' - 10;
        else
            break;
        if (c1 >= base)
            break;
        if (any < 0)
            continue;
        if (sign == -1)
        {
            if (acc < cutoff || (acc == cutoff && c1 > cutlim))
            {
                any = -1;
                acc = LONG_MIN;
                errno = ERANGE;
            }
            else
            {
                any = 1;
                acc *= base;
                acc -= c1;
            }
        }
        else
        {
            if (acc > cutoff || (acc == cutoff && c1 > cutlim))
            {
                any = -1;
                acc = LONG_MAX;
                errno = ERANGE;
            }
            else
            {
                any = 1;
                acc *= base;
                acc += c1;
            }
        }
    }
    if (endptr != 0)
        *endptr = (char *)(any ? ptr1 - 1 : nptr);
    return (acc);
}

char *mystrchr(const char *s, int c)
{
    char *s1 = (char *)s;
    char c1 = (char)c;

    for (; *s1 != 0; ++s1)
    {
        if (*s1 == c1)
        {
            return (char *)s1;
        }
    }
    return NULL;
}

char *mystrrchr(const char *s, int c)
{
    int32_t len = strlen(s);
    char *s1 = (char *)s;
    while (len--)
    {
        if (*(s1 + len) == c)
        {
            return s1 + len;
        }
    }
    return NULL;
}

size_t mystrspn(const char *s, const char *accept)
{

    const char *s1 = s;
    const char *s2;
    for (; *s1 != 0; s1++)
    {
        for (s2 = accept; *s2 != 0; s2++)
        {
            if (*s1 == *s2)
            {
                break;
            }
        }
        if (*s2 == 0)
        {
            break;
        }
    }

    return s1 - s;
}

size_t mystrcspn(const char *s, const char *reject)
{
    const char *s1 = s;
    const char *s2;
    for (; *s1 != 0; s1++)
    {
        for (s2 = reject; *s2 != 0; s2++)
        {
            if (*s1 == *s2)
            {
                break;
            }
        }
        if (*s2)
        {
            break;
        }
    }
    return s1 - s;
}

char *mystrpbrk(const char *s, const char *accept)
{
    char *s1 = (char *)s;
    const char *s2;
    for (; *s1 != 0; ++s1)
    {
        for (s2 = accept; *s2 != 0; s2++)
        {
            if (*s1 == *s2) //if the char is found
            {
                break;
            }
        }
        if (*s2) //breaks loop if char is not 0
        {
            break;
        }
    }

    if (*s1)
    {
        return s1;
    }
    else
    {
        return NULL;
    }
}

char *mystrstr(const char *haystack, const char *needle)
{
    char *s1 = (char *)haystack;
    char *s2 = (char *)needle;
    if (*s2 == 0) //empty string
    {
        return s1;
    }
    for (; *haystack != 0; haystack++)
    {
        if (*haystack != *s2) //looking for the first char that maches both s1 , s2
        {
            continue;
        }
        s1 = (char *)haystack;
        for (;;)
        {
            if (*s2 == 0)
            {
                return (char *)haystack;
            }
            if (*s1++ != *s2++)
            {
                break;
            }
        }
        s2 = (char *)needle; //reset s2
    }
    return NULL;
}

/*
char *mystrtok(char *str, const char *delim)
{
    static char *ptr;
    char *tok = delim;
    int32_t len1 = strlen( str );
    int32_t len2 =strlen( delim );

    
    if( len2 > len1 )
    {
        return NULL;
    }

    if( *str != NULL )
    {
        ptr = str;
    }
    
    for( ; *ptr ; ptr++ )
    {
        for( ; *tok ; tok++ )
        {
            if( *ptr == *tok )
            {
                *ptr = 0; 
                break;
            }
        }
    }
    ptr++;

}
*/