# ParallelProgrammingAssignments


# OMP BabelStream
<img width="814" height="360" alt="image" src="https://github.com/user-attachments/assets/47d2c656-39fa-4989-99a4-f05ca0bb8bc8" />

The OpenMP version runs entirely on the CPU. The benchmark shows memory bandwidth for some vector operations (Copy, Mul, Add, Triad, Dot). 
These values represent what the CPU can achieve using parallelism across multiple cores. 
The performance is limited by CPU memory bandwidth and the number of hardware threads. 
My PC has a Ryzen 5 5500U CPU this cpu has a memory bandwidth of 51.2 GB/s.

# OPC BabelStream

<img width="808" height="384" alt="image" src="https://github.com/user-attachments/assets/0b2495f5-6e85-433c-b03a-155a75aeeb3b" />

BabelStream selected the OpenCL device: `cpu-haswell-AMD Ryzen 5 5500U with Radeon Graphics`

This means the OpenCL backend did not run on a dedicated GPU but instead used either the CPU OpenCL driver or the integrated graphics driver, which makes sense as my pc does not have a dedicated GPU. Which means that performance is similar to the OpenMP version.

# CUDA BabelStream
<img width="864" height="207" alt="image" src="https://github.com/user-attachments/assets/3e69c49c-bb1a-4bc1-94c1-adfd5ead994d" />

This benchmark failed to run entirely for me, because i have integrated AMD graphics.



# SSH CONNECTION TO LAB PC

<img width="874" height="582" alt="image" src="https://github.com/user-attachments/assets/5553c2b1-b3de-4942-bd25-e8260af7a581" />



# CUDA

<img width="848" height="534" alt="image" src="https://github.com/user-attachments/assets/37ed16a6-dcb3-4286-b533-f4bd363793a4" />


# OMP AND OCL

<img width="838" height="929" alt="image" src="https://github.com/user-attachments/assets/fa979075-4225-4cf9-bba3-ab45217946f5" />



The bandwidth is greater on the PC lab even if it has a dedicated GPU, that is most likely because multiple students have been running these tests at once.

