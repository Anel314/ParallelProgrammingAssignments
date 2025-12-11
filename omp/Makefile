ifeq ($(OFFLOAD),1)
    OFFLOAD_FLAGS := -foffload=nvptx-none -foffload=-lm
else
    OFFLOAD_FLAGS :=
endif

CFLAGS := -pthread -g -O3 -std=gnu99 -fstrict-aliasing \
          -fopenmp -fno-lto -fopt-info-omp $(OFFLOAD_FLAGS)

default: all
all: StreamTriad StreamTriad_par1 StreamTriad_par2

%.o: %.c
	$(CC) $(CFLAGS) -c $<

StreamTriad: StreamTriad.o timer.o
	$(CC) $(CFLAGS) $^ -o $@

StreamTriad_par1: StreamTriad_par1.o timer.o
	$(CC) $(CFLAGS) $^ -o $@

StreamTriad_par2: StreamTriad_par2.o timer.o
	$(CC) $(CFLAGS) $^ -o $@

clean:
	rm -f *.o StreamTriad StreamTriad_par1 StreamTriad_par2
