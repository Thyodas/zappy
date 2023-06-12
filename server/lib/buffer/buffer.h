/*
** EPITECH PROJECT, 2023
** zappy_server
** File description:
** buffer.h
*/

#pragma once

#include <stdint.h>

/**
 * Defines the max bytes a buffer can be read until everything read before is
 * freed using realloc.
 */
#define MAX_READ_BUFFER 1024

#define NEW_LINE_TERMINATOR "\r\n"

typedef struct string_buffer_s {
    uint32_t len;
    uint32_t read_bytes;
    char *buffer;
} string_buffer_t;

/**
 * Initializes a string buffer.
 * @param buffer The string buffer to initialize.
 * @note This function must be called before using a string buffer.
 */
void buffer_init(string_buffer_t *buffer);

/**
 * Frees a string buffer internal and re-inits the struct.
 * @param buffer The string buffer to free.
 * @note Since the string buffer is re-init you can re-use it after freeing it.
 */
void buffer_free_content(string_buffer_t *buffer);

/**
 * Reallocates the buffer by removing already read part in the buffer.
 * @param buffer The string buffer to truncate.
 * @return 1 on error, 0 otherwise.
 * @note This function only truncates if
 * ready_bytes > MAX_READ_BUFFER
 */
int buffer_truncate(string_buffer_t *buffer);

/**
 * This function writes a string to the buffer.
 * @param buffer The string buffer to write to.
 * @param string The string to write on the buffer.
 * @param len Size of the string to write.
 * @return 1 on error, 0 otherwise.
 */
int buffer_write(string_buffer_t *buffer, const char *string, uint32_t len);

/**
 * This function searches for a string ended by a separator.
 * The function first tries to search for the whole separator in the string
 * and if that fails it tries to find any char in the separator.
 * The string is returned without the separator and is ended by a null
 * terminator.
 * @param buffer The string buffer to read.
 * @param separator Characters that define the end of a valid string.
 * @return Pointer to the start of the read string, NULL if there is nothing
 * available.
 * @warning The returned pointer is not malloced. Using the pointer after
 * another call of this library is undefined behavior.
 */
char *buffer_read_on_separator(string_buffer_t *buffer, const char *separator);

/**
 * This function searches for a string ended by a newline.
 * The string is returned without the newline and is ended by a null
 * terminator.
 * @param buffer The string buffer to read.
 * @return Pointer to the start of the read string, NULL if there is nothing
 * available.
 * @warning The returned pointer is not malloced. Using the pointer after
 * another call of this library is undefined behavior.
 */
char *buffer_read_on_newline(string_buffer_t *buffer);

/**
 * Reads the whole unread buffer.
 * @param buffer The string buffer to read.
 * @return Pointer to the start of the read string, NULL if there is nothing
 * available.
 * @note If you want the size that will be read you can use the function
 * buffer_get_read_len.
 * @warning The returned pointer is not malloced. Using the pointer after
 * another call of this library is undefined behavior.
 */
char *buffer_read_all(string_buffer_t *buffer);

/**
 * Get the len of the string that can be read.
 * @param buffer The string buffer to test.
 * @return The len of the remaining string in the buffer.
 */
uint32_t buffer_get_read_len(string_buffer_t *buffer);
