/*
** EPITECH PROJECT, 2023
** zappy_server
** File description:
** vector.c
*/

#include <criterion/criterion.h>

#include "vector/vector.h"

typedef struct {
    int value;
} __attribute__((packed)) MyStruct;

// Define the MyStruct vector struct using the vector_struct macro
typedef vector_struct(MyStruct) MyStructVector;

// Test vector initialization
Test(vector_init, initialization)
{
    MyStructVector vector;
    vector_init(vectorize(&vector), sizeof(MyStruct));
    cr_assert_eq(vectorize(&vector)->len, 0);
    cr_assert_eq(vectorize(&vector)->element_size, sizeof(MyStruct));
    cr_assert(vector.content == NULL);
    vector_free(vectorize(&vector));
}

// Test vector push_back
Test(vector_push_back, add_element)
{
    MyStructVector vector;
    vector_init(vectorize(&vector), sizeof(MyStruct));

    MyStruct element;
    element.value = 42;

    vector_push_back(vectorize(&vector), &element);

    cr_assert_eq(vectorize(&vector)->len, 1);
    cr_assert_eq(vector.content[0]->value, element.value);

    vector_free(vectorize(&vector));
}

// Test vector resize
Test(vector_resize, resize_array)
{
    MyStructVector vector;
    vector_init(vectorize(&vector), sizeof(MyStruct));

    MyStruct element;
    element.value = 42;

    vector_push_back(vectorize(&vector), &element);

    size_t new_len = 5;
    vector_resize(vectorize(&vector), new_len);

    cr_assert_eq(vectorize(&vector)->len, new_len);

    vector_free(vectorize(&vector));
}

// Test vector remove_by_pos
Test(vector_remove_by_pos, remove_element_by_position)
{
    MyStructVector vector;
    vector_init(vectorize(&vector), sizeof(MyStruct));

    MyStruct element1;
    element1.value = 42;

    MyStruct element2;
    element2.value = 24;

    vector_push_back(vectorize(&vector), &element1);
    vector_push_back(vectorize(&vector), &element2);

    size_t pos = 0;
    MyStruct *removed_element = vector_remove_by_pos(vectorize(&vector), pos);

    cr_assert_eq(vectorize(&vector)->len, 1);
    cr_assert_eq(vector.content[0]->value, element2.value);
    cr_assert_eq(removed_element->value, element1.value);

    vector_free(vectorize(&vector));
}

// Test vector remove_by_ptr
Test(vector_remove_by_ptr, remove_element_by_pointer)
{
    MyStructVector vector;
    vector_init(vectorize(&vector), sizeof(MyStruct));

    MyStruct element1;
    element1.value = 42;

    MyStruct element2;
    element2.value = 24;

    vector_push_back(vectorize(&vector), &element1);
    vector_push_back(vectorize(&vector), &element2);

    void *ptr = &element1;
    MyStruct *removed_element = vector_remove_by_ptr(vectorize(&vector), ptr);

    cr_assert_eq(vectorize(&vector)->len, 1);
    cr_assert_eq(vector.content[0]->value, element2.value);
    cr_assert_eq(removed_element->value, element1.value);

    vector_free(vectorize(&vector));
}

// Test vector free_content
Test(vector_free_content, free_content)
{
    MyStructVector vector;
    vector_init(vectorize(&vector), sizeof(MyStruct));

    MyStruct element1;
    element1.value = 42;

    MyStruct element2;
    element2.value = 24;

    vector_push_back(vectorize(&vector), &element1);
    vector_push_back(vectorize(&vector), &element2);



    vector_free(vectorize(&vector));
    cr_assert_eq(vectorize(&vector)->len, 0);
    cr_assert_eq(vectorize(&vector)->element_size, sizeof(MyStruct));
    cr_assert(vector.content == NULL);
}

// Custom function to free MyStruct elements
void freeMyStruct(void *data)
{
    MyStruct *element = (MyStruct *)data;
    free(element);
}

// Test vector free_content_with_function
Test(vector_free_content_with_function, free_content_with_function)
{
    MyStructVector vector;
    vector_init(vectorize(&vector), sizeof(MyStruct));

    MyStruct *element1 = malloc(sizeof(MyStruct));
    element1->value = 42;

    MyStruct *element2 = malloc(sizeof(MyStruct));
    element2->value = 24;

    vector_push_back(vectorize(&vector), element1);
    vector_push_back(vectorize(&vector), element2);



    vector_free_content_with_function(vectorize(&vector), freeMyStruct);

    cr_assert_eq(vectorize(&vector)->len, 0);

    vector_free(vectorize(&vector));
}

int save_func(void *data, FILE *file)
{
    return s_fwrite(data, sizeof(MyStruct), file);
}

void *load_func(FILE *file)
{
    MyStruct *element = malloc(sizeof(MyStruct));
    if (s_fread(element, sizeof(MyStruct), file)) {
        free(element);
        return NULL;
    }
    return element;
}

// Test vector save_content and vector_load_content
Test(vector_save_and_load_content, save_and_load_content)
{
    MyStructVector vector;
    vector_init(vectorize(&vector), sizeof(MyStruct));

    MyStruct element1;
    element1.value = 42;

    MyStruct element2;
    element2.value = 24;

    vector_push_back(vectorize(&vector), &element1);
    vector_push_back(vectorize(&vector), &element2);

    // Save vector content to a file
    FILE *file = fopen("test_vector.bin", "wb");
    int save_result = vector_save_content(vectorize(&vector), file, &save_func);
    fclose(file);

    cr_assert_eq(save_result, 0);

    vector_free(vectorize(&vector));

    MyStructVector vector2;

    vector_init(vectorize(&vector2), sizeof(MyStruct));
    // Load vector content from the file
    file = fopen("test_vector.bin", "rb");
    int load_result = vector_load_content(vectorize(&vector2), file, &load_func);
    fclose(file);

    cr_assert_eq(load_result, 0);
    cr_assert_eq(vectorize(&vector2)->len, 2);
    cr_assert_eq(vector2.content[0]->value, element1.value);
    cr_assert_eq(vector2.content[1]->value, element2.value);

    vector_free_content(vectorize(&vector2));

    // Cleanup the file
    remove("test_vector.bin");
}
