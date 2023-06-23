## C Vector Library

The `vector` library provides functions for managing dynamic arrays (vectors) in C. It allows you to resize the array, add elements to the back, remove elements, initialize the array, and free the array's content.

### Data Structures

The library defines the following data structure:

#### `vector_template_t`

```c
typedef struct {
    size_t len;
    size_t element_size;
    void **content;
} vector_template_t;
```

- `len`: The current length of the array.
- `element_size`: The size of each element in the array.
- `content`: An array of pointers to elements.

### Functions

The library provides the following functions:

#### `int vector_resize(vector_template_t *array, size_t new_len)`

Resizes the dynamic array to the specified length (`new_len`). Returns -1 in case of error, else 0.

#### `int vector_push_back(vector_template_t *array, void *element)`

Adds an element pointer to the back of the array. Returns -1 in case of error, else 0.

#### `int vector_push_back_copy(vector_template_t *array, void *element)`

Adds a copy of data from `element` to the back of the array. This function duplicates the data using `malloc`. Returns -1 in case of error, else 0.

#### `void *vector_remove_by_pos(vector_template_t *array, size_t pos)`

Removes an element at the specified index (`pos`) from the array. Returns NULL in case of error, else the removed element.

#### `void *vector_remove_by_ptr(vector_template_t *array, void *ptr)`

Removes a pointer to an element from the array. Returns NULL in case of error, else the removed element.

#### `int vector_init(vector_template_t *array, size_t element_size)`

Initializes the dynamic array. Returns -1 in case of error, else 0.

#### `int vector_free_content(vector_template_t *array)`

Frees the content of the array, not the struct passed as a parameter. All the structures added via pointer are also freed. Returns -1 in case of error, else 0.

#### `int vector_free_content_with_function(vector_template_t *array, void (*free_func)(void *data))`

Frees the content of the array using a custom free function. All the structures added via pointer are also freed using the specified `free_func`. Returns -1 in case of error, else 0.

#### `int vector_free(vector_template_t *array)`

Frees the vector content but not the user-added content. It only frees the internal array. Returns -1 in case of error, else 0.

### Example Usage

Here's an example code snippet demonstrating the usage of the `vector` library:

```c
#include "vector/vector.h"
#include <stdio.h>

typedef struct {
    int value;
} __attribute__((packed)) MyStruct;

// Define the MyStruct vector struct using the vector_struct macro
typedef vector_struct(MyStruct) MyStructVector;

int main() {
    MyStructVector vector;
    vector_init(vectorize(&vector), sizeof(MyStruct));

    MyStruct element;
    element.value = 42;

    vector_push_back(vectorize(&vector), &element);

    vector_free(vectorize(&vector));

    return 0;
}
```

This example demonstrates how to use the `vector` library. It initializes a vector of `MyStruct` elements, adds an element to the back of the vector, and then frees the vector's content.

### Advanced examples

Here's an example code snippet demonstrating the usage of the advanced functions `vector_remove_by_ptr`, 
`vector_save_content`, and `vector_load_content`:

```c
#include "vector/vector.h"

// ...

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

int main()
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

    // ...

    MyStructVector vector2;

    vector_init(vectorize(&vector2), sizeof(MyStruct));
    // Load vector content from the file
    file = fopen("test_vector.bin", "rb");
    int load_result = vector_load_content(vectorize(&vector2), file, &load_func);
    fclose(file);

    // ...

    return 0;
}
```

This example demonstrates how to use the `vector_remove_by_ptr` function to remove an element by its pointer, `vector_save_content` to save the vector's content to a file, and `vector_load_content` to load the vector's content from a file.