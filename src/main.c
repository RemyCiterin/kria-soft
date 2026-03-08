#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
#include <fcntl.h>
#include <sys/mman.h>
#include "arm_neon.h"

#include "fpga.h"

int main() {

  size_t ctrl_size;
  void* ctrl_buf = init_ctrl_buffer(&ctrl_size);

  printf("buf: %p size: %lx\n", ctrl_buf, ctrl_size);

  deinit_ctrl_buffer();

  size_t dma_size;
  intptr_t dma_phys;
  bool cachable = true;
  void* dma_buf = init_dma_buffer(&dma_size, &dma_phys, cachable);

  printf("buf: %p phys: %p size: %lx\n", dma_buf, (void*)dma_phys, dma_size);

  deinit_dma_buffer();

  return 0;
}
