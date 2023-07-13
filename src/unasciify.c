/* 
    unasciify -- Turn ascii representation into strings and files
    Copyright (C) 2023 Spydr06  

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version. 

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.  
      
    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <https://www.gnu.org/licenses/>.  
*/

#include <ctype.h>
#include <errno.h>
#include <getopt.h>
#include <locale.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "common.h"

#define PROGRAM_NAME "unasciify"

void emit_try_help(void)
{

}

_Noreturn void usage(int status)
{
    if(status != EXIT_SUCCESS)
        emit_try_help();
    else
    {
        printf("Usage: %s [OPTION]... [FILE|STRING]...\n", program_name);
        fputs("Turn a FILE or STRING in ascii-representation into a string.\n", stdout);
    
        fputs(_("\
\n\
  -d, --decimal   input in decimal format\n\
  -o, --octal     input in octal format\n\
  -f, --file      read from FILE\n\
  -s, --string    read from STRING\n\
"), stdout);
        fputs(HELP_OPTION_DESCRIPTION, stdout);
        fputs(VERSION_OPTION_DESCRIPTION, stdout);

        emit_ancillary_info();
    }
    exit(status);
}

int main(int argc, char* argv[]) {
    static const char short_options[] = "dof:s:";
    static struct option const long_options[] =
    {
        {"decimal", no_argument,      NULL, 'd'},
        {"octal",  no_argument,       NULL, 'o'},
        {"file",   required_argument, NULL, 'f'},
        {"string", required_argument, NULL, 's'},
        {GETOPT_HELP_OPTION_DECL               },
        {GETOPT_VERSION_OPTION_DECL            },
        {NULL, 0, NULL, 0                      }
    };

    set_program_name(argv[0]);
    setlocale(LC_ALL, "");

    const char* fmt = "%02x";
    unsigned char fmt_length = 2;
    
    const char* filename = NULL;
    const char* buffer = NULL;

    int c;
    while ((c = getopt_long(argc, argv, short_options, long_options, NULL)) != -1)
    {
        switch(c)
        {
        case 'd':
            fmt = "%03u";
            fmt_length = 3;
            break;
        case 'o':
            fmt = "%03o";
            fmt_length = 3;
            break;
        case 'f':
            fmt = optarg;
            break;
        case 's':
            buffer = optarg;
            break;
        
        case_GETOPT_HELP_CHAR;
        case_GETOPT_VERSION_CHAR(PROGRAM_NAME);
    
        default:
            usage(EXIT_FAILURE);
        }
    }

    if(!filename && !buffer)
    {
        printf("%s: neither an input string nor a file is defined.\n", program_name);
        emit_help_suggestion();
    }

    if(filename && buffer)
    {
        printf("%s: both an input string and a file is defined.\n", program_name);
        emit_help_suggestion();
    }

    if(buffer)
    {
        while(*buffer)
        {
            while(isspace(*buffer)) buffer++;

            int c;
            if(!sscanf(buffer, fmt, &c))
                error(EXIT_FAILURE, errno, "format error");
            buffer += fmt_length;
            putchar(c);
        }
    }
    else {
        FILE* fp = fopen(filename, "rb");
        if(!fp)
            error(EXIT_FAILURE, errno, filename);
        
        while(!feof(fp))
        {
            int c;
            while(isspace(c = fgetc(fp)));
            ungetc(c, fp);

            if(!fscanf(fp, fmt, &c))
                error(EXIT_FAILURE, errno, "format error");
            putchar(c);
        }

        fclose(fp);
    }

    putchar('\n');
    fflush(stdout);
    return 0;
}

