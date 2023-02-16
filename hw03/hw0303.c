#include <stdio.h>
#include <stdint.h>
#include <string.h>
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


int main()
{
    char inputName[64];
    char outputName[64];
    FILE *pinFile;
    FILE *poutFile;

    //--------------------------------------------------------------
    printf("Please enter the input image name: ");
    if (fgets(inputName, sizeof(inputName), stdin) == NULL)
    {
        perror("Error:");
        return 0;
    }

    if (inputName[strlen(inputName) - 1] == '\n')
    {
        inputName[strlen(inputName) - 1] = 0;
    }
    else
    {
        int c;
        while ((c = fgetc(stdin)) != '\n' && c != EOF)
        {
        }
    }
    //--------------------------------------------------------------
    printf("Please enter the output image name: ");
    if (fgets(outputName, sizeof(outputName), stdin) == NULL)
    {
        perror("Error.");
        return 0;
    }

    if (outputName[strlen(outputName) - 1] == '\n')
    {
        outputName[strlen(outputName) - 1] = 0;
    }
    else
    {
        int c;
        while ((c = fgetc(stdin)) != '\n' && c != EOF)
        {
        }
    }

    //--------------------------------------------------------------
    if ((pinFile = fopen(inputName, "r")) == NULL)
    {
        perror("Error:");
        return 0;
    }

    if ((poutFile = fopen(outputName, "w")) == NULL)
    {
        perror("Error:");
        return 0;
    }
    //--------------------------------------------------------------
    sBmpHeader header;
    fread(&header, sizeof(header), 1, pinFile);
    if( header.bm[0] != 'B' || header.bm[1] != 'M')
    {
        printf("This isn't a Bmp file.\n");
        return 0;
    }
    fwrite(&header, sizeof(header), 1, poutFile);
    //--------------------------------------------------------------

    int32_t x, y, r;
    printf("Please enter the center: ");
    if(scanf("(%d,%d)",&x,&y) != 2 )
    {
        printf("error");
    }
    printf("Please enter the radius: ");
    scanf("%d", &r);
    printf("%d",r);
    //--------------------------------------------------------------

    int32_t w = header.width;
    int32_t h = header.height;
    int32_t cnt = 0; // cnt = y * w + x
                     // cnt represent each pixel from top left to bottom right

    while (!feof(pinFile))
    {
        uint8_t original[999]; // R G B is each a byte
        uint8_t modified[999]; // 999 % 3 = 0

        size_t wid = fread(original, 1, 999, pinFile);

        for (size_t i = 0; i < wid; i = i + 3)
        {
            int32_t x2 = 0;
            int32_t y2 = 0;
            if (cnt % w == 0)//transforming cnt to coordinates
            {
                if (cnt != 0)
                {
                    x2 = w;
                    y2 = h - (cnt / w );
                    cnt++;
                }
                else
                {
                    x2 = 1;
                    y2 = h;
                    cnt++;
                }
            }
            else
            {
                x2 = cnt % w;
                y2 = h - (cnt / w + 1);
                cnt++;
            }

            if ((x2 - x) * (x2 - x) + (y2 - y) * (y2 - y) > r * r)
            {
                modified[i + 2] = 255;
                modified[i + 1] = 255;
                modified[i] = 255;
            }
            else
            {
                modified[i + 2] = original[i + 2];
                modified[i + 1] = original[i + 1];
                modified[i] = original[i];
            }
        }
        fwrite(modified, 999, 1, poutFile);
    }

    fclose(pinFile);
    fclose(poutFile);
}