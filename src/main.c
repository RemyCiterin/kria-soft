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
  volatile void* ctrl_buf = init_ctrl_buffer(&ctrl_size);

  printf("buf: %p size: %lx\n", ctrl_buf, ctrl_size);

  size_t dma_size;
  intptr_t dma_phys;
  bool cachable = true;
  void* dma_buf = init_dma_buffer(&dma_size, &dma_phys, cachable);

  printf("buf: %p phys: %p size: %lx\n", dma_buf, (void*)dma_phys, dma_size);

  volatile intptr_t* ctrl_buf_phys = ctrl_buf;
  volatile uint32_t* ctrl_buf_size = ctrl_buf+8;
  volatile uint8_t* ctrl_status = ctrl_buf+12;

  *ctrl_buf_phys = dma_phys;
  *ctrl_buf_size = 0x1000;
  *ctrl_status = 1;

  while (*ctrl_status != 0) {
    printf("status: %d\n", *ctrl_status);
  }

  for (int i=0; i < 0x1000/8; i++) {
    printf("dma[%d] = %lx\n", i, ((volatile uint64_t*)dma_buf)[i]);
  }

  deinit_ctrl_buffer();
  deinit_dma_buffer();

  return 0;
}
