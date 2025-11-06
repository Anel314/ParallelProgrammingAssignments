
-----

### Base Files (main.o & timer.o)

```
gcc -g -O3 -fstrict-aliasing -ftree-vectorize -fopenmp-simd -march=native -mtune=native -mprefer-vector-width=256 -fopt-info-vec-optimized -fopt-info-vec-missed -c -o main.o main.c
main.c:10:22: optimized: loop vectorized using 32 byte vectors
main.c:20:15: missed: statement clobbers memory: mymindt_6 = timestep (10000000, 9.800000000000000710542735760100185871124267578125e+0, 9.499999999999999555910790149937383830547332763671875e-1, &celltype, &H, &U, &V, &dx, &dy);
/usr/include/x86_64-linux-gnu/bits/stdio2.h:86:10: missed: statement clobbers memory: __printf_chk (2, "Minimum dt is %lf\n", mymindt_6);

gcc -g -O3 -fstrict-aliasing -ftree-vectorize -fopenmp-simd -march=native -mtune=native -mprefer-vector-width=256 -fopt-info-vec-optimized -fopt-info-vec-missed -c -o timer.o timer.c
timer.c:9:5: missed: statement clobbers memory: clock_gettime (1, tstart_cpu_2(D));
timer.c:14:5: missed: statement clobbers memory: clock_gettime (1, &tstop_cpu);
```

-----

### Building: stream_base

```
gcc -g -O3 -fstrict-aliasing -ftree-vectorize -fopenmp-simd -march=native -mtune=native -mprefer-vector-width=256 -fopt-info-vec-optimized -fopt-info-vec-missed -c -o timestep.o timestep.c
timestep.c:10:22: missed: couldn't vectorize loop
timestep.c:10:22: missed: not vectorized: control flow in loop.
timestep.c:12:25: missed: statement clobbers memory: wavespeed_46 = sqrt (_9);

gcc -g -O3 -fstrict-aliasing -ftree-vectorize -fopenmp-simd -march=native -mtune=native -mprefer-vector-width=256 -fopt-info-vec-optimized -fopt-info-vec-missed -o stream_base main.o timer.o timestep.o -lm
```

-----

### Building: stream_opt1

```
gcc -g -O3 -fstrict-aliasing -ftree-vectorize -fopenmp-simd -march=native -mtune=native -mprefer-vector-width=256 -fopt-info-vec-optimized -fopt-info-vec-missed -c -o timestep_opt1.o timestep_opt1.c
timestep_opt1.c:9:9: optimized: loop vectorized using 32 byte vectors
timestep_opt1.c:11:7: missed: couldn't vectorize loop
timestep_opt1.c:11:7: missed: not vectorized: control flow in loop.
timestep_opt1.c:9:9: optimized: loop vectorized using 32 byte vectors
timestep_opt1.c:12:22: missed: statement clobbers memory: wavespeed_58 = sqrt (_27);

gcc -g -O3 -fstrict-aliasing -ftree-vectorize -fopenmp-simd -march=native -mtune=native -mprefer-vector-width=256 -fopt-info-vec-optimized -fopt-info-vec-missed -o stream_opt1 main.o timer.o timestep_opt1.o -lm
```

-----

### Building: stream_opt2

```
gcc -g -O3 -fstrict-aliasing -ftree-vectorize -fopenmp-simd -march=native -mtune=native -mprefer-vector-width=256 -fopt-info-vec-optimized -fopt-info-vec-missed -c -o timestep_opt2.o timestep_opt2.c
timestep_opt2.c:9:9: optimized: loop vectorized using 32 byte vectors
timestep_opt2.c:11:7: missed: couldn't vectorize loop
timestep_opt2.c:11:7: missed: not vectorized: control flow in loop.
timestep_opt2.c:9:9: optimized: loop vectorized using 32 byte vectors
timestep_opt2.c:12:22: missed: statement clobbers memory: wavespeed_58 = sqrt (_27);

gcc -g -O3 -fstrict-aliasing -ftree-vectorize -fopenmp-simd -march=native -mtune=native -mprefer-vector-Wwidth=256 -fopt-info-vec-optimized -fopt-info-vec-missed -o stream_opt2 main.o timer.o timestep_opt2.o -lm
```

-----

### Building: stream_opt3 without flags

```
gcc -g -O3 -fstrict-aliasing -ftree-vectorize -fopenmp-simd -march=native -mtune=native -mprefer-vector-width=256 -fopt-info-vec-optimized -fopt-info-vec-missed -c -o timestep_opt3.o timestep_opt3.c
timestep_opt3.c:8:9: optimized: loop vectorized using 32 byte vectors
timestep_opt3.c:10:7: missed: couldn't vectorize loop
timestep_opt3.c:10:7: missed: not vectorized: control flow in loop.
timestep_opt3.c:8:9: optimized: loop vectorized using 32 byte vectors
timestep_opt3.c:11:29: missed: statement clobbers memory: wavespeed_58 = sqrt (_27);

gcc -fno-trapping-math -fno-math-errno -o stream_opt3 main.O timer.o timestep_opt3.o -lm
```

