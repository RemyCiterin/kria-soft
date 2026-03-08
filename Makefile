CFLAGS = -I src -O3 -lm -Wno-unused-result

all:
	gcc src/*.c -o build/main $(CFLAGS)


# install the kernel modules to interact with the FPGA via DMA
insmod:
	sudo insmod udmabuf/u-dma-buf.ko udmabuf0=1048576

clean:
	rm -f main
