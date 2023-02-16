#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>

int main()
{
    FILE *pFile = NULL;
    char name[100];
    printf("Open a srt file: ");

    if (fgets(name, 100, stdin) == NULL)
    {
        perror("error:");
        return 0;
    }

    if (name[strlen(name) - 1] == '\n')
    {
        name[strlen(name) - 1] = 0;
    }
    else
    {
        int c = 0;
        while ((c = fgetc(stdin)) != '\n' && c != EOF)
        {
        }
    }

    if ((pFile = fopen(name, "r")) == NULL)
    {
        printf("error:");
        return 0;
    }

    double speed = 0;
    printf("Speed (0.5-2): ");
    scanf("%lf", &speed);
    if( speed < 0.5 || speed > 2)
    {
        printf("Invalid speed.\n");
        return 0;
    }
    else
    {
        speed = 1.0 / speed;
    }
    
    

    while (!feof(pFile))
    {
        int32_t num = 1;
        int32_t hour1, hour2, min1, min2, sec1, sec2, mls1;
        int32_t mls2 = 0;
        char text[50];
        char tmp[100];

        int32_t start = 0;
        while (fgets(tmp, 100, pFile) != NULL)
        {
            if (start == 0)
            {
                sscanf(tmp, "%d%*c", &num);
                //printf("%d ", num);
                start += 1;
            }
            else if (start == 1)
            {
                int32_t mls_temp = mls2;
                sscanf(tmp, "%d:%d:%d,%d --> %d:%d:%d,%d%*c",
                       &hour1, &min1, &sec1, &mls1, &hour2, &min2, &sec2, &mls2); //"%[^:]:%[^:]:%[^,],%s --> %[^:]:%[^:]:%[^,]
                mls1 = hour1 * 3600000 + min1 * 60000 + sec1 * 1000 + mls1;
                mls2 = hour2 * 3600000 + min2 * 60000 + sec2 * 1000 + mls2;
                
                if( num == 1)
                {
                    usleep(mls1 * 1000 * speed);
                }
                else
                {
                    usleep( (mls1 - mls_temp) * 1000 * speed );
                }
                
                start += 1;
            }
            else if (start == 2)
            {
                sscanf(tmp, "%[^\n]%*c", text);
                system("clear");
                printf("%s\n",text);
                usleep( (mls2 - mls1) * 1000 * speed);
                start += 1;
            }
            else
            {
                sscanf(tmp, "%*c");
                // printf("%d %s:%s:%s,%s --> %s:%s:%s,%s %s\n", num, hour1, min1, sec1, mls1, hour2, min2, sec2, mls2, text);
                start = 0;
            }

            /*
            while(1)
            {

                clock_t t1;
                t1 = clock() - t;
                double time_passed = ((double)t1)/CLOCKS_PER_SEC;
                if( time_passed * 1000 >= mls1 && time_passed * 1000 <= mls2 )
                {
                    printf("%s\n",text);
                    usleep((mls2-mls1)*1000);
                }
            }
            */
        }
        /*
        fscanf(pFile, "%d%*c", &num);
        fscanf(pFile, "%[^:]:%[^:]:%[^:],%s --> %[^:]:%[^:]:%[^:],%s%*c",
                hour1, min1, sec1, mls1, hour2, min2, sec2, mls2);
        fscanf(pFile, "%s%*c", text);
        printf("%d %s:%s:%s,%s --> %s:%s:%s,%s %s\n", num, hour1, min1, sec1, mls1, hour2, min2, sec2, mls2, text);
        */
    }

    fclose(pFile);
    return 0;
}