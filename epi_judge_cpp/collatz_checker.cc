#include <vector>

#include "test_framework/generic_test.h"
using std::vector;

bool TestCollatzConjecture(int n) {
  // TODO - you fill in here.
  std::unordered_set<long> table;
  for (int i = 3; i <= n; ++i) {
      long c_val = i;
      std::unordered_set<long> search_path;
      while (c_val >= i) {
          if (table.find(c_val) != table.end()) {
              // 当前序列已经存在过
              break;
          }
          if (search_path.find(c_val) != search_path.end()) {
              return false; // 序列进入循环， 证伪
          }
          search_path.insert(c_val);
          if (c_val % 2 == 0) {
              c_val /= 2;
          } else {
              c_val = c_val * 3 + 1;
          }
      }
      table.insert(search_path.begin(), search_path.end()); //更新搜索序列
  }
  return true;
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"n"};
  return GenericTestMain(args, "collatz_checker.cc", "collatz_checker.tsv",
                         &TestCollatzConjecture, DefaultComparator{},
                         param_names);
}
