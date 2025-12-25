# ParallelProgrammingAssignments



<img width="1188" height="657" alt="Screenshot from 2025-12-25 13-10-39" src="https://github.com/user-attachments/assets/58681b89-c684-4ec7-ba6c-0f0680351c5b" />

Version 1 – Serial I/O (Baseline)
Only rank 0 reads the entire CSV file and distributes the data to other processes using MPI_Scatter. All reading and writing are done by a single process, which creates a major bottleneck. This version is mainly used as a reference to show how poorly serial file I/O scales.





<img width="1188" height="657" alt="Screenshot from 2025-12-25 13-13-10" src="https://github.com/user-attachments/assets/b68c9242-d8a8-4729-b55b-b01223365903" />


Version 2 – Independent MPI-IO
Each process opens the input file independently and reads only its own portion of the data. Writing is done in parallel using MPI_File_write_at, where each process writes to a specific file offset. This removes the single-process bottleneck but still lacks coordination between processes, which can limit performance on some file systems.







<img width="1372" height="601" alt="image" src="https://github.com/user-attachments/assets/41516874-4489-4aea-9a29-a3b68b4d4c75" />


Version 3 – Collective MPI-IO with Hints
This version builds on Version 2 by using collective MPI-IO (MPI_File_write_all) and MPI hints to optimize performance. The MPI library coordinates all processes during writing, reducing contention and improving bandwidth. This approach is usually more efficient on parallel file systems, especially with many processes.








<img width="832" height="941" alt="Screenshot from 2025-12-25 13-14-08" src="https://github.com/user-attachments/assets/094e52cb-812f-4ea1-96c0-a8cc2bc63ec3" />


Version 4 – MPI-IO with Datatypes (Halo Cells)
Instead of file performance, this version focuses on data layout. MPI derived datatypes are used to write only the real data while automatically skipping halo (ghost) cells. This avoids manual copying and reflects a common pattern in scientific simulations, showing how MPI-IO can simplify complex memory-to-file mappings.
