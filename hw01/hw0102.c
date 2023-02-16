#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#define BUFFER_SIZE 4097 //+1 > ?


void yellow () {
  printf("\033[1;33m");
}
void reset () {
  printf("\033[0m");
}
int main()
{
    printf("Please enter the string:");
    char *buffer = malloc(sizeof(char) * BUFFER_SIZE);
    fgets(buffer, BUFFER_SIZE, stdin);

    int32_t len = strlen(buffer);
    buffer[len - 1] = 0;
    char *string = malloc(sizeof(char) * len);
    strncpy(string, buffer, len);
    printf("len = %d",len);

    free(buffer);
    buffer = NULL; //dynamic input

    printf("Please enter the keyword:");
    char keystr[65] = "";
    fgets(keystr, 65, stdin); //keyword
    int32_t len1 = strlen(keystr);
    keystr[len1 - 1] = 0;
    printf("len1 = %d\n", len1);

    printf("Please enter the new word:");
    char *newstr = malloc(sizeof(char) * 65);
    fgets(newstr, 65, stdin); //newword
    int32_t len2 = strlen(newstr);
    newstr[len2 - 1] = 0;
    printf("len2 = %d\n", len2);

    int32_t count = 0;
    char *cntstr = string;
    char *cntstr2 = string;
    for( ; *cntstr; cntstr++)
    {
        if( strcasestr( cntstr, keystr) == cntstr )
        {
            count++;
        }
        cntstr += len1 - 2;
    }
    char *newString = malloc( sizeof(char) * ((len2 - len1 ) * count + len) + 1 );
    
    int32_t i = 0;//setting up cntstr2 as the string that contains the newword
    for( ; *cntstr2 ; cntstr2++)
    {
        if( strcasestr(cntstr2,keystr) == cntstr2 )
        {
            strncpy(&newString[i],newstr,len2 - 1);
            cntstr2 = cntstr2 + len1 - 2;
            i = i + len2 - 1;
        }
        else
        {
            newString[i] = *cntstr2;//use char arr so that the pointer does not change position
            i++;
        }
    }
    cntstr2[i] = 0;
    

    printf("Original:");
    for (; *string; string++)
    {
        if (strcasestr(string, keystr) == string)
        {
            char *str1 = string;
            for (int32_t j = len1 - 1; j > 0; j-- , str1++)
            {
                printf("\033[22;34m%c\033[0m", *str1);
            }
            string = string + len1 - 2;
        }
        else
        {
            printf("%c", *string);
        }
    }
    
    printf("\n");

    printf("New:");
    for (; *newString; newString++)
    {
        if (strcasestr(newString, newstr) == newString)
        {
            char *str2 = newString;
            for (int32_t j = len2 - 1; j > 0; j-- , str2++)
            {
                yellow();
                printf("%c", *str2);./
                reset();
            }
            newString = newString + len2 - 2;
        }
        else
        {
            printf("%c", *newString);
        }
    }

    printf("\n");
    return 0;
}