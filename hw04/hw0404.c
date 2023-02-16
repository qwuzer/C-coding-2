#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>

#include <stdint.h>
#include <sys/types.h>
#include <sys/stat.h>

#include <sys/mman.h>

void yellow ()
{
  printf("\033[1;33m");
}
void reset () 
{
  printf("\033[0m");
}

int32_t print_menu( void )
{
    int32_t num = 0;
    printf("------------------------------------------------\n");
    printf("This is the Main menu, please enter the number : \n ");
    printf("------------------------------------------------\n");
    printf("(1) Personal Statistics\n");
    printf("(2) General\n");
    printf("(3) Combat\n");
    printf("(4) Repuatation \n");
    printf("(5) Social & House skills\n");
    printf("(6) Money\n");
    printf("(7) Health status\n");
    printf("(8) Quit\n");
    printf("Your choice: ");
    scanf("%d",&num);
    return num;
}

int32_t printf_menu_general ( void )
{
    int32_t num = 0;
    printf("----------------------------------------------------\n");
    printf("This is the General menu, please enter the number : \n ");
    printf("----------------------------------------------------\n");
    printf("(1)  Constitution\n");
    printf("(2)  Strength\n");
    printf("(3)  Intelligence\n");
    printf("(4)  Renfinement\n");
    printf("(5)  Charisma\n");
    printf("(6)  Morals\n");
    printf("(7)  Faith\n");
    printf("(8)  Sin\n");
    printf("(9)  Sensitivity\n");
    printf("(10) Stress\n");
    printf("(11) Popularity\n");
    printf("(12) Previous menu\n");
    printf("Your choice: ");
    scanf("%d",&num);
    return num;
}

int32_t  printf_menu_personal(void)
{
    int32_t num = 0;
    printf("---------------------------------------------------------------\n");
    printf("This is the Personal Statistics menu, please enter the number : \n ");
    printf("---------------------------------------------------------------\n");
    printf("(1) Age\n");
    printf("(2) Weight\n");
    printf("(3) Height\n");
    printf("(4) Bust\n");
    printf("(5) Waist\n");
    printf("(6) Hips\n");
    printf("(7) Previous menu\n");
    printf("Your choice: ");
    scanf("%d",&num);
    return num;
}

int32_t  printf_menu_combat(void)
{
    int32_t num = 0;
    printf("--------------------------------------------------\n");
    printf("This is the Combat menu, please enter the number : \n ");
    printf("--------------------------------------------------\n");
    printf("(1) Combat skills\n");
    printf("(2) Combat attack\n");
    printf("(3) Combat defense\n");
    printf("(4) Magic skill\n");
    printf("(5) Magic attack\n");
    printf("(6) Magic defense\n");
    printf("(7) Previous menu\n");
    printf("Your choice: ");
    scanf("%d",&num);
    return num;
}
int32_t  printf_menu_reputation(void)
{
    int32_t num = 0;
    printf("------------------------------------------------------\n");
    printf("This is the Reputation menu, please enter the number : \n ");
    printf("-------------------------------------------------------\n");
    printf("(1) Fighter\n");
    printf("(2) Magical\n");
    printf("(3) Social\n");
    printf("(4) Housework\n");
    printf("(5) Previous menu\n");
    printf("Your choice: ");
    scanf("%d",&num);
    return num;
}

int32_t  printf_menu_skills(void)
{
    int32_t num = 0;
    printf("------------------------------------------------------------------\n");
    printf("This is the Social & House skill's menu, please enter the number : \n ");
    printf("------------------------------------------------------------------\n");
    printf("(1) Decorum\n");
    printf("(2) Art\n");
    printf("(3) Conversation\n");
    printf("(4) Cooking\n");
    printf("(5) Cleaning\n");
    printf("(6) Temperament");
    printf("(7) Previous menu\n");
    printf("Your choice: ");
    scanf("%d",&num);
    return num;
}

int32_t  printf_menu_health(void)
{
    int32_t num = 0;
    printf("------------------------------------------------------------\n");
    printf("This is the health status menu, please enter the number : \n ");
    printf("------------------------------------------------------------\n");
    printf("(1) Sickness\n");
    printf("(2) Deliquencey\n");
    printf("(3) Previous menu\n");
    printf("Your choice: ");
    scanf("%d",&num);
    return num;
}

uint64_t util_getFdSize( int fd )
{
    struct stat statbuf;
    
    if( fstat( fd, &statbuf ) < 0 )
    {
        close( fd );
        return -1;
    }
    
    return statbuf.st_size;
}

typedef struct _sAttributes//62
{
    uint16_t hp;
    uint16_t arm_strength;
    uint16_t iq;
    uint16_t grace;
    uint16_t charisma;
    uint16_t moral;
    uint16_t belief;
    uint16_t sin;
    uint16_t feelings;
    uint16_t fatigue;
}attributes;

typedef struct _sAbilities
{
    uint16_t fighting_skill;
    uint16_t attack;
    uint16_t defense;
    uint16_t magic_skill;
    uint16_t magic_abillity;
    uint16_t magic_defense;
}abilities;

