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
    uint16_t bpp; // bits per pixel(24 -> 16)
    uint32_t compression;
    uint32_t bitmap_size; // image size in bytes
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

uint16_t rgb888torgb565(uint8_t *rgb888Pixel)
{
    uint8_t red = rgb888Pixel[0];
    uint8_t green = rgb888Pixel[1];
    uint8_t blue = rgb888Pixel[2];

    uint16_t b = (blue >> 3) & 0x1f;
    uint16_t g = ((green >> 2) & 0x3f) << 5;
    uint16_t r = ((red >> 3) & 0x1f) << 11;

    return (uint16_t)(r | g | b);
}

int main()
{
    char input_name[100];
    char output_name[100];
    FILE *pinFile;
    FILE *poutFile;
    int32_t ret = 0;

    printf("Please enter the input image name: ");

    if (fgets(input_name, sizeof(input_name), stdin) == NULL)
    {
        perror("Error:");
        return 0;
    }

    if (input_name[strlen(input_name) - 1] == '\n')
    {
        input_name[strlen(input_name) - 1] = 0;
    }
    else
    {
        int c;
        while ((c = fgetc(stdin)) != '\n' && c != EOF)
        {
        }
    }

    printf("Please enter the output image name: ");

    if (fgets(output_name, sizeof(output_name), stdin) == NULL)
    {
        perror("Error:");
        return 0;
    }

    if (output_name[strlen(output_name) - 1] == '\n')
    {
        output_name[strlen(output_name) - 1] = 0;
    }
    else
    {
        int c;
        while ((c = fgetc(stdin)) != '\n' && c != EOF)
        {
        }
    }

    if ((pinFile = fopen(input_name, "r")) == NULL)
    {
        perror("Error");
        return 0;
    }

    if ((poutFile = fopen(output_name, "w")) == NULL)
    {
        perror("Error:");
        return 0;
    }

    sBmpHeader header;
    ret = fread(&header, sizeof(header), 1, pinFile);
    print_bmp_header(&header);

    if (header.bm[0] != 'B' || header.bm[1] != 'M')
    {
        printf("This isn't a Bmp file.\n");
        return 0;
    }
    if( header.bpp != 24)
    {
        printf("This isn't a 24-bit bmp.");
        return 0;
    }

    //print_bmp_header(&header);
    int32_t rgb_mask[3] = { 0xF800 , 0x07E0, 0x001F};

    header.offset = 14 + 40 + sizeof(rgb_mask);
    header.header_size = 40 + sizeof(rgb_mask);//40 = bmpinfoheader size
    header.compression = 3;
    header.bpp = 16;
    header.bitmap_size = header.width * header.height * 2;
    header.size = header.bitmap_size + header.offset;
    header.compression = 3;
    

    fwrite(&header, sizeof(header), 1, poutFile);
    fwrite( rgb_mask , sizeof(rgb_mask) , 1 , poutFile);
    
    
     uint16_t newBitmap[header.width];
     for (int32_t y = 0; y < header.height; y++)
     {
         for (int32_t x = 0; x < header.width; x++)
         {
             uint8_t r, g, b;
             fread(&b, sizeof(uint8_t), 1, pinFile);
             fread(&g, sizeof(uint8_t), 1, pinFile);
             fread(&r, sizeof(uint8_t), 1, pinFile);
             /*
             r = ((r >> 3)& 0x1F) << 10;
             g = ((g >> 2) & 0x1F) << 5;
             b = (b >> 3) & 0x1F;
             */
            r = r & rgb_mask[0];
            g = g & rgb_mask[1];
            b = b & rgb_mask[2];
             newBitmap[x] = r | g | b;
             fwrite( newBitmap , sizeof( newBitmap ) , 1 , poutFile);
         }
     }

     

     int32_t newHeight = 0;
     for( int32_t y = header.height ; y > 0 ; y-- )
     {
         for( int32_t x = 0 ; x < header.width ; x++ )
         {
             newBitmap[ y * newHeight + x ] = newBitmap[ y * header.height + x ];
         }
         newHeight++;
     }
     
    /*
    uint8_t i[3];
    while (!feof(pinFile))
    {
        fread(i, sizeof(uint8_t), 3, pinFile);
        uint16_t x = rgb888torgb565(i);
        fwrite(&x, sizeof(uint16_t), 1, poutFile);
    }
    */
    /*
        int heightIndex = 0;
        for ( int32_t y = header.height - 1; y >= 0; --y)
        {
            for (int x = 0; x < header.width; ++x)
            {
                newBitmap[heightIndex * header.width + x] = newBitmap[y * header.width + x];
            }
            ++heightIndex;
        }
    */
    fclose(pinFile);
    fclose(poutFile);
}