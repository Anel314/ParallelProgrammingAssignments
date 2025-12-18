# ParallelProgrammingAssignments



# Ran without batch scheduler
<img width="768" height="208" alt="Screenshot from 2025-12-18 15-47-59" src="https://github.com/user-attachments/assets/00f3e5e2-f03b-4f68-8408-7b30feedbc7a" />

In this case i ran the compute.sh programm directly without using a batch scheduler, what happened, the programm executed immediately did not even wait for the 5 minutes that it said in the programm.
So the process was never manually scheduled instead it was just ran.

# sbatch compute.sh
<img width="1856" height="1075" alt="Screenshot from 2025-12-18 15-32-42" src="https://github.com/user-attachments/assets/3fbd1fa9-5f65-43c9-8515-ff635e8581fb" />

Here i ran the compute.sh programm with the batch scheduler.
Using sbatch i enque the process and it runs in the background, when its execution time is over, it creates a file named work_JOBID.out, where the output is stored.
The programm used all resources possible, as seen in the top command that all my threads are under stress.




# sbatch Overload.sh with 1 thread
<img width="1856" height="1075" alt="Screenshot from 2025-12-18 15-41-00" src="https://github.com/user-attachments/assets/421e22a4-1c60-4d0d-80de-1b11cc4c58b7" />

In this case i ran the Overload.sh programm using batch scheduler, this code puts the cpu under stress with the stress tool. It is possible to change the amount of threads within the code in the line `stress --cpu 1 --timeout 60s` in this case it was ran with 1 thread as seen on the top command, for 2minutes. Then after it finishes it stores the output in the overload_JOBID.out file.

# sbatch overload.sh with 4 threads
<img width="1856" height="1075" alt="Screenshot from 2025-12-18 15-39-54" src="https://github.com/user-attachments/assets/a22e9245-3672-4eac-87e6-a00bd4ebd4da" />

This is the same case as beofre the only difference is in the line `stress --cpu 4 --timeout 60s` here i specified 4 threads to be used but still about 7 were under stress, which has to something to do with cgroups not allowing me to control the resources entirely.

# Summary 

Batch schedulers are basically used the schedule the execution of a process, where it is also possible to sinal the processes, and give them their own runtime. In this assignment basically what i did was scheduling these programms with different threads, for some reason the command 
```bash
salloc --nodes=1 --ntasks=1 --cpus-per-task=4 --cpu-bind=cores
srun ./overload.sh
```
basically did nothing for me because after i run `srun ./compute.sh` the job would not finish for some reason, but what the command does is it allocated the ammount of threads that will be used for that specific job. 



