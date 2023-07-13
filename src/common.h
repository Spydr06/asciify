/* 
    asciify -- turn strings and files into their ascii representation
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

#ifndef ASCIIFY_COMMON_H
#define ASCIIFY_COMMON_H

#include <stdlib.h>
#include "config.h"

#define COPYRIGHT_YEAR 2023
#define AUTHORS "Spydr06"

#define quote(t) #t
#define _(str) str

#define HELP_OPTION_DESCRIPTION _("\
      --help      display this help text and exit\n\
")

#define VERSION_OPTION_DESCRIPTION _("\
      --version   output version information and exit\n\
")

#define HELP_OPT 1000
#define VERSION_OPT 1001

#define GETOPT_HELP_OPTION_DECL "help", no_argument, NULL, HELP_OPT
#define GETOPT_VERSION_OPTION_DECL "version", no_argument, NULL, VERSION_OPT

#define case_GETOPT_HELP_CHAR \
    case HELP_OPT: usage(EXIT_SUCCESS);

#define case_GETOPT_VERSION_CHAR(program_name)                                           \
    case VERSION_OPT: printf(                                                            \
"%s %s\n"                                                                         \
"Copyright (C) %d\n"                                                                     \
"License: GPLv3+: GNU GPL version 3 lor later <https://gnu.org/licenses/gpl.html>.\n"    \
"This is free software; see the source for copying conditions.\n"                        \
"There is NO WARRANTY provided with this program.\n"                                     \
"\n"                                                                                     \
"Written by %s.\n"                                                                       \
, program_name, PACKAGE_VERSION, COPYRIGHT_YEAR, AUTHORS); \
exit(EXIT_SUCCESS);

static const char* program_name;

inline static void set_program_name(const char* name)
{
    program_name = name;
}

inline static _Noreturn void error(int exit_code, int _errno, const char* error_msg)
{
    fprintf(stderr, "%s: %s: %s\n", program_name, error_msg, strerror(_errno));
    exit(exit_code);
}

inline static _Noreturn void emit_help_suggestion(void)
{
    printf("Try '%s --help' for more information.\n", program_name);
    exit(EXIT_FAILURE);          
}

inline static void emit_ancillary_info(void)
{
    fputs("\nasciify online repository: <" PACKAGE_URL ">\n", stdout);
}

#endif /* ASCIIFY_COMMON_H */