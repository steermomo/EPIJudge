#include <vector>

#include "test_framework/generic_test.h"
using std::vector;

void MergeTwoSortedArrays(vector<int>& A, int m, const vector<int>& B, int n) {
  // TODO - you fill in here.
  int A_curr = m + n - 1, A_st = m - 1, B_st = n - 1;
  while (A_st >= 0 && B_st >= 0) {
      if (A[A_st] >= B[B_st]) {
          A[A_curr--] = A[A_st--];
      } else {
          A[A_curr--] = B[B_st--];
      }
  }
  while (B_st >= 0) {
      A[A_curr--] = B[B_st--];
  }
  return;
}
vector<int> MergeTwoSortedArraysWrapper(vector<int> A, int m,
                                        const vector<int>& B, int n) {
  MergeTwoSortedArrays(A, m, B, n);
  return A;
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"A", "m", "B", "n"};
  return GenericTestMain(
      args, "two_sorted_arrays_merge.cc", "two_sorted_arrays_merge.tsv",
      &MergeTwoSortedArraysWrapper, DefaultComparator{}, param_names);
}
