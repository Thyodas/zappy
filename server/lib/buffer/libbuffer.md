## Buffer C Library

The `buffer` library provides functions for handling string buffers in C. It allows you to write strings to a buffer, read strings from a buffer based on separators or newlines, and manage the buffer's memory.

### Data Structures

The library defines the following data structure:

#### `string_buffer_t`

```c
typedef struct string_buffer_s {
    uint32_t len;
    uint32_t read_bytes;
    char *buffer;
} string_buffer_t;
```

- `len`: The total length of the buffer.
- `read_bytes`: The number of bytes that have been read from the buffer.
- `buffer`: A character array that holds the string data.

### Functions

The library provides the following functions:

#### `void buffer_init(string_buffer_t *buffer)`

Initializes a string buffer. This function must be called before using a string buffer.

#### `void buffer_free_content(string_buffer_t *buffer)`

Frees the internal buffer and re-initializes the struct. After freeing, the string buffer can be re-used.

#### `int buffer_truncate(string_buffer_t *buffer)`

Reallocates the buffer by removing the already read part in the buffer. It only truncates if `read_bytes > MAX_READ_BUFFER`. Returns 1 on error, 0 otherwise.

#### `int buffer_write(string_buffer_t *buffer, const char *string, uint32_t len)`

Writes a string to the buffer. Takes the string and its length as input. Returns 1 on error, 0 otherwise.

#### `char *buffer_read_on_separator(string_buffer_t *buffer, const char *separator)`

Searches for a string ended by a separator in the buffer. First, it tries to search for the whole separator in the string. If that fails, it tries to find any character in the separator. The string is returned without the separator and is ended by a null terminator. Returns a pointer to the start of the read string or NULL if there is nothing available.

#### `char *buffer_read_on_newline(string_buffer_t *buffer)`

Searches for a string ended by a newline in the buffer. The string is returned without the newline and is ended by a null terminator. Returns a pointer to the start of the read string or NULL if there is nothing available.

#### `char *buffer_read_all(string_buffer_t *buffer)`

Reads the whole unread buffer. Returns a pointer to the start of the read string or NULL if there is nothing available. If you want to get the size that will be read, you can use the `buffer_get_read_len` function.

#### `uint32_t buffer_get_read_len(string_buffer_t *buffer)`

Gets the length of the remaining string that can be read from the buffer.

### Example Usage

Here's an example code snippet demonstrating the usage of the `buffer` library:

```c
#include "buffer.h"
#include <stdio.h>

int main() {
    string_buffer_t buffer;
    buffer_init(&buffer);

    // Write a string to the buffer
    buffer_write(&buffer, "Hello, ", 7);

    // Write another string to the buffer
    buffer_write(&buffer, "world!", 6);

    // Read a string from the buffer until a newline is encountered
    char *str = buffer_read_on_newline(&buffer);
    if (str != NULL) {
        printf("Read string: %s\n", str);
    }

    // Free the buffer's content
    buffer_free_content(&buffer);

    return 0;
}
```

This example initializes a string buffer, writes two strings to it, reads a string from the buffer until a newline is encountered, and finally frees the buffer's content.
