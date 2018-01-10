/**
 * UW CSE 351 Spring 2016 Lab 5
 *
 * Extra credit: implementing mm_realloc
 *
 * This requires mm_malloc and mm_free to be working correctly, so
 * don't start on this until you finish mm.c.
 */
#include <string.h>
#include "mm.c"

// Extra credit.
void* mm_realloc(void* ptr, size_t size) {
    size_t oldSize;
    BlockInfo *oldBlock; 

    if (ptr == NULL)
      return mm_malloc(size);
    if (size == 0) {
      mm_free(ptr); 
      return NULL;
    }  
    oldBlock = (BlockInfo*) UNSCALED_POINTER_SUB(ptr, WORD_SIZE);
    oldSize = SIZE(oldBlock->sizeAndTags) - WORD_SIZE;
    ptr = mm_malloc(size); 
    memcpy(ptr, UNSCALED_POINTER_ADD(oldBlock, WORD_SIZE), (size <= oldSize) ? size : oldSize);
    mm_free(UNSCALED_POINTER_ADD(oldBlock, WORD_SIZE));
    return ptr;
}
