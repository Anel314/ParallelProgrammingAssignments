VALGRIND ON THE SOURCE FILE:
```bash 
anel@AnelHP:~/GithubProjects/ParallelProgrammingAssignments/Assignment1$ make valgrind
    gcc -Wall -Wextra -g -std=c99 -o main main.c
    main.c: In function ‘main’:
    main.c:6:42: warning: ‘ipos’ may be used uninitialized [-Wmaybe-uninitialized]
        6 |   for (int i = 0; i<=10; i++){ iarray[i] = ipos; }
        |                                ~~~~~~~~~~^~~~~~
    main.c:3:7: note: ‘ipos’ was declared here
        3 |   int ipos, ival;
        |       ^~~~
    valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes ./main
    ==17670== Memcheck, a memory error detector
    ==17670== Copyright (C) 2002-2022, and GNU GPL'd, by Julian Seward et al.
    ==17670== Using Valgrind-3.22.0 and LibVEX; rerun with -h for copyright info
    ==17670== Command: ./main
    ==17670== 
    ==17670== Invalid write of size 4
    ==17670==    at 0x1091C6: main (main.c:6)
    ==17670==  Address 0x4a7f068 is 0 bytes after a block of size 40 alloc'd
    ==17670==    at 0x4846828: malloc (in /usr/libexec/valgrind/vgpreload_memcheck-amd64-linux.so)
    ==17670==    by 0x109185: main (main.c:4)
    ==17670== 
    ==17670== Conditional jump or move depends on uninitialised value(s)
    ==17670==    at 0x1091F4: main (main.c:8)
    ==17670==  Uninitialised value was created by a stack allocation
    ==17670==    at 0x109169: main (main.c:2)
    ==17670== 
    ==17670== Invalid read of size 4
    ==17670==    at 0x1091EF: main (main.c:8)
    ==17670==  Address 0x4a7f068 is 0 bytes after a block of size 40 alloc'd
    ==17670==    at 0x4846828: malloc (in /usr/libexec/valgrind/vgpreload_memcheck-amd64-linux.so)
    ==17670==    by 0x109185: main (main.c:4)
    ==17670== 
    ==17670== 
    ==17670== HEAP SUMMARY:
    ==17670==     in use at exit: 40 bytes in 1 blocks
    ==17670==   total heap usage: 1 allocs, 0 frees, 40 bytes allocated
    ==17670== 
    ==17670== 40 bytes in 1 blocks are definitely lost in loss record 1 of 1
    ==17670==    at 0x4846828: malloc (in /usr/libexec/valgrind/vgpreload_memcheck-amd64-linux.so)
    ==17670==    by 0x109185: main (main.c:4)
    ==17670== 
    ==17670== LEAK SUMMARY:
    ==17670==    definitely lost: 40 bytes in 1 blocks
    ==17670==    indirectly lost: 0 bytes in 0 blocks
    ==17670==      possibly lost: 0 bytes in 0 blocks
    ==17670==    still reachable: 0 bytes in 0 blocks
    ==17670==         suppressed: 0 bytes in 0 blocks
    ==17670== 
    ==17670== For lists of detected and suppressed errors, rerun with: -s
    ==17670== ERROR SUMMARY: 14 errors from 4 contexts (suppressed: 0 from 0)

```





THIS OUTPUT TELLS US:
[#PROBLEM 1] - "ipos" and "ival" were declared but used uninitialized
[#PROBLEM 2] - The for loops have the condition "i<=10", but our array is at size 10 which means we access memory locations that are not allocated for the array
[#PROBLEM 3] - "iarray" was never freed from memory which resulted in a memory leak



The source code is in "main.c"
The fixed code (with explanation) is in "fixedMain.C"





The valgrind output after fixing:
```bash
anel@AnelHP:~/GithubProjects/ParallelProgrammingAssignments/Assignment1$ make valgrind
gcc -Wall -Wextra -g -std=c99 -o main main.c
valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes ./main
==18342== Memcheck, a memory error detector
==18342== Copyright (C) 2002-2022, and GNU GPL'd, by Julian Seward et al.
==18342== Using Valgrind-3.22.0 and LibVEX; rerun with -h for copyright info
==18342== Command: ./main
==18342== 
==18342== 
==18342== HEAP SUMMARY:
==18342==     in use at exit: 0 bytes in 0 blocks
==18342==   total heap usage: 1 allocs, 1 frees, 40 bytes allocated
==18342== 
==18342== All heap blocks were freed -- no leaks are possible
==18342== 
==18342== For lists of detected and suppressed errors, rerun with: -s
==18342== ERROR SUMMARY: 0 errors from 0 contexts (suppressed: 0 from 0)

```

while doing it i was fixing main.c thats why valgrind buit that file instead of fixedMain.c