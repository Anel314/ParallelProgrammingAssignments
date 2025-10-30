#ifndef SUMS_H
#define SUMS_H


double do_knuth_sum(double* restrict var, long ncells);
double do_kahan_sum(double* restrict var, long ncells);
double do_pair_sum(double* restrict var, long ncells);
long double do_ldsum(double* restrict var, long ncells);

#endif /* SUMS_H */