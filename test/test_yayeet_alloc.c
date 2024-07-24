#include <stdio.h>
#include <assert.h>
#include <stdlib.h>

#include "../include/yayeet_alloc.h"

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


    void *ptr1_c = tribe_rent_free(4, 100);
    assert(ptr1_c != NULL);

    void *ptr2_c = tribe_rent_free(4, 200);
    assert(ptr2_c != NULL);

    yeet(ptr1_c);
    yeet(ptr2_c);

    void *ptr3_c = tribe_rent_free(4, 100);
    assert(ptr3_c != NULL);
    assert(ptr3_c == ptr1_c || ptr3_c == ptr2_c);

    yeet(ptr3_c);
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

    printf("Program break unit for rent_free passed\n");

    void *initial_break2 = sbrk(0);

    void *ptr2 = tribe_rent_free(4, 100000);
    assert(ptr2 != NULL);

    void *new_break2 = sbrk(0);
    assert(new_break2 > initial_break2);

    yeet(ptr2);

    void *final_break2 = sbrk(0);
    assert(final_break2 == initial_break2);

    printf("Program break unit for tribe_rent_free passed\n");
}

void* thread_func_rent_free(void *arg) {
    for (int i = 0; i < 1000; i++) {
        void *ptr = rent_free(100);
        yeet(ptr);
    }
    return NULL;
}

void* thread_func_tribe_rent_free(void * arg) {
    for (int i = 0; i < 1000; i++) {
        void *ptr = tribe_rent_free(4, 100);
        yeet(ptr);
    }
    return NULL;
}

void test_thread_safety() {
    pthread_t threads[10];

    for (int i = 0; i < 10; i++) {
        pthread_create(&threads[i], NULL, thread_func_rent_free, NULL);
    }

    for (int i = 0; i < 10; i++) {
        pthread_join(threads[i], NULL);
    }
    printf("Thread safety unit for rent_free passed\n");

    pthread_t threads2[10];

    for (int i = 0; i < 10; i++) {
        pthread_create(&threads2[i], NULL, thread_func_tribe_rent_free, NULL);
    }

    for (int i = 0; i < 10; i++) {
        pthread_join(threads2[i], NULL);
    }
    printf("Thread safety unit for tribe_rent_free passed\n");
}

void test_edge_cases() {
    void *ptr = rent_free(0);
    assert(ptr == NULL);

    ptr = rent_free((size_t)-1);
    assert(ptr == NULL);

    yeet(NULL);  // Should not crash

    printf("Edge cases for rent_free unit passed");

    void *ptr2 = tribe_rent_free(0, 0);
    assert(ptr2 == NULL);

    ptr2 = tribe_rent_free(4, (size_t)-1);
    assert(ptr2 == NULL);

    yeet(NULL);  // Should not crash
    printf("Edge cases for tribe_rent_free unit passed");
}

int main() {
    test_allocation_and_deallocation();
    test_program_break();
    test_thread_safety();
    test_edge_cases();

    printf("All tests passed!\n");
    return 0;
}
