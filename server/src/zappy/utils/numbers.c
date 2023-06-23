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

double constrain_angle(double x)
{
    x = fmod(x,360);
    if (x < 0)
        x += 360;
    return x;
}
