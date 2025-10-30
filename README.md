# Assignment 4
---


The task was to test a few ways of solving the global sum problem using different algorithms.

I took the code skeleton from this courses repository (branch week-5, `main.c`).
I replaced the header file from that repository with my own `"sums.h"` in which ive put the algorithms used for this problem.

I had to make a few adjustements to the `makefile` as well, as i did rename the header file and i had to add the `-lm` flag as the code failed to run because of `"pow"` and `"log"` functions not being recognized.
I took the algorithms from the books official repository (i took only the basic version of each).

After that i used a bit of code to make the programm test each algorithm separately and store the data into a `.txt` file.

<img width="913" height="764" alt="image" src="https://github.com/user-attachments/assets/24014c06-5bc8-469d-9e09-7234630fe4b7" />

However then i noticed that i had to make a google spreadsheet, so i took the `.txt` file and let an AI convert the data into `csv` format (just because its faster that way).

I loaded the csv into google spreadsheets on the following link:

https://docs.google.com/spreadsheets/d/1FGLAYzE_CMJckyyGykHNjt8AMigZR4G2Rok5Gzb-_9s/edit?gid=0#gid=0

On the sheet you will see the entire table containing all the data and 2 separate tables as well showing the runtime and the accuracy.
(The data is all the same i just made those tables for better readability)

---

### What the data Showcases:

* The most obvious this that is shown in the data is that the only algorithm that made mistakes is the basic Long Double sum one.

* Why is that? Because thats the only algorithm that just goes over the array of numbers and just sums it up sequentially without having any error "correction" (even if it is a long double that has more precision its still a hardware problem in essence because of bitwise operations)

* Kahan and Knuth are algorithms that use a correction variable hold the small rouded off part of each addition, then they add that back in the next loop, which prevents the errors.

* Pairwise sum this is a divide and conquer algorithm that avoid the problem rather than fixing it. It sums the numbers in paris so instead of `(A+B+C+D)` it does `(A+B) + (C+D)` this way ensures that it adds numbers of similar size which significantly reduces the error rate.

---

### How the Global sum problem affects parallelization:

The main problem here is the problem of Associativity. In math `(a+b) + c` is the same as `a+(b+c)`, but in computing this will not always be the case because of bitwise operations and hardware. While in normal serial code summing up an array is always `arr[0] + arr[1] + ... arr[n]` in parallel code this will be done by multiple devices/processors/threads and the output can be different making our final output non-deterministic (for same input we get different output).
