#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/mman.h>

#include "fpga.h"

// Control buffer size is 64K
#define CTRL_SIZE 0x10000
#define CTRL_PHYS 0x80000000

static int ctrl_fd = 0;
static int dma_fd = 0;

void* init_ctrl_buffer(size_t *size) {
  if (ctrl_fd) return NULL;
  if ((ctrl_fd = open("/dev/mem", O_RDWR)) < 0) return NULL;

  if (size) *size = CTRL_SIZE;
  return mmap(NULL, CTRL_SIZE, PROT_READ|PROT_WRITE, MAP_SHARED, ctrl_fd, CTRL_PHYS);
}

void deinit_ctrl_buffer() {
  close(ctrl_fd);
}

void* init_dma_buffer(size_t* size, intptr_t* phys, bool cachable) {
  if (dma_fd) return NULL;

  size_t dma_size;
  intptr_t dma_phys;

  int fd;
  unsigned char attr[1024];

  if ((fd  = open("/sys/class/u-dma-buf/udmabuf0/phys_addr", O_RDONLY)) != -1) {
    read(fd, attr, 1024);
    sscanf(attr, "%lx", &dma_phys);
    close(fd);
  } else return NULL;

  if ((fd  = open("/sys/class/u-dma-buf/udmabuf0/size", O_RDONLY)) != -1) {
    read(fd, attr, 1024);
    sscanf(attr, "%ld", &dma_size);
    close(fd);
  } else return NULL;

  if ((dma_fd = open("/dev/udmabuf0", O_RDWR | (cachable ? 0: O_SYNC))) < 0) return NULL;

  if (size) *size = dma_size;
  if (phys) *phys = dma_phys;
  return mmap(NULL, dma_size, PROT_READ|PROT_WRITE, MAP_SHARED, dma_fd, 0);
}

void deinit_dma_buffer() {
  close(dma_fd);
}