-----

### Building: stream_opt3 with flags

```
gcc ... -c -o timestep_opt3.o timestep_opt3.c
timestep_opt3.c:8:9: optimized: loop vectorized using 32 byte vectors
timestep_opt3.c:10:7: optimized: loop vectorized using 32 byte vectors
timestep_opt3.c:8:9: optimized: loop vectorized using 32 byte vectors
...
gcc ... -o stream_opt3 main.o timer.o timestep_opt3.o -lm

```
-----

### Likwid

So same as some weeks ago i still have an issue with the likwid tool as it does not support my proccessor.
I tried multiple ways of fixing it but it just wont support my cpu.
This is the output that i keep getting:

```bash
anel@AnelHP:~/GithubProjects/ParallelProgrammingAssignments/code$ likwid-perfctr -m -C S0:0-5 -g MEM_DP ./stream_base

--------------------------------------------------------------------------------
CPU name: AMD Ryzen 5 5500U with Radeon Graphics         
CPU type: nil
CPU clock: 2.10 GHz
ERROR - [/home/anel/likwid/src/perfmon.c:perfmon_init_maps:1364] No such file or directory.
Unsupported AMD Zen Processor
ERROR - [/home/anel/likwid/src/perfmon.c:perfmon_init_funcs:2115] No such file or directory.
Unsupported AMD K17 Processor
ERROR - [/home/anel/likwid/src/perfmon.c:perfmon_init:2352] Invalid argument.
Failed to initialize event and counter lists for (null)
anel@AnelHP:~/GithubProjects/ParallelProgrammingAssignments/code$ 
```

So instead of using this tool i did some research and found the `time` tool.
With the command `time file_name.o` i can measure the execution time for each stream.

```bash
anel@AnelHP:~/GithubProjects/ParallelProgrammingAssignments/code$ time ./stream_base 
Minimum dt is 0.016964
real	0m0.328s
user	0m0.081s
sys	0m0.246s

anel@AnelHP:~/GithubProjects/ParallelProgrammingAssignments/code$ time ./stream_opt1 
Minimum dt is 0.016964
real	0m0.325s
user	0m0.080s
sys	0m0.245s

anel@AnelHP:~/GithubProjects/ParallelProgrammingAssignments/code$ time ./stream_opt2
Minimum dt is 0.016964
real	0m0.328s
user	0m0.075s
sys	0m0.253s

anel@AnelHP:~/GithubProjects/ParallelProgrammingAssignments/code$ time ./stream_opt3
Minimum dt is 0.016964
real	0m0.296s
user	0m0.042s
sys	0m0.253s

```
Where the only interesting part is the "real" time, because it shows the actual execution time from start to finish which leaves me with:

`stream_base : real	0m0.328s`

`stream_opt1 : real	0m0.325s`

`stream_opt2 : real	0m0.328s`

`stream_opt3 (with flags) : real	0m0.296s`

Another tool i used was operf, this tool will show me the instruction in my code and how much time got spent in each part of the code (in percentages):

operf report for `stream_base`:
<img width="1737" height="1047" alt="image" src="https://github.com/user-attachments/assets/b37cde23-fffc-4c97-9b44-f2a6a77823e8" />


operf report for `stream_opt1`:
<img width="1465" height="892" alt="image" src="https://github.com/user-attachments/assets/17c49ed7-1ec5-4ad3-9baa-1cc07b52956d" />


operf report for `stream_opt2`:
<img width="1470" height="933" alt="image" src="https://github.com/user-attachments/assets/786175c6-2f22-48d0-81f7-9a539884ba3b" />


operf report for `stream_opt3`:
<img width="1483" height="995" alt="image" src="https://github.com/user-attachments/assets/4f10a1dd-1488-479e-90b5-25ad427e187e" />


-----
### Questions

<h2>Is it fully vectorized?</h2>

The only fully vectorized one is `stream_opt3` (with additional flags).
Why are the rest not?

There are 2 main issues the line: `if (celltype[ic] == REAL_CELL)` and the `sqrt()` function.
In the base stream both leads to not being able to vectorize, the compiler does not know how to branch in the vector and the sqrt function is considered unsafe.

In the other streams the `#pragma` does solve the first issue regarding the if statement and branching, but still the sqrt function blocks the vectorization.
I tried and added the flags to the other optimizations as well, and it is successfull all were fully vectorized.




-----

<h2>What vector length instructions were used? </h2>

In each case where there was a successfull vectorization the compiler told us that the vector size is 32 Bytes.

-----

<h2>Which of the runs is the best?</h2>

The best run is the `stream_opt3` with flags, why? Because it is the only fully vectorized one and we can see by the execution time that it is the fastest one.




