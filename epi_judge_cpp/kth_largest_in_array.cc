#include <vector>
#include <random>
#include "test_framework/generic_test.h"
using std::vector;

int PartitionAroundPivot(int left, int right, int pivot_idx, vector<int>* A_ptr) {
    vector<int> & A = *A_ptr;
    int pivot_value = A[pivot_idx];
    int new_pivot_idx = left;
    std::swap(A[right], A[pivot_idx]);
    for (int i = left; i < right; ++i) {
        if (A[i] > pivot_value) {
            std::swap(A[i], A[new_pivot_idx++]);
        }
    }
    std::swap(A[right], A[new_pivot_idx]); // swap pivot back
    return new_pivot_idx;
}

// The numbering starts from one, i.e., if A = [3, 1, -1, 2] then
// FindKthLargest(1, A) returns 3, FindKthLargest(2, A) returns 2,
// FindKthLargest(3, A) returns 1, and FindKthLargest(4, A) returns -1.
int FindKthLargest(int k, vector<int>* A_ptr) {
  // TODO - you fill in here.
  vector<int> & A = *A_ptr;
  int left = 0, right = A.size() - 1;
  std::default_random_engine gen((std::random_device())());
  while (left <= right) {
      int pivot_idx = std::uniform_int_distribution<int>{left, right}(gen);
      int new_pivot_idx = PartitionAroundPivot(left, right, pivot_idx, &A);
      if (new_pivot_idx == k - 1) {
          return A[new_pivot_idx];
      } else if (new_pivot_idx  < k - 1) {
          left = new_pivot_idx + 1;
      } else {
          right = new_pivot_idx - 1;
      }
  }
  return 0;
}
int FindKthLargestWrapper(int k, vector<int>& A) {
  return FindKthLargest(k, &A);
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"k", "A"};
  return GenericTestMain(args, "kth_largest_in_array.cc",
                         "kth_largest_in_array.tsv", &FindKthLargestWrapper,
                         DefaultComparator{}, param_names);
}
