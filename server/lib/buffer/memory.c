/*
** EPITECH PROJECT, 2023
** zappy_server
** File description:
** memory.c
*/

#include "buffer.h"

#include <stdlib.h>
#include <string.h>

void buffer_init(string_buffer_t *buffer)
{
    buffer->buffer = NULL;
    buffer->len = 0;
    buffer->read_bytes = 0;
}

void buffer_free_content(string_buffer_t *buffer)
{
    free(buffer->buffer);
    buffer_init(buffer);
}

int buffer_truncate(string_buffer_t *buffer)
{
    if (buffer->read_bytes <= MAX_READ_BUFFER)
        return 0;
    char *new_buffer = malloc(sizeof(char)
        * (buffer->len - buffer->read_bytes + 1));
    if (new_buffer == NULL)
        return 1;
    memcpy(new_buffer, buffer->buffer + buffer->read_bytes,
        buffer->len - buffer->read_bytes);
    new_buffer[buffer->len - buffer->read_bytes] = '\0';
    free(buffer->buffer);
    buffer->len -= buffer->read_bytes;
    buffer->read_bytes = 0;
    buffer->buffer = new_buffer;
    return 0;
}
