/*
** EPITECH PROJECT, 2023
** zappy_server
** File description:
** string.c
*/

#include <stdlib.h>
#include <string.h>

/**
 * Splits a string into an array of substrings based on the specified
 * separators.
 * @param str The string to be split.
 * @param separators A string containing the characters to be used as
 * separators.
 * @param len Pointer to an integer variable to store the length of the
 * resulting array.
 * @param max_arg Maximum number of substrings to be extracted. If the number
 * of substrings reaches or exceeds this value, the remaining separators
 * will be ignored.
 * @return A dynamically allocated array of strings, where each element is a
 * substring from the original string.
 * The last element of the array is set to NULL.
 * @note It is the responsibility of the caller to free the memory allocated
 * for the array.
 * @warning Strings are not malloced, they are pointers from the str, like
 * strtok.
 */
char **split_str_to_array(char *str, char *seperators, int *len, int max_arg)
{
    char **array = NULL;
    int size = 0;
    char **lasts = &str;
    char *token;
    if (max_arg > 1 && size + 1 >= max_arg)
        seperators = "";
    for (token = strtok_r(str, seperators, lasts); token;
        token = strtok_r(NULL, seperators, lasts)) {
        ++size;
        array = realloc(array, sizeof(char *) * (size + 1));
        array[size - 1] = token;
        array[size] = NULL;
        if (max_arg > 1 && size + 1 >= max_arg)
            seperators = "";
    }
    *len = size;
    return array;
}
