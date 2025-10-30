#define _POSIX_C_SOURCE 199309L

#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <time.h>
#include <sys/time.h>
#include "sums.h"

#define ORDERS_OF_MAGNITUDE 1.0e9
#define RESULTS_FILENAME "sum_results.txt"


void cpu_timer_start(struct timespec *tstart_cpu) {
   clock_gettime(CLOCK_MONOTONIC, tstart_cpu);
}

double cpu_timer_stop(struct timespec tstart_cpu) {
   struct timespec tstop_cpu, tresult;
   clock_gettime(CLOCK_MONOTONIC, &tstop_cpu);

   tresult.tv_sec = tstop_cpu.tv_sec - tstart_cpu.tv_sec;
   tresult.tv_nsec = tstop_cpu.tv_nsec - tstart_cpu.tv_nsec;

   return (double)tresult.tv_sec + (double)tresult.tv_nsec * 1.0e-9;
}


void print_sum_results(FILE *fp, const char *sum_name, double accurate_sum, double test_sum, double cpu_time)
{
   double diff = test_sum - accurate_sum;
   double rel_diff = (accurate_sum != 0.0) ? (diff / accurate_sum) : 0.0;

   fprintf(fp, "  %-13s | %-17.16lg | %10.4lg | %10.4lg | %lf\n",
          sum_name,
          test_sum,
          diff,
          rel_diff,
          cpu_time);
}



int main(int argc, char *argv[])
{
   FILE *results_file = fopen(RESULTS_FILENAME, "w");
   if (results_file == NULL) {
      perror("Error: Could not open results file for writing");
      return 1;
   }

   printf("========================================\n");
   printf("Starting summation tests...\n");
   printf("Results will be written to: %s\n", RESULTS_FILENAME);
   printf("========================================\n\n");
   
   fprintf(results_file, "========================================\n");
   fprintf(results_file, " Floating-Point Summation Test Results\n");
   fprintf(results_file, "========================================\n\n");

   /*
    * Test with different array sizes - powers of 2 from 2^10 to 2^27
    */
   for (int pow_of_two = 10; pow_of_two <= 27; pow_of_two++) {
      long ncells = (long)pow(2.0, (double)pow_of_two);
      long ncellsdiv2 = ncells / 2;

      printf(" > Testing 2^%d = %ld elements...\n", pow_of_two, ncells);

      fprintf(results_file, "========================================\n");
      fprintf(results_file, "TESTING WITH 2^%d = %ld elements\n", pow_of_two, ncells);
      fprintf(results_file, "========================================\n");

      double high_value = 1.0e-1;
      double low_value  = 1.0e-1 / ORDERS_OF_MAGNITUDE;

      double accurate_sum = (double)ncellsdiv2 * high_value +
                            (double)ncellsdiv2 * low_value;

      double *energy = (double *)malloc(ncells * sizeof(double));

      if (energy == NULL) {
         fprintf(stderr, "Error: Failed to allocate memory for %ld elements\n", ncells);
         fclose(results_file); 
         return 1;
      }

      for (long i = 0; i < ncells; i++){
         energy[i] = (i < ncellsdiv2) ? high_value : low_value;
      }

      fprintf(results_file, "Expected accurate sum: %-17.16lg\n\n", accurate_sum);
      
      fprintf(results_file, "  Method        | Test Sum            | Difference | Rel. Diff  | Runtime (s)\n");
      fprintf(results_file, "  --------------|-------------------|------------|------------|-------------\n");

      double test_sum;
      struct timespec cpu_timer;
      double cpu_time;
   
        // --- KAHAN SUM ---
        cpu_timer_start(&cpu_timer);
        test_sum = do_kahan_sum(energy, ncells);
        cpu_time = cpu_timer_stop(cpu_timer);
        print_sum_results(results_file, "Kahan", accurate_sum, test_sum, cpu_time);

        // --- KNUTH SUM ---
        cpu_timer_start(&cpu_timer);
        test_sum = do_knuth_sum(energy, ncells);
        cpu_time = cpu_timer_stop(cpu_timer);
        print_sum_results(results_file, "Knuth", accurate_sum, test_sum, cpu_time);

        // --- PAIRWISE SUM ---
        cpu_timer_start(&cpu_timer);
        test_sum = do_pair_sum(energy, ncells);
        cpu_time = cpu_timer_stop(cpu_timer);
        print_sum_results(results_file, "Pairwise", accurate_sum, test_sum, cpu_time);

        // --- LONG DOUBLE SUM ---
        cpu_timer_start(&cpu_timer);
        test_sum = do_ldsum(energy, ncells);
        cpu_time = cpu_timer_stop(cpu_timer);
        print_sum_results(results_file, "Long Double", accurate_sum, test_sum, cpu_time);

      fprintf(results_file, "\n\n"); 

      free(energy);
   }

   printf("\n========================================\n");
   printf("All tests complete!\n");
   printf("========================================\n");

   fprintf(results_file, "========================================\n");
   fprintf(results_file, "All tests complete!\n");
   fprintf(results_file, "========================================\n");

   fclose(results_file); 
   return 0;
}