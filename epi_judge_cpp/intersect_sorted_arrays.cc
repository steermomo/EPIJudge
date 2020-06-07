#include <vector>

#include "test_framework/generic_test.h"
using std::vector;

vector<int> IntersectTwoSortedArrays(const vector<int>& A,
                                     const vector<int>& B) {
  // TODO - you fill in here.
  vector<int> ret;
  int a_st = 0, b_st = 0;
  while (a_st < A.size() && b_st < B.size()) {
      if (A[a_st] == B[b_st] && (ret.empty() || ret.back() != A[a_st])) {
          ret.emplace_back(A[a_st]);
          ++a_st, ++b_st;
      } else if (A[a_st] < B[b_st]) {
          ++a_st;
      } else {
          ++b_st;
      }
  }
  return ret;
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"A", "B"};
  return GenericTestMain(
      args, "intersect_sorted_arrays.cc", "intersect_sorted_arrays.tsv",
      &IntersectTwoSortedArrays, DefaultComparator{}, param_names);
}
