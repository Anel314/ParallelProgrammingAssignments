default: all
all: StreamTriad StreamTriad_par1 StreamTriad_par2 StreamTriad_par3 StreamTriad_par4 \
    StreamTriad_kern1 StreamTriad_kern2 StreamTriad_kern3

# GPU offloading only when OFFLOAD=1
ifeq ($(OFFLOAD),1)
    ACC_FLAGS := -fopenacc -foffload=nvptx-none -foffload=-lm
else
    ACC_FLAGS := -fopenacc
endif

CFLAGS := -g -O3 -std=gnu99 -fstrict-aliasing \
          -fno-lto -fopt-info-omp $(ACC_FLAGS)

%.o: %.c
	$(CC) $(CFLAGS) -c $<

StreamTriad: StreamTriad.o timer.o
	$(CC) $(CFLAGS) $^ -o $@

StreamTriad_par1: StreamTriad_par1.o timer.o
	$(CC) $(CFLAGS) $^ -o $@

StreamTriad_par2: StreamTriad_par2.o timer.o
	$(CC) $(CFLAGS) $^ -o $@

StreamTriad_par3: StreamTriad_par3.o timer.o
	$(CC) $(CFLAGS) $^ -o $@

StreamTriad_par4: StreamTriad_par4.o timer.o
	$(CC) $(CFLAGS) $^ -o $@

StreamTriad_kern1: StreamTriad_kern1.o timer.o
	$(CC) $(CFLAGS) $^ -o $@

StreamTriad_kern2: StreamTriad_kern2.o timer.o
	$(CC) $(CFLAGS) $^ -o $@

StreamTriad_kern3: StreamTriad_kern3.o timer.o
	$(CC) $(CFLAGS) $^ -o $@

clean:
	rm -f StreamTriad StreamTriad.o
	rm -f StreamTriad_par1 StreamTriad_par1.o
	rm -f StreamTriad_par2 StreamTriad_par2.o
	rm -f StreamTriad_par3 StreamTriad_par3.o
	rm -f StreamTriad_par4 StreamTriad_par4.o
	rm -f StreamTriad_kern1 StreamTriad_kern1.o
	rm -f StreamTriad_kern2 StreamTriad_kern2.o
	rm -f StreamTriad_kern3 StreamTriad_kern3.o
	rm -f timer.o

distclean: clean
	rm -f Makefile
