/*
** EPITECH PROJECT, 2023
** myteams
** File description:
** secure.h
*/

#pragma once

#include <stddef.h>
#include <string.h>

size_t my_strlcpy(char *dst, const char *src, size_t size);

static inline char *add_null_terminator(char *input, size_t end_pos)
{
    input[end_pos] = '\0';
    return input;
}

/**
 * @brief Ensures that a string is secure by adding a null terminator at the
 * end.
 * @warning This macro should only be used with name_t, description_t, body_t
 * and uuid_string_t types.
 * @param str The string to modify.
 * @return Returns the modified string.
 */
#define secure_string(str) (add_null_terminator(str, sizeof(str) - 1))
