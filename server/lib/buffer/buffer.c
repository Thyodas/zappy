/*
** EPITECH PROJECT, 2023
** zappy_server
** File description:
** buffer.c
*/

#include "buffer.h"

#include <unistd.h>
#include <stdlib.h>
#include <string.h>

#include <assert.h>
#include <memory.h>

int buffer_write(string_buffer_t *buffer, const char *string, uint32_t len)
{
    buffer_truncate(buffer);
    char *tmp = realloc(buffer->buffer, len + buffer->len + 1);
    if (tmp == NULL) {
        buffer_free_content(buffer);
        return 1;
    }
    buffer->buffer = tmp;
    memcpy(buffer->buffer + buffer->len, string, len);
    buffer->len += len;
    buffer->buffer[buffer->len] = '\0';
    return 0;
}

char *buffer_read_on_separator(string_buffer_t *buffer, const char *separator)
{
    buffer_truncate(buffer);
    uint32_t delim_len = 1;
    char *delim_pos = strstr(buffer->buffer + buffer->read_bytes, separator);
    if (delim_pos == NULL)
        delim_pos = strpbrk(buffer->buffer + buffer->read_bytes, separator);
    else
        delim_len = strlen(separator);
    if (delim_pos == NULL)
        return NULL;
    char *read_string = buffer->buffer + buffer->read_bytes;
    *delim_pos = '\0';
    assert(read_string != NULL);
    buffer->read_bytes = (delim_pos - buffer->buffer) + delim_len;
    return read_string;
}

char *buffer_read_all(string_buffer_t *buffer)
{
    buffer_truncate(buffer);
    char *read_string = buffer->buffer + buffer->read_bytes;
    buffer->read_bytes += buffer->len - buffer->read_bytes;
    assert(buffer->read_bytes == buffer->len);
    return read_string;
}

char *buffer_read_on_newline(string_buffer_t *buffer)
{
    return buffer_read_on_separator(buffer, NEW_LINE_TERMINATOR);
}

uint32_t buffer_get_read_len(string_buffer_t *buffer)
{
    return buffer->len - buffer->read_bytes;
}
