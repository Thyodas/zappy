/*
** EPITECH PROJECT, 2023
** myteams
** File description:
** element.c
*/

#include "vector.h"

int vector_push_back(vector_template_t *array, void *element)
{
    if (vector_resize(array, array->len + 1))
        return -1;
    array->content[array->len - 1] = element;
    return 0;
}

int vector_push_back_copy(vector_template_t *array, void *element)
{
    if (vector_resize(array, array->len + 1))
        return -1;
    void *new_element = malloc(array->element_size);
    memcpy(new_element, element, array->element_size);
    array->content[array->len - 1] = new_element;
    return 0;
}

void *vector_remove_by_pos(vector_template_t *array, size_t pos)
{
    if (pos >= array->len)
        return NULL;
    void *removed = array->content[pos];
    memmove(array->content + pos, array->content + pos + 1,
        (array->len - pos - 1) * sizeof(void *));
    --array->len;
    return removed;
}

void *vector_remove_by_ptr(vector_template_t *array, void *ptr)
{
    size_t i = 0;
    if (array->len == 0)
        return NULL;
    for (; array->content[i] != ptr; ++i)
        if (i >= array->len)
            return NULL;
    return vector_remove_by_pos(array, i);
}
