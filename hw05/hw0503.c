#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <getopt.h>
#include <string.h>
#include <unistd.h>

#include <fcntl.h>
#include <sys/mman.h>
#include <sys/types.h>
#include <sys/stat.h>

struct option longopts[] = 
{
    { "enc" , 1 , NULL , 'e' },
    { "dec" , 1 , NULL , 'd' },
    { "output" , 1 , NULL , 'o' },
    { 0 , 0 , 0 , 0 }
};

char *encode( char *str , int32_t len )
{
    if( len == 0 || str == NULL )
    {
        return NULL;
    }

    int32_t output_len = ( (len + 2) / 3 ) * 4;//e.g. 7 ASCII chars -> ((7+2)/3)*4 = 3 * 4 (b64)

    char *output = malloc(output_len + 1);
    output[output_len] = 0;

    const char b64chars[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";

    int32_t bin;//binary str of input
    for( int32_t i = 0 , j = 0  ; i < len ; i += 3 , j += 4 )
    {
        bin = str[i];
        bin = i + 1 < len ? bin << 8 | str[i+1] : bin << 8;
        bin = i + 2 < len ? bin << 8 | str[i+2] : bin << 8;

        output[j] = b64chars[(bin >> 18) & 0x3F];
        output[j+1] = b64chars[(bin >> 12) & 0x3F];
        output[j+2] = i + 1 < len ? b64chars[(bin >> 6) & 0x3F] : '=';
        output[j+3] = i + 2 < len ? b64chars[(bin) & 0x3F] : '=';
    }

    return output;
}

int decode_chk(char c)
{
	if (c >= '0' && c <= '9')
		return 1;
	if (c >= 'A' && c <= 'Z')
		return 1;
	if (c >= 'a' && c <= 'z')
		return 1;
	if (c == '+' || c == '/' || c == '=')
		return 1;
	return 0;
}

int decode( char *input , char *output , int32_t len )
{
    int32_t r;
    int32_t outlen;
    switch ( len % 4 )
    {
        case 1 :
            printf("Invalid input length.\n");
            return 0;
        case 2 : case 3 :
            outlen = (( len + 2 ) / 4) * 3;
            break;
        dafault:
            outlen = (len / 4) * 3;
            break;
    }

   // char *output = malloc(outlen + 1);
   // output[outlen] = 0;

    int32_t decode_table[] = { 62, -1, -1, -1, 63, 52, 53, 54, 55, 56, 57, 58,
	                59, 60, 61, -1, -1, -1, -1, -1, -1, -1, 0, 1, 2, 3, 4, 5,
                    6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20,
	                21, 22, 23, 24, 25, -1, -1, -1, -1, -1, -1, 26, 27, 28,
	                29, 30, 31, 32, 33, 34, 35, 36, 37, 38, 39, 40, 41, 42,
	                43, 44, 45, 46, 47, 48, 49, 50, 51 };
    
    for (int32_t i = 0 ; i < len ; i++)
    {
		if (!decode_chk( input[i] )) 
        {
            printf("Not valid Base64 text.\n");
			return 0;
		}
	}

    int32_t bin;
	for ( int32_t i = 0, j = 0; i < len ; i += 4, j += 3) 
    {
	    bin = decode_table[input[i] - 43];
		bin = (bin << 6) | decode_table[input[i+1] - 43];
		bin = input[i+2] == '=' ? bin << 6 : (bin << 6) | decode_table[input[i+2] - 43];
		bin = input[i+3] == '=' ? bin << 6 : (bin << 6) | decode_table[input[i+3] - 43];

		output[j] = (bin >> 16) & 0xFF;
		if (input[i + 2] != '=')
			output[j + 1] = (bin >> 8) & 0xFF;
		if (input[i + 3] != '=')
			output[j + 2] = bin & 0xFF;
	}

	return 1;

}

int main( int argc , char *argv[] )
{/*
    printf("argc = %d\n",argc);
    for( int32_t i = 0 ; i < argc ; i++ )
    {
        printf("argv[%d] = %s\n",i,argv[i]);
    }
*/
    int32_t eflag = 0, dflag = 0, oflag = 0;
    char *enfile , *decfile ,*outfile;
    int c;
    while( ( c = getopt_long( argc , argv , "e:d:o:" , longopts , NULL )) != -1 )
    {
        switch(c)
        {
            case 'e':
                eflag += 1;
                enfile = optarg;
                break;
            case 'd':
                dflag += 1;
                decfile = optarg;
                break;
            case 'o':
                oflag += 1;
                outfile = optarg;
                break;
            dafault:
                break;
        }
    }
    //printf("%lu",strlen(enfile));
    

    if( eflag == 1 && oflag == 1 )
    {
        int fd;
        fd = open( enfile , O_RDWR);
        if( fd == -1 )
        {
            perror("Error opening file");
            return 0;
        }

        char    *_pFile = NULL;
        struct stat file_stat;
        fstat( fd, &file_stat );
        uint64_t fileSize = file_stat.st_size;
        if( fileSize == 0 )
        {
            printf("Unvalid input.\n");
            return 0;
        }
        printf("filesize = %llu\n",fileSize);
        
        
        _pFile = mmap( 0, fileSize, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0 );
        char *out = encode( _pFile , (int32_t)fileSize);
        
        munmap( _pFile, fileSize );
        close( fd );

        int fd_out;
        fd_out = open( outfile , O_WRONLY);
        if( fd_out == -1 )
        {
            perror("Open file error.\n");
            return 0;
        }
        write( fd_out , out , strlen(out));
        close(fd_out);
        printf("%s",out);
    }


    if( dflag == 1 && oflag == 1 )
    {
        int fd;
        fd = open( decfile , O_RDWR);
        if( fd == -1 )
        {
            perror("Error opening file");
            return 0;
        }

        char    *_pFile = NULL;
        struct stat file_stat;
        fstat( fd, &file_stat );
        uint64_t fileSize = file_stat.st_size;
        if( fileSize == 0 )
        {
            printf("Unvalid input.\n");
            return 0;
        }
        printf("filesize = %llu\n",fileSize);
       
        char *output = malloc(fileSize + 1);
        output[fileSize] = 0;
        
        _pFile = mmap( 0, fileSize, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0 );
        if( decode( _pFile , output, (int32_t)fileSize) == 0)
        {
            return 0;
        }
        
        munmap( _pFile, fileSize );
        close( fd );

        int fd_out;
        fd_out = open( outfile , O_WRONLY);
        if( fd_out == -1 )
        {
            perror("Open file error.\n");
            return 0;
        }
        write( fd_out , output , strlen(output));
        close(fd_out);
        printf("%s",output);

    }
    

    return 0;
}