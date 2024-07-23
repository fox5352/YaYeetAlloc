#include "../include/yayeet_alloc.h"
#include <stdio.h>

/** Global mutex for thread-safe operations */
pthread_mutex_t global_lock;

/** Pointer to the first block in the list */
header_t *head;

/** Pointer to the last block in the list */
header_t *tail;

/**
 * @brief Finds a free block of sufficient size
 *
 * @param size The required size of the block
 * @return header_t* Pointer to a suitable free block, or NULL if none found
 */
header_t *get_free_block(size_t size) {
	header_t *curr = head;
	// while curr is valid
	while (curr) {
		// if current block is free and its size is enough, return it
		if (curr->s.is_free && curr->s.size >= size) return curr;

		// else move on next block in linked list
		curr = curr->s.next;
	}

	// return Null if there is no chain
	return NULL;
}

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
void *rent_free(size_t size) {
	// initialize vars
	size_t total_size;
	void *block;
	header_t *header;

	// return null if there is no size
	if(!size) return NULL;

	// lock the global mutex before accessing the shared data structure
	pthread_mutex_lock(&global_lock);

	// try to get a free'd block from linked list if possible
	header = get_free_block(size);
	if(header) {
		header->s.is_free = 0;
		pthread_mutex_unlock(&global_lock);

		// Return a pointer to the usable memory, which starts right after the header
		// The '+1' here moves the pointer past the header structure
		return (void *)(header + 1);
	}

	// if no free block is available, allocate a new block from the heap
	total_size = sizeof(header_t) + size;
	block = sbrk(total_size);

	// if check if sbrk failed to get new chuck on mem
	if (block == (void *) -1) {
		pthread_mutex_unlock(&global_lock);
		return NULL;
	}

	// initialize the header and add it to the linked list
	header = block;
	header->s.size = size;
	header->s.is_free = 0;
	header->s.next = NULL;

	// very clever bit of code here if there is no header it creates a new head
	// but If there's already a tail, update its 'next' to point to the new block
	// This effectively adds the new block to the end of the list
	if (!head) head = header;
	if (tail) tail->s.next = header;


	// Set the tail to the new block, as it's now the last in the list
	tail = header;
	pthread_mutex_unlock(&global_lock);

	// Return a pointer to the usable memory, which starts right after the header
	// The '+1' here moves the pointer past the header structure
	return (void *)(header + 1);
}
