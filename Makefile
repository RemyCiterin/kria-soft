CFLAGS = -I src -O3 -lm -Wno-unused-result

all:
	gcc src/*.c -o build/main $(CFLAGS)


# install the kernel modules to interact with the FPGA via DMA
insmod:
	sudo insmod udmabuf/u-dma-buf.ko udmabuf0=1048576

# Reprogram the fpga with the default bitstream
reset_fpga:
	sudo fpgautil -b /lib/firmware/xilinx/k26-starter-kits/k26_starter_kits.bit.bin

clean:
	rm -f main
