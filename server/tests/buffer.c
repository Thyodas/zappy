/*
** EPITECH PROJECT, 2023
** zappy_server
** File description:
** buffer.c
*/

#include <criterion/criterion.h>
#include <string.h>

#include "buffer/buffer.h"

string_buffer_t buffer;

const char first_write[] = "Hello world!\n";
const char second_write[] = "Hope you're doing ok :)\n";
const char third_write[] = "aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa";
const char fourth_write[] = "bozo SEP final";

void test_init()
{
    buffer_init(&buffer);
    cr_assert(buffer.buffer == NULL);
    cr_assert_null(buffer.buffer);
    cr_assert_eq(buffer.len, 0);
    cr_assert_eq(buffer.read_bytes, 0);
}

void test_fini()
{
    buffer_free_content(&buffer);
    cr_assert(buffer.buffer == NULL);
    cr_assert_null(buffer.buffer);
    cr_assert_eq(buffer.len, 0);
    cr_assert_eq(buffer.read_bytes, 0);
}

void test_simple_write()
{
    const char *to_write = first_write;
    size_t len = strlen(to_write);
    buffer_write(&buffer, to_write, len);
    cr_assert_str_eq(buffer.buffer, to_write);
    cr_assert_eq(buffer.len, len);
    cr_assert_eq(buffer.read_bytes, 0);
}

void test_double_write()
{
    const char *to_write = second_write;
    size_t len = strlen(to_write);
    size_t previous_len = buffer.len;
    buffer_write(&buffer, to_write, len);

    char *concatenated = NULL;
    cr_asprintf(&concatenated, "%s%s", first_write, second_write);
    cr_assert_str_eq(buffer.buffer, concatenated);
    cr_asprintf_free(concatenated);

    cr_assert_eq(buffer.len, len + previous_len);
    cr_assert_eq(buffer.read_bytes, 0);
}

void test_read_newline()
{
    char *read = buffer_read_on_newline(&buffer);
    size_t previous_len = buffer.len;
    cr_assert(strncmp(read, first_write, strlen(first_write) - 1) == 0);
    cr_assert_eq(buffer.len, previous_len);
    cr_assert_eq(buffer.read_bytes, strlen(first_write));
}

void test_read_all()
{
    const char *to_write = third_write;
    size_t len = strlen(to_write);
    size_t previous_len = buffer.len;
    buffer_write(&buffer, to_write, len);

    char *concatenated = NULL;
    cr_asprintf(&concatenated, "%s%s", second_write, to_write);
    cr_assert_str_eq(buffer.buffer + buffer.read_bytes, concatenated);

    cr_assert_eq(buffer.len, len + previous_len);
    char *read = buffer_read_all(&buffer);
    cr_assert_str_eq(read, concatenated);
    cr_asprintf_free(concatenated);
}

void test_truncate()
{
    cr_assert_gt(buffer.read_bytes, 1024);
    const char *to_write = fourth_write;
    size_t len = strlen(to_write);
    size_t previous_len = buffer.len;
    // this write should truncate the buffer
    buffer_write(&buffer, to_write, len);
    cr_assert_str_eq(buffer.buffer, fourth_write);
    cr_assert_neq(buffer.len, len + previous_len);
    cr_assert_eq(buffer.read_bytes, 0);
}

Test(buffer, basic, .init=test_init, .fini=test_fini) {
    test_simple_write();
    test_double_write();
    test_read_newline();
    test_read_all();
    test_truncate();
}
