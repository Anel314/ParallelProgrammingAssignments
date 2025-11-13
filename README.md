# ParallelProgrammingAssignments

<img width="914" height="1691" alt="image" src="https://github.com/user-attachments/assets/744ecb9b-9d13-4b88-8174-24e2c6b95fa0" />


This code seems to calculate heat diffusion on a grid, where the center starts "hot" and everything else is cold.
The code runs a loop for 10.000 iterations each calculating the diffusion in that "step".

Each version of the code uses multiple threads to execute, the differences are in the `#pragma` notations.

### Questions

<h3>How many threads your CPU used to execute the code? </h3>
In my case the code used 12 threads, thats also the exact amount of threads my cpu has.
<img width="471" height="402" alt="image" src="https://github.com/user-attachments/assets/fa712a83-cde3-4f1d-898b-647ae5df2ca2" />


<h3>What are the parts of the code that were improved? What strategies were used to improve the code? </h3>
The main strategies that were used are different pragma annotations. 
They were primarily used to either create threads or split tasks across them.
Also there are cases of explicit barrier creations. These barriers serve as points in the code where each thread has to wait for the rest to finish. (Like synchronize in JAVA)

<h3>What is the difference between explicit and implicit barriers inside the code and did they exist inside any of these examples? What do they actually mean? </h3>

Explicit barriers are those that were explicitly created with pragmas such as  `#pragma omp barrier`, but they can also be explicitly removed with 
pragmas like `#pragma omp for nowait`.

Implicit barriers are those that are created without explicitly mentioning them.
`#pragma omp for` is a pragma that splits the iteration of a loop over already created threads and adds a barrier at the end of the loop for threads to synchronize.


### Pragma differences

./stencil_opt2 this version uses `#pragma omp parallel` and `#pragma omp parallel for`.
`#pragma omp parallel` this "creates" threads to run a piece of code in parallel.
`#pragma omp parallel for` this splits a loops iterations into the threads, meaning multiple threads are used in parallel to execute 1 loop.

./stencil_opt4 this version uses `#pragma omp parallel` and `#pragma omp parallel for` and `#pragma omp for nowait` and `#pragma omp for`.
`#pragma omp parallel` this "creates" threads to run a piece of code in parallel.
`#pragma omp parallel for` this splits a loops iterations into the threads, meaning multiple threads are used in parallel to execute 1 loop.
`#pragma omp for nowait`  this is the same as `#pragma omp for` but the `nowait` keyword removes the barrier at the end of the loop.
`#pragma omp for` this is used to divide the execution of a loop into already existing threads, it also has a  barrier at the end of it.

./stencil_opt6 this version uses `#pragma omp parallel` and `#pragma omp barrier`.
`#pragma omp parallel` this "creates" threads to run a piece of code in parallel.
`#pragma omp barrier` this is used to synchronize the threads, it serves as a "barrier" for each thread. 

