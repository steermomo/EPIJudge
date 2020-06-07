#include <vector>

#include "test_framework/generic_test.h"
using std::vector;

int SearchFirstOfK(const vector<int>& A, int k) {
  // TODO - you fill in here.
  int L = 0, U = A.size() - 1;
  while (L <= U) {
      int M = L + (U - L) / 2;
      if (A[M] == k && (M == 0 || A[M-1] != k)) {
          return M;
      }
      else if (A[M] < k) {
          L = M + 1;
      } else {
          U = M - 1;
      }
  }
  return -1;
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"A", "k"};
  return GenericTestMain(args, "search_first_key.cc", "search_first_key.tsv",
                         &SearchFirstOfK, DefaultComparator{}, param_names);
}
