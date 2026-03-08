#ifndef FPGA_H
#define FPGA_H

// Initialize the control buffer (FPGA is in slave mode)
void* init_ctrl_buffer(size_t* size);

// Initialize the DMA buffer (shared memory with the FPGA)
void* init_dma_buffer(size_t* size, intptr_t* phys, bool cachable);


void deinit_ctrl_buffer();

void deinit_dma_buffer();

#endif
