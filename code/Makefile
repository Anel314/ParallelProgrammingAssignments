CC=gcc
CFLAGS=-g -O3 -fstrict-aliasing -ftree-vectorize -fopenmp-simd \
       -march=native -mtune=native -mprefer-vector-width=256 \
       -fopt-info-vec-optimized -fopt-info-vec-missed 
LDLIBS=-lm


COMMON_OBJS = main.o timer.o

TARGETS = stream_base stream_opt1 stream_opt2 stream_opt3


all: $(TARGETS)

stream_base: $(COMMON_OBJS) timestep.o
	$(CC) $(CFLAGS) -o $@ $^ $(LDLIBS)

stream_opt1: $(COMMON_OBJS) timestep_opt1.o
	$(CC) $(CFLAGS) -o $@ $^ $(LDLIBS)

stream_opt2: $(COMMON_OBJS) timestep_opt2.o
	$(CC) $(CFLAGS) -o $@ $^ $(LDLIBS)

#Here stream_opt3 target is defined with additional flags for optimization 3
stream_opt3: $(COMMON_OBJS) timestep_opt3.o
	$(CC) $(CFLAGS) -fno-math-errno -fno-trapping-math -o $@ $^ $(LDLIBS)


%.o: %.c
	$(CC) $(CFLAGS) -c -o $@ $<


#I added the flags here as well for optimization 3 because of math functions used in the code
timestep_opt3.o: timestep_opt3.c
	$(CC) $(CFLAGS) -fno-math-errno -fno-trapping-math -c -o $@ $<

clean:
	rm -f $(TARGETS) *.o