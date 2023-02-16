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