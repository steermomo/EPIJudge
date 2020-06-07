#include <vector>

#include "test_framework/generic_test.h"
using std::vector;

int LongestContainedRange(const vector<int>& A) {
  // TODO - you fill in here.
  std::unordered_set<int> filter(A.begin(), A.end());
  int ret = 0;
  while (!filter.empty()) {
      int c_val = *filter.begin();
      filter.erase(c_val);
      int c_length = 1, bias = 1;
      while(filter.count(c_val+bias)) {
          filter.erase(c_val + bias); // 剔除已经访问过的元素
          ++bias;
          ++c_length;
      }
      bias = -1;
      while (filter.count(c_val + bias)) {
          filter.erase(c_val + bias);
          --bias;
          ++c_length;
      }
      ret = std::max(ret, c_length);
  }
  return ret;
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"A"};
  return GenericTestMain(
      args, "longest_contained_interval.cc", "longest_contained_interval.tsv",
      &LongestContainedRange, DefaultComparator{}, param_names);
}
