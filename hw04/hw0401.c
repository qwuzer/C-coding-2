#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <time.h>
#include <stdlib.h>

struct _sBmpHeader
{
    char bm[2];
    uint32_t size;
    uint32_t reserve;
    uint32_t offset;
    uint32_t header_size;
    uint32_t width;
    uint32_t height;
    uint16_t planes;
    uint16_t bpp;
    uint32_t compression;
    uint32_t bitmap_size;
    uint32_t hres;
    uint32_t vres;
    uint32_t used;
    uint32_t important;
} __attribute__((__packed__));

typedef struct _sBmpHeader sBmpHeader;

void print_bmp_header(sBmpHeader *pHeader)
{
    printf("ID: %c%c\n", pHeader->bm[0], pHeader->bm[1]);
    printf("Size: %u\n", pHeader->size);
    printf("Reserve: %u\n", pHeader->reserve);
    printf("Offset: %u\n", pHeader->offset);
    printf("Header Size: %u\n", pHeader->header_size);
    printf("Width: %u\n", pHeader->width);
    printf("Height: %u\n", pHeader->height);
    printf("Planes: %u\n", pHeader->planes);
    printf("Bits Per Pixel: %u\n", pHeader->bpp);
    printf("Compression: %u\n", pHeader->compression);
    printf("Bitmap Data Size: %u\n", pHeader->bitmap_size);
    printf("H-Resolution: %u\n", pHeader->hres);
    printf("V-Resolution: %u\n", pHeader->vres);
    printf("Used Colors: %u\n", pHeader->used);
    printf("Important Colors: %u\n", pHeader->important);

    return;
}

