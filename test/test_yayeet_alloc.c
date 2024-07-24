#include <stdio.h>
#include <assert.h>
#include <stdlib.h>

#include "yayeet_alloc.h"

int main() {
    // testing normal memory allocation
    int *ptr1 = NULL;
    ptr1 = malloc(125);
    assert(ptr1 != NULL && "Memory allocation failed on stock malloc");
    *ptr1 = 125;
    assert(*ptr1 == 125);

    free(ptr1);

    // testing rent_free memory allocation
   int *ptr2 = NULL;
    ptr2 = rent_free(125);
    assert(ptr2 != NULL && "Memory allocation failed on stock rent_free");
    *ptr2 = 125;
    assert(*ptr2 == 125);


    // TODO: implement free testing for ya_yeet_alloc
}
