#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define size_max 256
 
int main()
{
    char str[100];//str to parse

/*** The two names below will be used later ***/
    char urlname[100];//urlname name
    char filename[100];//filename
/*** *** *** *** *** *** *** *** *** *** *** ***/

    printf("input: ");
    scanf("%[^\n]%*c",str);

    str[strlen(str)-1] = 0;
    strcpy( urlname , str );
    strcpy( filename , str );

/*** parsing the string ***/
   
   // str[strlen(str)-1] = 0;
    char parsed[size_max][10];

    char *delim = "- ";
    char *ptr = strtok( str , delim );

    int32_t n = 0;
    for( n = 0 ; ptr != NULL ; n++ )
    {     
        snprintf( parsed[n], strlen(ptr) + 1 , "%s\n" , ptr );
        ptr = strtok( NULL , delim ); 
    }
/*** *** *** *** *** *** ***/
    //change tone except the last one 
    for( int32_t i = 0 ; i < n - 1 ; i++ )
    {
        switch( parsed[i][strlen(parsed[i])-1] )
        {
            case '1':
                parsed[i][strlen(parsed[i])-1] = '7';
                break;
            case '2':
                parsed[i][strlen(parsed[i])-1] = '1';
                break;
            case '3':
                parsed[i][strlen(parsed[i])-1] = '2';      
                break;         
            case '5':
                parsed[i][strlen(parsed[i])-1] = '7';
                break;
            case '7':
                parsed[i][strlen(parsed[i])-1] = '3';
                break;
            default:
                break;
        }
        switch( parsed[i][strlen(parsed[i])-2] )
        {
            case 'p': case 't': case 'k': 
                if(parsed[i][strlen(parsed[i])-1] == '4')
                {
                    parsed[i][strlen(parsed[i])-1] = '8';
                }
                else if(parsed[i][strlen(parsed[i])-1] == '8')
                {
                    parsed[i][strlen(parsed[i])-1] = '4';
                }
                break;
            case 'h':
                if(parsed[i][strlen(parsed[i])-1] == '4')
                {
                    parsed[i][strlen(parsed[i])-1] = '2';
                }
                else if(parsed[i][strlen(parsed[i])-1] == '8')
                {
                    parsed[i][strlen(parsed[i])-1] = '3';
                }
                break;
            default:
                break;
        }
    }

    char cmd[1000];
    for( int32_t i = 0 ; i < strlen(urlname) ; i++ )
    {
        if( urlname[i] == ' ' )
        {
            urlname[i] = '+';
        }
    }

    sprintf( cmd , "wget -O %s.wav https://hapsing.ithuan.tw/bangtsam?taibun=%s" , urlname , urlname );
    printf("\ncmd = %s",cmd);
    system( cmd );
    
    for( int32_t i = 0 ; i < strlen(parsed[i]) ; i++ )
    {
        char cmd1[100];
        sprintf( cmd1 , "wget -O %s.wav https://hapsing.ithuan.tw/bangtsam?taibun=%s" , parsed[i] , parsed[i] );
        system(cmd1);
    }
 
/*
    for( int32_t i = 0 ; i < n ; i++)
    {
        for( int32_t j = 0 ; j < strlen(parsed[i]) ; j++ )
        {
            printf("%c", parsed[i][j]);
        }
        printf("\n");
    }
*/
        
    //printf("\n str = %s\n",str);*/
    
    
    return 0;
}