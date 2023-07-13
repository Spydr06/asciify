#                                               -*- Autoconf -*-
# Process this file with autoconf to produce a configure script.
AC_PREREQ([2.71])
AC_INIT([asciify],[0.1],[https://www.github.com/spydr06/asciify/issues])
AM_INIT_AUTOMAKE([-Wall foreign])

AC_CONFIG_SRCDIR([src/asciify.c])
AC_CONFIG_SRCDIR([src/unasciify.c])
AC_CONFIG_HEADERS([src/config.h])
AC_CONFIG_FILES([
    Makefile
    src/Makefile
])

# Checks for programs.
AC_PROG_CC

# Checks for header files.
AC_CHECK_HEADERS([
    ctype.h
    errno.h
    getopt.h
    locale.h
    stdbool.h
    stdio.h
    stdlib.h
    string.h
])
AC_CHECK_HEADER_STDBOOL

# Checks for typedefs, structures, and compiler characteristics.
AC_C_INLINE

# Checks for library functions.
AC_FUNC_ERROR_AT_LINE
AC_FUNC_MALLOC
AC_CHECK_FUNCS([
    exit
    putchar
    printf
    fopen
    fseek
    feof
    ungetc
    fscanf
    fgetc
    ftell
    fread
    fclose
    fputs
    fprintf
    fflush
    setlocale
    strerror
    sscanf
    isspace
    getopt_long
])

AC_OUTPUT
