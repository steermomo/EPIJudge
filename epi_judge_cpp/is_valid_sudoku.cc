#include <vector>

#include "test_framework/generic_test.h"
using std::vector;
// Check if a partially filled matrix has any conflicts.
bool IsValidSudoku(const vector<vector<int>>& partial_assignment) {
  // TODO - you fill in here.
  vector<std::unordered_set<int>> rows(9);
  vector<std::unordered_set<int>> cols(9);
  vector<std::unordered_set<int>> inner(9);
  for (int r_idx = 0; r_idx < 9; ++r_idx) {
      for (int c_idx = 0; c_idx < 9; ++c_idx) {
          int c_val = partial_assignment[r_idx][c_idx];
          if (c_val == 0) {
              continue;
          }

          auto &c_row = rows[r_idx];
          if (c_row.find(c_val) != c_row.end()) {
              return false;
          }
          else {
              c_row.insert(c_val);
          }

          auto &c_col = cols[c_idx];
          if (c_col.find(c_val) != c_col.end()) {
              return false;
          }
          else {
              c_col.insert(c_val);
          }

          int inner_idx = (r_idx / 3) * 3 + c_idx / 3;
          auto &c_inner = inner[inner_idx];
          if (c_inner.find(c_val) != c_inner.end()) {
              return false;
          }
          else {
              c_inner.insert(c_val);
          }
      }
  }
  return true;
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"partial_assignment"};
  return GenericTestMain(args, "is_valid_sudoku.cc", "is_valid_sudoku.tsv",
                         &IsValidSudoku, DefaultComparator{}, param_names);
}
