#include "malloc.h"
#include "sram.h"
#include <stdint.h>
#include <stdio.h>

// 64k align
static uint8_t mem1base[64] __attribute__((aligned(64)));
static uint8_t mem2base[64] __attribute__((section(".sram_base_addr"), aligned(64)));
static MT_TYPE mem1mapbase[MEM1_ALLOC_TABLE_SIZE];
static MT_TYPE mem2mapbase[MEM2_ALLOC_TABLE_SIZE] __attribute__((section(".sram_base_addr_t")));

const uint32_t memtblsize[SRAMBANK] = {MEM1_ALLOC_TABLE_SIZE, MEM2_ALLOC_TABLE_SIZE};  // alloc table size
const uint32_t memblksize[SRAMBANK] = {MEM1_BLOCK_SIZE, MEM2_BLOCK_SIZE};              // block size
const uint32_t memsize[SRAMBANK]    = {MEM1_MAX_SIZE, MEM2_MAX_SIZE};                  // total memory size


struct _m_mallco_dev mallco_dev = {
    my_mem_init,     // Memory initialization
    my_mem_perused,  // Memory usage rate
    mem1base,
    mem2base,  // Memory pool
    mem1mapbase,
    mem2mapbase,  // Memory management status table
    0,
    0,  // Memory management not ready
};

/**
 * @description: memory management initialization function (internal/external call)
 * @param memx, memory bank
 * @return None
 */
void my_mem_init(uint8_t memx)
{
    uint8_t mttsize = sizeof(MT_TYPE);
    my_mem_set(mallco_dev.memmap[memx], 0, memtblsize[memx] * mttsize);
    mallco_dev.memrdy[memx] = 1;
}

/**
 * @description: Get memory usage rate (internal/external call)
 * @param memx, memory bank
 * @return None
 */
uint16_t my_mem_perused(uint8_t memx)
{
    uint32_t used = 0;
    uint32_t i;

    for(i = 0; i < memtblsize[memx]; i++)
    {
        if(mallco_dev.memmap[memx][i])
            used++;
    }
    return (used * 1000) / (memtblsize[memx]);
}

/**
 * @description: set memory
 * @param *s memory first address
 * @param c, memory value
 * @param count, memory length
 * @return
 */
void my_mem_set(void *s, uint8_t c, uint32_t count)
{
    uint8_t *xs = s;
    while(count--) *xs++ = c;
}

/**
 * @description: memory copy function
 * @param *des, memory destination address
 * @param *src, memory source address
 * @param n, memory length
 * @return None
 */
void my_mem_copy(void *des, void *src, uint32_t n)
{
    uint8_t *xdes = des;
    uint8_t *xsrc = src;
    while(n--) *xdes++ = *xsrc++;
}

/**
 * @brief       Frees memory (internal call)
 * @param       memx   : Memory bank
 * @param       offset : Memory address offset
 * @retval      Release result
 *   @arg       0, Success;
 *   @arg       1, Failure;
 *   @arg       2, Out of range (failure);
 */
static uint8_t my_mem_free(uint8_t memx, uint32_t offset)
{
    int i;

    if(!mallco_dev.memrdy[memx]) // Not initialized, perform initialization first
    {
        mallco_dev.init(memx);
        return 1; // Not initialized
    }

    if(offset < memsize[memx]) // Offset within memory pool
    {
        int index = offset / memblksize[memx];      // Block number of the offset
        int nmemb = mallco_dev.memmap[memx][index]; // Number of memory blocks

        for(i = 0; i < nmemb; i++) // Clear memory blocks
        {
            mallco_dev.memmap[memx][index + i] = 0;
        }

        return 0;
    } else
    {
        return 2; // Out of range
    }
}

/**
 * @description: free memory
 * @param memx, memory bank
 * @param *ptr, memory head address
 * @return None
 */
void myfree(uint8_t memx, void *ptr)
{
    uint32_t offset;
    if(ptr == NULL)
        return;
    offset = (uint32_t)ptr - (uint32_t)mallco_dev.membase[memx];
    my_mem_free(memx, offset);
}

/**
 * @description: internal memory allocation
 * @param {uint8_t} memx, memory bank
 * @param {uint32_t} size, allocated memory size
 * @return
 *   @arg       0~0xFFFFFFFF: effective memory address offset;
 *   @arg       1, 0xFFFFFFFF: uneffective memory address offset;
 */
static uint32_t my_mem_malloc(uint8_t memx, uint32_t size)
{
    signed long offset = 0;
    uint32_t    nmemb;      // needed memory blocks
    uint32_t    cmemb = 0;  // current memory block
    uint32_t    i;

    if(!mallco_dev.memrdy[memx])
    {
        mallco_dev.init(memx);
    }

    if(size == 0)
    {
        return 0xFFFFFFFF;
    }

    nmemb = size / memblksize[memx];
    if(size % memblksize[memx])
    {
        nmemb++;
    }

    for(offset = memtblsize[memx] - 1; offset >= 0; offset--)
    {
        if(!mallco_dev.memmap[memx][offset])
        {

            cmemb++;  // add continuous memory
        } else
        {
            cmemb == 0;
        }
        if(cmemb == nmemb)  // find continus memory
        {
            for(i = 0; i < nmemb; i++)  // mark non-empty memory block
            {
                mallco_dev.memmap[memx][offset + i] = nmemb;
            }
            return (offset * memblksize[memx]);
        }
    }
    return 0xFFFFFFFF;
}

/**
 * @description: allocate memory
 * @param memx, memory bank
 * @param size, memory length
 * @return None
 */
void *mymalloc(uint8_t memx, uint32_t size)
{
    uint32_t offset;
    offset = my_mem_malloc(memx, size);
    if(offset == 0XFFFFFFFF)
    {
        return NULL;
    } else
    {
        return (void *)((uint32_t)mallco_dev.membase[memx] + offset);
    }
}

/**
 * @description: reallocate memory
 * @param memx, memory bank
 * @param *ptr, old memory head address
 * @param size, new memory length
 * @return None
 */
void *myrealloc(uint8_t memx, void *ptr, uint32_t size)
{
    uint32_t offset;
    offset = my_mem_malloc(memx, size);
    if(offset == 0XFFFFFFFF)
    {
        return NULL;
    } else
    {
        my_mem_copy((void *)((uint32_t)mallco_dev.membase[memx] + offset), ptr, size);
        myfree(memx, ptr);
        return (void *)((uint32_t)mallco_dev.membase[memx] + offset);
    }
}