int main(int argc, char *argv[])
{
    srand(time(NULL));
    FILE *pFile = NULL;   // original
    FILE *pFile2 = NULL;  // overlap
    FILE *pFile_1 = NULL; // layer 1
    FILE *pFile_2 = NULL; // layer 2

    char filename[50];
    sscanf(argv[1], "%[^.]%*c.bmp", filename);
    //printf("%s\n", filename);

    if ((pFile = fopen(argv[1], "rb")) == NULL)
    {
        printf("File could not be opened!\n");
        return 0;
    }

    char filename2[50];
    sprintf(filename2, "%s_overlap.bmp", filename);
    //printf("%s\n",filename2);
    if ((pFile2 = fopen(filename2, "w+b")) == NULL)
    {
        printf("File could not be opened!\n");
        return 0;
    }

    char filename_1[50];
    sprintf(filename_1, "%s_layer1.bmp", filename);
    if ((pFile_1 = fopen(filename_1, "wb")) == NULL)
    {
        printf("File could not be opened!\n");
        return 0;
    }

    char filename_2[50];
    sprintf(filename_2, "%s_layer2.bmp", filename);
    if ((pFile_2 = fopen(filename_2, "wb")) == NULL)
    {
        printf("File could not be opened!\n");
        return 0;
    }

    sBmpHeader header;
    fread(&header, sizeof(header), 1, pFile);
    header.width *= 2;
    header.height *= 2;
    header.bitmap_size *= 4;
    header.size = header.bitmap_size + header.offset;
    fwrite(&header, sizeof(header), 1, pFile2);

    while (!feof(pFile))
    {
        uint8_t original[header.width / 2 * 3]; // since we modified the header ,
        uint8_t modified[header.width * 3];     // we will need to change the length of array too

        size_t count = fread(original, 1, header.width / 2 * 3, pFile);

        for (size_t i = 0; i < count; i = i + 3)
        {
            uint8_t gray = 0.299 * original[i + 2] + 0.587 * original[i + 1] + 0.114 * original[i];
            size_t k = i * 2;
            for (size_t j = 0; j < 6; j++)
            {
                modified[k + j] = gray;
                if (modified[k + j] >= 128)
                {
                    modified[k + j] = 255;
                }
                else
                {
                    modified[k + j] = 0;
                }
            }
        }

        fwrite(modified, count * 2, 1, pFile2);
        fwrite(modified, count * 2, 1, pFile2);
    }

    fclose(pFile2);
    if ((pFile2 = fopen( filename2, "rb")) == NULL)
    {
        printf("File could not be opened!\n");
        return 0;
    }

    // rewind(pFile2);
    fread(&header, sizeof(header), 1, pFile2);
    fwrite(&header, sizeof(header), 1, pFile_1);
    fwrite(&header, sizeof(header), 1, pFile_2);

    int32_t k = 1;
    int32_t r1 = rand() % 4 + 1;
    int32_t r2 = rand() % 4 + 1;

    while (!feof(pFile2))
    {
        uint8_t original[header.width * 3];
        uint8_t modified1[header.width * 3];
        uint8_t modified2[header.width * 3];
        size_t cnt = fread(original, 1, sizeof(original), pFile2);
        memcpy(modified1, original, sizeof(original));
        memcpy(modified2, original, sizeof(original));

        if (k % 2 == 1)
        {
            for (int32_t i = 0; i < header.width * 3; i += 6)
            { /*
                 r1 = rand() % 4 + 1;
                 r2 = rand() % 4 + 1;
                 while (r1 == r2)
                 {
                     r2 = rand() % 4 + 1;
                 }*/
                r1 = rand() % 2;
                if (original[i] >= 128)
                { /*
                     if (r1 == 1 || r2 == 1)
                     {
                         for (int32_t j = 0; j < 3; j++)
                         {
                             modified1[i + j] = 0;
                             modified2[i + j] = 0;
                         }
                     }
                     else if (r1 == 2 || r2 == 2)
                     {
                         for (int32_t j = 0; j < 3; j++)
                         {
                             modified1[i + 3 + j] = 0;
                             modified2[i + 3 + j] = 0;
                         }
                     }*/
                    if (r1 == 0)
                    {
                        for (int32_t j = 0; j < 3; j++)
                        {
                            modified1[i + j] = 0;
                            modified2[i + j] = 0;
                        }
                    }
                    else
                    {
                        for (int32_t j = 0; j < 3; j++)
                        {
                            modified1[i + 3 + j] = 0;
                            modified2[i + 3 + j] = 0;
                        }
                    }
                }
                else
                { /*
                     if (r1 == 1 || r2 == 1)
                     {
                         for (int32_t j = 0; j < 3; j++)
                         {
                             modified1[i + j] = 255;
                             modified2[i + 3 + j] = 255;
                         }
                     }
                     else if (r1 == 2 || r2 == 2)
                     {
                         for (int32_t j = 0; j < 3; j++)
                         {
                             modified1[i + 3 + j] = 255;
                             modified2[i + j] = 255;
                         }
                     }*/
                    if (r1 == 0)
                    {
                        for (int32_t j = 0; j < 3; j++)
                        {
                            modified1[i + j] = 255;
                            modified2[i + 3 + j] = 255;
                        }
                    }
                    else
                    {
                        for (int32_t j = 0; j < 3; j++)
                        {
                            modified1[i + 3 + j] = 255;
                            modified2[i + j] = 255;
                        }
                    }
                }
            }
        }
        else
        {
            for (int32_t i = 0; i < header.width * 3; i += 6)
            {
                r2 = rand() % 2;
                if (original[i] >= 128)
                { /*
                     if (r1 == 3 || r2 == 3)
                     {
                         for (int32_t j = 0; j < 3; j++)
                         {
                             modified1[i + j] = 0;
                             modified2[i + j] = 0;
                         }
                     }
                     else if (r1 == 4 || r2 == 4)
                     {
                         for (int32_t j = 0; j < 3; j++)
                         {
                             modified1[i + 3 + j] = 0;
                             modified2[i + 3 + j] = 0;
                         }
                     }*/

                    if (r2 == 0)
                    {
                        for (int32_t j = 0; j < 3; j++)
                        {
                            modified1[i + j] = 0;
                            modified2[i + j] = 0;
                        }
                    }
                    else
                    {
                        for (int32_t j = 0; j < 3; j++)
                        {
                            modified1[i + 3 + j] = 0;
                            modified2[i + 3 + j] = 0;
                        }
                    }
                }
                else
                { /*
                     if (r1 == 3 || r2 == 3)
                     {
                         for (int32_t j = 0; j < 3; j++)
                         {
                             modified1[i + j] = 255;
                             modified2[i + 3 + j] = 255;
                         }
                     }
                     else if (r1 == 4 || r2 == 4)
                     {
                         for (int32_t j = 0; j < 3; j++)
                         {
                             modified1[i + 3 + j] = 255;
                             modified2[i + j] = 255;
                         }
                     }*/
                    if (r2 == 1)
                    {
                        for (int32_t j = 0; j < 3; j++)
                        {
                            modified1[i + j] = 255;
                            modified2[i + 3 + j] = 255;
                        }
                    }
                    else
                    {
                        for (int32_t j = 0; j < 3; j++)
                        {
                            modified1[i + 3 + j] = 255;
                            modified2[i + j] = 255;
                        }
                    }
                }
            }
        }
        k++;
        fwrite(modified1, 1, cnt, pFile_1);
        fwrite(modified2, 1, cnt, pFile_2);
    } /*
    int32_t r1 = rand() % 4 + 1;
    int32_t r2 = rand() % 4 + 1;
    while (r1 == r2)
    {
     r2 = rand() % 4 + 1;
    }
    int32_t r3 = r1 + r2;
    int32_t k = 1;
    while (!feof(pFile2))
    {
     uint8_t original[header.width * 3 * 2];
     uint8_t modified1[header.width * 3 * 2];
     uint8_t modified2[header.width * 3 * 2];
     size_t cnt = fread(original, 1, sizeof(original), pFile2);
     memcpy(modified1, original, sizeof(original));
     memcpy(modified2, original, sizeof(original));
     for (int32_t i = 0; i < header.width * 3; i += 6)
     {
         r1 = rand() % 4 + 1;
         r2 = rand() % 4 + 1;
         while (r1 == r2)
         {
             r2 = rand() % 4 + 1;
         }
         int32_t r3 = r1 + r2;

         switch (r3)
         {
         case 3:
             if (original[i] >= 128)
             {
                 for (size_t j = 0; j < 6; j++)
                 {
                     modified1[i + j] = 0;
                     // modified1[i + header.width + j] = 128;
                     modified2[i + j] = 0;
                     // modified2[i + header.width + j ] = 128;
                 }
             }
             else
             {
                 for (size_t j = 0; j < 6; j++)
                 {
                     modified1[i + j] = 255;
                     // modified1[i + header.width + j] = 0;
                     modified2[i + j] = 255;
                     // modified2[i + header.width + j] = 0;
                 }
             }
             break;
         case 4:
             if (original[i] >= 128)
             {
                 for (size_t j = 0; j < 3; j++)
                 {
                     modified1[i + j] = 0;
                     modified1[i + header.width + j] = 0;
                     modified2[i + j] = 0;
                     modified2[i + header.width + j] = 0;
                 }
             }
             else
             {
                 for (size_t j = 0; j < 3; j++)
                 {
                     modified1[i + j] = 255;
                     modified1[i + header.width + j] = 255;
                     modified2[i + 3 + j] = 255;
                     modified2[i + 3 + header.width + j] = 255;
                 }
             }
             break;
         case 5:
             if (r1 == 1 || r1 == 4)
             {
                 if (original[i] >= 128)
                 {
                     for (size_t j = 0; j < 3; j++)
                     {
                         modified1[i + j] = 0;
                         modified1[i + 3 + header.width + j] = 0;
                         modified2[i + j] = 0;
                         modified2[i + 3 + header.width + j] = 0;
                     }
                 }
                 else
                 {
                     for (size_t j = 0; j < 3; j++)
                     {
                         modified1[i + j] = 255;
                         modified1[i + 3 + header.width + j] = 255;
                         modified2[i + 3 + j] = 255;
                         modified2[i + header.width + j] = 255;
                     }
                 }
             }
             else
             {
                 if (original[i] >= 128)
                 {
                     for (size_t j = 0; j < 3; j++)
                     {
                         modified1[i + 3 + j] = 0;
                         modified1[i + header.width + j] = 0;
                         modified2[i + 3 + j] = 0;
                         modified2[i + header.width + j] = 0;
                     }
                 }
                 else
                 {
                     for (size_t j = 0; j < 3; j++)
                     {
                         modified1[i + 3 + j] = 255;
                         modified1[i + header.width + j] = 255;
                         modified2[i + j] = 255;
                         modified2[i + 3 + header.width + j] = 255;
                     }
                 }
             }
             break;
         case 6:
             if (original[i] >= 128)
             {
                 for (size_t j = 0; j < 3; j++)
                 {
                     modified1[i + 3 + j] = 0;
                     modified1[i + 3 + header.width + j] = 0;
                     modified2[i + 3 + j] = 0;
                     modified2[i + 3 + header.width + j] = 0;
                 }
             }
             else
             {
                 for (size_t j = 0; j < 3; j++)
                 {
                     modified1[i + 3 + j] = 255;
                     modified1[i + 3 + header.width + j] = 255;
                     modified2[i + j] = 255;
                     modified2[i + header.width + j] = 255;
                 }
             }
             break;
         case 7:
             if (original[i] >= 128)
             {
                 for (size_t j = 0; j < 6; j++)
                 {
                     modified1[i + header.width + j] = 0;
                     modified2[i + header.width + j] = 0;
                 }
             }
             else
             {
                 for (size_t j = 0; j < 6; j++)
                 {
                     modified1[i + header.width + j] = 255;
                     modified2[i + j] = 255;
                 }
             }
             break;
         default:
             break;
         }
     }
     fwrite(modified1, cnt, 1, pFile_1);
     fwrite(modified2, cnt, 1, pFile_2);

     k++;
    }
     printf("%d", k);*/
    fclose(pFile);
    fclose(pFile2);
    fclose(pFile_1);
    fclose(pFile_2);
    return 0;
}