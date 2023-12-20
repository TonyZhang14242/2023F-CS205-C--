#include "mmpool.h"
#include <stdio.h>

/* Functions for tests */
/* ==BEGIN== */
void prt_mmpool_details(mmpool_t *pool)
{
    if (pool == NULL)
        return;
    puts("===MEMORY POOL DETAILS===");
    printf("POOL ADDRESS: %p\n", pool);
    printf("POOL SIZE (FOR EACH): %lu\n", MMPOOL_SIZE);
    printf("MAX ALLOCATION SIZE: %lu\n", MMPOOL_MAX_ALLOC);
    printf("MAX FAILED TIMES: %d\n", MMPOOL_MAX_FAILED);
    printf("CURRENT ACTIVE POOL ADDRESS: %p\n", pool->current);
    puts("\nSUB POOL DETAILS:");

    size_t count = 0;
    mmpool_t *cur = pool;
    while (cur != NULL)
    {
        printf("\t-> Sub pool #%lu, address=%p, free_space=%lu (bytes), failed=%lu\n",
               ++count, cur, (size_t)(cur->data.end - cur->data.last), cur->data.failed);
        cur = cur->data.next;
    }
    printf("SUB POOL COUNT: %lu\n", count);

    puts("\nLARGE BLOCK DETAILS: ");
    count = 0;
    mmpool_large_t *large = pool->large;
    while (large != NULL)
    {
        printf("\t-> Large block #%lu, address=%p\n", ++count, large);
        large = large->next;
    }
    printf("LARGE BLOCK COUNT: %lu\n", count);
    puts("===MEMORY POOL DETAILS END===\n");
}
/* ==END== */

mmpool_t *mmpool_create()
{
    mmpool_t *p = NULL;

    p = (mmpool_t *)malloc(sizeof(mmpool_t) + MMPOOL_SIZE);
    if (p != NULL)
    {
        p->data.last = (uint8_t *)p + sizeof(mmpool_t);
        p->data.end = p->data.last + MMPOOL_SIZE;
        p->data.next = NULL;
        p->data.failed = 0;

        p->current = p;
        p->large = NULL;
    }

    return p;
}

/* WRITE YOUR CODE HERE */
/* SUBMIT THIS PART */
/* ==BEGIN== */
void *mmpool_alloc(mmpool_t *pool, size_t size)
{
    // TODO
    //printf("%lu\n", size);
    if (size > MMPOOL_MAX_ALLOC) // alloc large
    {
        mmpool_large_t *large_block = mmpool_alloc_large(size);
        mmpool_large_t *tmp = pool->large;
        if (tmp == NULL)
        {
            pool->large = large_block;
        }
        else
        {
            while (tmp->next != NULL)
            {
                tmp = tmp->next;
            }
            tmp->next = large_block;
        }
        return large_block->alloc;
    }
    else // alloc normal
    {
        mmpool_t *tmp = pool->current;
        int no_free = 1;
        while (tmp->data.next != NULL)
        {
            size_t free_left = (size_t)(tmp->data.end - tmp->data.last);
            //printf("%lu  %lu\n", free_left, size);
            if (free_left < size)
            {
                tmp->data.failed++;
                if (tmp->data.failed > MMPOOL_MAX_FAILED)
                {
                    pool->current = tmp->data.next;
                }
            }
            else
            {
                //tmp->data.last = malloc(size);
                uint8_t* allocated_mem = tmp->data.last;
                tmp->data.last = tmp->data.last + size;
                no_free = 0;
                return allocated_mem;
            }
            tmp = tmp->data.next;
        }
        size_t free_left = (size_t)(tmp->data.end - tmp->data.last);
        //printf("%lu  %lu\n", free_left, size);
        if (free_left < size)
        {
            tmp->data.failed++;
            if (tmp->data.failed > MMPOOL_MAX_FAILED)
            {
                pool->current = tmp->data.next;
            }
        }
        else
        {
            //tmp->data.last = (uint8_t*)malloc(size);
            uint8_t* allocated_mem = tmp->data.last;
            tmp->data.last = tmp->data.last + size;
            //printf("last: %p %p\n", tmp->data.end, tmp->data.last);
            no_free = 0;
            return allocated_mem;
        }
        if (no_free)
        {
            mmpool_t *new_pool = mmpool_create();
            //new_pool->data.last = malloc(size);
            uint8_t* allocated_mem = new_pool->data.last;
            new_pool->data.last = new_pool->data.last + size;
            tmp->data.next = new_pool;
            return allocated_mem;
        }
    }
    return NULL;
}

mmpool_large_t *mmpool_alloc_large(size_t size)
{
    mmpool_large_t *p = (mmpool_large_t *)malloc(sizeof(mmpool_large_t));
    p->next = NULL;
    p->alloc = malloc(size);
    return p;
}

void mmpool_destroy(mmpool_t *pool)
{
    // Free large blocks
    while (pool->large != NULL) {
        mmpool_large_t* next = pool->large->next;
        free(pool->large->alloc);
        free(pool->large);
        pool->large = next;
    }
    // free all data in pool
    mmpool_t *current = pool;
    while (current != NULL)
    {
        mmpool_t *next = current->data.next;
        free(current);
        current = next;
    }
}

void mmpool_free_large(mmpool_t *pool, void *p)
{
    // TODO
    //printf("%p\n", p);
    mmpool_large_t *tmp = pool->large;
    //printf("%p\n", tmp);
    if (tmp->alloc == p)
    {
        pool->large = tmp->next;
        free(tmp->alloc);
        free(tmp);
    }
    else
    {
        while (tmp->next->alloc != p)
        {
            //printf("%p %p\n", tmp, tmp->alloc);
            tmp = tmp->next;
        }
        mmpool_large_t* to_link = tmp->next->next;
        free(tmp->next->alloc);
        free(tmp->next);
        tmp->next = to_link;
    }
}

void mmpool_reset(mmpool_t *pool)
{
    mmpool_t* tmp = pool;
    pool->current = pool;
    while (tmp!=NULL)
    {
        tmp->data.last = (uint8_t *)tmp + sizeof(mmpool_t);
        tmp->data.failed = 0;
        tmp = tmp->data.next;
    }
    
    // Free large blocks
    while (pool->large != NULL) {
        mmpool_large_t* next = pool->large->next;
        free(pool->large->alloc);
        free(pool->large);
        pool->large = next;
    }
}