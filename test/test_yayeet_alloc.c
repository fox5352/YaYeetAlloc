#include <stdio.h>
#include <assert.h>
#include <stdlib.h>

#include "yayeet_alloc.h"

void test_allocation_and_deallocation(){
    // testing normal memory allocation
    void *pt1_a = malloc(100);
    assert(pt1_a != NULL);

    void *pt2_a = malloc(200);
    assert(pt2_a != NULL);

    free(pt1_a);
    free(pt2_a);

    // try to allocate again to see if the memory is reused
    void *ptr3_a = malloc(100);
    assert(ptr3_a != NULL);
    assert(ptr3_a == pt1_a || ptr3_a == pt2_a);

    free(ptr3_a);

    printf("control unit passed\n");

    // testing rent_free memory allocation

    void *ptr1_b = rent_free(100);
    assert(ptr1_b != NULL);

    void *ptr2_b = rent_free(200);
    assert(ptr2_b != NULL);

    yeet(ptr1_b);
    yeet(ptr2_b);

    void *ptr3_b = rent_free(100);
    assert(ptr3_b != NULL);
    assert(ptr3_b == ptr1_b || ptr3_b == ptr2_b);

    yeet(ptr3_b);

    printf("YaYeetAlloc unit passed\n");
}

void test_program_break() {
    void *initial_break = sbrk(0);

    void *ptr = rent_free(100000);
    assert(ptr != NULL);

    void *new_break = sbrk(0);
    assert(new_break > initial_break);

    yeet(ptr);

    void *final_break = sbrk(0);
    assert(final_break == initial_break);

    printf("Program break unit passed\n");
}

void* thread_func(void *arg) {
    for (int i = 0; i < 1000; i++) {
        void *ptr = rent_free(100);
        yeet(ptr);
    }
    return NULL;
}

void test_thread_safety() {
    pthread_t threads[10];

    for (int i = 0; i < 10; i++) {
        pthread_create(&threads[i], NULL, thread_func, NULL);
    }

    for (int i = 0; i < 10; i++) {
        pthread_join(threads[i], NULL);
    }

    printf("Thread safety unit passed\n");
}

void test_edge_cases() {
    void *ptr = rent_free(0);
    assert(ptr == NULL);

    ptr = rent_free((size_t)-1);
    assert(ptr == NULL);

    yeet(NULL);  // Should not crash
}

int main() {
    test_allocation_and_deallocation();
    test_program_break();
    test_thread_safety();
    test_edge_cases();

    printf("All tests passed!\n");
    return 0;
}
