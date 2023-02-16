#include <stdio.h>
#include <string.h>
#include <errno.h>

int main()
{
    if( ( fopen( "kdndf", "r" ) ) == NULL )
    {
        printf( "errno = %d\n", errno );
        printf( "error: %s\n", strerror( errno ) );
        perror("this string will be printed before the error message and this is a colon -->");
    }   

    return 0;
}
