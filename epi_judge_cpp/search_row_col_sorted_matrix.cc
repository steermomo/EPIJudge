#include <vector>

#include "test_framework/generic_test.h"
using std::vector;

bool MatrixSearch(const vector<vector<int>>& A, int x) {
  // TODO - you fill in here.
  if (A.empty()) {
      return false;
  }
  int row = 0, max_col = A[0].size() - 1;
  while (row < A.size()) {
      for (int col = max_col; col >= 0; --col) {
          if (A[row][col] == x) {
              return true;
          }
          if (x > A[row][col]) {
              break;
          }
          if (x < A[row][col]) {
              max_col = col - 1;
          }
      }
      ++row;
  }
  return false;
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"A", "x"};
  return GenericTestMain(args, "search_row_col_sorted_matrix.cc",
                         "search_row_col_sorted_matrix.tsv", &MatrixSearch,
                         DefaultComparator{}, param_names);
}
