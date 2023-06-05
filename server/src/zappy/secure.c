/*
** EPITECH PROJECT, 2023
** myteams
** File description:
** secure.c
*/

#include "secure.h"

/**
 * The my_strlcpy() function copies up to size - 1 characters from
 * the NUL-terminated string src to dst, NUL-terminating the result.
 * @param dst Destination string ptr
 * @param src Src string ptr
 * @param size Size of the dst req_buffer (must be large enough for the \0)
 * @return
 */
size_t my_strlcpy(char *dst, const char *src, size_t size)
{
    size_t len = strnlen(src, size - 1);
    strncpy(dst, src, len);
    dst[len] = '\0';
    return len;
}
