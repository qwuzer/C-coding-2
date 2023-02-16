#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include <errno.h>
#define bufferSize 648

int main()
{
    FILE *pFile = NULL;
    if ((pFile = fopen("bible.txt", "r")) == NULL)
    {
        perror("error:");
        return 0;
    }

    printf("Please enter the search target: ");
    char *buffer = malloc(sizeof(char) * bufferSize);
    fgets(buffer, bufferSize, stdin);

    int32_t len = strlen(buffer);
    buffer[len - 1] = 0;
    char *string = malloc(sizeof(char) * len);
    strncpy(string, buffer, len);
    //printf("len = %d", len);
    free(buffer);
    buffer = NULL; // dynamic input

    int line_num = 0;
    int find_result = 0;
    char temp[648];

    int32_t chapter = 0;
    int32_t verse = 0;
    char text[512] = {0};
    char id[10] = {0};
    char name[10] = {0};

    while (fgets(temp, 648, pFile) != NULL)
    {
       sscanf(temp, "{\"chapter\":%d,\"verse\":%d,\"text\":\"%[^\"]\",\"translation_id\":\"ASV\",\"book_id\":\"%[^\"]\",\"book_name\":\"%[^\"]\"}%*c", &chapter, &verse, text, id, name);
       if (strcasestr(text, string) != NULL)
        {
            find_result++;
        }
    }

    printf("Found %d time(s)\n",find_result);
    rewind( pFile );

    while (fgets(temp, 648, pFile) != NULL)
    {
        sscanf(temp, "{\"chapter\":%d,\"verse\":%d,\"text\":\"%[^\"]\",\"translation_id\":\"ASV\",\"book_id\":\"%[^\"]\",\"book_name\":\"%[^\"]\"}%*c", &chapter, &verse, text, id, name);
        if (strcasestr(text, string) != NULL)
        {
            line_num++;
            printf("%d. %s %d:%d %s\n",line_num , id , chapter , verse , text );
        }
    }
    
    /*
    if (find_result == 0)
    {
        printf("\nThere is no match.\n");
    }
    */
    /*
    while (!feof(pFile))
    {
        int32_t chapter = 0;
        int32_t verse = 0;
        char text[200] = {0};
        char id[10] = {0};
        char name[10] = {0};

        int32_t chk = 0;
        fscanf(pFile, "{\"chapter\":%d,", &chapter);
        // printf("%d\n", chapter);
        fscanf(pFile, "\"verse\":%d,", &verse);
        // printf("%d\n", verse);
        fscanf(pFile, "\"text\":\"%[^\"]\",", text);
        // printf("%s\n", text);
        fscanf(pFile, "\"translation_id\":\"ASV\",\"book_id\":\"%[^\"]\",", id);
        // printf("%s\n", id);
        fscanf(pFile, "\"book_name\":\"%[a-zA-Z]\"}%*c", name);
        // printf("%s\n", name);

        // chk = fscanf(pFile, "{\"chapter\":%d,\"verse\":%d,\"text\":\"%[^\"]\",\"translation_id\":\"ASV\",\"book_id\":\"%[^\"]\",\"book_name\":\"%[^\"]\"}%*c", &chapter, &verse, text, id, name);
        //  printf("gi\n");

        printf("text = %s\n", text);
        printf("chap = %d\n", chapter);
        printf("vesre = %d\n", verse);
        printf("chk = %d\n", chk);
        printf("id = %s\n", id);

        if (strcasestr(text, string) != NULL)
        {
            printf("hi\n");
            printf("text = %s\n", text);
            printf("chap = %d\n", chapter);
            printf("vesre = %d\n", verse);
            printf("chk = %d\n", chk);
            printf("id = %s\n", id);
        }
        else
        {
            continue;
        }

    }
    */

    fclose(pFile);
    return 0;
}