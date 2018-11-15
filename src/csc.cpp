/*
 *   CSC(Compressed Sparse Column) format for sparse matrix.
 *
 */

// N: columns of sparse matrix
// nz_vals: non-zero elements of sparse matrix
// x: source vector, it has N x 1 double elements
// y: destination vector, it has M x 1 doule elements
void csc(const int &N, double *nz_vals, int *row_index, int *column_start,
         double *x, double *y) {
  int i, j;
#ifdef CSC_OMP
#pragma omp parallel for default(shared) private(i, j, tmp)
#endif // CSC_OMP
  // loop over the columns of sparse matrix
  for (i = 0; i < N; ++i) {
#ifdef CSC_OMP
    // hint compiler to ignore vector dependencies
    #pragma IVDEP
#endif
    for (j = column_start[i]; j < column_start[i + 1]; ++j) {
      y[row_index[j]] += nz_vals[j] * x[i];
    }
  }
}
