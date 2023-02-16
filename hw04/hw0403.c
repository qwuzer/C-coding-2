#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <getopt.h>
#include <string.h>

#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>

#define BUF_SIZE 1024

struct option long_options[] =
    {
        {"linenum", 0, NULL, 'n'},
        {"color", 0, NULL, 'c'},
        {"language", 2, NULL, 'l'},
        {0, 0, 0, 0},
};

int32_t nflag, cflag, lflag;

int main(int argc, char *argv[])
{
    // getopt_long
    int c = 0;
    int32_t index = 0;
    char *lstr = "C";
    while ((c = getopt_long(argc, argv, "ncl::", long_options, &index)) != -1)
    {
        switch (c)
        {
        case 'n':
            nflag = 1;
            break;
        case 'c':
            cflag = 1;
            break;
        case 'l':
            lflag = 1;
            lstr = optarg;
            if (optarg == NULL)
            {
                lstr = "C";
            }
            break;
        case '?':
            printf("option: ?\n");
            break;
        default:
            printf("option: unknown\n");
            break;
        }
    }

    //printf("optind: %d\n", optind);
    //printf("optarg = %s\n", lstr);

    char filename[100];
    int fd;
    if (argc - optind == 1) // File // ( ./hw0403 -l c d -n ) ?
    {
        if ((fd = open(argv[optind], O_RDONLY)) == -1)
        {
            printf("Open file error.");
            return 0;
        }
        strcpy(filename, argv[optind]);
    }
    else if (argc - optind == 2)
    {
        if ((fd = open(argv[argc - 1], O_RDONLY)) == -1)
        {
            printf("Open file error.");
            return 0;
        }
        strcpy(filename, argv[optind]);
    }
    else
    {
        printf("Invalid input.");
        return 0;
    }

    if (strcmp(lstr, "C") == 0)
    {
        if (nflag)
        {
            if (cflag)
            {
                char command[1000];
                sprintf(command, "GREP_COLOR='01;33;40' egrep -i  --color=always ' auto | break | case | char | const | continue | default | do | double | else | enum | extern | float | for | goto | if | inline | int | int|int | long | register | restrict | return | short | signed | sizeof | static | struct | switch | typedef | union | unsigned | void | volatile | while | _Alignas | _Alignof | _Atomic | _Bool | _Complex | _Generic | _Imaginary | _Noreturn | _Static_assert | _Thread_local|$' %s | GREP_COLOR='01;36' egrep -n  --color=always '//|printf|$'", filename);
                system(command);
            }
            else
            {
                char command[1000];
                sprintf(command, "grep -i -n '$' %s ", filename);
                system(command);
            }
        }
        else
        {
            if (cflag)
            {
                char command[1000];
                sprintf(command, "GREP_COLOR='01;33;40' egrep -i  --color=always ' auto | break | case | char | const | continue | default | do | double | else | enum | extern | float | for | goto | if | inline | int | long | register | restrict | return | short | signed | sizeof | static | struct | switch | typedef | union | unsigned | void | volatile | while | _Alignas | _Alignof | _Atomic | _Bool | _Complex | _Generic | _Imaginary | _Noreturn | _Static_assert | _Thread_local|$' %s | GREP_COLOR='01;36' egrep  --color=always '//|printf|$'", filename);
                system(command);
            }
            else
            {
                char command[1000];
                sprintf(command, "grep -i '$' %s ", filename);
                system(command);
            }
        }
    }
    else if (strcmp(lstr, "C++") == 0)
    {
        if (nflag)
        {
            if (cflag)
            {
                char command[1000];
                sprintf(command, "GREP_COLOR='01;33;40' egrep -i  --color=always ' asm | auto | bool | break | case | catch | char | class | const | const_cast | continue | default | delete | do | double | dynamic_cast | else | enum | explicit | export | extern | false | float | for |friend | goto | if| inline | int |int|int | long | mutable | namespace | new | operator | private | protected | public | register | reinterpret_cast | return | short | signed | sizeof | static | static_cast | struct | switch| template | this | throw |true| try |typedef |typeid |typename |union |unsigned |using |virtual |void |volatile | wchar_t |while| and |and_eq| bitand| bitor| compl |not |not_eq |or| or_eq |xor| xor_eq |$' %s | GREP_COLOR='01;36' egrep -n  --color=always '//|printf|$'", filename);
                system(command);
            }
            else
            {
                char command[1000];
                sprintf(command, "grep -i -n '$' %s ", filename);
                system(command);
            }
        }
        else
        {
            if (cflag)
            {
                char command[1000];
                sprintf(command, "GREP_COLOR='01;33;40' egrep -i  --color=always ' asm | auto | bool | break | case | catch | char | class | const | const_cast | continue | default | delete | do | double | dynamic_cast | else | enum | explicit | export | extern | false | float | for |friend | goto | if| inline | int |int|int | long | mutable | namespace | new | operator | private | protected | public | register | reinterpret_cast | return | short | signed | sizeof | static | static_cast | struct | switch| template | this | throw |true| try |typedef |typeid |typename |union |unsigned |using |virtual |void |volatile | wchar_t |while| and |and_eq| bitand| bitor| compl |not |not_eq |or| or_eq |xor| xor_eq |$' %s | GREP_COLOR='01;36' egrep --color=always '//|printf|$'", filename);
                system(command);
            }
            else
            {
                char command[1000];
                sprintf(command, "grep -i '$' %s ", filename);
                system(command);
            }
        }
    }
    else if (strcmp(lstr, "Java") == 0)
    {
        if (nflag)
        {
            if (cflag)
            {
                char command[1000];
                sprintf(command, "GREP_COLOR='01;33;40' egrep -i  --color=always ' abstract | assert | boolean | break | byte | case | catch | char | class | const | continue | default | do | double | else | enum | extends | final | finally | float | for | if | goto | implements | import | instanceof | int | interface | long | native | new | package | private | protected | public | return | short | static | strictfp | super | switch | synchronized | this | throw | throws | transient | try | void | volatile | while | _ |$' %s | GREP_COLOR='01;36' egrep -n  --color=always '//|printf|$' ", filename);
                system(command);
            }
            else
            {
                char command[1000];
                sprintf(command, "grep -i -n '$' %s ", filename);
                system(command);
            }
        }
        else
        {
            if (cflag)
            {
                char command[1000];
                printf(command, "GREP_COLOR='01;33;40' egrep -i  --color=always ' abstract | assert | boolean | break | byte | case | catch | char | class | const | continue | default | do | double | else | enum | extends | final | finally | float | for | if | goto | implements | import | instanceof | int | interface | long | native | new | package | private | protected | public | return | short | static | strictfp | super | switch | synchronized | this | throw | throws | transient | try | void | volatile | while | _ |$' %s | GREP_COLOR='01;36' egrep  --color=always '//|printf|$' ", filename);
                system(command);
            }
            else
            {
                char command[1000];
                sprintf(command, "grep -i '$' %s ", filename);
                system(command);
            }
        }
    }
    else if (strcmp(lstr, "JS") == 0)
    {
        if (nflag)
        {
            if (cflag)
            {
                char command[1000];
                sprintf(command, "GREP_COLOR='01;33;40' egrep -i  --color=always ' await | break | case | catch | class | const | continue | debugger | default | delete | do | else | enum | export | extends | false | finally | for | function | if | import | in | instanceof | new | null | return | super | switch | this | throw | true | try | typeof | var | void | while | with | yield |$' %s | GREP_COLOR='01;36' egrep -n  --color=always '//|printf|$' ", filename);
                system(command);
            }
            else
            {
                char command[1000];
                sprintf(command, "grep -i -n '$' %s ", filename);
                system(command);
            }
        }
        else
        {
            if( cflag )
            {
            char command[1000];
            sprintf(command, "GREP_COLOR='01;33;40' egrep -i  --color=always ' await | break | case | catch | class | const | continue | debugger | default | delete | do | else | enum | export | extends | false | finally | for | function | if | import | in | instanceof | new | null | return | super | switch | this | throw | true | try | typeof | var | void | while | with | yield |$' %s | GREP_COLOR='01;36' egrep --color=always '//|printf|$' ", filename);
            system(command);
            }
            else
            {
                char command[1000];
                sprintf(command, "grep -i '$' %s ", filename);
                system(command);
            }
        }
    }
    else if (strcmp(lstr, "Rust") == 0)
    {
        if (nflag)
        {
            if(cflag)
            {
            char command[1000];
            sprintf(command, "GREP_COLOR='01;33;40' egrep -i  --color=always ' as | break | const | continue | crate | else | enum | extern | false | fn | for | if | impl | in | let | loop | match | mod | move | mut | pub | ref | return | self | Self | static | struct | super | trait | true | type | unsafe | use | where | while | async | await | dyn | abstract | become | box | do | final | macro | override | priv | typeof | unsized | virtual | yield | try | union | 'static |$' %s | GREP_COLOR='01;36' egrep -n  --color=always 'printf|//|$' ", filename);
            system(command);
            }
            else
            {
                char command[1000];
                sprintf(command, "grep -i -n '$' %s ", filename);
                system(command);
            }
        }
        else
        {
            if(cflag)
            {
            char command[1000];
            sprintf(command, "GREP_COLOR='01;33;40' egrep -i  --color=always ' as | break | const | continue | crate | else | enum | extern | false | fn | for | if | impl | in | let | loop | match | mod | move | mut | pub | ref | return | self | Self | static | struct | super | trait | true | type | unsafe | use | where | while | async | await | dyn | abstract | become | box | do | final | macro | override | priv | typeof | unsized | virtual | yield | try | union | 'static |$' %s | GREP_COLOR='01;36' egrep  --color=always 'printf|//|$' ", filename);
            system(command);
            }
            else
            {
                char command[1000];
                sprintf(command, "grep -i '$' %s ", filename);
                system(command);
            }
        }
    }
    close(fd);
    return 0;
}
