#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>


typedef struct _sTag
{
    char T;
    char A;
    char G;
    uint8_t title[30];
    uint8_t artist[30];
    uint8_t album[30];
    uint8_t  year[4];
    uint8_t comment[28];
    uint8_t zero_byte;
    uint8_t track;
    uint8_t genre;
}stag;


void print_tag( stag *ptag )
{
   // printf("%c\n",ptag->T);
   // printf("%c\n",ptag->A);
   // printf("%c\n",ptag->G);
    printf("title : %.30s\n",ptag->title);
    printf("artist : %.30s\n",ptag->artist);
    printf("album : %.30s\n",ptag->album);
    printf("year : %.4s\n",ptag->year);
    printf("comment : %.28s\n",ptag->comment);
   // printf("zero byte : %hd\n",ptag->zero_byte);
    printf("track : %hd\n",ptag->track);
   // printf("genre : %hd\n",ptag->genre);
}

int32_t isTagValid( stag tag )
{
    if(tag.T != 'T' || tag.A != 'A' || tag.G != 'G')
    {
        //printf("%c\n",tag.T);printf("%c\n",tag.A);printf("%c\n",tag.G);
        printf("This is not a ID3v1 tag.\n");
        return -1;
    }
    return 1;

}
/*
int32_t O_R_file( char *filename , int fd , stag *TAG)
{
    fd = open( filename , O_RDONLY );
    if( fd == -1 )
    {
        printf("Open file error\n");
        return 0;
    }
    if( lseek( fd , -128 , SEEK_END) == -1) 
    {
        return 1;//initialize a tag
    }
    read( fd , TAG , 128);

    if( !isTagValid( *TAG ) )
    {
        return 2;
    }
    return 3;
} 
*/

