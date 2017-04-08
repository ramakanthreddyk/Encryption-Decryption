#include <stdio.h>
#include <string.h>
#include <stdlib.h>

/* protect.c */

int main ( int argc, char *argv[] )
{
    int exitCode = 0;
    char dummyFileName[] = "fd.jpg";                                /* name of the mask file */
    char targetFileName[300];
    FILE *target = NULL, *source = NULL;
    int ch;
    const int TRUE = 1;

    if ( argc < 2 )                                             /* verified if argument (filename) is given */
    {
        puts ( "Insufficient arguments.  Please try again." );
        exitCode = 1;
    }
    else
    {
        source = fopen ( dummyFileName, "rb" );                 /* tried to open our mask file */
        if ( NULL == source )
        {
            perror ( dummyFileName );
            exitCode = 2;
        }
        else
        {
            strcpy ( targetFileName, argv[1] );                 /* generated target file name by */
            strcat ( targetFileName, ".jpg" );                  /* adding .jpg at the end of the */
                                                                /* input file name taken from argv[1] */
            target = fopen ( targetFileName, "wb" );            /* tried to open the target file (new file) */
            if ( NULL == target )
            {
                fclose ( source );
                perror ( targetFileName );
                exitCode = 3;
            }
            else
            {
                while ( TRUE )                                  /* transferred contents of mask file to new file */
                {
                    ch = fgetc ( source );
                    if ( feof ( source ) )
                    {
                        break;
                    }
                    fputc ( ch, target );
                }
                fclose ( source );

                source = fopen ( argv[1], "rb" );               /* tried to open the input file (argv[1])*/
                if ( NULL == source )
                {
                    fclose ( target );
                    perror ( argv[1] );
                    exitCode = 4;
                }
                else
                {
                    while ( TRUE )                              /* transferred all the characters to new file */
                    {
                        ch = fgetc ( source );
                        if ( feof ( source ) )
                        {
                            break;
                        }
                        fputc ( ~ch, target );
                    }
                    fclose ( source );
                    fclose ( target );
                    puts ( "protected." );
                }
            }
        }
    }
    getchar ();
    return exitCode;
}
