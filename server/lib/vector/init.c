/*
** EPITECH PROJECT, 2023
** myteams
** File description:
** init.c
*/

#include "vector.h"

int vector_resize(vector_template_t *array, size_t new_len)
{
    array->content = realloc(array->content, sizeof(void *) * new_len);
    if (array->content == NULL) {
        array->len = 0;
        return -1;
    }
    array->len = new_len;
    return 0;
}

int vector_init(vector_template_t *array, size_t element_size)
{
    array->len = 0;
    array->element_size = element_size;
    array->content = NULL;
    return 0;
}

int vector_free_content(vector_template_t *array)
{
    if (array->content == NULL)
        return -1;
    for (size_t i = 0; i < array->len; ++i)
        free(array->content[i]);
    free(array->content);
    array->content = NULL;
    array->len = 0;
    return 0;
}

int vector_free_content_with_function(vector_template_t *array,
    void (*free_func)(void *data))
{
    if (array->content == NULL)
        return -1;
    for (size_t i = 0; i < array->len; ++i)
        free_func(array->content[i]);
    free(array->content);
    array->content = NULL;
    array->len = 0;
    return 0;
}

int vector_apply_on_element(vector_template_t *array)
{
    if (array->content == NULL)
        return -1;
}