int main( int argc , char *argv[] )
{

    char *Genre_arr[80] = { "Blues","Classic Rock","Country","Dance","Disco","Funk","Grunge"
,"Hip-Hop","Jazz","Metal","New Age","Oldies","Other","Pop","Rhythm and Blues","Rap","Reggae","Rock","Techno"
,"Industrial","Alternative","Ska","Death Metal","Pranks","Soundtrack","Euro-Techno","Ambient","Trip-Hop"
,"Vocal","Jazz & Funk","Fusion","Trance","Classical","Instrumental","Acid","House","Game","Sound Clip","Gospel"
,"Noise","Alternative Rock","Bass","Soul","Punk","Space","Meditative","Instrumental Pop","Instrumental Rock"
,"Ethnic","Gothic","Darkwave","Techno-Industrial","Electronic","Pop-Folk","Eurodance","Dream","Southern Rock"
,"Comedy","Cult","Gangsta","Top 40","Christian Rap","Pop/Funk","Jungle","Native US","Cabaret","New Wave","Psychadelic","Rave"
,"Showtunes","Trailer","Lo-Fi","Tribal","Acid Punk","Acid Jazz","Polka","Retro","Musical","Rock ’n’ Roll","Hard Rock"};

    int32_t tflag = 0, aflag = 0, Aflag = 0, cflag = 0 , yflag = 0, 
                gflag = 0, Tflag = 0, hflag = 0, dflag = 0, lflag = 0;
    char *title, *artist, *album, *comment, *year , *genre;
    uint8_t track = 0;
    int c = 0;
    while( (c = getopt(argc , argv , "t:T:a:A:y:c:g:hld" )) != -1 )
    {
        switch( c )
        {
            case 't':
                tflag = 1;
                if( strlen(optarg) > 30 )
                {
                    printf("The title is too long.\n");
                    return 0;
                } 
                else
                {
                    title = optarg;
                    //memcpy( title ,optarg, 30); ?
                }
                break;
            case 'T':
                Tflag = 1;
                track = (uint8_t)atoi(optarg);// strtol ?
                break;
            case 'a':
                aflag = 1;
                if( strlen(optarg) > 30 )
                {
                    printf("The artist's name is too long.\n");
                    return 0;
                } 
                else
                {
                    artist = optarg;
                }
                break;
            case 'A':
                Aflag = 1;
                if( strlen(optarg) > 30 )
                {
                    printf("The album name is too long.\n");
                    return 0;
                } 
                else
                {
                    album = optarg;
                }
                break;
            case 'y':
                yflag = 1;
                if( strlen(optarg) > 4 )
                {
                    printf("The year is too long.\n");
                    return 0;
                } 
                else
                {
                    year = optarg;
                }
                break;
            case 'c':
                cflag = 1;
                if( strlen(optarg) > 28 )
                {
                    printf("The comment is too long.\n");
                    return 0;
                } 
                else
                {
                    comment = optarg;
                }
                break;
            case 'g':
                gflag = 1;
                //genre = (uint8_t)atoi(optarg);
                genre = optarg;
                break;
            case 'h':
                hflag = 1;
                break;
            case 'l':
                lflag = 1;
                break;
            case 'd':
                dflag = 1;
                break;
            case '?':
                printf("option : ?\n");
                break;
            default:
                printf( "option: unknown\n" ); 
                break;
        }
    }
    
    if( optind < argc )
    {
        int32_t files_cnt = 0;
        files_cnt = argc - optind;

        int fd_arr[files_cnt];

        for( int32_t i = 0 ;i < files_cnt ;i++)
        {
            stag TAG;
            int32_t chk = 2;
            fd_arr[i] = open(  argv[optind+i] , O_RDWR );
            if( fd_arr[i] == -1 )
            {
                printf("Open file error\n");
                chk = 0;
            }
            lseek( fd_arr[i] , -128 , SEEK_END );
            read( fd_arr[i] , &TAG , 128);
            if( !isTagValid( TAG ) )
            {
                printf("Tag initialized.\n");
                chk = 1;//init a tag 
            }     
            

            if( chk == 0)//openfile error
            {
                printf("Error occured at file%d.\n",i+1);
                continue;
            }
            else if( chk == 1 )//init a tag.
            {
                for( int32_t i = 0 ; i < 30 ; i++ )
                {
                    TAG.title[i] = 0;
                    TAG.artist[i] = 0;
                    TAG.album[i] = 0;
                }
                for( int32_t i = 0 , j = 0 ; i < 28 && j < 4 ; i++ , j++ )
                {
                    TAG.year[j] = 0;
                    TAG.comment[i] = 0;
                }
                TAG.zero_byte = 0;
                TAG.track = 0;
                TAG.genre = 255;

                lseek( fd_arr[i] , 0 , SEEK_END );
                write( fd_arr[i] , &TAG , 128);
            }

           
            if(tflag)
            {
                memcpy( TAG.title , title ,30);
                //print_tag( &TAG );
            }
            if(aflag)
            {
                memcpy( TAG.artist , artist , 30);
            }
            if(Aflag)
            {
                memcpy( TAG.album , album , 30);
            }
            if(cflag)
            {
                memcpy( TAG.comment , comment , 28);
            }
            if(yflag)
            {
                memcpy( TAG.year , year , 4);
            }
            if(Tflag)
            {
                TAG.track = track;
            }
            if(gflag)
            {   
                for( int8_t i = 0 ; i < 80 ; i++ )
                {
                    if(strcmp( Genre_arr[i] ,genre ) == 0)
                    {
                        TAG.genre = i;
                        printf("i = %hd\n",i);
                        printf("%s\n",Genre_arr[65]);
                        break;
                    }
                    if( i == 79 )
                    {
                        printf("There is no such genre.\n");
                    }
                }
                //print_tag( &TAG);
            }
            if(dflag)
            {
                struct stat buf;
                fstat(fd_arr[i] , &buf);
                //printf("%lld\n",buf.st_size-128);
                int64_t size = buf.st_size;
                uint8_t buffer[size-128];
                int tmpfd = open("tmp" , O_CREAT | O_RDWR );
                //for( int64_t i = 0 ; i < size - 128 ; i++ )
                //{
                    read( fd_arr[i] , buffer , size-128);
                    write( tmpfd , buffer , size-128);
                //}
                close( tmpfd);      
                close(fd_arr[i]);
                rename( "tmp" , argv[optind+i] );
                //int newfd = open( argv[optind+i] , O_RDWR );

                
            }
            if(lflag)
            {
                print_tag( &TAG );
                printf("\n");
            }
            
            if( !dflag )
            {
                lseek( fd_arr[i], -128 , SEEK_END);
                write( fd_arr[i] , &TAG , 128);
                close( fd_arr[i] );
                
                //print_tag(&TAG);
            }
        }

    }

    if(hflag)
    {
        printf("usage: hw0502 -[tTaAycg] \"value\" file1 [file2...]\n");
        printf("       hw0502 -d file1 [file2...]\n");
        printf("       hw0502 -l file1 [file2...]\n");
        printf("       hw0502 -h\n");
        printf("-t    Modifies a Title tag\n");
        printf("-T    Modifies a Track tag\n");
        printf("-a    Modifies an Artist tag\n");
        printf("-A    Modifies an Album tag\n");
        printf("-y    Modifies a Year tag\n");
        printf("-c    Modifies a Comment tag\n");
        printf("-g    Modifies a Genre tag\n");
        printf("-l    Lists an ID3 tag\n");
        printf("-d    Deletes an ID3 tag\n");
        printf("-h    Displays this help info\n");
    }

    
    return 0;
}