typedef struct _sRatings
{
    uint16_t warrior;
    uint16_t magic;
    uint16_t social;
    uint16_t housework;
}ratings;

typedef struct _speformance
{
    uint16_t etiquette;
    uint16_t art;
    uint16_t speak;
    uint16_t cook;
    uint16_t wash;
    uint16_t greet;
}performance;


typedef struct _sBody_indexs
{
    uint16_t height;//cm
    uint16_t weight;//10g
    uint16_t breast;//0.1mm
    uint16_t waist;//0.1mm
    uint16_t hips;//0.1mm
}body_indexs;


int main()
{
    int32_t fd = 0;
    int32_t fd2 = 0;
    int32_t choice = 0;
    char	fileName[256] = {0};
    char    fileName2[256] = {0};
    
    printf( "Please enter the file name: " );
    
    if( fgets( fileName, sizeof( fileName ), stdin ) == NULL )
    {
        printf( "Error!\n" );
        return 0;
    }

    if( fileName[ strlen( fileName ) - 1 ] == '\n' )
    {
        fileName[ strlen( fileName ) - 1 ] = 0;
    }

    fd = open( fileName, O_RDWR );

    // Open file descriptor
    if( fd == -1 )
    {
        printf( "Open file error!\n" );
        return -1;
    }

    printf( "Please enter the file name: " );
    if( fgets( fileName2, sizeof( fileName2 ), stdin ) == NULL )
    {
        printf( "Error!\n" );
        return 0;
    }

    // Since fgets will include '\n', we need to remove this character.
    
    
    if( fileName2[ strlen( fileName2 ) - 1 ] == '\n' )
    {
        fileName2[ strlen( fileName2 ) - 1 ] = 0;
    }

    
    fd2 = open( fileName2, O_RDWR );

    if( fd2 == -1)
    {
         printf( "Open file error!\n" );
        return -1;
    }
    
    // MMAP
    
    char    *_pFile = NULL;
    char    *_pFile2 = NULL;
    uint64_t fileSize = util_getFdSize( fd );
    uint64_t fileSize2 = util_getFdSize( fd2 );
    
    attributes *attribute ;
    abilities *ability;
    ratings *rating;
    performance *perform;
    body_indexs *bodyindex;
    

    _pFile = mmap( 0, fileSize, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0 );
    _pFile2 = mmap( 0, fileSize2, PROT_READ | PROT_WRITE, MAP_SHARED, fd2, 0 );

    
    attribute = (attributes *)(_pFile + 62);
    ability = (abilities *)(_pFile + 92);
    rating = (ratings *)(_pFile + 84);
    perform = (performance *)(_pFile + 104);
    bodyindex = (body_indexs *)(_pFile + 210);
    uint16_t *money = (uint16_t *)(_pFile + 176);
    uint16_t *item = (uint16_t *)(_pFile + 2072);
    uint16_t *disease = (uint16_t *)(_pFile + 234);
    uint16_t *delinquent = (uint16_t *)(_pFile + 236);
    uint16_t *pop = (uint16_t *)(_pFile + 238);


    int32_t end = 1;
    while( end )
    {
        switch (print_menu())
        {
        case 1:
            switch(printf_menu_personal()) 
            {
                case 1 :
                    break;
                case 2:
                    printf("Change weight to(kg):");
                    uint16_t w = 0;
                    scanf("%hd",&w);
                    w *= 100;
                    bodyindex->weight = w;
                    break;
                case 3:
                    printf("Change height to(cm):");
                    uint16_t h = 0;
                    scanf("%hd",&h);
                    h *= 100;
                    bodyindex->height = h;
                    break;
                case 4:
                    printf("Change bust to(cm):");
                    int16_t b = 0;
                    scanf("%hd",&b);
                    b *= 100;
                    bodyindex->breast = b;
                    break;
                case 5:
                    printf("Change waist to(cm):");
                    uint16_t wst = 0;
                    scanf("%hd",&wst);
                    wst *= 100;
                    bodyindex->waist = wst;
                    break;
                case 6:
                    printf("Change hips to(cm):");
                    uint16_t hsp = 0;
                    scanf("%hd",&hsp);
                    hsp *= 100;
                    bodyindex->hips = hsp;
                    break;
                case 7:
                    break;
                default:
                    printf("Invalid.\n");
                    break;
            }
            break;
        case 2:
            switch(printf_menu_general())
            {
                case 1: 
                    printf("Change constitution to:");
                    scanf("%hd",&(attribute->hp));
                    break;
                case 2:
                    printf("Change strength to:");
                    scanf("%hd",&(attribute->arm_strength));
                    break;
                case 3:
                    printf("Change intelligence to:");
                    scanf("%hd",&(attribute->iq));
                    break;
                case 4:
                    printf("Change refinement to:");
                    scanf("%hd",&(attribute->grace));
                    break;
                case 5:
                    printf("Change charisma to:");
                    scanf("%hd",&(attribute->charisma));
                    break;
                case 6:
                    printf("Change morals to:");
                    scanf("%hd",&(attribute->moral));
                    break;
                case 7:
                    printf("Change faith to:");
                    scanf("%hd",&(attribute->belief));
                    break;
                case 8:
                    printf("Change sin to:");
                    scanf("%hd",&(attribute->sin));
                    break;
                case 9:
                    printf("Change sensitivity to:");
                    scanf("%hd",&(attribute->feelings));
                    break;
                case 10:
                    printf("Change stress to:");
                    scanf("%hd",&(attribute->fatigue));
                    break;
                case 11:
                    printf("Change popualarity to:");
                    scanf("%hd",pop);
                    break;
                default:
                    printf("Invalid.");
                    break;
            }
            break;
        case 3:
            switch(printf_menu_combat())
            {
                case 1:
                    printf("Change combat skills to:");
                    scanf("%hd",&(ability->fighting_skill));
                    break;
                case 2:
                    printf("Change combat attack to:");
                    scanf("%hd",&(ability->attack));
                    break;
                case 3:
                    printf("Change combat defense to:");
                    scanf("%hd",&(ability->defense));
                    break;
                case 4:
                    printf("Change magic skill to:");
                    scanf("%hd",&(ability->magic_skill));
                    break;
                case 5:
                    printf("Change magic attack to:");
                    scanf("%hd",&(ability->magic_abillity));
                    break;
                case 6:
                    printf("Change magic defense to:");
                    scanf("%hd",&(ability->magic_defense));
                    break;
                case 7:
                    break;
                default:
                    printf("Invalid.");
                    break;
            }
            break;
        case 4:
            switch( printf_menu_reputation())
            {
                case 1:
                    printf("Change fighter reputation to:");
                    scanf("%hd",&(rating->warrior));
                    break;
                case 2:
                    printf("Change magical reputation to:");
                    scanf("%hd",&(rating->magic));
                    break;
                case 3:
                    printf("Change social reputation to:");
                    scanf("%hd",&(rating->social));
                    break;
                case 4:
                    printf("Change housework reputation to:");
                    scanf("%hd",&(rating->housework));
                    break;
                case 5:
                    break;
                default:
                    printf("Invalid.");
                    break;
            }
            break;
        case 5:
            switch( printf_menu_skills() )
            {
                case 1:
                    printf("Change decorum skills to:");
                    scanf("%hd",&(perform->etiquette));
                    break;
                case 2:
                    printf("Change art skills to:");
                    scanf("%hd",&(perform->art));
                    break;
                case 3:
                    printf("Change conversation skills to:");
                    scanf("%hd",&(perform->speak));
                    break;
                case 4:
                    printf("Change cooking skills to:");
                    scanf("%hd",&(perform->cook));
                    break;
                case 5:
                    printf("Change cleaning skills to:");
                    scanf("%hd",&(perform->wash));
                    break;
                case 6:
                    printf("Change temperament skills to:");
                    scanf("%hd",&(perform->greet));
                    break;
                case 7:
                    break;
                default:
                    printf("Invalid.");
                    break;
            }
            break;
        case 6:
            printf("Change $money$ to:");
            scanf("%hd",money);
            break;
        case 7:
            switch(printf_menu_health())
            {
                case 1:
                    printf("Change sickness rate to:");
                    scanf("%hd",disease);
                    break;
                case 2:
                    printf("Change deliquency rate to:");
                    scanf("%hd",delinquent);
                    break;
                case 3:
                    break;
                    break;
                default:
                    break;
            }
            break;
        case 8:
            end = 0;
            break;
        default:
            break;
        }
    }
/*
    attribute->hp = 999;
    attribute->arm_strength = 999;
    attribute->iq = 999;
    attribute->grace = 999;
    attribute->charisma = 999;
    attribute->moral = 999;
    attribute->belief = 999;
    attribute->sin = 0;
    attribute->feelings = 999;
    attribute->fatigue = 0;

    ability->fighting_skill = 100;
    ability->attack = 100;
    ability->defense = 100;
    ability->magic_skill = 100;
    ability->magic_abillity = 999;
    ability->magic_defense = 999;

    rating->warrior = 999;
    rating->magic = 999;
    rating->social = 999;
    rating->housework = 999;

    perform->etiquette = 200;
    perform->art = 200;
    perform->cook =200;
    perform->greet =200;
    perform->speak =200;
    perform->wash =200;
*/
    //bodyindex->height = 18000;
    //*money = 65535;
    //*item = 5;
   /* int32_t cnt = 0;
    for(int32_t i = 0 , j = 0 ; i < 3400 ; i+=2 ,j++)
    {
        uint16_t *p = (uint16_t *)(_pFile + i);
        uint16_t *p2 = (uint16_t *)(_pFile2 + i);
        if( *p != *p2 )
        {
           // yellow();
            printf("%d %x :  p1 = %d p2 = %d\n", j*2 , j * 2 , *p , *p2);
           // reset();
            cnt++;
        }
        else
        {
            //printf("%d %x :  p1 = %d p2 = %d\n", j*2 , j * 2 , *p , *p2);
        }
        //printf("%d %x :  p1 = %d p2 = %d\n", j*2 , j * 2 , *p , *p2);
    }

    printf("cnt = %d",cnt);*/
    munmap( _pFile, fileSize );
    

   
    close( fd );
    
    return 0;
}
