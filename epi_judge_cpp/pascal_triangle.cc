#include <vector>

#include "test_framework/generic_test.h"
using std::vector;
vector<vector<int>> GeneratePascalTriangle(int num_rows) {
  // TODO - you fill in here.

  vector<vector<int>> ret = {{1}};
  if (num_rows == 0) {
      return {};
  }
  else if (num_rows == 1) {
      return ret;
  }
  for (int i = 1; i < num_rows; ++i) {
      vector<int> c_row;
      c_row.emplace_back(1);
      auto &last_row = ret[i-1];
      for (int j = 0; j < last_row.size() - 1; ++j) {
          c_row.push_back(last_row[j] + last_row[j+1]);
      }
      c_row.emplace_back(1);
      ret.emplace_back(c_row);
  }
  return ret;
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"num_rows"};
  return GenericTestMain(args, "pascal_triangle.cc", "pascal_triangle.tsv",
                         &GeneratePascalTriangle, DefaultComparator{},
                         param_names);
}
