#ifndef YAYEET
#define YAYEET
/**
 * @file custom_malloc.c
 * @brief Custom implementation of memory allocation functions.
 *
 * This file contains a custom implementation of memory allocation functions
 * similar to malloc and free. It uses a linked list of memory blocks and
 * provides thread-safe allocation using a global mutex.
 */

#include <stdio.h>
#include <time.h>
#include <unistd.h>
#include <pthread.h>
/** Alignment for memory blocks */
typedef char ALIGN[16];

/**
 * @struct header
 * @brief Memory block header structure
 *
 * This union represents the header of each memory block. It contains
 * information about the block size, whether it's free, and a pointer
 * to the next block in the linked list.
 */
union header {
	struct {
		size_t size;
		unsigned is_free;
		union header *next;
	} s;
	ALIGN stub;
};
typedef  union header header_t;

/**
 * @brief Finds a free block of sufficient size
 *
 * @param size The required size of the block
 * @return header_t* Pointer to a suitable free block, or NULL if none found
 */
header_t *get_free_block(size_t size);

/**
 * @brief Allocates memory of given size
 *
 * This function attempts to find a free block of sufficient size. If none
 * is found, it allocates a new block from the heap. It ensures thread-safety
 * using a global mutex.
 *
 * @param size The size of memory to allocate
 * @return void* Pointer to the allocated memory, or NULL if allocation fails
 */
void *rent_free(size_t size);

void yeet(void *block);

#endif
