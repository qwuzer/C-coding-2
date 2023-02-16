#include <stdio.h>
#include <stdint.h>
#include <string.h>

struct _sBmpHeader
{
    char bm[2];
    uint32_t size; // bit_map size + offset
    uint32_t reserve;
    uint32_t offset;
    uint32_t header_size;
    uint32_t width;
    uint32_t height;
    uint16_t planes;
    uint16_t bpp;
    uint32_t compression;
    uint32_t bitmap_size; // image size in bytes
    uint32_t hres;
    uint32_t vres;
    uint32_t used;
    uint32_t important;
} __attribute__((__packed__));

typedef struct _sBmpHeader sBmpHeader;

int main()
{
    char fileName[50];
    FILE *pFile;
    printf("Please enter the image: ");

    if (fgets(fileName, sizeof(fileName), stdin) == NULL)
    {
        printf("Error.");
        return 0;
    }

    if (fileName[strlen(fileName) - 1] == '\n')
    {
        fileName[strlen(fileName) - 1] = 0;
    }
    else
    {
        int c;
        while ((c = fgetc(stdin)) != '\n' && c != EOF)
        {
        }
    }

    if ((pFile = fopen(fileName, "r")) == NULL)
    {
        printf("error:");
        return 0;
    }

    sBmpHeader header;
    fread(&header, sizeof(header), 1, pFile);

    if (header.bm[0] != 'B' || header.bm[1] != 'M')
    {
        printf("This is not an bmp file.");
        return 0;
    }
    rewind(pFile);
    //-------------------------------------------------------------------
    char textName[50];
    FILE *pText;
    printf("Please enter the puzzle: ");

    if (fgets(textName, sizeof(textName), stdin) == NULL)
    {
        printf("Error.");
        return 0;
    }

    if (textName[strlen(textName) - 1] == '\n')
    {
        textName[strlen(textName) - 1] = 0;
    }
    else
    {
        int c;
        while ((c = fgetc(stdin)) != '\n' && c != EOF)
        {
        }
    }

    if ((pText = fopen(textName, "r")) == NULL)
    {
        printf("error:");
        return 0;
    }
    //-------------------------------------------------------------------

    int32_t m, n, k;
    char tmp[2 * header.width];

    fgets(tmp, sizeof(tmp), pText);
    sscanf(tmp, "%d%*c%d%*c", &m, &n);
    if (m > header.width || n > header.height)
    {
        printf("Error. m or n is too large.\n");
        return 0;
    }

    fgets(tmp, sizeof(tmp), pText);
    sscanf(tmp, "%d%*c", &k);
    if (k == 0)
    {
        printf("There are no steps.\n");
        return 0;
    }

    int32_t cnt = 0;
    while (fgets(tmp, sizeof(tmp), pText) != NULL)
    {
        cnt++;
    }
    rewind(pText);
    fgets(tmp, sizeof(tmp), pText);
    fgets(tmp, sizeof(tmp), pText);
    //-------------------------------------------------------------------
    if ((cnt / m) != k)
    {
        printf("Error.Invalid text file format.\n");
        return 0;
    }
    else
    {
        //-------------------------------------------------------------------------------text processing
        int32_t numarr_chk[n][m];
        for (int32_t j = 0; j < n; j++)
        {
            for (int32_t i = 0; i < m; i++)
            {
                numarr_chk[j][i] = j * m + i + 1;
            }
        }
        
        int32_t numarr[n][m];
        uint8_t tmpnewbitmap[header.bitmap_size];
        for (int32_t k1 = 0; k1 < k; k1++) // k numarrays
        {
            int32_t zerocnt = 0;
            for (int32_t j = 0; j < n; j++) // for every numarr we read in one line each time
            {
                char *p = tmp;
                fgets(p, sizeof(tmp), pText);
                char space;
                for (int32_t i = 0; i < m; i++)
                {
                    sscanf(p, "%d%c", &(numarr[j][i]), &space);
                    p += 2;
                    printf("%d [j][i] = (%d,%d)", numarr[j][i], j, i);
                    if (numarr[j][i] != 0)
                    {
                        if (numarr_chk[j][i] != 0)
                        {
                            if (numarr_chk[j][i] != numarr[j][i])
                            {
                                printf("Invalid.hi");
                                return 0;
                            }
                        }
                    }
                    else if (numarr[j][i] == 0)
                    {
                        if (k1 != 0)
                        {
                            if (numarr_chk[j + 1][i] == 0 || numarr_chk[j - 1][i] == 0 || numarr_chk[j][i + 1] == 0 || numarr_chk[j][i - 1] == 0)
                            {
                                // printf("%d",numarr_chk[i+1][j]);
                            }
                            else
                            {
                                // printf(" ans =%d",numarr_chk[i+1][j]);
                                printf("0 in wrong position.");
                                return 0;
                            }
                        }
                        zerocnt++;
                    }
                }
                printf("\n");
            }
            if (zerocnt != 1)
            {
                // printf("%d", zerocnt);
                printf("Invalid format.");
                return 0;
            }
            
            //-------------------------------------------------------------------image processing
            int32_t h = header.height;
            int32_t w = header.width;
            char outputname[250];
            snprintf(outputname, 250, "%d.bmp", k1);
            FILE *poutFile;
            if ((poutFile = fopen(outputname, "w")) == NULL)
            {
                printf("file could not be opened.");
                return 0;
            }
            fread(&header, sizeof(header), 1, pFile);
            fwrite(&header, sizeof(header), 1, poutFile);
            
            int32_t whiteposx;
            int32_t whiteposy;
            int32_t changex;
            int32_t changey;
            for (int32_t j = 0; j < n; j++)
            {
                for (int32_t i = 0; i < m; i++)
                {
                    if (numarr[j][i] == 0)
                    {
                        whiteposx = i * (header.width / m) * 3;
                        whiteposy = j * (header.height / n);
                    }
                    if (numarr_chk[j][i] == 0)
                    {
                        changex = i * (header.width / m) * 3;
                        changey = j * (header.height / n);
                    }
                }
            }
            uint8_t newBitmap[header.bitmap_size];
            
            if (k1 == 0)
            {
                fread(newBitmap, sizeof(newBitmap), 1, pFile);
                for (int32_t j = 0; j < h; j++)
                {
                    for (int32_t i = 0; i < w * 3; i++)
                    {
                        if (j >= whiteposy && j <= whiteposy + (header.height / n) && i >= whiteposx && i <= whiteposx +(w/m)*3)
                        {
                            newBitmap[j * w * 3 + i] = 255;
                        }
                    }
                }
            }
            else
            {
                for (int32_t j = 0; j < h; j++)
                {
                    for (int32_t i = 0; i < w * 3; i++)
                    {
                        newBitmap[j*w+i] = tmpnewbitmap[j*w+i];
                    }
                }
                for (int32_t j = 0; j < h; j++)
                {
                    for (int32_t i = 0; i < w * 3; i++)
                    {
                        if (j >= whiteposy && j <= whiteposy + (header.height / n) && i >= whiteposx && i <= whiteposx + (w / m)*3)
                        {
                            uint8_t tmp = newBitmap[j * w * 3 + i];
                            newBitmap[j * w * 3 + i] = newBitmap[changey * w * 3 + changex];
                            newBitmap[changey * w * 3+ changex] = tmp;
                            changex++;
                        }
                    }
                    changey++;
                }
            }
            
            fwrite(newBitmap, sizeof(newBitmap), 1, poutFile);

            fread(tmpnewbitmap, sizeof(tmpnewbitmap), 1, poutFile);
            rewind(pFile);
            fclose(poutFile);

            for (int32_t j = 0; j < n; j++)
            {
                for (int32_t i = 0; i < m; i++)
                {
                    numarr_chk[j][i] = numarr[j][i];
                    printf("%d [j][i] = (%d,%d) ", numarr_chk[j][i], j, i);
                }
                printf("\n");
            }
        }
    }

    fclose(pFile);
    fclose(pText);
    return 0;
}