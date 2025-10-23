# Assignment 3: Memory Allocation Timer


This program is designed to measure the time it takes to allocate, write to, and deallocate memory. 
Its using an **Array of Structures of Arrays (AoSoA)**/

The program uses a **Structure of Arrays (SoA)** to store pixel data. 
This structure contains separate arrays for the Red, Green, and Blue color values.

It creates a large **Array of Structures of Arrays (AoSoA)**. The total size (`num_blocks`) is calculated based on variables defined in the `Makefile`.

Allocates memory for the AoSoA.
Writes random data into all arrays.
Calculates the total time taken for allocation and writing.
Frees the allocated memory.


The program outputs its results to a `.csv` file, logging the time taken for different configurations. The columns are:


### Example Output (`N = 1K`)

```csv
N, V, Time (ms)
1000, 2, 8e-05
1000, 4, 9e-05
1000, 8, 8e-05
1000, 16, 8e-05
1000, 32, 8e-05
1000, 64, 8.1e-05
1000, 128, 8e-05
1000, 256, 8e-05
```


### SpreadSheet
After running the program for each of the tests (1K, 10K, 100K, 1M, and 10M) the data collected and formatted into a table looks like the following:
<p align="center">
  <img width="928" height="476" alt="image" src="https://github.com/user-attachments/assets/bd64c402-5c3e-4a59-ba9b-4d48d38f78f3" />
</p>

It is clearly visible that for more data items the time it takes increases as well.

And if the data is converted into a Chart it looks like this:
<p align="center">
  <img width="782" height="516" alt="image" src="https://github.com/user-attachments/assets/46ddfd58-eedd-45bf-91e0-19a94d85ce51" /> <br />
  Chart with all the values
</p>

### Additional
<p align="center">
<img width="1518" height="577" alt="image" src="https://github.com/user-attachments/assets/545739ce-e0b1-496f-8475-dab7fda897de" />
Charts for each test

</p>






