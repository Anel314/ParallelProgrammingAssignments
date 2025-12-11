# ParallelProgrammingAssignments

The Stream Triad benchmark is used to measure memory bandwidth and computational performance.


# CUDA 
<img width="418" height="1864" alt="image" src="https://github.com/user-attachments/assets/04663e6c-80a4-4969-bab4-a71b029d7b55" />

The CUDA Stream Triad fails because i run a system with an AMD gpu which is not compatible with NVIDIA’s CUDA platform. 
And that why the GPU kernel did not run, leaving the result array c filled with zeros. 
All iterations caused errors because the expected computation was never performed. 
The timing measurements for kernel execution and data transfer are zero because of it.

# OCL
<img width="1198" height="649" alt="image" src="https://github.com/user-attachments/assets/f20407a8-eeb6-4e4d-bd7f-c6fb2d403871" />

The code did compile correctly, even tho there are some warnings (deprecated funtions).
But again, because it failed to locate a GPU device the program crashed.

# OMP

<img width="1046" height="217" alt="image" src="https://github.com/user-attachments/assets/573eb053-dcfe-46eb-bb43-a88759f2c1a8" />

This is the first one that actually ran correctly on my device, this is because this code ran on the CPU.
It gave an output of `0.029362 msecs`, which is the mean execution time for the benchmark.

# openacc

<img width="1052" height="681" alt="image" src="https://github.com/user-attachments/assets/886f7763-f6cd-4ffa-95f1-14340e235e1c" />

So similar to the omp version, this one also ran on the CPU which is why it succeeded.
The code that is executed is the original C code, even with the compiler detecting OpenACC parallelism. Instead of offloading to a GPU, the `fopenacc` flags probably used vectorization or multi-core CPU parallelism to optimize the CPU-based loops. The compiler is just attempting to parallelize the standard C loops on the CPU cores it has access to because the code has no OpenACC directives. 



# Notice

On some of the makefiles for these StreamTriads there was the flag `-qthreaded` because my system did not find the correct compiler for it, it recommended to use `-qthreaded` instead, which allowed me to run them.

# LAB PC

<img width="687" height="656" alt="image" src="https://github.com/user-attachments/assets/20ea2035-3b4f-4af8-90bf-9f9dc2908919" />

What we can notice here:
why kern2 is the slowest, the work is being ofloaded to the gpu but the data overhead is huge, the data is not stored on the gpu which led to a significant performance decrease instead of increase, the next optimizations are there to resolve this issue.


The kern2 is using the `restring` keyword upon variable declaration, which signals to the compiler that there will be no overlap between those variables, which means that the compiler can parallelize this execution.

The kern3 is optimizing the data overhead, by creating the variables directly on the gpu, which led to significant performance increase. 


Same goes for the par programs, par4 is the most optimized by adding restrict on the variables and using `acc_malloc(...)` which allocates space for the variables on the gpu rather than on the cpu memory.






