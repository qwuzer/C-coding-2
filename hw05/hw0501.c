#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <unistd.h>
#include <getopt.h>

int kilo = 0, mega = 0, help = 0;
struct option longopts[] =
{
    { "bytes" , 0 , NULL , 'b'},
    { "kilo"  , 0 , &kilo , 1 },
    { "mega"  , 0 , &mega , 1 },
    { "seconds" , 1 , NULL , 's'},
    { "count" , 1 , NULL , 'c'},
    { "help" , 0 , &help , 1 },
    { 0 , 0 , 0 , 0 }
};


void print( FILE *fp1 , FILE *fp2 , double sec , double type )//type = byte , kb , mb
{                                                                // 1000 , 1 , 1/1000
    char  mem_avail[512];
    char  mem_total[512];
    fp1 = popen("grep -i 'mema'  /proc/meminfo | awk '{print $2}'" , "r");
    fp2 = popen("grep -i 'memt'  /proc/meminfo | awk '{print $2}'" , "r");
    if( fp1 == NULL || fp2 == NULL )
    {
        printf("Error end.\n");
        exit(1);
    }        

    char *endptr;
    fgets( mem_avail , 512 , fp1);
    fgets( mem_total , 512 , fp2);
    double kb_avail = strtod( mem_avail , &endptr );
    double kb_total = strtod( mem_total , &endptr );
    double percent = kb_avail / kb_total;
    if( type == 1000 ) printf("Available: %.lf B (%.2lf%%)\n",kb_avail*type , percent*100);
    if( type == 1 ) printf("Available: %.lf KB (%.2lf%%)\n",kb_avail*type , percent*100);
    if( type == 1/1000 ) printf("Available: %.2lf MB (%.2lf%%)\n",kb_avail*0.001 , percent*100);
    pclose(fp1);
    pclose(fp2);
    usleep(sec*1000000);
}

void flag_chk(  int32_t sflag , int32_t cflag , double type , int32_t ntimes , double nsec)
{
    FILE *fp1 = NULL;
    FILE *fp2 = NULL;

    if(sflag)
    {
        if(cflag)
        {
            for( int32_t i = 0 ; i < ntimes ; i++ )
            {
                print( fp1 , fp2 , nsec , type );
            }
        }
        else
        {
            while(1)
            {
                print( fp1 , fp2 , nsec , type );
            }
        }          
    }
    else
    {
        if(cflag)
        {
            for( int32_t i = 0 ; i < ntimes ; i++ )
            {
                print( fp1 , fp2 , 0 , type );
            }
        }
        else
        {
            print( fp1 , fp2 , 0 , type);
        }           
    }       
}



int main( int argc , char *argv[] )
{
    int c, index;
    int32_t bflag = 0, sflag = 0, cflag = 0, kflag = 0 ,mflag = 0 ,hflag = 0;
    int32_t ntimes = 0;
    double nsec = 0;char *eptr;
    while( ( c = getopt_long( argc , argv , "bs:c:", longopts , &index)) != -1)
    {
        switch(c)
        {
            case 'b':
                bflag = 1;
                break;
            case 's':
                sflag = 1;
                //nsec = atoi(optarg);//err
                nsec = strtod(optarg , &eptr);
                if(nsec <= 0)
                {
                    printf("Invalid input.\n");
                    return 0;
                }
                break;
            case 'c':
                cflag = 1;
                //ntimes = atoi(optarg);
                ntimes = strtod(optarg , &eptr);
                if(ntimes <= 0)
                {
                    printf("Invalid input\n");
                    return 0;
                }
                break;
            case  0 :
                if(kilo)
                {
                    kflag = 1;
                }
                if(mega)
                {
                    mflag = 1;
                }
                if(help)
                {
                    hflag = 1;
                }
                break;
            case '?':
                printf("option unknown.\n");
                return 0;
                break;
            default:
                return 0;
                break;
        }
    }

    if( (bflag && mflag) || (bflag && kflag) || (kflag && mflag)  )
    {
        printf("Only support showing one data type each time.\n");
        return 0;
    }

    if(hflag)
    {
        printf("Usage:\n");
        printf("    hw0501 [options]:\n");
        printf("Options\n");
        printf(" -b, --bytes        show output in bytes\n");
        printf("     --kilo         show output in kilobytes (default)\n");
        printf("     --mega         show output in megabytes\n");
        printf(" -s N, --seconds N  repeat printing every N seconds\n");
        printf(" -c N, --count N    repeat printing N times, then exit\n");
        printf("     --help     display this help and exit\n");
    }
    if(bflag) flag_chk( sflag , cflag , 1000 , ntimes , nsec);
    if(kflag) flag_chk( sflag , cflag , 1 , ntimes , nsec);
    if(mflag) flag_chk( sflag , cflag , 1/1000 , ntimes , nsec);
    if( !bflag && !kflag && !mflag ) flag_chk(sflag , cflag , 1 , ntimes , nsec);
    
    return 0;
}