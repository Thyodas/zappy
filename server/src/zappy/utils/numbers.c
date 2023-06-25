/*
** EPITECH PROJECT, 2023
** zappy_server
** File description:
** numbers.c
*/

#include <stdint.h>
#include <stdlib.h>
#include <errno.h>
#include <limits.h>
#include <math.h>
#include <stdio.h>

#include "data.h"

/**
 * Parses a number from a string and stores the result in a uint32_t variable.
 * @param parsed_nb Pointer to a uint32_t variable to store the parsed number.
 * @param to_parse The string to be parsed as a number.
 * @return 0 on success, 1 on error.
 */
int parse_number(uint32_t *parsed_nb, const char *to_parse)
{
    char *end;

    errno = 0;
    const long sl = strtol(to_parse, &end, 10);
    if (end == to_parse)
        return 1;
    if ('\0' != *end)
        return 1;
    if ((LONG_MIN == sl || LONG_MAX == sl) && ERANGE == errno)
        return 1;
    if (sl > UINT32_MAX)
        return 1;
    if (sl < 0)
        return 1;
    *parsed_nb = sl;
    return 0;
}

/**
 * Parses a number from a string and stores the result in a uint32_t variable.
 * @note Prints to stderr the detailed error.
 * @param parsed_nb Pointer to a uint32_t variable to store the parsed number.
 * @param to_parse The string to be parsed as a number.
 * @return 0 on success, 1 on error.
 */
int parse_number_print_error(uint32_t *parsed_nb, const char *to_parse)
{
    char *end;

    errno = 0;
    const long sl = strtol(to_parse, &end, 10);
    if (end == to_parse)
        return fprintf(stderr, HELP_MSG "\n'%s' not a decimal number.\n",
        to_parse);
    if ('\0' != *end)
        return fprintf(stderr, HELP_MSG
    "\n'%s' extra characters at end of input: %s.\n",to_parse, end);
    if ((LONG_MIN == sl || LONG_MAX == sl) && ERANGE == errno)
        return fprintf(stderr, HELP_MSG
    "\n%s is out of range of type uint32.\n", to_parse);
    if (sl > UINT32_MAX)
        return fprintf(stderr, HELP_MSG "\n%ld greater than INT_MAX.\n", sl);
    if (sl <= 0)
        return fprintf(stderr, HELP_MSG "\nValues must be >0.\n");
    *parsed_nb = sl;
    return 0;
}

/**
 * Constrains an angle value to the range [0, 360) degrees.
 *
 * @param x - The angle value to constrain.
 * @return The constrained angle value.
 */
double constrain_angle(double x)
{
    x = fmod(x,360);
    if (x < 0)
        x += 360;
    return x;
}
