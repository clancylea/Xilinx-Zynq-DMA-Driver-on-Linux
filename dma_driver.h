/**
 *  dma_driver.h - user space dma driver communicating with the aes hardware.
 *
 *  Author: Hsiang-Ju Lai <happyx94@gmail.com>
 */
#ifndef _DMA_DRIVER_H
#define _DMA_DRIVER_H


#ifndef u32
  #define u32 unsigned int
#endif

#ifndef u8
  #define u8 unsigned char
#endif

#define SUCCESS 0
#define FAILURE (-1)

#define RSV_BUF_LEN         (1024 * 1024)
#define MAX_SRC_LEN         (RSV_BUF_LEN / 2)
#define MAX_DEST_LEN        (RSV_BUF_LEN / 2)

extern int mem_fd;
extern int polling_interval;

/* -------------------- DMA Functions -------------------- */

/**
 *  Initialize the user-space dma driver. Must be called
 *  before any functions in this header.
 *
 *  Pre-condiction:
 *    /dev/mem and /dev/rsvmem can be opened.
 *
 *  Post-condition:
 *    /dev/mem is open and mem_fd is set properly.
 *    psrc points to the default source buffer for DMA.
 *    pdest points to the destination buffer for DMA.
 *
 *  Return: SUCCESS or FAILURE
 */
extern int dma_init();

/**
 *  Reclaim the resouce used by the DMA driver.
 *
 *  Post-condition:
 *    DMA driver goes back to the uninitialized state.
 */
extern void dma_clean_up();

/**
 *  Reset the DMA hardware.
 */
extern int dma_reset();

/**
 *  Start the DMA transfer with len bytes of data at psrc.
 *  The destination is set to pdest.
 *  Note that this function does NOT sync.
 *
 *  Paramenters:
 *    len -> the number of bytes to transfer.
 *
 *  Post-condition:
 *    DMA transfer is started.
 *
 *  Return: SUCCESS or FAILURE
 */
extern int dma_start(u32 len);

/**
 *  Sync the process with the DMA transfer.
 *
 *  Return:
 *    SUCCESS when the DMA transfer is completed.
 *    FAILURE if the DMA doesn't respond in 1 ms.
 */
extern int dma_sync();

/**
 *  Return immedieately:
 *    SUCCESS if the DMA is idle.
 *    FAILURE if the DMA is running.
 */
extern int dma_quick_poll();


/* -------------------- AES Functions ------------------- */

/**
 *  Set the key for the AES hardware.
 *
 *  Parameters:
 *    *pkey -> pointer to the key (expect 16 bytes)
 *
 *  Return: SUCCESS or FAILURE
 */
extern int aes_set_key(void *pkey);

/**
 *  Set the initialization vector (IV) of the AES hardware.
 *
 *  Parameters:
 *    *pkey -> pointer to the key (expect 16 bytes)
 *
 *  Return: SUCCESS or FAILURE
 */
extern int aes_set_iv(void *piv);


/* ---------------------- Utilities ---------------------- */
#define MEM_DUMP_MAX_BYTES  256
/**
 *  Print the buffer.
 */
extern void memdump(void* buf, int byte_count);

#endif
